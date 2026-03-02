#!/usr/bin/env python3
"""
Lua Output Validator for Lex Compiler
Validates generated Lua syntax and structure without needing Lua runtime
"""

import re
import sys
from pathlib import Path
from dataclasses import dataclass
from typing import List, Optional

@dataclass
class ValidationError:
    line: int
    message: str
    severity: str  # 'error' or 'warning'

class LuaValidator:
    def __init__(self, source: str):
        self.source = source
        self.lines = source.split('\n')
        self.errors: List[ValidationError] = []
        self.tables_found = {}
        self.entries_found = {}
    
    def add_error(self, line: int, message: str, severity: str = 'error'):
        self.errors.append(ValidationError(line, message, severity))
    
    def validate(self) -> bool:
        """Run all validations"""
        self.check_tables_exist()
        self.check_syntax_basic()
        self.check_entries()
        self.check_braces_matched()
        
        return all(e.severity != 'error' for e in self.errors)
    
    def check_tables_exist(self):
        """Check that required tables are defined"""
        required_tables = ['Buildings', 'Units', 'Technologies', 'Eras', 'Resources']
        for table in required_tables:
            pattern = rf'^{table}\s*=\s*{table}\s*or\s*{{}}'
            found = any(re.match(pattern, line) for line in self.lines)
            if not found:
                self.add_error(0, f"Missing table definition: {table}")
            else:
                self.tables_found[table] = True
    
    def check_syntax_basic(self):
        """Basic syntax validation"""
        for i, line in enumerate(self.lines, 1):
            line_stripped = line.strip()
            
            # Skip empty lines and comments
            if not line_stripped or line_stripped.startswith('--'):
                continue
            
            # Check for common Lua syntax issues
            # Check string literals are properly closed
            if line_stripped.count('"') % 2 != 0 and '[[' not in line_stripped:
                # Could be in multiline string, check context
                if not any('[[' in l for l in self.lines[i-2:i]):
                    self.add_error(i, f"Unmatched double quote", 'warning')
            
            # Check for C-style syntax that's invalid in Lua
            if re.search(r'if\s*\(', line_stripped) and 'then' not in line_stripped:
                self.add_error(i, f"C-style if statement without 'then'")
            
            # Check for semicolons (valid but unusual in Lua)
            if line_stripped.endswith(';'):
                # Just a warning, semicolons are valid
                pass
    
    def check_braces_matched(self):
        """Check that braces are balanced"""
        brace_count = 0
        bracket_count = 0
        paren_count = 0
        in_string = False
        in_multiline_string = False
        
        for i, line in enumerate(self.lines, 1):
            # Skip comments
            if line.strip().startswith('--'):
                continue
            
            j = 0
            while j < len(line):
                c = line[j]
                
                # Handle multiline strings
                if j < len(line) - 1 and line[j:j+2] == '[[':
                    in_multiline_string = True
                    j += 2
                    continue
                if in_multiline_string and j < len(line) - 1 and line[j:j+2] == ']]':
                    in_multiline_string = False
                    j += 2
                    continue
                if in_multiline_string:
                    j += 1
                    continue
                
                # Handle regular strings
                if c == '"' and (j == 0 or line[j-1] != '\\'):
                    in_string = not in_string
                
                if not in_string:
                    if c == '{': brace_count += 1
                    elif c == '}': brace_count -= 1
                    elif c == '[': bracket_count += 1
                    elif c == ']': bracket_count -= 1
                    elif c == '(': paren_count += 1
                    elif c == ')': paren_count -= 1
                    
                    if brace_count < 0:
                        self.add_error(i, f"Unmatched closing brace")
                        brace_count = 0
                    if bracket_count < 0:
                        self.add_error(i, f"Unmatched closing bracket")
                        bracket_count = 0
                    if paren_count < 0:
                        self.add_error(i, f"Unmatched closing parenthesis")
                        paren_count = 0
                
                j += 1
        
        if brace_count != 0:
            self.add_error(len(self.lines), f"Unbalanced braces: {brace_count} unclosed")
        if bracket_count != 0:
            self.add_error(len(self.lines), f"Unbalanced brackets: {bracket_count} unclosed")
        if paren_count != 0:
            self.add_error(len(self.lines), f"Unbalanced parentheses: {paren_count} unclosed")
    
    def check_entries(self):
        """Check that entries are properly defined"""
        # Pattern: TableName.EntryName = {
        entry_pattern = r'^(\w+)\.(\w+)\s*=\s*\{'
        
        for i, line in enumerate(self.lines, 1):
            match = re.match(entry_pattern, line.strip())
            if match:
                table_name, entry_name = match.groups()
                self.entries_found[f"{table_name}.{entry_name}"] = i
                
                # Check that table was declared
                if table_name not in self.tables_found:
                    self.add_error(i, f"Entry for undeclared table: {table_name}")
    
    def print_results(self):
        """Print validation results"""
        print("\n" + "=" * 60)
        print("Lua Validation Results")
        print("=" * 60)
        
        print(f"\nTables found: {len(self.tables_found)}")
        for t in sorted(self.tables_found.keys()):
            print(f"  - {t}")
        
        print(f"\nEntries found: {len(self.entries_found)}")
        for e in sorted(self.entries_found.keys())[:10]:  # Show first 10
            print(f"  - {e}")
        if len(self.entries_found) > 10:
            print(f"  ... and {len(self.entries_found) - 10} more")
        
        if self.errors:
            print(f"\nIssues: {len(self.errors)}")
            for e in sorted(self.errors, key=lambda x: x.line):
                sev = f"[{e.severity.upper()}]"
                print(f"  Line {e.line}: {sev} {e.message}")
        else:
            print("\nNo issues found!")
        
        return len([e for e in self.errors if e.severity == 'error']) == 0


def validate_file(filepath: str) -> bool:
    """Validate a Lua file"""
    path = Path(filepath)
    if not path.exists():
        print(f"Error: File not found: {filepath}")
        return False
    
    print(f"Validating: {filepath}")
    source = path.read_text(encoding='utf-8')
    
    validator = LuaValidator(source)
    validator.validate()
    success = validator.print_results()
    
    return success


if __name__ == '__main__':
    if len(sys.argv) < 2:
        print("Usage: python lua_validator.py <file.lua>")
        print("\nValidates Lex-generated Lua output")
        sys.exit(1)
    
    success = validate_file(sys.argv[1])
    sys.exit(0 if success else 1)

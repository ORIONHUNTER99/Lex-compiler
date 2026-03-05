#!/usr/bin/env pwsh
# Lex Compiler Installer for Windows
# Usage: irm https://raw.githubusercontent.com/David-Imperium/Lex-compiler/main/install.ps1 | iex

param(
    [string]$Version = "latest",
    [string]$InstallDir = ""
)

$ErrorActionPreference = "Stop"

# Colors
function Write-Info { Write-Host "$args" -ForegroundColor Cyan }
function Write-Success { Write-Host "✓ $args" -ForegroundColor Green }
function Write-Error { Write-Host "✗ $args" -ForegroundColor Red }

# Detect architecture
$Arch = if ([Environment]::Is64BitOperatingSystem) { "x64" } else { "x86" }

# Set install directory
if (-not $InstallDir) {
    $InstallDir = if ($IsWindows -or $env:OS) {
        "$env:LOCALAPPDATA\Lex"
    } else {
        "$HOME/.local/bin"
    }
}

Write-Info "Lex Compiler Installer"
Write-Info "====================="
Write-Info ""

# Get latest version
if ($Version -eq "latest") {
    Write-Info "Fetching latest version..."
    try {
        $LatestRelease = Invoke-RestMethod -Uri "https://api.github.com/repos/David-Imperium/Lex-compiler/releases/latest"
        $Version = $LatestRelease.tag_name
        Write-Success "Latest version: $Version"
    } catch {
        Write-Error "Failed to fetch latest version. Using v0.4.0"
        $Version = "v0.4.0"
    }
}

# Download URL
$DownloadUrl = "https://github.com/David-Imperium/Lex-compiler/releases/download/$Version/lexc-windows-$Arch.zip"
$TempDir = [System.IO.Path]::GetTempPath()
$ZipFile = "$TempDir\lexc-$Version.zip"

Write-Info "Downloading Lex $Version for Windows $Arch..."
Write-Info "URL: $DownloadUrl"

try {
    Invoke-WebRequest -Uri $DownloadUrl -OutFile $ZipFile -UseBasicParsing
    Write-Success "Download complete"
} catch {
    Write-Error "Download failed: $_"
    Write-Info ""
    Write-Info "The binary release may not be available yet."
    Write-Info "Please build from source:"
    Write-Info "  git clone https://github.com/David-Imperium/Lex-compiler.git"
    Write-Info "  cd Lex-compiler"
    Write-Info "  cmake -B build -S ."
    Write-Info "  cmake --build build --config Release"
    exit 1
}

# Extract
Write-Info "Extracting..."
$ExtractDir = "$TempDir\lexc-extract"
if (Test-Path $ExtractDir) { Remove-Item $ExtractDir -Recurse -Force }
Expand-Archive -Path $ZipFile -DestinationPath $ExtractDir

# Create install directory
if (-not (Test-Path $InstallDir)) {
    New-Item -ItemType Directory -Path $InstallDir -Force | Out-Null
}

# Copy binary
$BinaryPath = "$ExtractDir\lexc.exe"
if (Test-Path $BinaryPath) {
    Copy-Item $BinaryPath -Destination $InstallDir -Force
    Write-Success "Installed to $InstallDir\lexc.exe"
} else {
    Write-Error "Binary not found in archive"
    exit 1
}

# Add to PATH
$CurrentPath = [Environment]::GetEnvironmentVariable("Path", "User")
if ($CurrentPath -notlike "*$InstallDir*") {
    [Environment]::SetEnvironmentVariable("Path", "$CurrentPath;$InstallDir", "User")
    Write-Success "Added to PATH"
    Write-Info "Restart your terminal or run: `$env:Path += ';$InstallDir'"
} else {
    Write-Info "Already in PATH"
}

# Cleanup
Remove-Item $ZipFile -Force
Remove-Item $ExtractDir -Recurse -Force

Write-Info ""
Write-Success "Installation complete!"
Write-Info ""
Write-Info "Run 'lexc --help' to get started."
Write-Info "Documentation: https://github.com/David-Imperium/Lex-compiler"

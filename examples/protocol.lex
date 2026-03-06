// =============================================================================
// Aurelius RPC Protocol Definition
// =============================================================================
// This file defines the JSON-RPC protocol between Go UI and Python backend.
// Compile with: lexc protocol.lex -t rpc --types method,struct --no-validate
// NOTE: 'id', 'type', 'name' are reserved keywords in Lex - use alternatives
// =============================================================================

// =============================================================================
// Base Types (fictitious definitions to satisfy Lex references)
// =============================================================================

resource string { label: "string" }
resource int { label: "int" }
resource bool { label: "bool" }
resource float { label: "float" }

// =============================================================================
// Session Types
// =============================================================================

struct SessionInfo {
    session_identifier: string
    session_name: string
    created_at: int
    cwd: string
    message_count: int
}

struct SessionList {
    sessions: SessionInfo
}

// =============================================================================
// Message Types
// =============================================================================

struct Message {
    message_identifier: string
    role: string
    content: string
    timestamp: int
    tool_calls: ToolCall
    thinking: string
}

struct ToolCall {
    tool_identifier: string
    tool_name: string
    arguments: string
    result: string
}

struct Todo {
    todo_identifier: string
    content: string
    status: string
}

// =============================================================================
// Chat Types
// =============================================================================

struct SendMessageResult {
    message_identifier: string
    status: string
}

struct ChatToken {
    message_identifier: string
    content: string
}

struct UsageInfo {
    prompt_tokens: int
    completion_tokens: int
    total_tokens: int
}

// =============================================================================
// File Types
// =============================================================================

struct FileContent {
    content: string
    size: int
    modified: int
}

struct FileInfo {
    path: string
    file_type: string
    size: int
    modified: int
}

struct FileList {
    files: FileInfo
}

// =============================================================================
// Attachment Types
// =============================================================================

struct Attachment {
    content_type: string
    path: string
    data: string
}

// =============================================================================
// LSP Types
// =============================================================================

struct Diagnostic {
    range_start_line: int
    range_start_char: int
    range_end_line: int
    range_end_char: int
    severity: int
    message: string
    source: string
}

struct DiagnosticsResult {
    diagnostics: Diagnostic
}

// =============================================================================
// MCP Types
// =============================================================================

struct MCPServer {
    server_name: string
    status: string
    tools: int
    resources: int
}

struct MCPTool {
    tool_name: string
    description: string
    input_schema: string
}

// =============================================================================
// Model Types
// =============================================================================

struct ModelInfo {
    model_identifier: string
    model_name: string
    provider: string
    context_window: int
    supports_vision: bool
}

struct ModelList {
    models: ModelInfo
}

// =============================================================================
// Settings Types
// =============================================================================

struct Settings {
    model: string
    provider: string
    temperature: float
    max_tokens: int
    thinking: bool
    context_window: int
}

// =============================================================================
// Methods
// =============================================================================

method session_new {
    input: SessionNewRequest
    output: SessionInfo
}

struct SessionNewRequest {
    session_name: string
    cwd: string
}

method session_list {
    input: Empty
    output: SessionList
}

method session_load {
    input: SessionLoadRequest
    output: SessionLoadResult
}

struct SessionLoadRequest {
    session_identifier: string
}

struct SessionLoadResult {
    session_identifier: string
    messages: Message
    todos: Todo
}

method session_delete {
    input: SessionDeleteRequest
    output: SuccessResult
}

struct SessionDeleteRequest {
    session_identifier: string
}

// Chat methods

method chat_sendMessage {
    input: ChatSendMessageRequest
    output: SendMessageResult
}

struct ChatSendMessageRequest {
    session_identifier: string
    content: string
    attachments: Attachment
}

// File methods

method file_read {
    input: FileReadRequest
    output: FileContent
}

struct FileReadRequest {
    path: string
    encoding: string
}

method file_write {
    input: FileWriteRequest
    output: WriteResult
}

struct FileWriteRequest {
    path: string
    content: string
}

struct WriteResult {
    success: bool
    size: int
}

// Models method

method models_list {
    input: Empty
    output: ModelList
}

// Settings methods

method settings_get {
    input: Empty
    output: Settings
}

method settings_set {
    input: SettingsSetRequest
    output: SuccessResult
}

struct SettingsSetRequest {
    key: string
    value: string
}

// =============================================================================
// Common Types
// =============================================================================

struct Empty {
    dummy: string
}

struct SuccessResult {
    success: bool
}

struct Error {
    code: string
    message: string
}

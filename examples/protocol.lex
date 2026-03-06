// =============================================================================
// Aurelius RPC Protocol Definition
// =============================================================================
// This file defines the JSON-RPC protocol between Go UI and Python backend.
// Compile with: lexc protocol.lex -t rpc --types method,struct
// =============================================================================

// =============================================================================
// Common Types
// =============================================================================

struct Session {
    id: string
    name: string
    created_at: string
    cwd: string
}

struct Message {
    id: string
    role: string
    content: string
    timestamp: string
}

struct Model {
    id: string
    name: string
    provider: string
    context_window: int
    supports_vision: bool
}

struct Attachment {
    type: string
    data: string
    mime_type: string
}

struct ResponseContent {
    type: string
    text: string
}

struct AgentResult {
    response: ResponseContent[]
    session_id: string
}

struct File {
    path: string
    name: string
    is_dir: bool
    size: int
    modified: int
}

struct LSPDiagnostics {
    uri: string
    diagnostics: Diagnostic[]
}

struct Diagnostic {
    range: Range
    severity: int
    message: string
    source: string
}

struct Range {
    start: Position
    end: Position
}

struct Position {
    line: int
    character: int
}

// =============================================================================
// Session Methods
// =============================================================================

method session/new {
    input: SessionNewRequest
    output: Session
}

struct SessionNewRequest {
    name: string
    cwd: string
}

method session/list {
    input: Empty
    output: SessionListResult
}

struct SessionListResult {
    sessions: Session[]
}

method session/load {
    input: SessionLoadRequest
    output: Session
}

struct SessionLoadRequest {
    session_id: string
}

method session/delete {
    input: SessionDeleteRequest
    output: SuccessResult
}

struct SessionDeleteRequest {
    session_id: string
}

// =============================================================================
// Chat Methods
// =============================================================================

method chat/sendMessage {
    input: ChatSendMessageRequest
    output: AgentResult
}

struct ChatSendMessageRequest {
    session_id: string
    content: string
    attachments: Attachment[]
}

method chat/abort {
    input: ChatAbortRequest
    output: SuccessResult
}

struct ChatAbortRequest {
    message_id: string
}

method chat/editMessage {
    input: ChatEditMessageRequest
    output: SuccessResult
}

struct ChatEditMessageRequest {
    message_id: string
    content: string
}

// =============================================================================
// File Methods
// =============================================================================

method file/read {
    input: FileReadRequest
    output: FileReadResult
}

struct FileReadRequest {
    path: string
    encoding: string
}

struct FileReadResult {
    content: string
    size: int
    modified: int
}

method file/write {
    input: FileWriteRequest
    output: SuccessResult
}

struct FileWriteRequest {
    path: string
    content: string
}

method file/list {
    input: FileListRequest
    output: FileListResult
}

struct FileListRequest {
    path: string
    pattern: string
}

struct FileListResult {
    files: File[]
}

method file/delete {
    input: FileDeleteRequest
    output: SuccessResult
}

struct FileDeleteRequest {
    path: string
}

// =============================================================================
// LSP Methods
// =============================================================================

method lsp/start {
    input: LSPStartRequest
    output: LSPStartResult
}

struct LSPStartRequest {
    language: string
    cwd: string
}

struct LSPStartResult {
    success: bool
    language: string
}

method lsp/diagnostics {
    input: LSPDiagnosticsRequest
    output: LSPDiagnosticsResult
}

struct LSPDiagnosticsRequest {
    uri: string
}

struct LSPDiagnosticsResult {
    diagnostics: Diagnostic[]
}

// =============================================================================
// MCP Methods
// =============================================================================

method mcp/listServers {
    input: Empty
    output: MCPServersResult
}

struct MCPServersResult {
    servers: MCPServer[]
}

struct MCPServer {
    name: string
    status: string
}

method mcp/listTools {
    input: MCPToolsRequest
    output: MCPToolsResult
}

struct MCPToolsRequest {
    server_name: string
}

struct MCPToolsResult {
    tools: MCPTool[]
}

struct MCPTool {
    name: string
    description: string
    input_schema: string
}

// =============================================================================
// Settings Methods
// =============================================================================

method settings/get {
    input: Empty
    output: SettingsResult
}

struct SettingsResult {
    model: string
    provider: string
    temperature: float
    max_tokens: int
    thinking: bool
    context_window: int
}

method settings/set {
    input: SettingsSetRequest
    output: SuccessResult
}

struct SettingsSetRequest {
    key: string
    value: string
}

// =============================================================================
// Models Methods
// =============================================================================

method models/list {
    input: Empty
    output: ModelsResult
}

struct ModelsResult {
    models: Model[]
}

// =============================================================================
// Agent Methods
// =============================================================================

method agent/run {
    input: AgentRunRequest
    output: AgentResult
}

struct AgentRunRequest {
    session_id: string
    prompt: string
    attachments: Attachment[]
}

method agent/summarize {
    input: AgentSummarizeRequest
    output: SuccessResult
}

struct AgentSummarizeRequest {
    session_id: string
}

// =============================================================================
// Common Result Types
// =============================================================================

struct Empty {}

struct SuccessResult {
    success: bool
}

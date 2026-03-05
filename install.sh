#!/bin/bash
# Lex Compiler Installer for Linux/macOS
# Usage: curl -fsSL https://raw.githubusercontent.com/David-Imperium/Lex-compiler/main/install.sh | bash

set -e

VERSION="${VERSION:-latest}"
INSTALL_DIR="${INSTALL_DIR:-}"
BINARY_NAME="lexc"

# Colors
RED='\033[0;31m'
GREEN='\033[0;32m'
CYAN='\033[0;36m'
NC='\033[0m' # No Color

info() { echo -e "${CYAN}$1${NC}"; }
success() { echo -e "${GREEN}✓ $1${NC}"; }
error() { echo -e "${RED}✗ $1${NC}"; }

# Detect OS and architecture
detect_platform() {
    OS="$(uname -s)"
    case "$OS" in
        Linux*)  PLATFORM="linux";;
        Darwin*) PLATFORM="macos";;
        *)       error "Unsupported OS: $OS"; exit 1;;
    esac
    
    ARCH="$(uname -m)"
    case "$ARCH" in
        x86_64|amd64)  ARCH="x64";;
        arm64|aarch64) ARCH="arm64";;
        *)             error "Unsupported architecture: $ARCH"; exit 1;;
    esac
}

# Set install directory
set_install_dir() {
    if [ -z "$INSTALL_DIR" ]; then
        if [ "$PLATFORM" = "macos" ]; then
            INSTALL_DIR="/usr/local/bin"
        else
            # Check if we can write to /usr/local/bin
            if [ -w "/usr/local/bin" ] || [ "$EUID" -eq 0 ]; then
                INSTALL_DIR="/usr/local/bin"
            else
                INSTALL_DIR="$HOME/.local/bin"
                mkdir -p "$INSTALL_DIR"
            fi
        fi
    fi
}

# Get latest version from GitHub API
get_latest_version() {
    info "Fetching latest version..."
    LATEST=$(curl -fsSL "https://api.github.com/repos/David-Imperium/Lex-compiler/releases/latest" | grep '"tag_name"' | sed -E 's/.*"([^"]+)".*/\1/')
    if [ -n "$LATEST" ]; then
        VERSION="$LATEST"
        success "Latest version: $VERSION"
    else
        error "Failed to fetch version, using v0.4.0"
        VERSION="v0.4.0"
    fi
}

# Download and install
install() {
    detect_platform
    set_install_dir
    
    if [ "$VERSION" = "latest" ]; then
        get_latest_version
    fi
    
    # Download URL - handle both .zip and .tar.gz
    if [ "$PLATFORM" = "linux" ]; then
        DOWNLOAD_URL="https://github.com/David-Imperium/Lex-compiler/releases/download/$VERSION/lexc-$PLATFORM-$ARCH.tar.gz"
        EXT="tar.gz"
    else
        DOWNLOAD_URL="https://github.com/David-Imperium/Lex-compiler/releases/download/$VERSION/lexc-$PLATFORM-$ARCH.tar.gz"
        EXT="tar.gz"
    fi
    
    TEMP_DIR=$(mktemp -d)
    ARCHIVE="$TEMP_DIR/lexc.$EXT"
    
    info ""
    info "Lex Compiler Installer"
    info "====================="
    info ""
    info "Platform: $PLATFORM-$ARCH"
    info "Version: $VERSION"
    info "Install dir: $INSTALL_DIR"
    info ""
    
    # Download
    info "Downloading Lex $VERSION..."
    if ! curl -fsSL "$DOWNLOAD_URL" -o "$ARCHIVE"; then
        error "Download failed from $DOWNLOAD_URL"
        info ""
        info "The binary release may not be available yet."
        info "Please build from source:"
        info "  git clone https://github.com/David-Imperium/Lex-compiler.git"
        info "  cd Lex-compiler"
        info "  cmake -B build -S ."
        info "  cmake --build build --config Release"
        info "  sudo cmake --install build"
        rm -rf "$TEMP_DIR"
        exit 1
    fi
    success "Download complete"
    
    # Extract
    info "Extracting..."
    cd "$TEMP_DIR"
    tar -xzf "$ARCHIVE"
    
    # Find the binary
    BINARY=$(find . -name "lexc" -type f | head -1)
    if [ -z "$BINARY" ]; then
        error "Binary not found in archive"
        rm -rf "$TEMP_DIR"
        exit 1
    fi
    
    # Make executable
    chmod +x "$BINARY"
    
    # Install
    if [ -w "$INSTALL_DIR" ] || [ "$EUID" -eq 0 ]; then
        cp "$BINARY" "$INSTALL_DIR/$BINARY_NAME"
        success "Installed to $INSTALL_DIR/$BINARY_NAME"
    else
        info "Need sudo to install to $INSTALL_DIR"
        sudo cp "$BINARY" "$INSTALL_DIR/$BINARY_NAME"
        sudo chmod +x "$INSTALL_DIR/$BINARY_NAME"
        success "Installed to $INSTALL_DIR/$BINARY_NAME"
    fi
    
    # Cleanup
    rm -rf "$TEMP_DIR"
    
    # Check PATH
    if ! echo "$PATH" | grep -q "$INSTALL_DIR"; then
        info ""
        info "Add to PATH by adding this to your ~/.bashrc or ~/.zshrc:"
        info "  export PATH=\"\$PATH:$INSTALL_DIR\""
    fi
    
    info ""
    success "Installation complete!"
    info ""
    info "Run 'lexc --help' to get started."
    info "Documentation: https://github.com/David-Imperium/Lex-compiler"
}

install

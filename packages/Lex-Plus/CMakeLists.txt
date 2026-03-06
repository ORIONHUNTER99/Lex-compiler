# Lex-Plus Package - Premium Extensions
cmake_minimum_required(VERSION 3.20)

message(STATUS "Configuring Lex-Plus package...")

# ============================================================================
# Premium Backends Library
# ============================================================================

add_library(lex_plus STATIC
    src/codegen/unreal_backend.cpp
    # Add more premium backends here as they are implemented:
    # src/codegen/gamemaker_backend.cpp
    # src/codegen/rust_backend.cpp
    # src/codegen/cpp_backend.cpp
    # src/codegen/python_backend.cpp
)

# Include paths - access to Lex base headers
target_include_directories(lex_plus
    PUBLIC
        ${CMAKE_SOURCE_DIR}/src           # Lex base headers (backend.hpp, etc.)
        ${CMAKE_CURRENT_SOURCE_DIR}/src   # Lex-Plus headers
)

# Link against base Lex library
target_link_libraries(lex_plus PUBLIC lex)

# Set a variable so main CMakeLists knows to link lex_plus
set(LEX_PLUS_FOUND ON PARENT_SCOPE)

message(STATUS "Lex-Plus package configured successfully")

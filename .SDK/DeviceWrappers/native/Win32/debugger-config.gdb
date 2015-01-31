# =====================================
#  GDB preload initialization commands
# =====================================

# Set Unicode Charset
#set target-charset UCS-2
#set host-charset UCS-2
#set charset UCS-2
#set target-wide-charset UCS-2

# Set UTF-8 Charset
set target-charset UTF-8
set host-charset UTF-8
set charset UTF-8
set target-wide-charset UTF-8

# Request async target mode
set target-async 1

# Do not complain about pending breakpoints
set breakpoint pending on

# Enable All-Stop for all Threads
set non-stop off

# Do not ask for confirmations
set confirm off

# Do not create new console for output/logging
set new-console off

# Turn-off paggination to allow integration with IDE
set pagination off

# Call Stack files (and anywhere else) should be absolute path
set filename-display absolute

# Enable Pretty Print in GDB Panel
set print pretty on

# Enable notification of completion for asynchronous execution commands.
set exec-done-display on

# Show Addresses in objects, required for integration with IDE
set print address on

# Enable Pretty Print for Arrays
set print array on

# Flatten objects, required for integration with IDE
set print object off

# Include static members, required for integration with IDE
set print static-members on

# Show demangled vtable, required for integration with IDE
set print vtbl off
set print demangle on
set demangle-style gnu-v3

# Print full eight-bit characters, required for integration with IDE
set print sevenbit-strings off

# Set path for obj files
path $(TARGET_ROOT)/obj

# Load gdb scripts for STL (string, vector, map, etc.)
source $(PATH_SDK_DEBUGGER)/stl-views-1.0.3.gdb

# List of source code files
dir $(PATH_SDK_COMMON)
dir $(PATH_SDK_FRAMEWORKS)
dir $(PATH_SDK_INCLUDES)
dir $(PROJECT_PATHS.NATIVE_COMMON)

# Load the binary
file $(TARGET_OUTPUT)

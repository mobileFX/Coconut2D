# =====================================
#  GDB preload initialization commands
# =====================================

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
path D:/mobileFX/Projects/Software/Coconut/Projects/Coco.project/.targets/native/Win32/obj

# Load gdb scripts for STL (string, vector, map, etc.)
source D:/mobileFX/Projects/Software/Coconut/Projects/Coco.project/.SDK/Toolchain/Debugger/stl-views-1.0.3.gdb

# List of source code files
dir D:/mobileFX/Projects/Software/Coconut/Projects/Coco.project/.SDK/DeviceWrappers/native/_Common
dir D:/mobileFX/Projects/Software/Coconut/Projects/Coco.project/.SDK/Frameworks
dir D:/mobileFX/Projects/Software/Coconut/Projects/Coco.project/.SDK/DeviceWrappers/native/_Includes
dir D:/mobileFX/Projects/Software/Coconut/Projects/Coco.project/.targets/native/_Common

# Load the binary
file D:/mobileFX/Projects/Software/Coconut/Projects/Coco.project/.targets/native/Win32/Coconut2D.exe

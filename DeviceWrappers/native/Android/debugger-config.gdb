# =====================================
#  GDB preload initialization commands
# =====================================

# Load Coconut2D IDE Python Pretty Printers
python
import sys
sys.path.insert(0, '$(PATH_SDK)/Toolchain/Debugger')
from Coconut2D.printers import register_printer_gen
register_printer_gen(None)
end

info type-printers

show charset
show host-charset
show target-charset
show target-wide-charset

# Request async target mode
set target-async 1

# Do not complain about pending breakpoints
set breakpoint pending on
set breakpoint always-inserted on

# Enable All-Stop for all Threads
set non-stop off

# Do not ask for confirmations
set confirm off

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
set print symbol-filename on
set print max-symbolic-offset 0
set print symbol on

# Enable Pretty Print for Arrays
set print array on
set print array-indexes on
set print elements 0
set print null-stop

# Flatten objects, required for integration with IDE
set print object off
set print type methods off
set print type typedefs off
set print static-members on

# Show demangled vtable, required for integration with IDE
set print vtbl off
set print demangle on
set print asm-demangle on
set demangle-style gnu-v3
set case-sensitive on
set overload-resolution on
set print frame-arguments none
set print sevenbit-strings off
set print union off

# Set path for obj files
path $(TARGET_ROOT)/obj

# Load gdb scripts for STL (string, vector, map, etc.)
source $(PATH_SDK_DEBUGGER)/stl-views-1.0.3.gdb

# List of sources and includes
$(PATH_SDK_INCLUDES)
dir $(TARGET_ROOT)/jni/src
dir $(PATH_3RD_PARTY_ANDROID_NDK)/sources/android/native_app_glue
dir $(PATH_3RD_PARTY_ANDROID_NDK)/sources/cxx-stl/gnu-libstdc++/4.8/include
dir $(PATH_3RD_PARTY_ANDROID_NDK)/sources/cxx-stl/gnu-libstdc++/4.8/libs/$(ABI_ARCH)/include
dir $(PATH_3RD_PARTY_ANDROID_NDK)/sources/cxx-stl/gnu-libstdc++/4.8/include/backward

# Set lib search path
set solib-search-path $(TARGET_ROOT)/obj/local/$(ABI_ARCH)

# Load the proxy process
file ./obj/local/$(ABI_ARCH)/app_process

# Load the Coconut2D JNI Library
# file $(TARGET_ROOT)/obj/local/$(ABI_ARCH)/libCoconut2D.so

# connect to gdb server
target remote :5039


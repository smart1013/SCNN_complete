CXX = g++
CXXFLAGS = -I include -std=c++17 -O3 -Wall

# Source files common to both executables
# Note: src/pe.cc is no longer used in the cycle-accurate version
SRCS_COMMON = src/tensor.cc \
              src/loader.cc \
              src/convlayer.cc \
              src/mult_array.cc \
              src/dispatcher.cc \
              src/buffer_queue.cc \
              src/accumulator.cc

# Main programs
SRC_TOP = top.cc
SRC_VERIFY = verify_top.cc

# Output binary names
TARGET_TOP = top
TARGET_VERIFY = verify_top

# Default target (builds both)
all: $(TARGET_TOP) $(TARGET_VERIFY)

# Link top
# Usage: make top
$(TARGET_TOP): $(SRC_TOP) $(SRCS_COMMON)
	$(CXX) $(CXXFLAGS) -o $(TARGET_TOP) $(SRC_TOP) $(SRCS_COMMON)

# Link verify_top
# Usage: make verify_top
$(TARGET_VERIFY): $(SRC_VERIFY) $(SRCS_COMMON)
	$(CXX) $(CXXFLAGS) -o $(TARGET_VERIFY) $(SRC_VERIFY) $(SRCS_COMMON)

# Clean build artifacts
clean:
	rm -f $(TARGET_TOP) $(TARGET_VERIFY) *.o

# Phony targets to strictly separate command usage
.PHONY: all clean top verify_top

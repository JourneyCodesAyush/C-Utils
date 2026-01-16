# Compiler and flags
CC = gcc
CFLAGS = -Wall -g

# Source and header directories
SRC_DIR = src
INC_DIR = include
BUILD_DIR = makeBuild

# Source and header files
SRC = $(wildcard $(SRC_DIR)/*.c)
HDR = $(wildcard $(INC_DIR)/*.h)

# Object files in build directory
OBJ = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRC))

# Executable
ifeq ($(OS),Windows_NT)
    TARGET = cutils.exe
else
    TARGET = cutils
endif

# Ensure build directory exists
$(shell mkdir $(BUILD_DIR) 2> NUL)

# Build the executable
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -I$(INC_DIR) -o $(TARGET) $(OBJ)

# Compile .c to .o and track headers
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c $(HDR)
	$(CC) $(CFLAGS) -I $(INC_DIR) -c $< -o $@

# Clean build files
clean:
ifeq ($(OS),Windows_NT)
	del /Q $(BUILD_DIR)\*.o 2> NUL || true
	del /Q $(TARGET) 2> NUL || true
else
	rm -f $(BUILD_DIR)/*.o
	rm -f $(TARGET)
endif

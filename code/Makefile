CXX := g++
CXXFLAGS := -std=c++11 -I include
LDFLAGS := -lcatch2

# Directories
SRC_DIR := src
INCLUDE_DIR := include
TEST_DIR := tests
BUILD_DIR := build

# Files
SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
TEST_FILES := $(wildcard $(TEST_DIR)/*.cpp)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRC_FILES))
TEST_OBJ_FILES := $(patsubst $(TEST_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(TEST_FILES))

# Executables
TARGET := AnimeReccomend
TEST_TARGET := test_runner

# Phony targets
.PHONY: all clean test

all: $(TARGET)

# Build main program
$(TARGET): $(OBJ_FILES)
	$(CXX) $(LDFLAGS) $^ -o $@

# Build object files for main program
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Build and run tests
test: $(TEST_TARGET)
	./$(TEST_TARGET)

# Build test runner
$(TEST_TARGET): $(TEST_OBJ_FILES) $(OBJ_FILES)
	$(CXX) $(LDFLAGS) $^ -o $@

# Build object files for test cases
$(BUILD_DIR)/%.o: $(TEST_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Create build directory
$(BUILD_DIR):
	mkdir -p $@

# Clean build artifacts
clean:
	rm -rf $(BUILD_DIR) $(TARGET) $(TEST_TARGET)

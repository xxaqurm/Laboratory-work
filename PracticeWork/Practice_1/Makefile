CXX := g++

CXXFLAGS := -std=c++17 -Wall -Wextra -O2 -Iinclude
SRC_DIR := src
BUILD_DIR := build
TARGET := main

SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
SRC_OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRC_FILES))
MAIN_OBJ := $(BUILD_DIR)/main.o
OBJS := $(MAIN_OBJ) $(SRC_OBJS)

.PHONY: all clean rebuild

all: $(BUILD_DIR) $(TARGET)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(MAIN_OBJ): main.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

clean:
	rm -rf $(BUILD_DIR) $(TARGET)

rebuild: clean all
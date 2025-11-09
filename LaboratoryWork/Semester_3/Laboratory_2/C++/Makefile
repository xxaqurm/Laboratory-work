CXX = g++
CXXFLAGS = -std=c++20 -Iinclude -Wall -Wextra
SRC_DIR = src/tasks
OBJ_DIR = build
SRC = $(SRC_DIR)/SetPartition.cpp $(SRC_DIR)/ArithmeticExpression.cpp $(SRC_DIR)/InteractionWithDoubleHashSet.cpp $(SRC_DIR)/Subarrays.cpp $(SRC_DIR)/AVLBalance.cpp $(SRC_DIR)/BST.cpp $(SRC_DIR)/ChainedHash.cpp $(SRC_DIR)/LRUHash.cpp $(SRC_DIR)/InteractionWithHashs.cpp $(SRC_DIR)/InteractionWithLRUHash.cpp $(SRC_DIR)/OpenAddressingHash.cpp main.cpp
OBJ = $(patsubst %.cpp,$(OBJ_DIR)/%.o,$(SRC))

all: $(OBJ)
	$(CXX) $(OBJ) -o main

$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) main


BUILD_DIR =./build
SRC_DIR =./src
app.out : main.o DecisionTable.o DecisionTree.o
	g++ -o app.out $(BUILD_DIR)/main.o $(BUILD_DIR)/DecisionTable.o $(BUILD_DIR)/DecisionTree.o

main.o : $(SRC_DIR)/main.cpp
	g++ -c -o $(BUILD_DIR)/main.o $(SRC_DIR)/main.cpp


DecisionTable.o : $(SRC_DIR)/DecisionTable.hpp $(SRC_DIR)/DecisionTable.cpp
	g++ -c -o $(BUILD_DIR)/DecisionTable.o $(SRC_DIR)/DecisionTable.cpp

	
DecisionTree.o : $(SRC_DIR)/DecisionTree.hpp $(SRC_DIR)/DecisionTree.cpp
	g++ -c -o $(BUILD_DIR)/DecisionTree.o $(SRC_DIR)/DecisionTree.cpp



clean:
	rm $(BUILD_DIR)/*.o

BUILD_DIR =./build
SRC_DIR =./src
app.out : main.o word_cluster.o
	g++ -o app.out $(BUILD_DIR)/main.o $(BUILD_DIR)/word_cluster.o

main.o : $(SRC_DIR)/main.cpp
	g++ -c -o $(BUILD_DIR)/main.o $(SRC_DIR)/main.cpp


word_cluster.o : $(SRC_DIR)/word_cluster.hpp $(SRC_DIR)/word_cluster.cpp
	g++ -c -o $(BUILD_DIR)/word_cluster.o $(SRC_DIR)/word_cluster.cpp


clean:
	rm $(BUILD_DIR)/*.o

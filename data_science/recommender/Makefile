BUILD_DIR =./build
SRC_DIR =./src
app.out : main.o rating_matrix.o
	g++ -o app.out $(BUILD_DIR)/main.o $(BUILD_DIR)/rating_matrix.o

main.o : $(SRC_DIR)/main.cpp
	g++ -c -o $(BUILD_DIR)/main.o $(SRC_DIR)/main.cpp

rating_matrix.o : $(SRC_DIR)/rating_matrix.hpp $(SRC_DIR)/rating_matrix.cpp
	g++ -c -o $(BUILD_DIR)/rating_matrix.o $(SRC_DIR)/rating_matrix.cpp

clean:
	rm $(BUILD_DIR)/*.o

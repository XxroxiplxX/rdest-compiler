

clean :
	rm -f $(TESTS) gtest.a gtest_main.a *.o
	rm -f $(OBJ) $(EXEC)
	rm -f ./src/parsery.hpp	./src/parsery.cpp ./src/analyzer.cpp

SRC_DIR=../src
INC_DIR=../include


EXEC := main.out
SRC := $(wildcard $(SRC_DIR)/*.cpp)
INC := $(wildcard $(INC_DIR)/*.h)
OBJ := $(SRC:%.cpp=%.o)
$(SRC) : parsery.cpp analyzer.cpp

HEADERS := -I $(INC_DIR)

parsery.cpp:
	bison -d -o ../src/parsery.cpp ../src/parser.y
analyzer.cpp:
	flex -o ../src/analyzer.cpp ../src/lexer.l
# COMPILING
%.o: %.cpp $(INC)
	g++ -Wall $(HEADERS) -c $< -o $@


$(EXEC): $(SRC) $(INC) $(OBJ)
	g++ $(HEADERS) $(OBJ) -o $@
run: $(EXEC)
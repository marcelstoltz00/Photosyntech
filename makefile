CXX = g++
CXXFLAGS = -std=c++11 -g --coverage -Werror=sign-compare -Werror=delete-non-virtual-dtor

# add the cpp files here that you want to compile.

TEST_SRC = unitTests.cpp\
			



SRC = $(TEST_SRC)
OBJ := $(SRC:.cpp=.o)
BIN := app


all: test

test: 
	$(MAKE) SRC="$(TEST_SRC)" all-internal



all-internal: $(BIN)

$(BIN):	$(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o:	%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

run r:	$(BIN)
	./$(BIN)



test-run: test
	./$(BIN)


cov: test
	./$(BIN)
	gcovr --root . \
	    --exclude '.*\.h' \
	    --print-summary > coverage.txt
	@echo "Coverage report generated in coverage.txt"


clean c:
	find . -name '*.o' -delete
	rm -f $(BIN) vgcore.*
	find . -name '*.gcno' -delete
	find . -name '*.gcda' -delete
	find . -name '*.gcov' -delete
	rm -f coverage.txt
	rm -f coverage.html coverage*.html coverage.css

valgrind v:	$(BIN)
	valgrind --leak-check=full --show-leak-kinds=all -s --track-origins=yes ./$(BIN)

leaks: $(BIN)
	leaks --atExit -- ./$(BIN)

CXX = g++
CXXFLAGS = -std=c++11 -g --coverage -I. -Ithird_party/doctest


DOCTEST_DIR = third_party/doctest
DOCTEST_HEADER = $(DOCTEST_DIR)/doctest.h

.PHONY: fetch-doctest
fetch-doctest:
	@mkdir -p $(DOCTEST_DIR)
	@if [ ! -f $(DOCTEST_HEADER) ]; then \
		echo "Downloading doctest single header..."; \
		curl -sSL -o $(DOCTEST_HEADER) https://raw.githubusercontent.com/onqtam/doctest/master/doctest/doctest.h; \
		if [ $$? -ne 0 ]; then \
			echo "Failed to download doctest.h; please download it manually to $(DOCTEST_HEADER)"; exit 1; \
		fi; \
	fi



TEST_SRC = unitTests.cpp\
            strategy/LowWater.cpp\
            strategy/MidWater.cpp\
            strategy/HighWater.cpp\
            strategy/AlternatingWater.cpp\
            strategy/LowSun.cpp\
            strategy/MidSun.cpp\
            strategy/HighSun.cpp\
            singleton/Singleton.cpp\
            prototype/LivingPlant.cpp\
            composite/PlantComponent.cpp\
            state/Dead.cpp\
            state/Mature.cpp\
            state/Seed.cpp\
            state/Vegetative.cpp\
            prototype/LivingPlant.cpp\
            decorator/PlantAttributes.cpp\
            decorator/ConcreteDecorators.cpp\
			strategy/AlternatingSun.cpp\
			composite/PlantGroup.cpp\
			builder/Director.cpp\
			builder/RoseBuilder.cpp\
			builder/CactusBuilder.cpp\
			iterator/AggPlant.cpp\
			iterator/AggSeason.cpp\
			iterator/PlantIterator.cpp\
			iterator/SeasonIterator.cpp\

SRC = $(TEST_SRC)
OBJ := $(SRC:.cpp=.o)
BIN := app


all: test

test: fetch-doctest
	$(MAKE) SRC="$(TEST_SRC)" all-internal


all-internal: $(BIN)

$(BIN): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: 	%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

run r: 	$(BIN)
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

valgrind v: $(BIN)
	valgrind --leak-check=full --show-leak-kinds=all -s --track-origins=yes ./$(BIN)

leaks: $(BIN)
	leaks --atExit -- ./$(BIN)
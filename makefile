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


TEST_SRC = tests/tests_core.cpp\
            strategy/LowWater.cpp\
            strategy/MidWater.cpp\
            strategy/HighWater.cpp\
            strategy/AlternatingWater.cpp\
            strategy/LowSun.cpp\
            strategy/MidSun.cpp\
            strategy/HighSun.cpp\
            strategy/AlternatingSun.cpp\
            singleton/Singleton.cpp\
            prototype/LivingPlant.cpp\
            composite/PlantComponent.cpp\
            composite/PlantGroup.cpp\
            state/Dead.cpp\
            state/Mature.cpp\
            state/Seed.cpp\
            state/Vegetative.cpp\
            decorator/PlantAttributes.cpp\
            decorator/ConcreteDecorators.cpp\
            builder/Builder.cpp\
            builder/Director.cpp\
            builder/RoseBuilder.cpp\
            builder/CactusBuilder.cpp\
            builder/CherryBlossomBuilder.cpp\
            builder/SunflowerBuilder.cpp\
            builder/PineBuilder.cpp\
            builder/MapleBuilder.cpp\
            builder/JadePlantBuilder.cpp\
            builder/LavenderBuilder.cpp\
            iterator/Aggregate.cpp\
            iterator/AggPlant.cpp\
            iterator/AggSeason.cpp\
            iterator/AggPlantName.cpp\
            iterator/PlantIterator.cpp\
            iterator/SeasonIterator.cpp\
            iterator/PlantNameIterator.cpp\
            mediator/Mediator.cpp\
            mediator/Customer.cpp\
            mediator/SalesFloor.cpp\
            mediator/Staff.cpp\
            mediator/SuggestionFloor.cpp\
            observer/Observer.cpp\
            observer/Subject.cpp\
			facade/NurseryFacade.cpp

SRC = $(TEST_SRC)
OBJ := $(SRC:.cpp=.o)
BIN := app


all: test

test: fetch-doctest
	$(MAKE) SRC="$(TEST_SRC)" all-internal

all-internal: $(BIN)

$(BIN): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

run r: $(BIN)
	./$(BIN)

test-run: test
	./$(BIN)

cov: test
	./$(BIN)
	gcovr --root . --exclude '.*\.h' --print-summary > coverage.txt
	@echo "Coverage report generated in coverage.txt"

clean c:
	find . -name '*.o' -delete
	rm -f $(BIN) vgcore.*
	find . -name '*.gcno' -delete
	find . -name '*.gcda' -delete
	find . -name '*.gcov' -delete
	rm -f coverage.txt coverage.html coverage.css
	rm -f $(BIN)
	rm  -f $(DEMO_BIN)

valgrind v: $(BIN)
	valgrind --leak-check=full --show-leak-kinds=all -s --track-origins=yes ./$(BIN)

leaks: $(BIN)
	leaks --atExit -- ./$(BIN)

# Documentation generation targets
.PHONY: docs doxygen

docs: doxygen

doxygen:
	doxygen Doxyfile
	@echo "Documentation generated in docs/doxygen/html"

# -----------------------------------------------------------------------------
# TUI (TUIKit) helper targets
# -----------------------------------------------------------------------------
# Downloads the single-header nlohmann/json and places it where the TUIKit CMake
# expects it (supports both "json.hpp" and <nlohmann/json.hpp> include styles).
CPU_CORES := $(shell sysctl -n hw.ncpu)
TUI_SRC := TUI/TUIKit
TUI_BUILD := $(TUI_SRC)/build
JSON_DIR := $(TUI_SRC)/external/json
JSON_NLO_DIR := $(JSON_DIR)/nlohmann
JSON_URL := https://raw.githubusercontent.com/nlohmann/json/develop/single_include/nlohmann/json.hpp

.PHONY: fetch-json cmake-config cmake-build tui tui-clean

fetch-json:
	@mkdir -p $(JSON_NLO_DIR)
	@if [ ! -f $(JSON_NLO_DIR)/json.hpp ]; then \
		echo "Downloading nlohmann/json single header..."; \
		curl -sSL -o $(JSON_NLO_DIR)/json.hpp $(JSON_URL); \
		if [ $$? -ne 0 ]; then \
			echo "Failed to download json.hpp; please download manually to $(JSON_NLO_DIR)/json.hpp"; exit 1; \
		fi; \
	fi
	@# Provide the header at both locations used by the project source
	@mkdir -p $(JSON_DIR)
	@cp -f $(JSON_NLO_DIR)/json.hpp $(JSON_DIR)/json.hpp || true

# Configure the TUIKit CMake project into the build directory
cmake-config:
	cmake -S $(TUI_SRC) -B $(TUI_BUILD)

# Build the TUIKit project (uses all CPU cores by default)
cmake-build:
	cmake --build $(TUI_BUILD) --parallel $(CPU_CORES)

# Convenience target to fetch externals, configure and build TUIKit
tui: fetch-json cmake-config cmake-build

# Clean the TUIKit build directory
tui-clean:
	rm -rf $(TUI_BUILD)

# -----------------------------------------------------------------------------
# Optional convenience targets to reproduce upstream build steps (requested)
# These run the explicit commands you listed: clone TUIKit, clone FTXUI into
# external/ftxui, download specific nlohmann/json release, create build dir,
# configure with cmake .. and build with cmake --build .
# -----------------------------------------------------------------------------

.PHONY: tui-clone tui-deps tui-configure-raw tui-build-raw tui-full

# Clone the TUIKit repository into TUI/TUIKit (if it's not already present)
tui-clone:
	@if [ -d "TUI/TUIKit/.git" ]; then \
		echo "TUI/TUIKit already exists, skipping clone"; \
	else \
		git clone https://github.com/skhelladi/TUIKit.git TUI/TUIKit; \
	fi

# Install dependencies: clone FTXUI into external/ftxui and download nlohmann/json
tui-deps:
	@mkdir -p TUI/TUIKit/external
	@# Ensure `git` is available before attempting clones
	@if ! command -v git >/dev/null 2>&1; then \
		echo "git not found; please install git to clone external dependencies"; exit 127; \
	fi
	@if [ -d "TUI/TUIKit/external/ftxui/.git" ]; then \
		echo "external/ftxui already present, skipping clone"; \
	else \
		git clone https://github.com/ArthurSonzogni/FTXUI.git TUI/TUIKit/external/ftxui; \
	fi
	@if [ -d "TUI/TUIKit/external/ftxui-image-view/.git" ]; then \
		echo "external/ftxui-image-view already present, skipping clone"; \
	else \
		git clone https://github.com/ljrrjl/ftxui-image-view.git TUI/TUIKit/external/ftxui-image-view; \
	fi
	@mkdir -p TUI/TUIKit/external/json
	@echo "Downloading nlohmann/json (v3.12.0) into external/json..."
	@mkdir -p TUI/TUIKit/external/json/nlohmann
	@if command -v wget >/dev/null 2>&1; then \
		wget -q -O TUI/TUIKit/external/json/nlohmann/json.hpp https://github.com/nlohmann/json/releases/download/v3.12.0/json.hpp || { echo "Failed to download nlohmann/json.hpp via wget"; exit 1; }; \
	else \
		curl -sSL -o TUI/TUIKit/external/json/nlohmann/json.hpp https://github.com/nlohmann/json/releases/download/v3.12.0/json.hpp || { echo "Failed to download nlohmann/json.hpp via curl"; exit 1; }; \
	fi
	# Also put a copy at external/json/json.hpp for sources that include "json.hpp"
	@cp -f TUI/TUIKit/external/json/nlohmann/json.hpp TUI/TUIKit/extetui-deps:
	@mkdir -p TUI/TUIKit/external
	@if [ -d "TUI/TUIKit/external/ftxui/.git" ]; then \
		echo "external/ftxui already present, skipping clone"; \
	else \
		git clone https://github.com/ArthurSonzogni/FTXUI.git TUI/TUIKit/external/ftxui; \
	fi
	@mkdir -p TUI/TUIKit/external/json
	@echo "Downloading nlohmann/json (v3.12.0) into external/json..."
	@mkdir -p TUI/TUIKit/external/json/nlohmann
	@if command -v wget >/dev/null 2>&1; then \
		wget -q -O TUI/TUIKit/external/json/nlohmann/json.hpp https://github.com/nlohmann/json/releases/download/v3.12.0/json.hpp || { echo "Failed to download nlohmann/json.hpp via wget"; exit 1; }; \
	else \
		curl -sSL -o TUI/TUIKit/external/json/nlohmann/json.hpp https://github.com/nlohmann/json/releases/download/v3.12.0/json.hpp || { echo "Failed to download nlohmann/json.hpp via curl"; exit 1; }; \
	fi
	# Also put a copy at external/json/json.hpp for sources that include "json.hpp"
	@cp -f TUI/TUIKit/external/json/nlohmann/json.hpp TUI/TUIKit/external/json/json.hpp || truernal/json/json.hpp || true

# Create build directory and run 'cmake ..' from inside it (raw command form)
tui-configure-raw:
	@mkdir -p TUI/TUIKit/build
	@if ! command -v cmake >/dev/null 2>&1; then \
		echo "cmake not found. Install it with 'brew install cmake' or from https://cmake.org/download/"; exit 127; \
	fi
	@cd TUI/TUIKit/build && cmake ..

# Build the project from the build directory using cmake --build .
tui-build-raw:
	@cd TUI/TUIKit/build && cmake --build .

# Full sequence: clone repo (if needed), fetch deps, configure and build
tui-full: tui-clone tui-deps tui-configure-raw tui-build-raw
	@echo "TUIKit build complete (tui-full)"

tui-manager: tui
	cd TUI/TUIKit/build && ./TUI


tui-manager-v: tui
	cd TUI/TUIKit/build && valgrind --leak-check=full --show-leak-kinds=all -s --track-origins=yes ./TUI


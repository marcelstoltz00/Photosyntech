# =============================================================================
# Compiler Configuration
# =============================================================================
CXX = g++
CXXFLAGS = -std=c++11 -g --coverage -I. -Ithird_party/doctest

# Detect number of CPU cores for parallel compilation
CPU_CORES := $(shell sysctl -n hw.ncpu)
MAKEFLAGS += -j$(CPU_CORES)

# =============================================================================
# Doctest Configuration
# =============================================================================
DOCTEST_DIR = third_party/doctest
DOCTEST_HEADER = $(DOCTEST_DIR)/doctest.h

.PHONY: fetch-doctest
fetch-doctest:
	@mkdir -p $(DOCTEST_DIR)
	@if [ ! -f $(DOCTEST_HEADER) ]; then \
		echo "Downloading doctest single header..."; \
		curl -sSL -o $(DOCTEST_HEADER) https://raw.githubusercontent.com/onqtam/doctest/master/doctest/doctest.h; \
		if [ $$? -ne 0 ]; then \
			echo "Failed to download doctest.h; please download it manually to $(DOCTEST_HEADER)"; \
			exit 1; \
		fi; \
	fi

# =============================================================================
# Source Files Configuration
# =============================================================================
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

# =============================================================================
# Build Targets
# =============================================================================
.PHONY: all test all-internal run r test-run cov clean c valgrind v leaks info

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
	rm -f $(DEMO_BIN)

valgrind v: $(BIN)
	valgrind --leak-check=full --show-leak-kinds=all -s --track-origins=yes ./$(BIN)

leaks: $(BIN)
	leaks --atExit -- ./$(BIN)

info:
	@echo "==================================================================="
	@echo "Photosyntech Build Configuration"
	@echo "==================================================================="
	@echo "Compiler:        $(CXX)"
	@echo "CPU Cores:       $(CPU_CORES)"
	@echo "Parallel Jobs:   $(CPU_CORES) (via -j flag)"
	@echo "C++ Standard:    C++11"
	@echo "Build Flags:     $(CXXFLAGS)"
	@echo "Test Files:      $(words $(TEST_SRC)) source files"
	@echo "Binary Output:   $(BIN)"
	@echo "==================================================================="
	@echo "Available commands:"
	@echo "  make test-run       - Build and run tests"
	@echo "  make clean          - Clean build artifacts"
	@echo "  make docs           - Generate documentation"
	@echo "  make tui-manager    - Build TUI manager"
	@echo "  make info           - Show this information"
	@echo "==================================================================="

# =============================================================================
# Documentation Targets
# =============================================================================
.PHONY: docs doxygen

docs: doxygen

doxygen:
	doxygen Doxyfile
	@echo "Documentation generated in docs/doxygen/html"

# =============================================================================
# TUI (TUIKit) Configuration
# =============================================================================
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
			echo "Failed to download json.hpp; please download manually to $(JSON_NLO_DIR)/json.hpp"; \
			exit 1; \
		fi; \
	fi
	@mkdir -p $(JSON_DIR)
	@cp -f $(JSON_NLO_DIR)/json.hpp $(JSON_DIR)/json.hpp || true

cmake-config: tui-clone tui-deps
	@if ! command -v cmake >/dev/null 2>&1; then \
		echo "cmake not found. Install it with 'brew install cmake' or from https://cmake.org/download/"; \
		exit 127; \
	fi
	cmake -S $(TUI_SRC) -B $(TUI_BUILD)

cmake-build: cmake-config
	# Ensure configuration step runs before attempting to build.
	cmake --build $(TUI_BUILD) --parallel $(CPU_CORES)

tui: fetch-json tui-clone tui-deps cmake-config cmake-build

tui-clean:
	rm -rf $(TUI_BUILD)

# =============================================================================
# TUI Repository Setup
# =============================================================================
.PHONY: tui-clone tui-deps tui-configure-raw tui-build-raw tui-full tui-manager tui-manager-v

tui-clone:
	@if ! command -v git >/dev/null 2>&1; then \
		echo "git not found; please install git to clone repositories"; \
		exit 127; \
	fi
	@if [ -d "TUI/TUIKit/.git" ] && git -C TUI/TUIKit rev-parse --git-dir >/dev/null 2>&1; then \
		echo "TUI/TUIKit already exists (valid git repo found), skipping clone"; \
	else \
		if [ -d "TUI/TUIKit" ]; then \
			echo "TUI/TUIKit exists but is not a valid git repo; cleaning up..."; \
			rm -rf TUI/TUIKit; \
		fi; \
		echo "Cloning TUIKit repository..."; \
		git clone https://github.com/skhelladi/TUIKit.git TUI/TUIKit; \
		if [ $$? -ne 0 ]; then \
			echo "Failed to clone TUIKit repository"; \
			exit 1; \
		fi; \
	fi

tui-deps: tui-clone
	@mkdir -p TUI/TUIKit/external
	@if ! command -v git >/dev/null 2>&1; then \
		echo "git not found; please install git to clone external dependencies"; \
		exit 127; \
	fi
	@# Clone FTXUI
	@if [ -d "TUI/TUIKit/external/ftxui/.git" ]; then \
		echo "external/ftxui already present, skipping clone"; \
	else \
		echo "Cloning FTXUI..."; \
		git clone https://github.com/ArthurSonzogni/FTXUI.git TUI/TUIKit/external/ftxui; \
		if [ $$? -ne 0 ]; then \
			echo "Failed to clone FTXUI repository"; \
			exit 1; \
		fi; \
	fi
	@# Clone ftxui-image-view
	@if [ -d "TUI/TUIKit/external/ftxui-image-view/.git" ]; then \
		echo "external/ftxui-image-view already present, skipping clone"; \
	else \
		echo "Cloning ftxui-image-view..."; \
		git clone https://github.com/ljrrjl/ftxui-image-view.git TUI/TUIKit/external/ftxui-image-view; \
		if [ $$? -ne 0 ]; then \
			echo "Failed to clone ftxui-image-view repository"; \
			exit 1; \
		fi; \
	fi
	@# Copy images to ftxui-image-view
	@echo "Preparing TUIKit externals (copying images and CMake files)..."
	@mkdir -p TUI/TUIKit/external/ftxui-image-view/imgs
	@if [ -d "docs/images" ]; then \
		cp -af docs/images/* TUI/TUIKit/external/ftxui-image-view/imgs/ || true; \
		echo "Copied docs/images to TUI/TUIKit/external/ftxui-image-view/imgs"; \
	else \
		echo "Warning: docs/images not found; skipping image copy"; \
	fi
	@# Copy top-level CMakeLists.txt
	@if [ -f "TUI_files/CMakeLists.txt" ]; then \
		mkdir -p TUI/TUIKit; \
		cp -f TUI_files/CMakeLists.txt TUI/TUIKit/CMakeLists.txt && echo "Copied TUI_files/CMakeLists.txt -> TUI/TUIKit/CMakeLists.txt"; \
	else \
		echo "Warning: TUI_files/CMakeLists.txt not found; skipping"; \
	fi
	@# Copy image dependency CMakeLists.txt
	@if [ -f "TUI_files/Cmake for Image dependency/CMAKELists.txt" ]; then \
		mkdir -p TUI/TUIKit/external/ftxui-image-view; \
		cp -f "TUI_files/Cmake for Image dependency/CMAKELists.txt" TUI/TUIKit/external/ftxui-image-view/CMakeLists.txt && echo "Copied image-dependency CMakeLists into ftxui-image-view"; \
	else \
		echo "Warning: TUI_files/Cmake for Image dependency/CMAKELists.txt not found; skipping"; \
	fi
	@# Download nlohmann/json
	@echo "Downloading nlohmann/json (v3.12.0) into external/json..."
	@mkdir -p TUI/TUIKit/external/json/nlohmann
	@if command -v wget >/dev/null 2>&1; then \
		wget -q -O TUI/TUIKit/external/json/nlohmann/json.hpp https://github.com/nlohmann/json/releases/download/v3.12.0/json.hpp; \
		if [ $$? -ne 0 ]; then \
			echo "Failed to download nlohmann/json.hpp via wget"; \
			exit 1; \
		fi; \
	else \
		curl -sSL -o TUI/TUIKit/external/json/nlohmann/json.hpp https://github.com/nlohmann/json/releases/download/v3.12.0/json.hpp; \
		if [ $$? -ne 0 ]; then \
			echo "Failed to download nlohmann/json.hpp via curl"; \
			exit 1; \
		fi; \
	fi
	@cp -f TUI/TUIKit/external/json/nlohmann/json.hpp TUI/TUIKit/external/json/json.hpp || true

tui-configure-raw:
	@mkdir -p TUI/TUIKit/build
	@if ! command -v cmake >/dev/null 2>&1; then \
		echo "cmake not found. Install it with 'brew install cmake' or from https://cmake.org/download/"; \
		exit 127; \
	fi
	@cd TUI/TUIKit/build && cmake ..

tui-build-raw:
	@if [ ! -d "TUI/TUIKit/build" ]; then \
		echo "Build directory not found. Run 'make tui-configure-raw' first."; \
		exit 1; \
	fi
	@cd TUI/TUIKit/build && cmake --build . --parallel $(CPU_CORES)

tui-full: tui-clone tui-deps tui-configure-raw tui-build-raw
	@echo "TUI build complete (tui-full)"

tui-manager: tui
	@if [ ! -f "TUI/TUIKit/build/TUI" ]; then \
		echo "TUI executable not found. Build may have failed."; \
		exit 1; \
	fi
	cd TUI/TUIKit/build && ./TUI

tui-manager-v: tui
	@if [ ! -f "TUI/TUIKit/build/TUI" ]; then \
		echo "TUI executable not found. Build may have failed."; \
		exit 1; \
	fi
	@if ! command -v valgrind >/dev/null 2>&1; then \
		echo "valgrind not found. Install it with 'brew install valgrind' or from your package manager."; \
		exit 127; \
	fi
	cd TUI/TUIKit/build && valgrind --leak-check=full --show-leak-kinds=all -s --track-origins=yes ./TUI


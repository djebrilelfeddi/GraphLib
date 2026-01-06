# Author: EL FEDDI DJEBRIL

CXX = g++
CXXFLAGS = -std=c++20 -Wall -Ofast

# Detect OS and set appropriate Boost library name
ifeq ($(OS),Windows_NT)
    BOOST_LIBS = -lboost_unit_test_framework-mt
    EXE_EXT = .exe
    RUN_PREFIX = 
    MKDIR = if not exist build mkdir build
    RMDIR = if exist build rmdir /s /q build
else
    BOOST_LIBS = -lboost_unit_test_framework
    EXE_EXT =
    RUN_PREFIX = ./
    MKDIR = mkdir -p build
    RMDIR = rm -rf build
endif

# Test targets
TESTS = test1 test2 test3 test4 test5 test6

.PHONY: all clean test testboost docs

all: $(TESTS)

# Build test executables
test%: tests/test%.cpp graph.hpp
	$(MKDIR)
	$(CXX) $(CXXFLAGS) -I. -o build/$@$(EXE_EXT) $<

# Boost tests
boost: tests/boosttests.cpp graph.hpp
	$(MKDIR)
	$(CXX) $(CXXFLAGS) -I. -o build/boosttests$(EXE_EXT) $< $(BOOST_LIBS)

clean:
	$(RMDIR)

# Run all tests
test: all
	@echo "=== test1 ===" 
	$(RUN_PREFIX)build/test1$(EXE_EXT)
	@echo "=== test2 ===" 
	$(RUN_PREFIX)build/test2$(EXE_EXT)
	@echo "=== test3 ===" 
	$(RUN_PREFIX)build/test3$(EXE_EXT)
	@echo "=== test4 ===" 
	$(RUN_PREFIX)build/test4$(EXE_EXT)
	@echo "=== test5 ===" 
	$(RUN_PREFIX)build/test5$(EXE_EXT)
	@echo "=== test6 ===" 
	$(RUN_PREFIX)build/test6$(EXE_EXT)

testboost: boost
	@echo "Running Boost tests..."
	$(RUN_PREFIX)build/boosttests$(EXE_EXT)

docs:
	doxygen Doxyfile

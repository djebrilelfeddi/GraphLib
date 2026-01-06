# Author: EL FEDDI DJEBRIL

CXX = g++
CXXFLAGS = -std=c++20 -Wall -Ofast

# Detect OS and set appropriate Boost library name
# Windows/MSYS2 uses -mt suffix since only mt is available on MSYS2, MINGW,.., Linux uses no suffix
ifeq ($(OS),Windows_NT)
    BOOST_LIBS = -lboost_unit_test_framework-mt
    EXE_EXT = .exe
    RUN_PREFIX = 
else
    BOOST_LIBS = -lboost_unit_test_framework
    EXE_EXT =
    RUN_PREFIX = ./
endif

# Targets
EXERCISES = exercice1 exercice2 exercice3 exercice4 exercice5 exercice6

.PHONY: all clean boost test testboost

all: $(EXERCISES)

exercice%: exercice%.cpp graph.hpp
	$(CXX) $(CXXFLAGS) -o $@$(EXE_EXT) $<

boost: boosttest.cpp graph.hpp
	$(CXX) $(CXXFLAGS) -o boosttest$(EXE_EXT) $< $(BOOST_LIBS)

clean:
	rm -f *.exe exercice1 exercice2 exercice3 exercice4 exercice5 exercice6 boosttest

test: all
	@echo "=== exercice1 ===" && $(RUN_PREFIX)exercice1$(EXE_EXT)
	@echo "=== exercice2 ===" && $(RUN_PREFIX)exercice2$(EXE_EXT)
	@echo "=== exercice3 ===" && $(RUN_PREFIX)exercice3$(EXE_EXT)
	@echo "=== exercice4 ===" && $(RUN_PREFIX)exercice4$(EXE_EXT)
	@echo "=== exercice5 ===" && $(RUN_PREFIX)exercice5$(EXE_EXT)
	@echo "=== exercice6 ===" && $(RUN_PREFIX)exercice6$(EXE_EXT)

testboost: boost
	@echo "Running Boost tests..."
	$(RUN_PREFIX)boosttest$(EXE_EXT)

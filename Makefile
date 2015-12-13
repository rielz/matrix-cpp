
CXX := clang++-3.7
GDB := gdb
FORMAT := clang-format-3.7

CXX_FLAGS += -std=c++14 -msse -msse2 -msse3 -Iinclude/
CXX_FLAGS += -Wall -Wextra -Wno-missing-braces
# -pedantic-errors

all: bin/run.elf

bin/run.elf: test/test.cpp $(wildcard include/*.hpp)
	$(CXX) $(CXX_FLAGS) -o bin/run.elf test/test.cpp
	
test: bin/run.elf test/unit.hpp
	@bin/run.elf
	
debug: bin/run.elf
	$(GDB) bin/run.elf
	
format:
	$(FORMAT) -i $(wildcard include/*.hpp)
	
clean:
	find bin -name "*.elf" -type f -delete
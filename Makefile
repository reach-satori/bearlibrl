CXX = clang++
EXE = build/test
SRC = $(wildcard src/*.cpp)
OBJ = $(SRC:src/%.cpp=build/%.o)
DEP = $(OBJ:%.o=%.d)
INC = $(shell pkg-config --cflags libnoise) -Iinclude
CXXFLAGS = $(INC) -Wfatal-errors -MMD -fPIC -std=c++14 -g -Wall -Wextra -Wpedantic
LDFLAGS = -lBearLibTerminal $(shell pkg-config --libs libnoise)

all: $(EXE)


$(EXE): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(EXE) $(LDFLAGS)

-include $(DEP)

build/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm $(EXE) $(OBJ) $(DEP)

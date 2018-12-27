CXX = clang++
EXE = build/test
SRC = $(wildcard src/*.cpp)
OBJ = $(SRC:src/%.cpp=build/%.o)
DEP = $(OBJ:%.o=%.d)
CXXFLAGS = -Iinclude -Wfatal-errors -Wall -MMD -fPIC -g -std=c++14
LDFLAGS = -Llibs -lBearLibTerminal

all: $(EXE)


$(EXE): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(EXE) $(LDFLAGS)

-include $(DEP)

build/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm $(EXE) $(OBJ) $(DEP)

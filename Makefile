CXX = g++
EXE = test
SRC = $(wildcard src/*.cpp)
OBJ = $(SRC:src/%.cpp=build/%.o)
DEP = $(OBJ:%.o=%.d)
CXXFLAGS = -Iinclude -Wfatal-errors -Wall -MMD -g
LDFLAGS = -Llibs -lBearLibTerminal

all: $(EXE)


$(EXE): $(OBJ)
	$(CXX) $(OBJ) -o $(EXE) $(LDFLAGS)

-include $(DEP)

build/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm $(EXE) $(OBJ)

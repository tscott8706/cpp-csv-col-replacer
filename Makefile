SRC_EXE = colReplacer
TEST_EXE = testColReplacer

SRC_DIR = src
TEST_DIR = test
OBJ_DIR = obj

SRC = $(wildcard $(SRC_DIR)/*.cpp)
SRC_NO_MAIN = $(filter-out main.cpp,$(SRC))
SRC_OBJ = $(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
SRC_OBJ_NO_MAIN = $(filter-out main.o,$(SRC_OBJ))

TEST = $(wildcard $(TEST_DIR)/*.cpp)
TEST_OBJ = $(TEST:$(TEST_DIR)/%.cpp=$(OBJ_DIR)/%.o)

CXXFLAGS += -Iinclude -Wall
LDFLAGS += -Llib
LDLIBS += -lm

.PHONY: all test clean

all: $(SRC_EXE)

test: $(TEST_EXE)

$(SRC_EXE): $(SRC_OBJ)
	$(CXX) $(LDFLAGS) $^ $(LDLIBS) -o $@

$(TEST_EXE): $(TEST_OBJ)
	$(CXX) $(LDFLAGS) $^ $(LDLIBS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(TEST_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ) $(SRC_EXE) $(TEST_EXE)

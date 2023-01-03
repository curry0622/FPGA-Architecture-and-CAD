CXX := g++
CXXFLAGS := -std=c++11 -O3 -march=native -pipe
LIBS := -lm
EXEC := topart
SRC_DIRS := .
SRCS := main.cpp $(wildcard $(SRC_DIRS:=/*.cpp))
OBJS := $(SRCS:.cpp=.o)
BM_PATH := ../benchmarks

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CXX) $(LIBS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(EXEC) $(OBJS)

verify: $(EXEC)
	./topart $(BM_PATH)/B$(b).txt tmp.out
	./verify $(BM_PATH)/B$(b).txt tmp.out

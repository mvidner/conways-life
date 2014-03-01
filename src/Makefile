CXXFLAGS = -g3 -Wall
all: conways_life
conways_life.o: conways_life.h
conways_life: conways_life.o main.o random.o
	$(CXX) $^ -o $@

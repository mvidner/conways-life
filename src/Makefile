CXXFLAGS = -g3 -O3 -Wall
all: conways_life
conways_life.o main.o: conways_life.h
OBJECTS = conways_life.o main.o random.o
conways_life: $(OBJECTS)
	$(CXX) $^ -o $@

clean:
	rm $(OBJECTS) conways_life

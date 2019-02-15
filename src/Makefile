#OPT_FLAGS= -g3 -O3
OPT_FLAGS= -g3
UBSAN_FLAGS = -fno-sanitize-recover -fsanitize=undefined -fsanitize=leak -fsanitize=address
CXXFLAGS = -Wall $(OPT_FLAGS) $(UBSAN_FLAGS)
LDFLAGS = $(UBSAN_FLAGS)
all: conways_life
conways_life.o main.o: conways_life.h
OBJECTS = conways_life.o main.o random.o
conways_life: $(OBJECTS)
	$(CXX) $(LDFLAGS) $^ -o $@

clean:
	-rm $(OBJECTS) conways_life

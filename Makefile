exec = lumalang.out
sources = $(wildcard src/*.c)
objects = $(sources:.c=.o)
flags = -g -I/include

$(exec): $(objects)
	g++ $(objects) $(flags) -o $(exec)

%.o: %.c include/%.h
	g++ -c $(flags) $< -o $@

clean:
	-rm *.out
	-rm src/*.o

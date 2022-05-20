exec = lumalang.out
sources = $(wildcard src/*.cpp)
objects = $(sources:.cpp=.o)
flags = -g -Wall -lm -ldl -fPIC -rdynamic -Iinclude

%.o: %.cpp
	g++ -std=c++11 ${flags} -c $< -o $@

$(exec): $(objects)
	g++ -std=c++11 -g $(objects) $(flags) -Iinclude -o $(exec)

clean:
	-rm *.out
	-rm src/*.o

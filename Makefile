cc = g++
prom = main
deps_universe = $(shell find ./lib/ -name "*.h")
src = $(shell find ./src/ -name "*.cpp")
obj = $(src:%.c=%.o)

$(prom): $(obj)
	$(cc) $(obj) -lpthread -o $(prom)

%.o: %.cpp $(deps) lib/universe.h main.cpp
	$(cc) -c $< -lpthread -o $@

main.o: main.cpp lib/universe.h
	$(cc) -c main.cpp -lpthread -o $@

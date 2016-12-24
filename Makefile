cc = g++
prom = main
VPATH = src:inc
deps = ./lib/bad.h ./lib/correct1.h ./lib/correct2.h
universe = ./lib/universe.h
srcs = bad.cpp correct1.cpp correct2.cpp

obj = $(src:%.c=%.o)

$(prom): $(obj)
	$(cc) $(obj) -lpthread -o $(prom)

%.o: %.cpp $(deps)
	$(cc) -c -MM $< -lpthread -o $@

main.o: main.cpp lib/universe.h
	$(cc) -c main.cpp -lpthread -o $@

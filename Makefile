#第一次使用 Makefile ，不太会写

cc = g++
prom = main
VPATH = src:inc
objs = main.o util.o bad.o correct1.o correct2.o

$(prom): $(objs)
	$(cc) $(objs) -lpthread -o $(prom)

bad.o: bad.cpp bad.h
	$(cc) -c -lpthread src/bad.cpp

correct1.o: correct1.cpp correct1.h
	$(cc) -c -lpthread src/correct1.cpp

correct2.o: correct2.cpp correct2.h
	$(cc) -c -lpthread src/correct2.cpp

util.o: util.cpp util.h bad.h correct1.h correct2.h
	$(cc) -c -lpthread src/util.cpp

main.o: main.cpp util.h
	$(cc) -c -lpthread main.cpp

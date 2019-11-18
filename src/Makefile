OBJS = Hashtable.o main.o MainUtils.o Database.o Hypercube.o CubeUtils.o cube_main.o
SOURCE = ../include/Hashtable.cpp main.cpp MainUtils.cpp \\ ../include/Database.cpp ../include/Hypercube.cpp cube_main.cpp CubeUtils.cpp
HEADER = ../include/Hashtable.h main.h MainUtils.hpp ../include/Database.hpp ../include/Hypercube.cpp CubeUtils.hpp
OUT = lsh cube
CC = g++
FLAGS = -g -c -std=c++11

cube : $(OBJS)
		$(CC) -g Hashtable.o Database.o Hypercube.o CubeUtils.o cube_main.o -o cube
lsh : $(OBJS)
		$(CC) -g Hashtable.o main.o MainUtils.o Database.o -o lsh
main.o: main.cpp
		$(CC) $(FLAGS) main.cpp
cube_main.o: cube_main.cpp
		$(CC) $(FLAGS) cube_main.cpp
CubeUtils.o : CubeUtils.cpp
		$(CC) $(FLAGS) CubeUtils.cpp
MainUtils.o : MainUtils.hpp
		$(CC) $(FLAGS) MainUtils.cpp
Hashtable.o: ../include/Hashtable.cpp
		$(CC) $(FLAGS) ../include/Hashtable.cpp
Database.o : ../include/Database.cpp
		$(CC) $(FLAGS) ../include/Database.cpp
Hypercube.o : ../include/Hypercube.cpp
		$(CC) $(FLAGS) ../include/Hypercube.cpp
clean:
		rm -f $(OBJS) $(OUT) out

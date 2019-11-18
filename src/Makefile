OBJS = CMDParser.o main.o Parser.o Database.o VectorParser.o
SOURCE = CMDParser.cpp main.cpp Parser.cpp Database.cpp VectorParser.cpp
HEADER = CMDParser.hpp main.hpp Parser.hpp Database.hpp VectorParser.hpp
OUT = cluster
CC = g++
FLAGS = -g -c -std=c++11

cluster : $(OBJS)
		$(CC) -g $(OBJS) -o cluster
main.o: main.cpp
		$(CC) $(FLAGS) main.cpp
CMDParser.o: CMDParser.cpp
		$(CC) $(FLAGS) CMDParser.cpp
Parser.o : Parser.cpp
		$(CC) $(FLAGS) Parser.cpp
Database.o : Database.cpp
		$(CC) $(FLAGS) Database.cpp
VectorParser.o : VectorParser.cpp
		$(CC) $(FLAGS) VectorParser.cpp

clean:
		rm -f $(OBJS) $(OUT) out

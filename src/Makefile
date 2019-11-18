OBJS = CMDParser.o main.o Parser.o Database.o VectorParser.o Item.o Vector.o test.o
TESTOBJS = CMDParser.o  Parser.o Database.o VectorParser.o Item.o Vector.o test.o
SOURCE = CMDParser.cpp main.cpp Parser.cpp Database.cpp VectorParser.cpp Item.cpp Vector.cpp test.cpp
HEADER = CMDParser.hpp main.hpp Parser.hpp Database.hpp VectorParser.hpp Item.hpp Vector.hpp
OUT = cluster test
CC = g++
FLAGS = -g -c -std=c++11

cluster : $(OBJS)
		$(CC) -g $(OBJS) -o cluster
test : $(TESTOBJS)
		$(CC) -g $(TESTOBJS) -o ../test/test
test.o : ../test/test.cpp
		$(CC) $(FLAGS) ../test/test.cpp
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
Item.o : Item.cpp
		$(CC) $(FLAGS) Item.cpp
Vector.o : Vector.cpp
		$(CC) $(FLAGS) Vector.cpp

clean:
		rm -f $(OBJS) $(OUT) out

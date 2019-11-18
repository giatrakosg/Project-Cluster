OBJS = CMDParser.o main.o
SOURCE = CMDParser.cpp main.cpp
HEADER = CMDParser.hpp main.hpp
OUT = cluster
CC = g++
FLAGS = -g -c -std=c++11

cluster : $(OBJS)
		$(CC) -g $(OBJS) -o cluster
main.o: main.cpp
		$(CC) $(FLAGS) main.cpp
CMDParser.o: CMDParser.cpp
		$(CC) $(FLAGS) CMDParser.cpp
clean:
		rm -f $(OBJS) $(OUT) out

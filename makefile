OBJS	= infix.o function.o main1.o number.o stack.o
SOURCE	= infix.c function.c main1.c number.c stack.c
HEADER	= infix.h function.h number.h stack.h
OUT	= 
CC	 = gcc
FLAGS	 = -g -c -Wall
LFLAGS	 = 

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

infix.o: infix.c
	$(CC) $(FLAGS) infix.c 

function.o: function.c
	$(CC) $(FLAGS) function.c 

main1.o: main1.c
	$(CC) $(FLAGS) main1.c 

number.o: number.c
	$(CC) $(FLAGS) number.c 

stack.o: stack.c
	$(CC) $(FLAGS) stack.c 


clean:
	rm -f $(OBJS) $(OUT)
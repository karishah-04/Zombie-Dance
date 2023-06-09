OBJS = zombie_shah.o hw5_shah_karina.o 
CC = g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)

exe: $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o exe

zombie_shah.o: zombie_shah.h zombie_shah.cpp 
	$(CC) $(CFLAGS) zombie_shah.cpp

hw5_shah_karina.o: hw5_shah_karina.cpp zombie_shah.h linkedlist_shah.hpp
	$(CC) $(CFLAGS) hw5_shah_karina.cpp

clean:
	rm *.o *~ exe

tar:
	tar –cvf hw5_shah_karina.cpp linkedlist_shah.hpp zombie_shah.h zombie_shah.cpp

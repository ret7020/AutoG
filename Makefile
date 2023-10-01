CC = /bin/gcc
NAME = auto_gcc
SOURCES = main.cpp
LIBS = ncurses


build:
	$(CC) -O3 -o $(NAME) $(SOURCES) -l$(LIBS)

clean:
	rm auto_gcc
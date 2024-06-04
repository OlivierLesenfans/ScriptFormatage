CFLAGS = -g -Wall -Wextra -pedantic -Wno-unused-parameter
CC = gcc -I./include
OBJETS = bin
SOURCE = src


all: $(PROGRAMS)

$(OBJETS)/dstring.o: $(SOURCE)/dstring.c
	$(CC) $(CFLAGS) -c -o $@ $^
$(OBJETS)/format.o: $(SOURCE)/entree.c
	$(CC) $(CFLAGS) -c -o $@ $^
format: $(OBJETS)/format.o $(OBJETS)/dstring.o
	$(CC) $(CFLAGS) -o $@ $^
	
clean:
	rm -f $(OBJETS)/*.o
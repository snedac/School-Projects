OBJ = main.o connect.o heroes.o flyer.o escape.o hollow.o spectator.o
EXE = a5
CC = gcc -Wall

$(EXE): $(OBJ)
	$(CC) -o $(EXE) $(OBJ)

main.o: main.c defs.h
	$(CC) -c main.c

connect.o: connect.c defs.h
	$(CC) -c connect.c

heroes.o: heroes.c defs.h
	$(CC) -c heroes.c

flyer.o: flyer.c defs.h
	$(CC) -c flyer.c

escape.o: escape.c defs.h
	$(CC) -c escape.c

hollow.o: hollow.c defs.h
	$(CC) -c hollow.c

spectator.o: spectator.c defs.h
	$(CC) -c spectator.c

clean:
	rm -f $(EXE) $(OBJ)

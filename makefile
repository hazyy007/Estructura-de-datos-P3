CC = gcc
CFLAGS = -Wall -g
EXE = p3_e1
VALGRIND = valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all

all: $(EXE)

$(EXE): p3_e1.o queue.o radio.o music.o
	$(CC) $(CFLAGS) -o $@ $^

p3_e1.o: p3_e1.c queue.h radio.h music.h
	$(CC) $(CFLAGS) -c p3_e1.c

queue.o: queue.c queue.h types.h
	$(CC) $(CFLAGS) -c queue.c

radio.o: radio.c radio.h music.h
	$(CC) $(CFLAGS) -c radio.c

music.o: music.c music.h types.h
	$(CC) $(CFLAGS) -c music.c
run: $(EXE)
	./$(EXE) radio.txt

# Regla de ejecución con Valgrind
runv: $(EXE)
	$(VALGRIND) ./$(EXE) radio.txt

clean:
	rm -f *.o $(EXE)

.PHONY: all clean run_v
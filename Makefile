all: main.o graphics.o input.o logic.o
	gcc main.o graphics.o input.o logic.o -o main -lSDL -lSDL_image

main.o: main.c
	gcc -c main.c

graphics.o: graphics.h
	gcc -c graphics.c
	
input.o: input.h
	gcc -c input.c

logic.o: logic.h
	gcc -c logic.c
clean:
	rm main.o graphics.o input.o logic.o
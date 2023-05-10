all: main2
main1:
	gcc -Wall -g -o main matriz.c list.c node.c main.c -lm
main2: main1
	gcc -Wall -g -o main2 matriz.c list.c node.c main2.c -lm
clean:
	rm -f main main2 binario.bin
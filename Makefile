roboking_unpacker : main.o util.o
	gcc -o roboking_unpacker  main.o util.o

main.o : main.c
	gcc -c -o main.o main.c

util.o : util.c
	gcc -c -o util.o util.c
clean:
	rm -rf *.o roboking_unpacker

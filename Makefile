roboking_unpacker : main.o
	gcc -o roboking_unpacker  main.o

main.o : main.c
	gcc -c -o main.o main.c

clean:
	rm -rf *.o roboking_unpacker

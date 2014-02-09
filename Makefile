# Make file for project 1


all : crop bw overlay colorshift

clean : 
	rm *.o


openFile.o : openFile.c 
	gcc -ansi -pedantic -g -c openFile.c

saveFile.o : saveFile.c
	gcc -ansi -pedantic -g -c saveFile.c

crop.o : crop.c openFile.o saveFile.o
	gcc -ansi -pedantic -g -c crop.c

bw.o : bw.c openFile.o saveFile.o
	gcc -ansi -pedantic -g -c bw.c

overlay.o : overlay.c openFile.o saveFile.o
	gcc -ansi -pedantic -g -c overlay.c

colorshift.o : colorshift.c saveFile.o
	gcc -ansi -pedantic -g -c colorshift.c

crop : crop.o openFile.o
	gcc -ansi -pedantic -o crop crop.o openFile.o saveFile.o
	
bw : bw.o openFile.o
	gcc -ansi -pedantic -o bw bw.o openFile.o saveFile.o

overlay : overlay.o openFile.o
	gcc -ansi -pedantic -o overlay overlay.o openFile.o saveFile.o

colorshift : colorshift.o openFile.o
	gcc -ansi -pedantic -o colorshift colorshift.o openFile.o saveFile.o

test : test.c
	gcc -ansi -pedantic -o test test.c

# Make file for project 1


all : crop bw overlay colorshift

clean : 
	rm *.o


openFile.o : openFile.c 
	gcc -ansi -pedantic -g -c openFile.c

saveFile.o : saveFile.c
	gcc -ansi -pedantic -g -c saveFile.c

image.o : image.c
	gcc -ansi -pedantic -g -c image.c

crop.o : crop.c openFile.o saveFile.o image.o
	gcc -ansi -pedantic -g -c crop.c

bw.o : bw.c openFile.o saveFile.o image.o
	gcc -ansi -pedantic -g -c bw.c

overlay.o : overlay.c openFile.o saveFile.o image.o
	gcc -ansi -pedantic -g -c overlay.c

colorshift.o : colorshift.c saveFile.o image.o
	gcc -ansi -pedantic -g -c colorshift.c

crop : crop.o openFile.o
	gcc -ansi -pedantic -o crop crop.o openFile.o saveFile.o image.o
	
bw : bw.o openFile.o
	gcc -ansi -pedantic -o bw bw.o openFile.o saveFile.o image.o

overlay : overlay.o openFile.o
	gcc -ansi -pedantic -o overlay overlay.o openFile.o saveFile.o image.o

colorshift : colorshift.o openFile.o
	gcc -ansi -pedantic -o colorshift colorshift.o openFile.o saveFile.o image.o

test.o : test.c
	gcc -ansi -pedantic -g -c test.c

test : test.o
	gcc -ansi -pedantic -o test test.o openFile.o saveFile.o

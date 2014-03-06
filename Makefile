# Make file for project 1


all : bw colorshift meme

clean : 
	rm *.o bw crop colorshift overlay 


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

#crop : crop.o openFile.o
#	gcc -ansi -pedantic -o crop crop.o openFile.o saveFile.o image.o

	
bw : bw.o openFile.o
	gcc -ansi -pedantic -o bw bw.o openFile.o saveFile.o image.o

#overlay : overlay.o openFile.o
#	gcc -ansi -pedantic -o overlay overlay.o openFile.o saveFile.o image.o

colorshift : colorshift.o openFile.o
	gcc -ansi -pedantic -o colorshift colorshift.o openFile.o saveFile.o image.o

font.o : font.h font.c letter.h
	gcc -ansi -pedantic -g -c font.c

meme.o : meme.c
	gcc -ansi -pedantic -g -c meme.c

meme : font.o meme.o image.o crop.o overlay.o
	gcc -ansi -pedantic -o meme font.o meme.o image.o crop.o overlay.o

tarball : 
	tar czf 978378401.tar.gzip *.c *.h Makefile README
test : test.c font.o crop.o overlay.o
	gcc -ansi -pedantic -g -o test test.c font.o crop.o overlay.o

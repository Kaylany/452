all:	cipher

cipher:	cipher.o DES.o AES.o mainfunctions.o errorhandling.o
	g++ cipher.o DES.o AES.o mainfunctions.o errorhandling.o -o cipher -lcrypto

cipher.o:	cipher.cpp
	g++ -g -c cipher.cpp

DES.o:	DES.cpp DES.h
	g++ -g -c DES.cpp

AES.o:	AES.cpp AES.h
	g++ -g -c AES.cpp

mainfunctions.o:	mainfunctions.cpp mainfunctions.h
	g++  -g -c mainfunctions.cpp

errorhandling.o:	errorhandling.cpp errorhandling.h
	g++  -g -c errorhandling.cpp

clean:
	rm -rf *.o cipher

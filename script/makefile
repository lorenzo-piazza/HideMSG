CXXFLAGS = -std=c++17

CXXINCLUDES = .

hidemsg.exe: hidemsg.o inputparser.o encoder.o encoder111.o encoder422.o bitmapfilehandler.o cipherhandler.o
	g++ $(CXXFLAGS) hidemsg.o inputparser.o encoder.o encoder111.o encoder422.o bitmapfilehandler.o cipherhandler.o -o hidemsg.exe -I../crytopp/ -L../cryptopp -lcryptopp

hidemsg.o: hidemsg.cpp hidemsg.h
	g++ $(CXXFLAGS) -I$(CXXINCLUDES) -c hidemsg.cpp -o hidemsg.o

encoder422.o: encoder422.cpp encoder422.h
	g++ $(CXXFLAGS) -I$(CXXINCLUDES) -c encoder422.cpp -o encoder422.o

encoder111.o: encoder111.cpp encoder111.h
	g++ $(CXXFLAGS) -I$(CXXINCLUDES) -c encoder111.cpp -o encoder111.o

encoder.o: encoder.cpp encoder.h
	g++ $(CXXFLAGS) -I$(CXXINCLUDES) -c encoder.cpp -o encoder.o

inputparser.o: inputparser.cpp inputparser.h
	g++ $(CXXFLAGS) -I$(CXXINCLUDES) -c inputparser.cpp -o inputparser.o

bitmapfilehandler.o: bitmapfilehandler.cpp bitmapfilehandler.h
	g++ $(CXXFLAGS) -I$(CXXINCLUDES) -c bitmapfilehandler.cpp -o bitmapfilehandler.o

cipherhandler.o: cipherhandler.cpp cipherhandler.h
	g++ $(CXXFLAGS) -I$(CXXINCLUDES) -c cipherhandler.cpp -o cipherhandler.o

.PHONY: clean doc all

clean:
	rm *.o *.exe

doc:
	doxygen

all: main.exe doc
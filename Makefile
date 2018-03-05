all: lcs

lcs: Timer.h
	g++ -Wall -std=c++11 lcs.cpp -o lcs

clean:
	rm -rf lcs

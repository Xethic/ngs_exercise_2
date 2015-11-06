all: kmer

kmer: kmer_finder.o
	g++ -o kmer kmer_finder.o

kmer_finder.o: kmer_finder.cpp
	g++ -c kmer_finder.cpp

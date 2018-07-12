CXX = g++
CXXFLAGS = -g -std=c++11
RM = rm

all: decoder encoder

clean: 
	$(RM) *.o encoder decoder

encoder: encoder.o pairingheap.o binaryheap.o fourarycoheap.o
	$(CXX) $(CXXFLAGS) -o encoder encoder.o pairingheap.o binaryheap.o fourarycoheap.o


encoder.o: encoder.cpp pairingheap.h binaryheap.h fourarycoheap.h
	$(CXX) $(CXXFLAGS) -c encoder.cpp


pairingheap.o: pairingheap.h	

binaryheap.o: binaryheap.h

fourarycoheap.o: fourarycoheap.h

decoder: decoder_huffman.o decoder.o encoder.o
	$(CXX) $(CXXFLAGS) -o decoder decoder_huffman.o decoder.o 

decoder_HMT.o: decoder_huffman.cpp decoder.h 
	$(CXX) $(CXXFLAGS) -c decoder_huffman.cpp

decoder.o: decoder.h

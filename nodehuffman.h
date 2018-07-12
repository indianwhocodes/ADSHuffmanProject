#ifndef NODEHUFFMAN_H_
#define NODEHUFFMAN_H_

#include<cstddef>
struct node_huffman{
int data;
unsigned int freq;
node_huffman const			*left;
node_huffman const			*right;
	
node_huffman(  int const &data,
unsigned int const &freq,
node_huffman const* left,
node_huffman const* right):
		data(data),
		freq(freq),
		left(left),
		right(right){}
	
bool operator<(const node_huffman& rhs) const{
		return freq < rhs.freq;
	}
};
#endif /* NODEHUFFMAN_H_ */

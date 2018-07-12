#ifndef BINARYHEAP_H_
#define BINARYHEAP_H_

#include <vector>
#include "nodehuffman.h"

class binaryheap{
private:
std::vector<node_huffman const*> vec;

int parent(int i);
int lchild(int i);
int rchild(int i);

void heapup(int i);
void heapdown(int i);

public:
binaryheap(std::vector<node_huffman const *> &nums);

void remove_min();
void insert(node_huffman const* newele);
node_huffman const* minextract();
int size();
};

#endif /* BINARYHEAP_H_ */

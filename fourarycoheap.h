/* fourarycoHeap.h */
#ifndef FOURARYCOHEAP_H
#define FOURARYCOHEAP_H_
#include <vector>
#include "nodehuffman.h"

class fourarycoheap{
private:
std::vector<node_huffman const*> vec;
void heapup(int i);
void heapdown(int i);
int parent(int i);
int k_child(int i, int k);
int min_ch(int i);

public:
int size();
void remove_min();
void insert(node_huffman const* ele);
fourarycoheap(std::vector<node_huffman const *> &numbers);

node_huffman const* minextract();

};
#endif /*FOURARYCOHEAP_H_*/

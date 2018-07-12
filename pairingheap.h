/*pairingheap.h*/
#ifndef PAIRINGHEAP_H_
#define PAIRINGHEAP_H_
#include <cstddef>
#include <vector>
#include "nodehuffman.h"

class node_pair
{
	public:
	node_pair *prev;
	node_pair *sibling_next;
	node_pair *lchild;
	node_huffman const *nodehuffman;

	node_pair(node_huffman const* huff_node):
			nodehuffman(huff_node),
			lchild(NULL),
			sibling_next(NULL),
			prev(NULL)
			{ }
};

class pairingheap
{
private:

void meld(node_pair * &fst, node_pair *sec);
node_pair *sib_combine(node_pair *sibling_first);
void mem_reclaim(node_pair *m);
int vecsize;
node_pair *root;
std::vector<node_pair*> pnode_list;


public:
pairingheap();
pairingheap(std::vector<node_huffman const*> & numbers);
bool isEmpty();
bool isFull();
node_huffman const *min_find();
node_pair *insert(node_huffman const* i);
void remove_min();
void empty();
int size();
};
#endif /* PAIRINGHEAP_H_ */

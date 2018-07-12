#include <iostream>
#include <cstdlib>
#include <vector>

#include "nodehuffman.h"
#include "pairingheap.h"
using namespace std;

void pairingheap::meld(node_pair * &first, node_pair *second)
{

    if (*(second->nodehuffman) < *(first->nodehuffman))
    {
        second->prev = first->prev;
        first->prev = second;
        first->sibling_next = second->lchild;
        if (first->sibling_next != NULL)
            first->sibling_next->prev = first;
        second->lchild = first;
        first = second;
    }
    else
    {
        second->prev = first;
        first->sibling_next = second->sibling_next;
        if (first->sibling_next != NULL)
            first->sibling_next->prev = first;
        second->sibling_next = first->lchild;
        if (second->sibling_next != NULL)
            second->sibling_next->prev = second;
        first->lchild = second;
    }
    if (second == NULL)
        {
        	return;
        }
}

node_pair *pairingheap::sib_combine(node_pair *sibling_first)
{
    if (sibling_first->sibling_next == NULL)
        return sibling_first;
    static vector<node_pair *> t_arr(5);
    int sib_nums = 0;
    for (; sibling_first != NULL; sib_nums++){
        if (sib_nums == t_arr.size())
            t_arr.resize(sib_nums * 2);
        t_arr[sib_nums] = sibling_first;
        sibling_first->prev->sibling_next = NULL;
        sibling_first = sibling_first->sibling_next;
    }
    if (sib_nums == t_arr.size())
        t_arr.resize(sib_nums + 1);
    t_arr[sib_nums] = NULL;
    int i = 0;
    for (; i + 1 < sib_nums; i += 2)
        meld(t_arr[i], t_arr[i + 1]);
    int j = i - 2;
    if (j == sib_nums - 3)
        meld (t_arr[j], t_arr[j + 2]);
    for (; j >= 2; j -= 2)
        meld(t_arr[j - 2], t_arr[j] );
    return t_arr[0];
}

void pairingheap::mem_reclaim(node_pair * t)
{
    if (t != NULL)
    {
        mem_reclaim(t->lchild);
        mem_reclaim(t->sibling_next);
        delete t;
    }
}

pairingheap::pairingheap()
{
	vecsize=0;
    root = NULL;
}


bool pairingheap::isEmpty()
{
    return root == NULL;
}

bool pairingheap::isFull()
{
    return false;
}

node_huffman const* pairingheap::min_find()
{
    return root->nodehuffman;
}

node_pair *pairingheap::insert(node_huffman const* x)
{
   node_pair *nnode = new node_pair(x);

    if (root == NULL)
    {
        root = nnode;
    }
    else{
        meld(root, nnode);
    }
    ++vecsize;
    return nnode;
}

pairingheap::pairingheap(vector<node_huffman const*> &numbers){
	root=NULL;
	vecsize=0;
	for(auto ele:numbers){
		insert(ele);
	}
	std::cout<<"\n";
}

void pairingheap::remove_min()
{
    node_pair *root_prev = root;
    if (root->lchild == NULL)
        root = NULL;
    else
        root = sib_combine(root->lchild);
    --vecsize;
    delete root_prev;
}


void pairingheap::empty()
{
    mem_reclaim(root);
    root = NULL;
}

int pairingheap::size(){
	return vecsize;
}


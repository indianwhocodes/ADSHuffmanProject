#include <iostream>
#include <algorithm>
#include "binaryheap.h"

void binaryheap::heapup(int i)
{
int p=parent(i);
	if(i<vec.size() && p>=0 && (*vec[i]< *vec[p]))
	{
		std::swap(vec[p],vec[i]);
		heapup(p);
	}
}

void binaryheap::heapdown(int i){

	int left=lchild(i);
	int right=rchild(i);
	int smallest=i; /* cited from the CLRS Textbook on binary heap */
	if(smallest!=i)
		{
			std::swap(vec[i],vec[smallest]);
			heapdown(smallest);
		}

	if(left<vec.size() && (*(vec[left])< *(vec[smallest])))
	{
		smallest=left;
	}
	if(right<vec.size() && (*(vec[right]) < *(vec[smallest])))
	{
		smallest=right;
	}
}

void binaryheap::insert(node_huffman const* newele){

	vec.push_back(newele);
	heapup(vec.size()-1);
}

void binaryheap::remove_min(){
	int len=vec.size()-1;
	if(len>=0){
		vec[0]=vec[len];
		vec.pop_back();
		heapdown(0);
	}
}

node_huffman const* binaryheap::minextract(){
	if(vec.size()==0){
		return NULL;
	}

	return vec[0];
}


binaryheap::binaryheap(std::vector<node_huffman const*> &nodes_hufftree){
	for(node_huffman const * node:nodes_hufftree){
		insert(node);
	}
}

int binaryheap::parent(int i){
	return (i-1)/2;
}


int binaryheap::lchild(int i){
	return 2*i+1;
}

int binaryheap::rchild(int i){
	return 2*i+2;
}

int binaryheap::size(){
	return vec.size();
}



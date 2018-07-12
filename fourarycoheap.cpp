/* fourarycoheap.cpp*/
#include <iostream>
#include <algorithm>
#include "fourarycoheap.h"

fourarycoheap::fourarycoheap(std::vector<node_huffman const*> &hnodes){

	for(int i=0;i<3;i++){
		insert(NULL);
	}
/*this is to make the four-way heap cache optimized*/
	for(node_huffman const * huff_node:hnodes){
		insert(huff_node);
	}
}

void fourarycoheap::heapup(int i){

    node_huffman const* j = vec[i];
    for (; i > 3 && *j < *(vec[parent(i)]); i = parent(i))
        vec[i] = vec[parent(i)];
    vec[i] = j;
}

void fourarycoheap::heapdown(int i){

	int ch;
	node_huffman const* j = vec[i];
	for ( ; k_child(i, 1) < vec.size(); i = ch)
	{
		ch = min_ch( i );
		if (*(vec[ch]) < *j)
			vec[i] = vec[ch];
		else
			break;
	}
	vec[i] = j;
}

int fourarycoheap::parent(int i){

	return i/4+2;
}


int fourarycoheap::k_child(int i, int j){
		return (4 * (i-2) + (j-1));
}

int fourarycoheap::min_ch(int i)
{
    int smallest_child = k_child(i, 1);
    int j = 2;
    int cand_child = k_child(i, j);
    while ((j <= 4) && (cand_child < vec.size()))
    {
        if (*(vec[cand_child]) < *(vec[smallest_child]))
        	smallest_child = cand_child;
        j++;
        cand_child = k_child(i, j);
    }
    return smallest_child;
}


int fourarycoheap::size(){
	return vec.size();
}

void fourarycoheap::remove_min(){
	int len=vec.size()-1;
	if(len >=3){
		vec[3]=vec[len];
		vec.pop_back();
		heapdown(3);
	}
}

void fourarycoheap::insert(node_huffman const* newelement){

	vec.push_back(newelement);
	heapup(vec.size()-1);
}

node_huffman const* fourarycoheap::minextract(){
	if(vec.size()==3){
		return NULL;
	}

	return vec[3];
}

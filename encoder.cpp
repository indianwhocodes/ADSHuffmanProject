#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <cstddef>
#include <ctime>
#include <stack>
#include <string>
#include <queue>
#include "binaryheap.h"
#include "fourarycoheap.h"
#include "pairingheap.h"
#include "nodehuffman.h"

void FillFreqMapFromFile(
	std::ifstream &infile,
	std::unordered_map<int,unsigned int> &freq_map){

	int number;
	while(infile >> number){
		auto it_f=freq_map.find(number);
		if(it_f!=freq_map.end()){
			it_f->second++;	
		} else {
			freq_map[number]=1;
		}
	}
}

void CreateHnodeVecFromFreqMap(	
	std::unordered_map<int,unsigned int> const &freq_map,
	std::vector<node_huffman const*> &vec){
	
	for(auto it:freq_map){
		node_huffman* huff_node=new node_huffman(it.first,it.second,NULL,NULL);
		vec.push_back(huff_node);	
	}
}

node_huffman const* BuildTreeFheap(
		std::unordered_map<int,unsigned int> const &freq_map){

	std::vector<node_huffman const*> vec;
	CreateHnodeVecFromFreqMap(freq_map,vec);

	fourarycoheap fourarycoheap_obj(vec);

	unsigned int freq;

	while (fourarycoheap_obj.size() > 4)
	{
		node_huffman const *left =fourarycoheap_obj.minextract();
		fourarycoheap_obj.remove_min();


		node_huffman const *right = fourarycoheap_obj.minextract();
		fourarycoheap_obj.remove_min();


		freq=left->freq + right->freq;

		node_huffman const* parent = new node_huffman(-1,freq, left, right );
		fourarycoheap_obj.insert(parent);

	}
	return fourarycoheap_obj.minextract();
}

node_huffman const* BuildTreeBheap(
		std::unordered_map<int,unsigned int> const &freq_map){

	std::vector<node_huffman const*> vec;
	CreateHnodeVecFromFreqMap(freq_map,vec);

	binaryheap binaryheap_obj(vec);

	unsigned int freq;

	int count=0;
	while ((binaryheap_obj.size() > 1))
	{	count++;

	node_huffman const *left =binaryheap_obj.minextract();
		binaryheap_obj.remove_min();

		
		node_huffman const *right = binaryheap_obj.minextract();
		binaryheap_obj.remove_min();

		
		freq=left->freq + right->freq;

		node_huffman const* parent = new node_huffman(-1,freq, left, right );
		binaryheap_obj.insert(parent);

	}
	return binaryheap_obj.minextract();
}


node_huffman const* BuildTreePheap(
		std::unordered_map<int,unsigned int> const &freq_map){

	std::vector<node_huffman const*> vec;
	CreateHnodeVecFromFreqMap(freq_map,vec);

	pairingheap pairingheap_obj(vec);

	unsigned int freq;

	while ((pairingheap_obj.size() > 1))
	{
		node_huffman const *left =pairingheap_obj.min_find();
		pairingheap_obj.remove_min();
		node_huffman const *right = pairingheap_obj.min_find();
		pairingheap_obj.remove_min();

		freq=left->freq + right->freq;

		node_huffman const* parent = new node_huffman(-1,freq, left, right );
		pairingheap_obj.insert(parent);
	}
	return pairingheap_obj.min_find();
}

void printCodes(
		node_huffman const *root,
		std::string str,
		std::unordered_map<int,std::string> &code_table_map
		)
{

    if (!root)
        return;

    if (root->data != -1){

    	code_table_map[root->data]=str;
    }

    printCodes(root->left, str + "0",code_table_map);
    printCodes(root->right, str + "1",code_table_map);
}


char setBit(char num, int i){
	return num|(1<<i);
}

void compress(std::string &value,std::vector<char> &result){

	char res=0;
	char str;
	for(long i=0;i<value.size();){
		res=0;
		for(int j=7;j>=0;j--){
			if(value[i]=='1')
				res=setBit(res,j);
			i++;
		}
		result.push_back(res);
	}
}

void binfilecreate(
		std::unordered_map<int,std::string> &code_table_map,
		char *filename,
		char const *out
		){

	std::ifstream infile (filename);
	std::ofstream onfile (out,std::ios::out | std::ios::binary);

	int number;
	std::string value;
	while(infile >> number){
		auto it_f=code_table_map.find(number);
		if(it_f!=code_table_map.end()){
			value+=it_f->second;

		} else {
			std::cout<<"-----------This cannot happen : "<<(it_f->first)<<std::endl;
		}
	}
	std::cout<<"File writing reached"<<std::endl;
	std::vector<char> result;
	compress(value,result);
	std::cout<<"Result size:"<<result.size()<<", String size:"<<value.size()<<std::endl;
	char *res=&result[0];
	onfile.write(res,result.size());
	onfile.close();
	infile.close();

}

int main(int argc, char *argv[]){

	if ( argc != 2 ){
		std::cout<<"Usage:./"<<argv[0]<<" <input_file_name>\n";
		return 0;
	}

	std::ifstream infile (argv[1]);
	if ( !infile.is_open() ){
	  std::cout<<"Could not open file\n";
	  return 0;
	}

	std::unordered_map<int,unsigned int> freq_map;

	
	FillFreqMapFromFile(infile,freq_map);

	infile.close();
	clock_t start_time;


//	std::cout<<"Huffman binary heap:"<<std::endl;
//	start_time=clock();
//	hnode const* rootb=BuildTreeBheap(freq_map);
//	std::unordered_map<int,std::string> code_table_map1;
//	printCodes(rootb,"",code_table_map1);
//	std::cout << "Time using binary heap (microsecond):  " << (clock() - start_time)/10 << std::endl;


	std::string of;
	std::cout<<"Huffman 4way heap:"<<std::endl;
	start_time=clock();
	node_huffman const* rootf=BuildTreeFheap(freq_map);
	std::unordered_map<int,std::string> code_table_map2;
	printCodes(rootf,"",code_table_map2);
	of="encoded.bin";
	char const *o2=of.c_str();
	binfilecreate(code_table_map2,argv[1],o2);
	std::cout << "Time using 4-way heap (microsecond):  " << (clock() - start_time)/10 << std::endl;
	std::cout<<"Encode table:"<<std::endl;
	std::string code_table_file_name="code_table.txt";
	std::ofstream onfile (code_table_file_name,std::ios::out);
	for(auto it:code_table_map2){
		onfile<<it.first<<" "<<it.second<<"\n";
	}

	onfile.close();

//	std::cout<<"Huffman pairing heap:"<<std::endl;
//	start_time=clock();
//	hnode const* rootp=BuildTreePheap(freq_map);
//	std::unordered_map<int,std::string> code_table_map3;
//	printCodes(rootp,"",code_table_map3);
//	std::cout << "Time using pairing heap (microsecond):  " << (clock() - start_time)/10 << std::endl;


	return 0;
}


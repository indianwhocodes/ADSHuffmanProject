
#include <iostream>
#include <string>
using namespace std;

struct Node {
struct Node *right = NULL;
struct Node *left = NULL;
int value;
bool isLeaf = false;
};


class Decode {
	private:
	Node* root;

public:
Node* getRoot();
void addleaf_at(int value, string binaryString);
int extract(string binaryString);

Decode() {
root = new (struct Node);
}
};


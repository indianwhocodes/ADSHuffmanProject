#include <iostream>
#include <string>
#include <fstream>
#include "decoder.h"

using namespace std;

int main(int char_arg, char const *var_arg[]) {

   if ( char_arg != 3 ){
	cout<<"Usage: "<<var_arg[0]<<" encoded.bin code_table.txt"<<endl;
	return 0;
    }

    std::ifstream f (var_arg[1],ios::binary | ios::in);
    if ( !f.is_open() ){
	  std::cout<<"Could not open file\n";
	  return 0;
    }

    ifstream ct(var_arg[2], ios::in);
    if ( !ct.is_open() ){
	  std::cout<<"Could not open file\n";
	  return 0;
    }

    Decode D = Decode();
    int x; string y;
    cout << "Building Decode Tree" << endl;
    while (ct >> x >> y) {
        D.addleaf_at(x, y);
    }

    cout << "Decoding binary file" << endl;
    ofstream onfile ("decoded.txt",std::ios::out);

    char j;
    string res;
    while (f.get(j)) {
        for (int i = 7; i >= 0; i--) {
            int k = (j >> i) & 1;
            res.append(to_string(k));
            if (D.extract(res) != -1)
            {
                onfile << D.extract(res) << endl;
                res = "";
            }
        }
    }
    onfile.close();
    f.close();
    ct.close();
    return 0;
}


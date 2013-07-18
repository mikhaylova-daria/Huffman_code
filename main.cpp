#include "libr.h"
#include "classes.h"


int main()
{
    string file_name;
    file_name = "test.txt";
    unordered_map<char, int> count_characters;
    try {
        count_characters = count_char(file_name);
    } catch (my_exception exp) {
        cerr << exp.what();
        return 1;
    }
//    unordered_map<char, int>::iterator itr1;
//    for (itr1 = count_characters.begin(); itr1 != count_characters.end(); ++itr1) {
//        cout << itr1->first <<  "-" << itr1->second << endl;
//    }
    Huffman_tree tree (count_characters);
    unordered_map<char, vector<int> > code = tree.coding();
    key_file(code, file_name, writing(code, file_name));
//    unordered_map<char, vector<int> >::iterator itr;
//        for (itr = code.begin(); itr != code.end(); ++itr) {
//            cout << itr->first <<  "#";
//            vector<int>::iterator itr2;
//            for (itr2 = itr->second.begin(); itr2 != itr->second.end(); ++itr2) {
//                cout << *itr2;
//            }
//            cout<<endl;
//        }
    return 0;
}


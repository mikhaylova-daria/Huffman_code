#include "libr.h"
#include "classes.h"


int main()
{
    string file_name;
    file_name = "hello.txt";
    unordered_map<char, int> count_characters;
    try {
        count_characters = count_char(file_name);
    } catch (my_exception exp) {
        cerr << exp.what();
        return 1;
    }
    Huffman_tree tree (count_characters);
    unordered_map<char, vector<int> > code = tree.coding();
    key_file(count_characters, file_name, writing(code, file_name));
    decoding(file_name);
    return 0;
}


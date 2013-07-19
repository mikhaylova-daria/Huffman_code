#ifndef LIBR_H
#define LIBR_H

#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <exception>
#include <queue>
#include <map>
using namespace std;

unordered_map<char, int>  count_char(const string & file_name);

void key_file (const unordered_map<char, int> &count_characters, const string &file_name, const short &last_char_length);

int writing(const unordered_map<char, vector<int> > &code, const string & file_name);

void decoding(const string & file_name);

class my_exception: public exception {
private:
    string _what;
public:
    my_exception(const char * _what) throw() {
           this->_what = _what;
    }
    const char* what() const throw(){
        return _what.c_str();
    }
    ~my_exception() throw(){}
};




class Huffman_tree {

    class Huffman_node {
    public :
        Huffman_node * left = nullptr;
        Huffman_node * right = nullptr;
        Huffman_node * parent = nullptr;
        int value;
        char key;

        Huffman_node(const char & _key, const int & _value): key(_key), value(_value){}
        Huffman_node(Huffman_node * _left, Huffman_node * _right): left(_left), right(_right){
            value = _left->value + _right->value;
            _left->parent = this;
            if (_left->left != nullptr) {
            }
            _right->parent = this;
            if (_right->left != nullptr) {
            }
        }
        ~Huffman_node(){}
    };
    struct comp_node : binary_function < Huffman_tree::Huffman_node*,Huffman_tree::Huffman_node*,bool> {
      bool operator() ( Huffman_tree::Huffman_node* x, Huffman_tree::Huffman_node* y) const {
          if (x->value == y->value) {
              return x->key > y->key;
          } else {
            return x->value > y->value;
          }
      }
    };
    map <int, int> count_equival;
    priority_queue <Huffman_node*, vector<Huffman_node*>, comp_node> subtrees;
    friend void decoding(const string & file_name);
public:
    Huffman_tree(const unordered_map <char, int> & characters);
    ~Huffman_tree();
    unordered_map<char, vector<int> > coding();

private:
    void delete_tree(Huffman_node* node);
    void tree_walk(Huffman_node* node, unordered_map<char, vector<int> > * answer, vector<int> * code);
};



#endif // LIBR_H

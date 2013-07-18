#ifndef CLASSES_H
#define CLASSES_H


unordered_map<char, int>  count_char(const string & file_name) {
    ifstream fin (file_name.c_str());
    if (!fin.is_open()) {
        my_exception exp(("File \""  + file_name +"\" was not found\n").c_str());
        throw (exp);
    } else {
        unordered_map<char, int> count_characters;
        while (!fin.eof()){
            unordered_map<char, int>::iterator itr;
            char ch = fin.get();
            itr = count_characters.find(ch);
            if (itr == count_characters.end()){
                count_characters.insert(make_pair<char, int>((const char)ch, 1));

            } else {
                 itr->second = itr->second + 1;
            }
        }
        fin.close();
        return count_characters;
    }
}

int key_file (const unordered_map<char, vector<int> > &code, const string &file_name, const char &last_char_length){
    ofstream fkey (("key_" +file_name).c_str());
    unordered_map<char, vector<int> >::const_iterator itr;
    fkey << (int)last_char_length << endl;
    for (itr = code.cbegin(); itr != code.cend(); ++itr) {
        vector<int>::const_iterator iter;
        for (iter = itr->second.cbegin(); iter != itr->second.cend(); ++iter) {
            fkey<<(*iter);
        }
        fkey<<itr->first;
        fkey<<endl;
    }
    fkey.close();
    return 0;
}


int writing(const unordered_map<char, vector<int> > &code, const string & file_name) {
    ifstream fin (file_name.c_str());
    char buf_length = 0;
    if (!fin.is_open()) {
        my_exception exp(("File \""  + file_name +"\" was not found\n").c_str());
        throw (exp);
    } else {
        ofstream fout (("zip_" + file_name ).c_str());
        if (!fout.is_open()) {
            my_exception exp(("File \""  + file_name +"\" was not found\n").c_str());
            throw (exp);
        } else {
            char buf = 0;
            char current_char;
            vector <int> current_vector_code;
            while (!fin.eof()) {
                current_char = fin.get();
                current_vector_code = code.find(current_char)->second;
                for (int i = 0; i < current_vector_code.size(); ++i) {
                    buf = buf * 2 + current_vector_code[i];
                    ++buf_length;
                    if (buf_length == 8) {
                        fout<<buf;
                        buf = 0;
                        buf_length = 0;
                    }
                }
            }
            char buf_length_2 = buf_length;
            if (buf_length_2 != 0) {
                while (buf_length_2 != 8) {
                    buf = buf * 2;
                    ++buf_length_2;
                }
                fout<<buf;
            }
            fin.close();
            fout.close();
        }
    }
    return buf_length;
}


Huffman_tree::Huffman_tree(const unordered_map <char, int> & characters) {
        int n = characters.size();
        unordered_map <char, int>::const_iterator itr;
        for (itr = characters.cbegin(); itr !=characters.cend(); ++ itr) {
            Huffman_node * list = new Huffman_node(itr->first, itr->second);
            subtrees.push(list);
        }

        for (int i = 1; i < n; ++i) {
            Huffman_node* left = subtrees.top();
            subtrees.pop();
            Huffman_node* right = subtrees.top();
            subtrees.pop();
            Huffman_node* node = new Huffman_node(left, right);
            subtrees.push(node);
        }
        //Теперь в очереди лежит единственный элемент - указатель на корень дерева
}

Huffman_tree::~Huffman_tree() {
    Huffman_node* subroot = this->subtrees.top();
    delete_tree(subroot);
}

void Huffman_tree::delete_tree(Huffman_node* node) {
    if (node->right != nullptr) {
        delete_tree(node->right);
    }
    if (node->left != nullptr) {
        delete_tree (node->left);
    }
    delete(node);
}

void Huffman_tree::tree_walk(Huffman_node* node, unordered_map<char, vector<int> > * answer, vector<int> * code) {
    if (node->left != nullptr) {
        code->push_back(1);
        tree_walk(node->left, answer, code);
    }
    if (node->right != nullptr){
        code->push_back(0);
        tree_walk(node->right, answer, code);
    }
    if (node->left == nullptr && node->right == nullptr) {
        answer->insert(pair<char, vector<int> > (node->key, *code));
    }
    code->pop_back();
    return;

}

unordered_map<char, vector<int> > Huffman_tree::coding() {
    unordered_map<char, vector<int> > answer;
    vector<int> code;
    Huffman_node* node = this->subtrees.top();
    this->tree_walk(node, &answer, &code);
    return answer;
}


#endif // CLASSES_H

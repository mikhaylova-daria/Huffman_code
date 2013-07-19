#ifndef CLASSES_H
#define CLASSES_H


void decoding(const string & file_name) {
    ifstream f_key(("key_" + file_name).c_str());
    short length_last_char;
    f_key >> length_last_char;
    unordered_map <char, int> decode;
    f_key.get();
    while (!f_key.eof()) {
        char ch_1 = f_key.get();
        char ch;
        f_key.get();
        ch = f_key.get();
        int count = 0;
        while ('0' <= ch && ch <= '9') {
            count = count * 10 + ch - '0';
            ch = f_key.get();
        }
        decode.insert(pair <char, int> ((char)ch_1, count));
    }
    Huffman_tree tree(decode);
    ifstream f_cod(("zip_" + file_name).c_str(), ios_base::binary);
    ofstream f_out(("answer_"+file_name).c_str(),ios_base::binary);
    Huffman_tree::Huffman_node * root = tree.subtrees.top();
    Huffman_tree::Huffman_node * node = tree.subtrees.top();
    char r;

    while (!f_cod.eof()) {
        r = f_cod.get();
        int count = 7;
        while (count >= 0){
            if ((r & (1 << count))){
                node = node -> left;
            } else {
                node = node -> right;
            }
            --count;
            if (node -> left == nullptr) {
                f_out.put((char) node -> key);
                node = root;
            }

         }
    }
    f_out.close();
    f_cod.close();
    return;
}


unordered_map<char, int>  count_char(const string & file_name) {
    ifstream fin (file_name.c_str(), ios_base::binary);
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

void key_file (const unordered_map<char, int > &count_characters, const string &file_name, const short &last_char_length)
{
    ofstream fkey (("key_" +file_name).c_str());
    unordered_map<char, int>::const_iterator itr1;
    fkey << last_char_length << endl;
    for (itr1 = count_characters.cbegin(); itr1 != count_characters.cend(); ++itr1) {
        fkey << itr1->first<< '-' << itr1->second << endl;
    }
    fkey.close();
    return;
}


int writing(const unordered_map<char, vector<int> > &code, const string & file_name) {
    ifstream fin (file_name.c_str(), ios_base::binary);
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
            pair <map<int, int>::iterator, bool> p;
            p = count_equival.insert(pair <int, int> (node->value, 1));
            if (p.second == false) {
                p.first->second += 1;
            }
            node->key = p.first->second;
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

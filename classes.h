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

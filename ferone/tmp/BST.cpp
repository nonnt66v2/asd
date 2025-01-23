#include <iostream>
#include <vector>
#include "string"

using namespace std;
template<typename T> class BST;
template<typename T> class Node;
template<typename T>
class Node{
    T key;
    Node<T>* parent;
    Node<T>* left;
    Node<T>* right;
    Node(T key) : key{key}{
        parent = left = right = nullptr;
    }
    template<typename Tkey> friend class BST;
};
template<typename T>
class BST{
    Node<T>* root;
    void preorder(Node<T>* root);
    void inorder(Node<T>* root);
    void postorder(Node<T>* root);
    Node<T>* search(Node<T>* root, T key);
    Node<T>* searchIt(Node<T>* root, T key);
    Node<T>* min(Node<T>* root);
    Node<T>* max(Node<T>* root);
    Node<T>* successor(Node<T>* root);
    Node<T>* predecessor(Node<T>* root);
    void insert(Node<T>* z);
    void transplant(Node<T>* u, Node<T>* v);
    void deletion(Node<T>* z);
public:
    BST() : root{nullptr}{}
    void preorder();
    void inorder();
    void postorder();
    bool search(T key);
    T min();
    T max();
    void insert(T key);
    bool deletion(T key);
};

template<typename T>
void BST<T>::preorder(Node<T>* root){
    if(root != nullptr){
        std::cout << root->key << " ";
        preorder(root->left);
        preorder(root->right);
    }
}
template<typename T>
void BST<T>::inorder(Node<T>* root){
    if(root != nullptr){
        inorder(root->left);
        std::cout << root->key << " ";
        inorder(root->right);
    }
}
template<typename T>
void BST<T>::postorder(Node<T>* root){
    if(root != nullptr){
        postorder(root->left);
        postorder(root->right);
        std::cout << root->key << " ";
    }
}
template<typename T>
Node<T>* BST<T>::search(Node<T>* root, T key){
    if(root == nullptr || key == root->key)
        return root;
    if(key < root->key)
        return search(root->left,key);
    else
        return search(root->right,key);
}
template<typename T>
Node<T>* BST<T>::searchIt(Node<T>* root, T key){
    Node<T>* tmp = root;
    while(tmp != nullptr && key != tmp->key)
        tmp = (key < tmp->key)? tmp->left : tmp->right;
    return tmp;
}

template<typename T>
Node<T>* BST<T>::min(Node<T>* root){
    Node<T>* tmp = root;
    while(tmp->left != nullptr)
        tmp = tmp->left;
    return tmp;
}
template<typename T>
Node<T>* BST<T>::max(Node<T>* root){
    Node<T>* tmp = root;
    while(tmp->right != nullptr)
        tmp = tmp->right;
    return tmp;
}
template<typename T>
Node<T>* BST<T>::successor(Node<T>* root){
//caso 1: il nodo "v" ha un figlio destro, dunque il successore
//è il minimo del sottoalbero destro di v
    if(root->right != nullptr)
        return min(root->right);
//caso 2: il nodo "v" NON ha un figlio destro, dunque il successore
//è il primo antenato di v tale che v sia figlio sx del proprio antenato
    Node<T>* parent = root->parent;
    while(parent != nullptr && root == parent->right){ //...risaliamo l'albero
        root = parent;
        parent = parent->parent;
    }
    return parent; //se succ non trovato, parent è un nullptr
}
template<typename T>
Node<T>* BST<T>::predecessor(Node<T>* root){
//caso 1: il nodo "v" ha un figlio sinistro, dunque il predecessore
//è il massimo del sottoalbero sinistro di v
    if(root->left != nullptr)
        return max(root->left);
//caso 2: il nodo "v" NON ha un figlio sinistro, dunque il predecessore
//è il primo antenato di v tale che v sia figlio dx del proprio antenato
    Node<T>* parent = root->parent;
    while(parent != nullptr && root == parent->left){ //...risaliamo l'albero
        root = parent;
        parent = parent->parent;
    }
    return parent; //se pred non trovato, parent è un nullptr
}

template<typename T>
void BST<T>::insert(Node<T>* z){
    Node<T>* x = this->root;
    Node<T>* xp = nullptr;
    while(x != nullptr){
        xp = x;
        x = (z->key < x->key)? x->left : x->right;
    }
    z->parent = xp;
    if(z->parent == nullptr)
        this->root = z;
    else if(z->key < z->parent->key)
        z->parent->left = z;
    else
        z->parent->right = z;
}
template<typename T>
void BST<T>::transplant(Node<T>* u, Node<T>* v){
    Node<T>* p = u->parent;
    if(p == nullptr)
        this->root = v;
    else if(u == p->left)
        p->left = v;
    else
        p->right = v;
    if(v != nullptr)
        v->parent = p;
}
template<typename T>
void BST<T>::deletion(Node<T>* z){
    if(z->left == nullptr)
        transplant(z,z->right);
    else if(z->right == nullptr)
        transplant(z,z->left);
    else{
        Node<T>* y = min(z->right);
        if(y != z->right){
            transplant(y,y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        transplant(z,y);
        y->left = z->left;
        y->left->parent = y;
    }
}

template<typename T>
void BST<T>::preorder(){
    preorder(this->root);
}
template<typename T>
void BST<T>::inorder(){
    inorder(this->root);
}
template<typename T>
void BST<T>::postorder(){
    postorder(this->root);
}
template<typename T>
bool BST<T>::search(T key){
    Node<T>* found = search(this->root, key);
    return (found != nullptr)? true : false;
}
template<typename T>
T BST<T>::min(){
    Node<T>* m = min(this->root);
    return m->key;
}
template<typename T>
T BST<T>::max(){
    Node<T>* m = max(this->root);
    return m->key;
}
template<typename T>
void BST<T>::insert(T key){
    insert(new Node(key));
}
template<typename T>
bool BST<T>::deletion(T key){
    Node<T>* z = search(this->root, key);
    if(z == nullptr)
        return false;
    deletion(z);
//cut out 'z' from the tree
    delete(z);
//deallocation
    return true;
}


int main(int, char **) {
    BST<int> bst;
    bst.insert(15);
    bst.insert(6);
    bst.insert(3);
    bst.insert(2);
    bst.insert(4);
    bst.insert(7);
    bst.insert(13);
    bst.insert(9);
    bst.insert(18);
    bst.insert(17);
    bst.insert(20);
    bst.inorder();
    cout << endl;
    BST<string> bst2;
    bst2.insert("dado");
    bst2.insert("birra");
    bst2.insert("alba");
    bst2.insert("fiume");
    bst2.insert("cinta");
    bst2.insert("dente");
    bst2.deletion("dente");
    bst2.inorder();
    return 0;
}
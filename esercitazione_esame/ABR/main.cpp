#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <queue>

using namespace std;


template<typename T>
class Nodo {
public:
    T chiave;
    Nodo<T> *sx, *dx;
    Nodo<T> *padre;
    char ch;
    int freq;
public:
    Nodo(T chiave) : chiave(chiave) {
        sx = dx = padre = nullptr;
        ch = '\0';
        freq = 0;
    }

    Nodo(T chiave, char ch, int freq) : chiave(chiave), ch(ch), freq(freq) { sx = dx = padre = nullptr; }

    Nodo(T chiave, int freq) : chiave(chiave), freq(freq) { sx = dx = padre = nullptr; }

    Nodo() : Nodo(0, '\0', 0) {};
};

template<typename T>
struct NodeCmp {
    bool operator()(const Nodo<T> *u, const Nodo<T> *v) const {
        return u->freq > v->freq;
    }
};

template<typename T>
class BST {
private:
    Nodo<T> *radice;

    void preorder(Nodo<T> *radice);

    void inorder(Nodo<T> *radice);

    Nodo<T> *ricerca(Nodo<T> *radice, T chiave);

    Nodo<T> *min(Nodo<T> *radice);

    Nodo<T> *max(Nodo<T> *radice);

    void inserimento(Nodo<T> *radice, T chiave);

    void inserimento(Nodo<T> *radice, T chiave, int freq);

    void printBT(const std::string &prefix, const Nodo<T> *radice, bool isLeft);

    void transplant(Nodo<T> *u, Nodo<T> *v);

    int altezza(Nodo<T> *radice);

    int numeroNodi(Nodo<T> *radice);


public:
    BST() : radice(nullptr) {};

    BST(Nodo<T> *radice) : radice(radice) {};

    void caricaAlbero();

    void preorder();

    void inorder();

    T min();

    T max();

    Nodo<T> *ricerca(T chiave);

    Nodo<T> *successor(T chiave);

    Nodo<T> *predecessor(T chiave);

    void inserimento(T chiave);

    void inserimento(T chiave, int freq);

    void printBT();

    void eliminazione(int chiave);

    int altezza();

    int numeroNodi();

    Nodo<T> *HuffmanCoder(const map<char, int> &charMap);

};





class NodoHuffman{
public:
    char ch;
    int freq;
    NodoHuffman* sx,*dx;

    NodoHuffman(char ch,int freq) : ch(ch),freq(freq){sx = dx = nullptr;}
    NodoHuffman(): NodoHuffman('\0',0){};
};

struct NodoCmp {
    bool operator()(const NodoHuffman *u, const NodoHuffman *v) const {
        return u->freq > v->freq;
    }
};

NodoHuffman* HuffmanCode(const map<char,int>& mapHuff){
    int n = mapHuff.size();
    std::priority_queue<NodoHuffman*,vector<NodoHuffman*>,NodoCmp> Q;
    for(auto x : mapHuff){
        Q.push(new NodoHuffman(x.first,x.second));
    }
    for(int i=0;i<n-1;i++){
        auto* z = new NodoHuffman;
        auto *x = z->sx = Q.top();Q.pop();
        auto *y = z->dx = Q.top();Q.pop();
        z->freq = x->freq + y->freq;
        Q.push(z);
    }
    return Q.top();
}

string HuffmanDecode(NodoHuffman* radice,const int arr[],int N){
    string text;
    NodoHuffman* pnode = radice;
    for(int i=0;i<N;i++){
        if(arr[i]==0) pnode = pnode->sx;
        else pnode = pnode->dx;
        if(!pnode->sx && !pnode->dx){
            text += pnode->ch;
            pnode = radice;
        }
    }
    return text;
}

template<typename T>
void BST<T>::inserimento(Nodo<T> *radice, T chiave, int freq) {
    auto *z = new Nodo<T>(chiave, freq);
    Nodo<T> *x = radice;
    Nodo<T> *xp = nullptr;
    while (x != nullptr) {
        xp = x;
        if (z->chiave < x->chiave) x = x->sx;
        else x = x->dx;
    }
    z->padre = xp;
    if (z->padre == nullptr) this->radice = z;
    else if (z->chiave < z->padre->chiave) z->padre->sx = z;
    else z->padre->dx = z;
}

template<typename T>
void BST<T>::inserimento(T chiave, int freq) {
    inserimento(this->radice, chiave, freq);
}

template<typename T>
Nodo<T> *BST<T>::HuffmanCoder(const map<char, int> &charMap) {
    int n = charMap.size();
    std::priority_queue<Nodo<char> *, vector<Nodo<char> *>, NodeCmp<char>> Q;
    for (auto x: charMap) {
        Q.push(new Nodo<char>(0, x.first, x.second));
    }
    for (int i = 0; i < n; i++) {
        auto *z = new Nodo<char>();
        auto *x = z->sx = Q.top();
        Q.pop();
        auto *y = z->dx = Q.top();
        Q.pop();
        z->freq = x->freq + y->freq;
    }
    return Q.top();


}


template<typename T>
int BST<T>::numeroNodi() {
    return numeroNodi(this->radice);
}

template<typename T>
int BST<T>::numeroNodi(Nodo<T> *radice) {
    if (radice == nullptr) return 0;
    return 1 + (numeroNodi(radice->sx) + numeroNodi(radice->dx));
}

template<typename T>
int BST<T>::altezza(Nodo<T> *radice) {
    if (radice == nullptr) return 0;
    int fSx = altezza(radice->sx);
    int fDx = altezza(radice->dx);
    return 1 + std::max(fSx, fDx);
}


template<typename T>
int BST<T>::altezza() {
    return altezza(this->radice);
}


template<typename T>
void BST<T>::eliminazione(int chiave) {
    Nodo<T> *z = ricerca(chiave);
    if (z->sx == nullptr) transplant(z, z->dx);
    else if (z->dx == nullptr) transplant(z, z->sx);
    else {
        Nodo<T> *y = min(z->dx);
        if (y != z->dx) {
            transplant(y, y->dx);
            y->dx = z->dx;
            y->dx->padre = y;
        }
        transplant(z, y);
        y->sx = z->sx;
        z->sx->padre = y;
    }
}

template<typename T>
void BST<T>::transplant(Nodo<T> *u, Nodo<T> *v) {
    Nodo<T> *p = u->padre;
    if (p == nullptr) this->radice = v;
    else if (v == p->sx) p->sx = v;
    else p->dx = v;
    if (v != nullptr) v->padre = p;
}

template<typename T>
void BST<T>::inorder(Nodo<T> *radice) {
    if (radice != nullptr) {
        inorder(radice->sx);
        cout << radice->chiave << "\n";
        inorder(radice->dx);
    }
}

template<typename T>
void BST<T>::inorder() {
    inorder(this->radice);
}

template<typename T>
Nodo<T> *BST<T>::max(Nodo<T> *radice) {
    Nodo<T> *tmp = radice;
    while (tmp->dx != nullptr) {
        tmp = tmp->dx;
    }
    return tmp;
}

template<typename T>
Nodo<T> *BST<T>::min(Nodo<T> *radice) {
    Nodo<T> *tmp = radice;
    while (tmp->sx != nullptr) {
        tmp = tmp->sx;
    }
    return tmp;
}

template<typename T>
void BST<T>::inserimento(Nodo<T> *radice, T chiave) {

    auto *z = new Nodo<T>(chiave);
    Nodo<T> *x = radice;
    Nodo<T> *xp = nullptr;
    while (x != nullptr) {
        xp = x;
        if (z->chiave < x->chiave) x = x->sx;
        else x = x->dx;
    }
    z->padre = xp;
    if (z->padre == nullptr) this->radice = z;
    else if (z->chiave < z->padre->chiave) z->padre->sx = z;
    else z->padre->dx = z;

}

template<typename T>
void BST<T>::inserimento(T chiave) {
    inserimento(this->radice, chiave);
}

template<typename T>
T BST<T>::max() {
    Nodo<T> *tmp = max(this->radice);
    return tmp->chiave;
}

template<typename T>
T BST<T>::min() {
    Nodo<T> *tmp = min(this->radice);
    return tmp->chiave;
}

template<typename T>
void BST<T>::caricaAlbero() {
    fstream f;
    f.open("a.txt", ios::out);
    vector<int> vet;
    char a;
    for (int i = 0; i < 26; i++) {
        a = rand() % (91 - 65) + 65;
        f << a - 65;
        f << "\n";
    }
    f.close();
}


template<typename T>
Nodo<T> *BST<T>::ricerca(Nodo<T> *radice, T chiave) {
    Nodo<T> *tmp = radice;
    while (tmp != nullptr && chiave != tmp->chiave) {
        if (chiave < tmp->chiave) tmp = tmp->sx;
        else tmp = tmp->dx;
    }
    return tmp;
}

template<typename T>
Nodo<T> *BST<T>::ricerca(T chiave) {
    return ricerca(this->radice, chiave);
}

template<typename T>
void BST<T>::preorder(Nodo<T> *radice) {
    if (radice != nullptr) {
        cout << radice->chiave << "\n";
        preorder(radice->sx);
        preorder(radice->dx);
    }
}

template<typename T>
void BST<T>::preorder() {
    preorder(this->radice);
}

template<typename T>
Nodo<T> *min(Nodo<T> *radice) {
    if (radice->sx != nullptr) {
        min(radice->sx);
    }
    return radice;
}

template<typename T>
Nodo<T> *max(Nodo<T> *radice) {
    if (radice->dx != nullptr) {
        max(radice->dx);
    }
    return radice;
}


template<typename T>
Nodo<T> *BST<T>::predecessor(T chiave) {
    Nodo<T> *x = ricerca(chiave);
    if (x == nullptr) return nullptr;
    if (x->sx != nullptr) {
        return max(x->sx);
    } else {
        Nodo<T> *xp = x->padre;
        while (xp != nullptr && x == xp->sx) {
            x = xp;
            xp = xp->padre;
        }
        return xp;
    }
}


template<typename T>
Nodo<T> *BST<T>::successor(T chiave) {
    Nodo<T> *x = ricerca(chiave);
    if (x == nullptr) return nullptr;
    if (x->dx != nullptr) {
        return min(x->dx);
    } else {
        Nodo<T> *xp = x->padre;
        while (xp->padre != nullptr && xp->dx == x) {
            x = xp;
            xp = xp->padre;
        }
        return xp;
    }
}

template<typename T>
void BST<T>::printBT(const std::string &prefix, const Nodo<T> *radice, bool isLeft) {
    if (radice != nullptr) {
        std::cout << prefix;

        // print the value of the node

        std::cout << (isLeft ? "L├──" : "R└──");
        std::cout << radice->chiave << ":" << radice->freq << std::endl;
        // enter the next tree level - left and right branch
        printBT(prefix + (isLeft ? "│    " : "    "), radice->sx, true);

        printBT(prefix + (isLeft ? "│    " : "    "), radice->dx, false);
    }
}

template<typename T>
void BST<T>::printBT() {
    printBT("", this->radice, false);
}

void printArr(int *arr,int n){
    for(int i=0;i<n;i++){
        cout<<arr[i];
    }
    cout<<endl;
}
void stampaHuffman(NodoHuffman *tmp,int *arr, int top) {

    if (tmp->sx) {
        arr[top] = 0;
        stampaHuffman(tmp->sx, arr, top + 1);
    }
    if (tmp->dx) {
        arr[top] = 1;
        stampaHuffman(tmp->dx, arr, top + 1);
    }
    if (!tmp->sx && !tmp->dx){
        cout<<tmp->ch<<":";
        printArr(arr, top);
    }


}
// pass the root node of your binary tree

int main(int argc, char **argv) {
    /*if (argc < 2) {
        perror("argomenti");
        exit(-1);
    }*/
    /* clock_t t0, t1;
     t0 = clock();
     auto *abr = new BST<string>();
     fstream f;
     f.open("/home/nonnt66/Scaricati/utili/Chat WhatsApp con Ilenia Pastore/Chat WhatsApp con Ilenia Pastore.txt", ios::in);
     string num;
     f >> num;
     while (f >> num) {
         abr->inserimento(num);
     }
     f.close();
 //    abr->printBT();
 //    abr->inorder();
     auto *succ = abr->successor("a");
     auto *prede = abr->predecessor("a");
     string massimo = abr->max();
     string minimo = abr->min();

     t1 = clock();
     cout << "successore:\t" << ((succ == nullptr) ? (string) "successore inesistente" : succ->chiave) << endl;
     cout << "predecessore:\t" << ((prede == nullptr) ? (string) "predecessore inesistente" : prede->chiave) << endl;
     cout << "massimo:\t" << ((minimo.empty()) ? (string) "massimo inesistente" : massimo) << endl;
     cout << "minimo:\t" << ((minimo.empty()) ? (string) "minimo inesistente" : minimo) << endl;
     for (int i = 1; argv[i] != nullptr; i++)
         cout << "cerco il termine: \"" << argv[i]
              << ((abr->ricerca(argv[i]) == nullptr) ? (string) "\" non trovato\n"
                                                     : "\" TROVATO\n") << endl;
     cout << "t0\t" << t0 << "\tt1\t" << t1;
     cout << "\ntempo di ricerca :" << (float) (t1 - t0) / CLOCKS_PER_SEC << "secondi" << endl;

     cout << "altezza albero: " << abr->altezza() << endl;
     cout << "numero nodi: " << abr->numeroNodi() << endl;
     free(abr);*/

    if (argc < 2) {
        perror("argomenti");
        exit(-1);
    }


    clock_t t0, t1;
    t0 = clock();
    auto *abr = new BST<char>();
    fstream f;
    f.open("a.txt", ios::in);
    char num;
    int freq;
    map<char, int> map;
    while (f >> num) {
        f >> freq;
        map.insert(pair<char, int>(num, freq));
        abr->inserimento(num, freq);
    }
    f.close();
    abr->printBT();
    abr->inorder();
    auto *succ = abr->successor(7);
    auto *prede = abr->predecessor(7);
    char massimo = abr->max();
    char minimo = abr->min();

    /*t1 = clock();
    cout << "successore:\t" << ((succ == nullptr) ? (int) 0 : succ->chiave) << endl;
    cout << "predecessore:\t" << ((prede == nullptr) ? (int) 0 : prede->chiave) << endl;
    cout << "massimo:\t" << ((massimo == 0) ? (int) 0 : massimo) << endl;
    cout << "minimo:\t" << ((minimo == 0) ? (int) 0 : minimo) << endl;
    for (int i = 1; argv[i] != nullptr; i++)
        cout << "cerco il termine: \"" << argv[i]
             << ((abr->ricerca(stoi(argv[i])) == nullptr) ? (string) "\" non trovato\n" : "\" TROVATO\n") << endl;
    cout << "t0\t" << t0 << "\tt1\t" << t1;
    cout << "\ntempo di ricerca :" << (float) (t1 - t0) / CLOCKS_PER_SEC << "secondi" << endl;

    cout << "altezza albero: " << abr->altezza() << endl;
    cout << "numero nodi albero: " << abr->numeroNodi() << endl;*/

//    NodoHuffman* nodoHuffman = new NodoHuffman();
//    auto * nodoHuffman = new NodoHuffman();

    auto * huffmanCode = HuffmanCode(map);
    int *arr = new int[map.size()];
    int top=0;
    /*for(auto &x: map){
        cout<<x.first<<":"<<x.second<<endl;
    }*/

    stampaHuffman(huffmanCode,arr,top);
    for(int i=0;i<map.size();i++){
        cout<<arr[i];
    }
    cout<<endl;
    string testo = HuffmanDecode(huffmanCode,arr,map.size());
    cout<<testo<<endl;

    /*free(abr);*/

}
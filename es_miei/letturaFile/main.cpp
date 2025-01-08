#include <fstream>
#include <iostream>
#include <vector>
#include <map>

using namespace std;


enum trovato {
    NON_TROVATO, TROVATO
};

map<string, int> caricaMap() {
    fstream f("a.txt");
    if (!f.is_open()) {
        perror("file:");
    }
    char b = 'a';
    int i = 0;
    while (i++ < 26) {
        f << b++ << " " << i << "\n";
    }
    f.close();
    f.open("a.txt");
    map<string, int> nodo;
    string label;
    int value;

    while (!f.eof()) {
        f >> label;
        f >> value;
        nodo[label] = value;
    }
//    for (auto &coppia: nodo) {
//        cout << coppia.first << " " << coppia.second << "\n";
//    }
    return nodo;

}

template<typename T>
class Nodo {
public:
    Nodo<T> *sx;
    Nodo<T> *dx;
    T chiave;
    string label;
    Nodo<T> *padre;
public:
    Nodo() {
        this->sx = nullptr;
        this->dx = nullptr;
        chiave = 0;
        padre = nullptr;
    }

    void setLeft(Nodo *sx) {
        this->sx = sx;
    }

    void setRight(Nodo *dx) {
        this->dx = dx;
    }

    bool isRadice() {
        if (padre == nullptr) return true;
        else return false;
    }

    void setChiave(int chiave) {
        this->chiave = chiave;
    }
    template<typename Tkey> friend class BST;
};

template<typename T>
class BST {
private:
    Nodo<T> *radice;

    void preorder(Nodo<T> *radice);

    void inorder(Nodo<T> *radice);

    void postorder(Nodo<T> *radice);

    Nodo<T> *min(Nodo<T> *);

    Nodo<T> *max(Nodo<T> *);

    Nodo<T> *search(Nodo<T> *radice, T chiave);


    Nodo<T> *successor(Nodo<T> *radice);

    Nodo<T> *predecessor(Nodo<T> *radice);


public:
    BST() { radice = nullptr; };

    void preorder();

    void inorder();

    void postorder();

    bool search(T chiave);

    T min();

    T max();

    void insert(Nodo<T> *nodo);
};


template<typename T>
void BST<T>::preorder() {
    if (radice != nullptr) {
        cout << radice->chiave << endl;
        preorder(radice->sx);
        preorder(radice->dx);
    }
}

template<typename T>
void BST<T>::preorder(Nodo<T> *radice) {
    preorder(this->radice);
}

template<typename T>
void BST<T>::inorder() {
    inorder(this->radice);

}

template<typename T>
void BST<T>::inorder(Nodo<T> *radice) {
    if (radice != nullptr) {
        inorder(radice->sx);
        cout << radice->chiave << endl;
        inorder(radice->dx);
    }
}

template<typename T>
void BST<T>::postorder() {
    if (radice != nullptr) {
        postorder(radice->sx);
        postorder(radice->dx);
        cout << radice->chiave << endl;
    }
}

template<typename T>
void BST<T>::postorder(Nodo<T> *radice) {
    postorder(this->radice);
}


template<typename T>
Nodo<T> *BST<T>::search(Nodo<T> *radice, T chiave) {
    if (radice == nullptr) {
        return nullptr;
    }
    if (radice->chiave == chiave) {
        return radice;
    } else if (radice->chiave < chiave)return search(radice->dx, chiave);
    else return search(radice->sx, chiave);
}

template<typename T>
bool BST<T>::search(T chiave) {
    Nodo<T> *trovato = search(this->radice, chiave);
    return (trovato != nullptr) ? TROVATO : NON_TROVATO;
}

template<typename T>
Nodo<T> *BST<T>::min(Nodo<T> *radice) {
    Nodo<T>* tmp = radice;
    while (radice->sx != nullptr) {
        min(radice->sx);
    }
    return tmp;
}

template<typename T>
T BST<T>::min() {
    Nodo<T> *minimo = min(this->radice);
    return (minimo->chiave);
}

template<typename T>
Nodo<T> *BST<T>::max(Nodo<T> *radice) {
    Nodo<T>* tmp = radice;
    while (radice->dx != nullptr) {
        max(radice->dx);
    }
    return tmp;
}

template<typename T>
T BST<T>::max() {
    Nodo<T> *maximo = max(this->radice);
    return (maximo->chiave);
}

template<typename T>
Nodo<T> *BST<T>::successor(Nodo<T> *radice) {
    if (radice->dx != nullptr) {
        return min(radice->dx);
    } else {
        Nodo<T> *padre = radice->padre;
        while (padre != nullptr && radice == padre->dx) {
            radice = padre;
            padre = padre->padre;
        }
        //se ritorna nullptr è perchè il nodo non ha padre
        return padre;
    }
}

template<typename T>
Nodo<T> *BST<T>::predecessor(Nodo<T> *radice) {
    if (radice->sx != nullptr) {
        return max(radice->dx);
    } else {
        Nodo<T> *padre = radice->padre;
        while (padre != nullptr && radice == padre->sx) {
            radice = padre;
            padre = padre->padre;
        }
        //se ritorna nullptr è perchè il nodo non ha padre
        return padre;
    }
}

template<typename T>
void BST<T>::insert(Nodo<T> *nodo) {
    Nodo<T> *x = this->radice;
    Nodo<T> *xp = nullptr;
    while (x != nullptr) {
        xp = x;
        nodo->chiave < x->chiave ? x= x->sx : x=x->dx;
    }
    nodo->padre = xp;
    if (nodo->padre == nullptr) this->radice = nodo;
    else {(nodo->chiave < nodo->padre->chiave) ? nodo->padre->sx = nodo : nodo->padre->dx = nodo;}
}

int main() {
    map<string, int> coppia;
    coppia = caricaMap();
    auto *nodo = new Nodo<int>();
    nodo->setChiave(coppia.begin()->second);
    auto bst = new BST<int>();
    auto *a = new Nodo<int>();
    a->setChiave(8);
    auto *b = new Nodo<int>();
    b->setChiave(3);
    auto *c = new Nodo<int>();
    c->setChiave(10);
    auto *d = new Nodo<int>();
    d->setChiave(1);


    bst->insert(a);
    bst->insert(c);
    bst->insert(d);
    bst->insert(b);
    bst->inorder();
    /*bst->postorder();*/

//    if (bst->search(3) == TROVATO)cout << "trovato\n";
//    cout << "minimo:" << bst->min()->chiave << endl;
    cout << "massimo:" << bst->max() << endl;
    return 0;
}
#include <iostream>
#include <map>
#include <fstream>
#include <vector>
#include <list>

#define N 5

using namespace std;

template<typename K, typename V>
class Element {

public:
    K k;
    V v;
    bool isDeleted;
public:
    Element(K k, V v, bool isDeleted) : K{k}, V{v}, isDeleted{isDeleted} {};

    Element() : Element(-1, -1, false) {};


};

template<typename K, typename V>
class Hash {
    map<K, list<V>> hashtable;
    int dim;
    ifstream fileI;
    ofstream fileO;
public:
    Hash(int dim, string fileI, string fileO) {
        this->dim = dim;
        for (int i = 0; i < N; i++) hashtable[i] = list<V>();
        this->fileI.open(fileI.c_str(), ios::in);
        if (!this->fileI) {
            cout << "errore nell'apertura di IN.txt\n";
        }
        this->fileO.open(fileO.c_str(), ios::in);
        if (!this->fileO) {
            cout << "errore nell'apertura di OUT.txt\n";
        }
    }

    void init_ht();

    void caricaHash();

    int hashU(K chiave);

    void insert();

    void printInfo();

    void elimina(K chiave);

    void setTable(Element<K, V> **newtable) {
        this->hashtable = newtable;
    }


};

template<typename K, typename V>
void Hash<K, V>::elimina(K chiave) {
    int k = hashU(chiave);
    cout<<k<<"\t";
    if(hashtable.at(k).empty()){
        cout<<"elemento da eliminare non esistente\n";
    }
    else{
        if(hashtable.at(k).size() == 1) hashtable.at(k).pop_front();
        else hashtable.at(k).pop_back();
    }
}

template<typename K, typename V>
void Hash<K, V>::init_ht() {

}


template<typename K, typename V>
void Hash<K, V>::caricaHash() {
    K chiave;
    V valore;
    fileI >> chiave;
    while (fileI >> chiave >> valore) {
        int k  = hashU(chiave);
        if(valore == 4) cout<<k<<":\t"<<valore<<endl;        //insert;
        if(hashtable.at(k).empty()) hashtable.at(k).push_front(valore);
        else hashtable.at(k).push_back(valore);
    }
    //🐫

}

template<typename K, typename V>
void Hash<K, V>::printInfo() {
    for (int i = 0; i < N; i++) {
        cout<<"["<<i<<"]:\t";
        if(!hashtable.at(i).empty()){
            for(auto &x : hashtable.at(i)){
                cout<<x<<"\t";
            }
        }
        cout<<endl;
    }
}


template<typename K, typename V>
int Hash<K, V>::hashU(K chiave) {
    int a = rand()%130;
    int b = rand()%512-a;
    int p = 9781;
    return (((a * chiave + b) % p) % N);
}

int main() {

    ifstream fileI;
    fileI.open("IN.txt", ios::in);
    int dim;
    fileI >> dim;
    auto *hash = new Hash<int, int>(dim, "IN.txt", "OUT.txt");
    hash->caricaHash();
    hash->printInfo();
    hash->elimina(4);
    cout<<endl;
    hash->printInfo();
    free(hash);


}
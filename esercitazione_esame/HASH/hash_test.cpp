//
// Created by nonnt66 on 27/01/25.
//
// FeroneOttobre.cpp : Questo file contiene la funzione 'main', in cui inizia e termina l'esecuzione del programma.
//

#include <iostream>
#include <list>
#include <map>
#include <string>
#include <cmath>
#include <ctime>
using namespace std;

#define A 19
#define N 5

//Struct per i Set
typedef struct Set {
    int r; //Rango
    string p; //Rappresentante
};

//Classe per la HashTable
class HT {
private:
    //Mappa con lista - HT
    map<int, list<string>> ht;
    //Mappa con set - Set
    map<string, Set> sets;
public:
    HT() {
        for (int i = 0; i < N; i++)
            ht[i] = list<string>();
    }
    //|-------------Metodi per la HT-------------|
    void ht_init(); //Metodo per inizializzare la HT
    int hash(int k); //Function di Hash normale
    void insert(int k, string s); //Insert nell'HT
    string find(int k); //Metodo di ricerca
    void elimina(int k); //Metodo di delete
    void prt(); //Metodo per la stampa
    int randomHash(int k); //Hash Universale
    //Getter per avere il riferimento alla HT
    map<int, list<string>>& getHT() { return ht; }
    //|-------------Metodi per i Set-------------|
    string findSet(string x);
    void makeSet(string x);
    void Union(string x, string y);
    void prt_sets();//Metodo di stampa
};
//Stampo il contenuto di tutti i set
void HT::prt_sets() {
    cout << "Sets (elem -> rappr)" << endl;
    for (auto& s : sets) {
        cout << s.first << " -> " << s.second.r << endl;
    }
}
//Metodo di Union
void HT::Union(string x, string y) {
    string rootX = this->findSet(x);
    string rootY = this->findSet(y);
    if (rootX != rootY) {
        if (this->sets[rootX].r >= this->sets[rootY].r) {
            this->sets[rootX].r++;
            this->sets[rootY].p = rootX;
        }
        else {
            this->sets[rootY].r++;
            this->sets[rootX].p = rootY;
        }
    }
}
//Metodo Make-Set
void HT::makeSet(string x) {
    this->sets[x] = { 0, x };
}
//Metodo Find-Set
string HT::findSet(string x) {
    if (this->sets[x].p != x) {
        this->sets[x].p = findSet(this->sets[x].p);
    }
    return this->sets[x].p;
}
//Function per l'Hashing Universale (generatore di hash)
int HT::randomHash(int k) {
    int a = rand() % 256;
    int b = rand() % 512 - a;
    int p = 691;
    return ((a * k + b) % p) % N;
}
//Metodo per stampare la HT (elementi non vuoti)
void HT::prt() {
    cout << "Contenuto della Hash Table:" << endl;
    for (int i = 0; i < ht.size(); i++) {
        cout << "Cella: " << i << " = ";
        if (!ht.at(i).empty()) {
            for (auto& s : ht.at(i)) {
                cout << s << " ";
            }
        }
        cout << endl;
    }
}
//Metodo di inizializzazione della HT
void HT::ht_init() {
    //Sarebbe da fare via file, faccio piu' rapidamente
    string s = "abcdefghijklmnopqrstuvwxyz";
    for (int i = 0; i < 5; i++) {
        insert(hash(i), string(1, s[i]));
        //Inserisco ogni volta un valore diverso (a+1 = b,...)
    }
}
//Metodo di hash con Moltiplicazione
int HT::hash(int k) {
    double A_factor = (sqrt(5) - 1) / 2; // Costante di Knuth per il metodo della moltiplicazione
    return (int)(floor(N * (k * A_factor - floor(k * A_factor))));
}
//Function per l'inserimento nella HT
void HT::insert(int k, string s) {
    int key = hash(k);//randomHash(k); //Universale
    if (ht.at(key).empty()) {
        ht.at(key).push_front(s);
    }
    else {
        ht.at(key).push_back(s);
    }
}
//Function per la ricerca nella HT
string HT::find(int k) {
    int key = hash(k);//randomHash(k);
    string fnd;
    if (ht.empty())
        return "La HT non esiste (null)";
    if (ht.at(key).empty()) {
        return "Non trovata";
    }
    else {
        fnd = "Elementi trovati per la chiave: " + key;
        fnd + "\n";
        for (const string& s : ht.at(key)) {
            fnd + s + " ";
        }
    }
    return fnd;
}
//Function per la rimozione
void HT::elimina(int k) {
    int key = hash(k);
    if (ht[key].empty()) {
        cout << "Cella vuota";
        return;
    }
    if (ht.empty()) {
        cout << "Table vuota";
        return;
    }
    ht[key].clear();
    cout << "Eliminato";
}

int main()
{
    //srand per cambiare il seed della rand ad ogni run
    srand(time(0));
    HT h;
    h.ht_init();
    h.prt();
    //Creazione dei set a partire dalla HT
    for (const auto& cell : h.getHT()) {
        for (const auto& el : cell.second) {
            h.makeSet(el);
        }
    }
    //Prendo elementi randomici dalla stringa
    //(elementi random della mia HT)

    //Effettuo le Union se ho gli elementi
    for (int i = 0; i < 3; i++) {
        int idx1 = rand() % N;
        int idx2 = rand() % N;
        if (!h.getHT()[idx1].empty() && !h.getHT()[idx2].empty()) {
            auto el1 = h.getHT()[idx1].front();
            auto el2 = h.getHT()[idx2].front();
            h.Union(el1, el2);
            cout << "Union effettuata tra: " << el1 << " ed " << el2 << endl;
        }
        else {
            cout << "Almeno una cella vuota" << endl;
        }
    }
    //Stampo i set che ho
    h.prt_sets();

    return 0;
}
//
// Created by nonnt66 on 24/01/25.
//

#include <fstream>
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <stack>
#include <queue>

using namespace std;


enum Colore {
    BIANCO, GRIGIO, NERO
};

enum tipoArco {
    ND, AVANTI, INDIETRO, TRASVERSALE, ALBERO
};

template<typename T>
class Edge;


template<typename T>
class Nodo {
public:
    int chiave;
    char label;
    Nodo<T> *sx, *dx;
    Nodo<T> *padre;
    vector<Edge<T> *> adj;
    Colore colore;
    int d, f;
public:
    explicit Nodo(T chiave) : chiave(chiave) {
        label = '\0';
        sx = dx = padre = nullptr;
        colore = BIANCO;
        d = f = 0;
    }

    Nodo() : Nodo(-1) {};
};

template<typename T>
class Edge {
public:
    Nodo<T> *u;
    Nodo<T> *v;
    int weight;
    tipoArco ta;
public:
    Edge(Nodo<T> *u, Nodo<T> *v, int weight) : u(u), v(v), weight(weight) { ta = ND; };

    Edge() : Edge(nullptr, nullptr, -1) {};
};

template<typename T>
class Graph {
public:
    std::vector<Nodo<T> *> V;
public:
    explicit Graph(int numNodi) {
        std::vector<Nodo<T> *> tmp(numNodi);
        V = tmp;
    }

    void addNodo(T chiave);

    void addEdge(T ukey, T vkey, T weight);

    vector<Nodo<T> *> DFS();

    void DFS_Visit(Nodo<T> *u, int time, vector<Nodo<T> *> &massimo);

    stack<Nodo<T> *> tsDFS();

    void tsDFS_visit(Nodo<T> *u, int tempo, stack<Nodo<T> *> &S);

    void BFS(int source);


    void printInfo();



    void getTransposed(Graph<T> &GT);


    void SCC_Visit(Nodo<T>* u,int tempo,queue<Nodo<T>*> &Q);

    Graph<T> *SCC(Graph<T>* G, Graph<T> &SCC);
};

template<typename T>
void Graph<T>::SCC_Visit(Nodo<T> *u,int tempo,queue<Nodo<T>*> &Q) {
    u->colore = GRIGIO;
    u->d = ++tempo;
    for(auto uvedge: u->adj){
        if(uvedge->v->colore == BIANCO){
            uvedge->v->padre = u;
            SCC_Visit(uvedge->v,tempo,Q);
        }
        else if(uvedge->v->colore == NERO){
            Q.push(uvedge->v);
        }
    }
    u->colore = NERO;
    u->d = ++tempo;

}

template<typename T>
void Graph<T>::getTransposed(Graph<T> &GT) {
    for(auto u: V){
        GT.addNodo(u->chiave);
    }
    for(auto u:V){
        for(auto uvedge: u->adj){
            Nodo<T>* tmp = uvedge->v;
            GT.addEdge(tmp->chiave,u->chiave,uvedge->weight);
        }
    }
}

template<typename T>
Graph<T> *Graph<T>::SCC(Graph<T>* G, Graph<T> &SCC) {
    auto S = tsDFS();
    auto *GT = new Graph<T>(15);
    G->getTransposed(*GT);
    queue<Nodo<T>*> Q;
    int tempo =0;
    while(!S.empty()){
        Nodo<T>* tmp = S.top();S.pop();
        if(GT->V[tmp->chiave]->colore == BIANCO){
            SCC_Visit(GT->V[tmp->chiave], tempo, Q);
            GT->addNodo(GT->V[tmp->chiave]->chiave);
            while(!Q.empty()){
                for(int i=0; i < SCC.V.size() - 1; i++){
                    if((SCC.V[i]->chiave) != -1){
                        SCC.addEdge(i, SCC.V.back()->chiave, 1);
                    }
                }
            }

            Q.pop();
        }

    }
    return GT;
}



template<typename T>
void Graph<T>::BFS(int source) {
    Nodo<T>* s = V[source];
    queue<Nodo<T>*> Q;
    for(auto &x : V){
        x->colore = BIANCO;
        x->padre = nullptr;
        x->d = -1000;
    }
    s->colore = GRIGIO;
    s->padre = nullptr;
    s->d = 0;
    Q.push(s);
    while(!Q.empty()){
        Nodo<T>* u = Q.front();Q.pop();
        for(auto &uvedge: u->adj ){
            Nodo<T>* v = uvedge->v;
            if(v->colore == BIANCO){
                v->colore = GRIGIO;
                v->padre = u;
                v->d = u->d+1;
                Q.push(v);
            }
        }
        u->colore = NERO;
    }
}

template<typename T>
void Graph<T>::tsDFS_visit(Nodo<T> *u, int tempo, stack<Nodo<T> *> &S) {
    u->colore = GRIGIO;
    u->d = ++tempo;
    for (auto uvedge: u->adj) {
        Nodo<T> *v = uvedge->v;
        if (v->colore == BIANCO) {
            v->padre = u;
            tsDFS_visit(v, tempo, S);
        }
    }
    u->colore = NERO;
    u->d = ++tempo;
    S.push(u);
}

template<typename T>
stack<Nodo<T> *> Graph<T>::tsDFS() {
    stack<Nodo<T> *> S;
    for (auto x: V) {
        x->colore = BIANCO;
        x->padre = nullptr;
    }
    int tempo = 0;
    for (auto x: V) {
        if (x->colore == BIANCO) {
            tsDFS_visit(x,tempo,S);
        }
    }
    return S;
}

template<typename T>
void Graph<T>::printInfo() {
    for (auto x: V) {
//        cout << x->chiave << endl;
        for (auto uvedge: x->adj) {
            cout << "\t" << uvedge->u->chiave << ":" << uvedge->v->chiave << ":" << uvedge->weight << endl;
        }
    }
}


template<typename T>
void Graph<T>::addNodo(T chiave) {
    V[chiave] = new Nodo<T>(chiave);
    V[chiave]->label = 'a' + chiave;
}

template<typename T>
void Graph<T>::addEdge(T ukey, T vkey, T weight) {
    auto *edge = new Edge<T>(V[ukey], V[vkey], weight);
    V[ukey]->adj.push_back(edge);
//    V[ukey]->adj.push_back(edge);
}

template<typename T>
vector<Nodo<T> *> Graph<T>::DFS() {
    int time = 0;
    for (auto x: V) {
        x->colore = BIANCO;
    }

    vector<Nodo<T> *> massimoTotale(0);
    for (auto x: V) {
        if (x->colore == BIANCO)
            DFS_Visit(x, time, massimoTotale);
    }
    return massimoTotale;
}


template<typename T>
void Graph<T>::DFS_Visit(Nodo<T> *u, int time, vector<Nodo<T> *> &massimo) {

    vector<Nodo<T> *> maxCiclo(0);
    u->colore = GRIGIO;
    u->d = ++time;
    for (auto uvedge: u->adj) {
        if (uvedge->v->colore == BIANCO) {
            uvedge->v->padre = uvedge->u;
            DFS_Visit(uvedge->v, time, massimo);

        }
        auto *tmp = uvedge->u;
        if (uvedge->v->colore == GRIGIO) {
//            maxCiclo.push_back(uvedge->v);
            while (tmp != uvedge->v) {
                maxCiclo.push_back(tmp);
                tmp = tmp->padre;
            }
        }
//        cout<<"size maxCiclo("<<maxCiclo.size()<<") -- size massimoTotale("<<massimo.size()<<")\n";
        if (maxCiclo.size() > massimo.size()) massimo = maxCiclo;
    }

    u->colore = NERO;
    u->f = ++time;
}//
// Created by nonnt66 on 25/01/25.
//


int main() {
    fstream f;
    f.open("grf.txt", ios::in);
    int numNodi = 0, numArchi = 0;
    f >> numNodi;
    f >> numArchi;
    cout << "num nodi: " << numNodi << " num archi: " << numArchi << std::endl;
//    map<int,int,int> *u;
    string b;
    int v, u, peso;
    auto *dg = new Graph<int>(numNodi);
    map<int, int, int> mappa;
    while (f >> u >> v >> peso) {
        dg->addNodo(u);
        dg->addNodo(v);
    }
    /*f.seekg(SEEK_SET);
    while (f >> u >> v >> peso) {
        dg->addEdge(u, v, peso);
    }*/
    f.close();
    dg->addEdge(0, 1, 10);
    dg->addEdge(0, 2, 10);
    dg->addEdge(0, 3, 10);
    dg->addEdge(2, 3, 10);
    dg->addEdge(3, 0, 10);
    dg->addEdge(2, 0, 10);
    dg->addEdge(1, 2, 10);
    dg->addEdge(2, 3, 10);
    dg->addEdge(3, 1, 10);
    dg->addEdge(1, 0, 10);
    vector<Nodo<int> *> ciclo = dg->DFS();
    fstream ff2;
    ff2.open("fine.txt", ios::out);

    for (auto &x: ciclo) {
        cout << x->label << " -> ";
        ff2 << x->chiave << " -> ";
    }
    ff2.close();
//    dg->printInfo();

    stack<Nodo<int>*> ts = dg->tsDFS();
    while(!ts.empty()){
        cout<<ts.top()->chiave<<endl;ts.pop();
    }

    dg->BFS(0);

    for(auto x : dg->V){
        cout<<x->chiave<<":"<<x->d<<endl;
    }
    dg->printInfo();
    auto SCC = new Graph<int>(numNodi);
    auto G = dg;
    dg->SCC(G, *SCC);
    free(dg);

}
//
// Created by nonnt66 on 24/01/25.
//
#include "grafo.h"


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
    V[ukey]->adj.push_back(new Edge<T>(V[ukey], V[vkey], weight));
//    V[ukey]->adj.push_back(edge);
}

template<typename T>
void Graph<T>::DFS() {
    int time = 0;
    for (auto x: V) {
        x->colore = BIANCO;
    }
    for (auto x: V) {
        if (x->colore == BIANCO)
            DFS_Visit(x, time);
    }
}

template<typename T>
void Graph<T>::DFS_Visit(Nodo<T> *u, int time) {
    u->colore = GRIGIO;
    u->d = ++time;
    for (auto v: V) {
        for (auto uvedge: v->adj) {
            if (uvedge->v->colore == BIANCO) {
                uvedge->v->padre = uvedge->u;
                DFS_Visit(uvedge->v, time);
            }
        }
    }
    u->colore = NERO;
    u->f = ++time;
}//
// Created by nonnt66 on 25/01/25.
//

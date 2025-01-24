//
// Created by nonnt66 on 24/01/25.
//

#include "grafo.h"

template<typename T>
void Graph<T>::addEdge(int ukey,int vkey, int weight) {
    V[ukey].adj->push_back(new Edge(V[ukey],V[vkey],weight));
}

template<typename T>
void Graph<T>::DFS() {
    int time = 0;
    for(auto x: V){
        x->colore = BIANCO;
    }
    for(auto x: V){
        if(x->colore == BIANCO)
            DFS_Visit(x);
    }
}

template<typename T>
void Graph<T>::DFS_Visit(Nodo<T>* u,int time) {
    u->colore = GRIGIO;
    u->d = ++time;
    for(auto v : V){
        for(auto uvedge : v){
            if(uvedge->colore == BIANCO){
                DFS_Visit(uvedge,time);
            }
        }
    }
    u->colore = NERO;
    u->f = ++time;
}



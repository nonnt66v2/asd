//
// Created by nonnt66 on 24/01/25.
//

#ifndef GRAFO_GRAFO_H
#define GRAFO_GRAFO_H

#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

enum Colore{BIANCO,GRIGIO,NERO};
template<typename T>
class Edge;

template<typename T>
class Nodo{
    int chiave;
    std::string label;
    Nodo<T>* sx,*dx;
    Nodo<T>* padre;
    vector<Edge<T>>* adj;
    Colore colore;
    int d,f;
public:
    Nodo(T chiave):chiave(chiave){label="";sx=dx=padre=nullptr;colore=BIANCO;d= f=0;}
    Nodo():Nodo(-1){};
};

template<typename T>
class Edge{
    Nodo<T>* u;
    Nodo<T>* v;
    int weight;
public:
    Edge(Nodo<T>* u,Nodo<T>* v,int weight):u(u),v(v),weight(weight){};
    Edge():Edge(nullptr, nullptr,-1) {};
};

template<typename T>
class Graph{
    Nodo<T>* V;
public:
    void addEdge(int ukey,int vkey, int weight);
    void DFS();
    void DFS_Visit(Nodo<T>* u,int time);
};
#endif //GRAFO_GRAFO_H

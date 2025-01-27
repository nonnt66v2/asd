//
// Created by nonnt66 on 24/01/25.
//

#ifndef GRAFO_GRAFO_H
#define GRAFO_GRAFO_H

#include <fstream>
#include <iostream>
#include <vector>
#include <map>
#include <string>

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

    void DFS();

    void DFS_Visit(Nodo<T> *u, int time);

    void printInfo();
};

#endif //GRAFO_GRAFO_H//
// Created by nonnt66 on 25/01/25.
//

#ifndef GRAFO1_GRAFO_H
#define GRAFO1_GRAFO_H

#endif //GRAFO1_GRAFO_H

#include <vector>
#include <string>
#include <iostream>
#include <climits>
#include <queue>
#include <algorithm>

using namespace std;

enum ColoreVertice {
    WHITE, GRAY, BLACK
};
enum TipoArco {
    ND, ARCO_AVANTI, ARCO_INDIETRO, ARCO_ALBERO, ARCO_CROSS
};

class Edge;

class nodo {
public:
    int chiave;
    int rank;
    string label;
    short color;
    int d;
    int f;
    nodo *p;
    vector<Edge *> adj;

    nodo(int key, string label) : chiave{key}, label{label} {}
};

class Edge {
public:
    nodo *u;
    nodo *v;
    int weight;
    short type;

    Edge(nodo *u, nodo *v, int weight, short type = ND) : u{u}, v{v}, weight{weight}, type{type} {}
};

class Graph {
public:
    vector<nodo *> V;

    nodo *addNodo(string label = "");

    virtual void addEdge(int ukey, int vkey, int wieght) = 0;

    void graphUnion(Edge *uv);

    vector<Edge *> getEdges();

    void printInfo();

    void printExtendedInfo();

    void BFS(int s);

    void DFS();

    void DFS_Visit(nodo *u, int &time);

    void makeSet(nodo *x);

    nodo *findSet(nodo *x);

    void unionGraph(nodo *x, nodo *y);

};

nodo *Graph::addNodo(std::string label) {
    string newlabel = "";
    if (label == "") {
        newlabel[0] = 97 + V.size();
    } else {
        newlabel = label;
    }
    V.push_back(new nodo(V.size(), newlabel));
    return V.back();
}

vector<Edge *> Graph::getEdges() {
    vector<Edge *> edge;
    for (auto u: V)
        for (auto uedge: u->adj)
            edge.push_back(uedge);
    return edge;
}

void Graph::printInfo() {
    for (auto &u: V) {
        std::cout << "vertex{" << u->chiave << "} " << u->label << " -> ";
        for (auto edge: u->adj)
            cout << edge->v->label << ",";
        cout << "\b\n";
    }
}

void Graph::BFS(int s) {
    for (auto u: V) {
        u->color = WHITE;
        u->p = nullptr;
        u->d = INT_MAX;
    }
    V[s]->color = GRAY;
    V[s]->p = nullptr;
    V[s]->d = 0;

    queue<nodo *> q;
    q.push(V[s]);
    while (!q.empty()) {
        nodo *u = q.front();
        q.pop();
        cout << "vertex{" << u->label << "}: \n";
        for (auto edge: u->adj) {
            if (edge->v->color == WHITE) {
                V[edge->v->chiave]->color = GRAY;
                V[edge->v->chiave]->p = u;
                V[edge->v->chiave]->d = u->d + 1;
                cout << "\tvertex{" << V[edge->v->chiave]->label << "}: \n";
                q.push(V[edge->v->chiave]);
                cout << "\t dimensione coda -> " << q.size() << "\n";
            }

        }
        u->color = BLACK;
//        printInfo();
    }

}

void Graph::printExtendedInfo() {
    for (auto u: V) {
        std::cout << "vertex{" << u->label << "} -> \n";
        std::cout << "\t chiave: " << u->chiave << "\n";
        if (u->p != nullptr) {
            std::cout << "\t padre: " << u->p->label << "\n";
        }
        std::cout << "\t inizio: " << u->d << "\n";
        std::cout << "\t fine: " << u->f << "\n";
        std::cout << "\t colore: " << u->color << "\n";

    }
}

void Graph::DFS_Visit(nodo *u, int &time) {
    u->color = GRAY;
    u->d = ++time;
    cout << "vertex{" << u->label << ", " << time << "}: \n";
    for (auto edge: u->adj) {
        if (edge->v->color == WHITE) {
            edge->v->p = u;
            DFS_Visit(edge->v, time);
        }
    }
    u->color = BLACK;
    u->f = ++time;
}

void Graph::DFS() {
    for (auto u: V) {
        u->color = WHITE;
        u->p = nullptr;
    }
    int time = 0;
    for (auto u: V) {
        if (u->color == WHITE) {
            DFS_Visit(u, time);
        }
    }
}

void Graph::makeSet(nodo *x) {
    x->p = x;
}

nodo *Graph::findSet(nodo *x) {
    if (x->p != x) {
            x->p = findSet(x->p);
    }
    return x->p;
}

void Graph::unionGraph(nodo *x, nodo *y) {
    nodo *a = findSet(x);
    nodo*b = findSet(y);
    if(a->rank > b->rank){
        b->p = a ;
    }
    else {
        a->p = b;
        if(a->rank == b->rank){
            b->rank++;
        }
    }
}



class DirectedGraph : public Graph {
public:
    DirectedGraph(int n = 0);

    void addEdge(int ukey, int vkey, int weight);

    void getTransposed(DirectedGraph &dgt);

    ~DirectedGraph();


};

DirectedGraph::DirectedGraph(int n) {
    for (int i = 0; i < n; i++)
        addNodo();
}

void DirectedGraph::addEdge(int ukey, int vkey, int weight) {
    V[ukey]->adj.push_back(new Edge(V[ukey], V[vkey], weight));
}

void DirectedGraph::getTransposed(DirectedGraph &dgt) {
    for (auto u: V) {
        dgt.addNodo(u->label);
    }

    for (auto u: V) {
        for (auto uedge: u->adj) {
            nodo *v = uedge->v;
            dgt.addEdge(v->chiave, u->chiave, uedge->weight);
        }
    }
}

DirectedGraph::~DirectedGraph() {
    for (auto u: V) {
        for (auto uedge: u->adj) {
            delete uedge;
        }
        delete u;
    }
}

class UndirectedGraph : public Graph {
public:
    UndirectedGraph(int n = 0);

    void addEdge(int ukey, int vkey, int wieght);

    UndirectedGraph Kruskal(UndirectedGraph *g);
    ~UndirectedGraph();

};

UndirectedGraph::UndirectedGraph(int n) {
    for (int i = 0; i < n; i++) {
        addNodo();
    }
}

void UndirectedGraph::addEdge(int ukey, int vkey, int weight) {
    V[vkey]->adj.push_back(new Edge(V[vkey], V[ukey], weight));
    V[ukey]->adj.push_back(new Edge(V[ukey], V[vkey], weight));
}

UndirectedGraph::~UndirectedGraph() {
    for (auto u: V) {
        for (auto uedge: u->adj) {
            delete uedge;
        }
        delete u;
    }
}

bool edgeCompare(Edge* uv, Edge* xy){
    return (uv->weight < xy->weight);
}
UndirectedGraph UndirectedGraph::Kruskal(UndirectedGraph *g) {
    UndirectedGraph A;
    for(auto u : g->V){
        makeSet(u);
    }
    vector<Edge*> edges = g->getEdges();
    sort(edges.begin(),edges.end(),edgeCompare);
    for(auto uv: edges){
        if(findSet(uv->u) != findSet(uv->v)){
            A.unionGraph(uv->u,uv->v);
            union
        }
    }
}


int main(int argc, char **argv) {
    DirectedGraph *dg = new DirectedGraph();
    nodo *a = dg->addNodo("a");
    nodo *b = dg->addNodo("b");
    dg->addEdge(a->chiave, b->chiave, 10);
    nodo *c = dg->addNodo("c");
    nodo *d = dg->addNodo("d");
    dg->addEdge(c->chiave, d->chiave, 23);
    nodo *e = dg->addNodo("e");
    nodo *f = dg->addNodo("f");
    dg->addEdge(e->chiave, f->chiave, 670);

//    dg->printInfo();

//    DirectedGraph *dgt = new DirectedGraph();
//    dg->getTransposed(*dgt);
    dg->addEdge(a->chiave, c->chiave, 13);
    dg->addEdge(a->chiave, d->chiave, 16);
    dg->addEdge(d->chiave, e->chiave, 17);
    vector<Edge *> edges = dg->getEdges();
    for (auto u: edges) {
        cout << u->u->label << " " << u->v->label << " " << u->weight << "\n";
    }
    dg->BFS(0);
    cout << "\n\nNON ORIENTATO\n\n";
    UndirectedGraph *ung = new UndirectedGraph();
    nodo *h = ung->addNodo("h");
    nodo *g = ung->addNodo("g");
    ung->addEdge(h->chiave, g->chiave, 300);
    vector<Edge *> unEdges = ung->getEdges();
    for (auto u: unEdges) {
        cout << u->u->label << " " << u->v->label << " " << u->weight << "\n";
    }
    ung->printInfo();
    ung->BFS(h->chiave);
    dg->printExtendedInfo();

    cout << "\n\nDFS\n\n";

    dg->DFS();
    dg->printExtendedInfo();
}
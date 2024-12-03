#include <vector>
#include <string>
#include <iostream>

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
    vector<Edge*> adj;

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
    for (auto& u: V)
        for (auto& uedge: u->adj)
            edge.push_back((Edge*)uedge);
    return edge;
}

void Graph::printInfo() {
    for(auto& u:V){
        std::cout<<"vertex{"<<u->chiave<<"} "<<u->label<<" -> ";
        for(auto edge:u->adj)
            cout<<edge->v->label<<",";
        cout<<"\b\n";
    }
}
class DirectedGraph : public Graph{
public:
    DirectedGraph(int n=0);
    void addEdge(int ukey, int vkey, int wieght);
    void getTransposed(DirectedGraph& dgt);
    ~DirectedGraph();

};

DirectedGraph::DirectedGraph(int n){
    for(int i=0; i<n; i++)
        addNodo();
}

void DirectedGraph::addEdge(int ukey, int vkey, int weight) {
    V[ukey]->adj.push_back(new Edge(V[ukey],V[vkey],weight));
}

void DirectedGraph::getTransposed(DirectedGraph &dgt) {
    for(auto u:V){
        dgt.addNodo(u->label);
    }

    for(auto u:V){
        for(auto uedge:u->adj){
            nodo *v = uedge->v;
            dgt.addEdge(v->chiave,u->chiave,uedge->weight);
        }
    }
}

int main(int argc, char **argv) {
    DirectedGraph *dg = new DirectedGraph(12);
    dg->addEdge(0,1,12);
    dg->addEdge(0,2,13);
    dg->addEdge(0,3,14);
    dg->addEdge(0,4,15);
    dg->printInfo();
}
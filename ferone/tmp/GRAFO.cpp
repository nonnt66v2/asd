#include <iostream>
#include <vector>
#include <climits>
#include <queue>
#include <stack>
#include <algorithm> // Aggiunto per std::sort

enum vertixesColor{ WHITE, GRAY, BLACK };
enum edgeType{ NDEFINED, TREE_EDGE, BACK_EDGE, FORWARD_EDGE, CROSS_EDGE };

class Edge; // Forward declaration

class Node{
public:
    int key;
    int rank;
    std::string label;
    short color;
    int d;
    int f;
    Node* p;
    std::vector<Edge*> adj;
    Node(int key, std::string label) : key{key}, label{label}{}
};

class Edge{
public:
    Node* u;
    Node* v;
    int weight;
    short type;
    Edge(Node* u, Node* v, int weight = 0, short type = NDEFINED)
            : u{u}, v{v}, weight{weight}, type{type}{}
};

class Graph{
public:
    std::vector<Node*> V;
    Node* addNode(std::string label = "");
    virtual void addEdge(int ukey, int vkey, int weight = 0) = 0;
    virtual void graphUnion(Edge* uv); // Reso virtuale
    std::vector<Edge*> getEdges();
    void printInfo();
    void printExtendedInfo();
};

Node* Graph::addNode(std::string label){
    std::string newlabel(1,0);
    if(label == "")
        newlabel[0] = 97+V.size();
    else
        newlabel = label;
    V.push_back(new Node(V.size(), newlabel));
    return V.back();
}

std::vector<Edge*> Graph::getEdges(){
    std::vector<Edge*> edges;
    for(auto& u:V)
        for(auto& uedge:u->adj)
            edges.push_back(uedge);
    return edges;
}

void Graph::printInfo(){
    for(auto& u:V){
        std::cout<<"vertex{"<<u->key<<"} "<<u->label<<" -> ";
        for(auto& edge:u->adj)
            std::cout<<edge->v->label<<",";
        std::cout<<"\b\n";
    }
}

class DirectedGraph : public Graph{
public:
    DirectedGraph(int n=0);
    void addEdge(int ukey, int vkey, int weight = 0);
    void getTransposed(DirectedGraph& dgt);
    ~DirectedGraph();
};

DirectedGraph::DirectedGraph(int n){
    for(int i=0; i<n; i++)
        addNode();
}

void DirectedGraph::addEdge(int ukey, int vkey, int weight){
    V[ukey]->adj.push_back(new Edge(V[ukey],V[vkey],weight));
}

void DirectedGraph::getTransposed(DirectedGraph& dgt){
    for(auto& u:V)
        dgt.addNode(u->label);
    for(auto& u:V)
        for(auto& uedge:u->adj){
            Node* v = uedge->v;
            dgt.addEdge(v->key, u->key, uedge->weight);
        }
}

DirectedGraph::~DirectedGraph(){
    for(auto& u:V){
        for(auto& edge:u->adj)
            delete edge;
        delete u;
    }
}

class UndirectedGraph : public Graph{
public:
    UndirectedGraph(int n=0);
    void addEdge(int ukey, int vkey, int weight = 0);
    ~UndirectedGraph();
};

UndirectedGraph::UndirectedGraph(int n){
    for(int i=0; i<n; i++)
        addNode();
}

void UndirectedGraph::addEdge(int ukey, int vkey, int weight){
    V[ukey]->adj.push_back(new Edge(V[ukey],V[vkey],weight));
    V[vkey]->adj.push_back(new Edge(V[vkey],V[ukey],weight));
}

UndirectedGraph::~UndirectedGraph(){
    for(auto& u:V){
        for(auto& edge:u->adj)
            delete edge;
        delete u;
    }
}

void BFS(Graph* G, int source){
    Node* s = G->V[source];
    for(auto u:G->V){
        u->color = WHITE;
        u->p = nullptr;
        u->d = INT_MAX;
    }
    s->color = GRAY;
    s->d = 0;
    s->p = nullptr;
    std::queue<Node*> Q;
    Q.push(s);
    while(!Q.empty()){
        Node* u = Q.front(); Q.pop();
        for(auto& uedge:u->adj){
            Node* v = uedge->v;
            if(v->color == WHITE){
                v->color = GRAY;
                v->p = u;
                v->d = u->d + 1;
                Q.push(v);
            }
        }
        u->color = BLACK;
    }
}

int t;

void DFSvisit(Node* u){
    u->color = GRAY;
    u->d = ++t;
    for(auto& uedge:u->adj){
        Node* v = uedge->v;
        if(v->color == WHITE){
            v->p = u;
            DFSvisit(v);
        }
    }
    u->color = BLACK;
    u->f = ++t;
}

void DFS(Graph* G){
    for(auto& u:G->V){
        u->color = WHITE;
        u->p = nullptr;
    }
    t = 0;
    for(auto u:G->V)
        if(u->color == WHITE)
            DFSvisit(u);
}

void ECvisit(Node* u){
    u->color = GRAY;
    for(auto& uedge:u->adj){
        Node* v = uedge->v;
        if(v->color == WHITE){
            uedge->type = TREE_EDGE;
            ECvisit(v);
        }
        else if(v->color == GRAY)
            uedge->type = BACK_EDGE;
        else
            uedge->type = (u->d < v->d)? FORWARD_EDGE : CROSS_EDGE;
    }
    u->color = BLACK;
}

void edgeClassification(DirectedGraph* G){
    for(auto& u:G->V)
        u->color = WHITE;
    for(auto u:G->V)
        if(u->color == WHITE)
            ECvisit(u);
}



void tsDFSvisit(Node* u, std::stack<Node*>& S){
    u->color = GRAY;
    u->d = ++t;
    for(auto& uedge:u->adj){
        Node* v = uedge->v;
        if(v->color == WHITE){
            v->p = u;
            tsDFSvisit(v,S);
        }
    }
    u->color = BLACK;
    u->f = ++t;
    S.push(u);
}


std::stack<Node*> tsDFS(DirectedGraph *G){
    std::stack<Node*> S;
    for(auto& u:G->V){
        u->color = WHITE;
        u->p = nullptr;
    }
    t=0;
    for(auto& u:G->V)
        if(u->color == WHITE)
            tsDFSvisit(u,S);
    return S;
}

void sccDFSvisit(Node* u, std::string& sccLabel, std::queue<std::string>& Q){
    u->color = GRAY;
    u->d = ++t;
    for(auto uedge:u->adj){
        Node* v = uedge->v;
        if(v->color == WHITE){
            sccLabel += v->label + ",";
            v->p = u;
            sccDFSvisit(v,sccLabel,Q);
        }
        else if(v->color == BLACK){
            Q.push(v->label);
        }
    }
    u->color = BLACK;
    u->f = ++t;
}

void makeset(Node* x){
    x->p = x;
}
void SCC(DirectedGraph G, DirectedGraph& GSCC){
    DirectedGraph GT;
    std::string sccLabel = "";
    std::queue<std::string> Q;
    std::stack<Node*> S = tsDFS(&G);
    G.getTransposed(GT);
    while(!S.empty()){
        Node* v = S.top(); S.pop();
        Node* gtv = GT.V[v->key];
        if( gtv->color == WHITE ){
            sccLabel += "(" + gtv->label + ",";
            sccDFSvisit(gtv,sccLabel,Q);
            sccLabel += "\b)";
            GSCC.addNode(sccLabel);
            sccLabel = "";
            while(!Q.empty()){
                for(int i=0; i<GSCC.V.size()-1; i++){
                    if( (GSCC.V[i]->label).find(Q.front()) != std::string::npos){
                        GSCC.addEdge(i, GSCC.V.back()->key);
                        break;
                    }
                }
                Q.pop();
            }
        }
    }
}



Node* findset(Node* x){
    if(x != x->p)
        x->p = findset(x->p);
    return x->p;
}

void unionsets(Node* x, Node* y){
    Node* rx = findset(x);
    Node* ry = findset(y);
    if(rx->rank > ry->rank)
        ry->p = rx;
    else
        rx->p = ry;
    if(rx->rank == ry->rank)
        ry->rank++;
}

bool edgeWeightComparison(Edge* uv, Edge* xy){
    return (uv->weight < xy->weight);
}

void kruskalMST(UndirectedGraph G, UndirectedGraph &A){
    for(auto& u:G.V)
        makeset(u);
    std::vector<Edge*> edges = G.getEdges();
    std::sort(edges.begin(), edges.end(), edgeWeightComparison);
    for(auto& uv:edges)
        if(findset(uv->u) != findset(uv->v)){
            A.graphUnion(uv);
            unionsets(uv->u, uv->v);
        }
}

void Graph::graphUnion(Edge* uv){
    Node *u, *v;
    bool found = false;
    for(auto& x:V)
        if(x->label == uv->u->label){
            found = true;
            u = x;
            break;
        }
    if(!found)
        u = addNode(uv->u->label);
    found = false;
    for(auto& x:V)
        if(x->label == uv->v->label){
            found = true;
            v = x;
            break;
        }
    if(!found)
        v = addNode(uv->v->label);
    addEdge(u->key,v->key,uv->weight);
}

int main(){
    DirectedGraph *dg = new DirectedGraph();
    dg->addNode("a");
    dg->addNode("b");
    dg->addEdge(0,1,40);
    dg->printInfo();
    delete dg; // Aggiunto per evitare memory leak

}
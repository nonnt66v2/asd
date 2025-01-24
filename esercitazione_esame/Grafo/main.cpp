#include "grafo.h"



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
    while (f >> u) {
        f >> v;
        f >> peso;
        dg->addNodo(u);
        dg->addNodo(v);
        dg->addEdge(u, v, peso);

    }
    f.close();
    dg->DFS();
    dg->printInfo();

    /*for (auto x: dg->V) {
        cout<<x->chiave<<":"<<x->label<<endl;
    }*/

    free(dg);


}
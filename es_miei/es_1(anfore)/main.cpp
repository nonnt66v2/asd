//Si hanno due anfore, una può contenere al massimo 5 litri
//        d’acqua, l’altra 3 litri. Si vuole misurare solo con l’ausilio
//        delle due anfore la quantità di 4 litri d’acqua.
//• Classe Indovinello
//– Risolve l'indovinello: ha due attributi anfora una da 3 lt ed una
//da 5 lt ed un metodo risolvi() che risolve l'indovinello mostrando
//a video il contenuto delle due anfore ad ogni passo della
//        risoluzione.
//– Es.: Riempi anfora A: A=3 B=0
//Scrivere un main che mostri la soluzione dell'indovinello

#include <iostream>

using namespace std;

class Anfora {
public:
    int capienzaMax;
    int capienzaAttuale;
public:
    Anfora(int capienza) { this->capienzaMax = capienza; };

    void riempi() { capienzaAttuale = capienzaMax; };

    void svuota() { capienzaAttuale = 0; };
};

class Indovinello {
private:
    Anfora A = Anfora(5);
    Anfora B = Anfora(3);

public:
    void risolvi(){

        cout<<"A = ";
    }

};

int main(int argc, char **argv) {
    Indovinello risolvi;
    risolvi.risolvi();
}




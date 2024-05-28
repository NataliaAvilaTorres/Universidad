#ifndef CARTA_H
#define CARTA_H

#include<string>
using namespace std;

class Carta
{
private:
    int id_carta;
    string tipo_carta; //(TR) Territorio - (CM) Comodin
    int territorio;
    int figura; //(1) Soldado - (2) Canon - (3) Caballo - (0) Los tres

public:
    Carta();
    Carta(int,string,int,int);
    ~Carta();

    int getId_carta();
    string getTipo_carta();
    int getTerritorio();
    int getFigura();
};

#endif // CARTA_H
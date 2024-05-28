#ifndef CONTINENTE_H
#define CONTINENTE_H

#include<list>
#include "Pais.h"

class Continente
{
private:
    int id_continente;
    string nombre_continente;
    list<Pais>paises;
public:
    Continente ();
    Continente(int,string,list<Pais>);
    ~Continente();

    int getId_continente();
    string getNombre_continente();
    list<Pais> getPaises();
};

#endif // CONTINENTE_H   
#include "Continente.h"

Continente::Continente()
{

}
Continente::Continente(int id_continente,string nombre_continente,list<Pais>paises)
{
    this->id_continente = id_continente;
    this->nombre_continente = nombre_continente;
    this->paises= paises;
}

int Continente::getId_continente()
{
    return id_continente;
}

string Continente::getNombre_continente()
{
    return nombre_continente;
}


list<Pais> Continente::getPaises()
{
    return paises;
}

Continente::~Continente()
{
    //dtor
}


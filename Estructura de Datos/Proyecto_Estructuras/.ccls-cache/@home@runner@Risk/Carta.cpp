#include "Carta.h"

Carta::Carta(int id_carta,string tipo_carta,int territorio,int figura)
{
    this->id_carta = id_carta;
    this->tipo_carta = tipo_carta;
    this->territorio = territorio;
    this->figura = figura;

}

Carta::Carta()
{
    //ctor
}

Carta::~Carta()
{
    //dtor
}

int Carta::getId_carta()
{
    return id_carta;
}

string Carta::getTipo_carta()
{
    return tipo_carta;
}

int Carta::getTerritorio()
{
    return territorio;
}

int Carta::getFigura()
{
    return figura;
}
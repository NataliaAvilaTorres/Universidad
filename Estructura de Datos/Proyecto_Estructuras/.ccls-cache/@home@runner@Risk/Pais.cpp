#include "Pais.h"

Pais::Pais()
{

}

Pais::Pais(int id_pais,string nombre_pais,int color,int cantidad_Tropas,list<int>paises_cercanos)
{
    this->id_pais = id_pais;
    this->nombre_pais = nombre_pais;
    this->color = color;
    this->cantidad_Tropas = cantidad_Tropas;
    this->paises_cercanos = paises_cercanos;
}

string Pais::getNombre_pais()
{
    return nombre_pais;
}

int Pais::getId_pais()
{
    return id_pais;
}

int Pais::getColor()
{
    return color;
}

int Pais::getCantidad_Tropas()
{
    return cantidad_Tropas;
}

list<int>& Pais::getPaises_cercanos()
{
    return paises_cercanos;
}

void Pais::setNombre_pais(string nombre_pais)
{
    this->nombre_pais = nombre_pais;
}

void Pais::setId_pais(int id_pais)
{
    this->id_pais = id_pais;
}

void Pais::setColor(int color)
{
    this->color = color;
}

void Pais::setCantidad_Tropas(int cantidad_Tropas)
{
    this->cantidad_Tropas = cantidad_Tropas;
}

void Pais::setPaises_cercanos(list<int> paises_cercanos)
{
    this->paises_cercanos = paises_cercanos;
}

Pais::~Pais()
{
    //dtor
}
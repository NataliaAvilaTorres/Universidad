#include "Jugador.h"
#include <iostream>
using namespace std;

Jugador::Jugador()
{

}

Jugador::Jugador(string nombre_jugador,int color_jugador,int cantidad_Tropas,list<Pais> paises_jugador,list<Carta> cartas_jugador)
{
    this->nombre_jugador = nombre_jugador;
    this->color_jugador = color_jugador;
    this->cantidad_Tropas = cantidad_Tropas;
    this->paises_jugador = paises_jugador;
    this->cartas_jugador = cartas_jugador;
}

Jugador::~Jugador()
{

}

//GETTERS
string Jugador::getNombre_jugador()
{
    return nombre_jugador;
}


int Jugador::getColor_jugador()
{
    return color_jugador;
}

int Jugador::getCantidad_Tropas()
{
    return cantidad_Tropas;
}

list<Pais>& Jugador::getPaises_jugador()
{
    return paises_jugador;
}

list<Carta>& Jugador::getCartas_jugador()
{
    return cartas_jugador;
}

//SETTERS
void Jugador::setNombre_jugador(string nombre_jugador)
{
    this->nombre_jugador = nombre_jugador;
}


void Jugador::setColor_jugador(int color_jugador)
{
    this->color_jugador = color_jugador;
}

void Jugador::setCantidad_Tropas(int cantidad_Tropas)
{
    this->cantidad_Tropas = cantidad_Tropas;
}

void Jugador::setPaises_jugador(list<Pais> paises_jugador)
{
    this->paises_jugador = paises_jugador;
}

void Jugador::setCartas_jugador(list<Carta> cartas_jugador)
{
    this->cartas_jugador = cartas_jugador;
}

void Jugador::agregarPais(Pais paisNuevo)
{
    paises_jugador.push_back(paisNuevo);
}

void Jugador::agregarCarta(Carta cartaNueva)
{
    cartas_jugador.push_back(cartaNueva);
}
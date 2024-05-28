#ifndef JUGADOR_H
#define JUGADOR_H

#include<list>
#include"Pais.h"
#include"Carta.h"

class Jugador
{
private:
    string nombre_jugador;
    int color_jugador;
    int cantidad_Tropas;
    list<Carta> cartas_jugador;
    list<Pais> paises_jugador;

public:
    Jugador();
    Jugador(string,int,int,list<Pais>,list<Carta>);
    ~Jugador();

    string getNombre_jugador();
    int getColor_jugador();
    int getCantidad_Tropas();
    list<Pais>& getPaises_jugador();
    list<Carta>& getCartas_jugador();

    void setNombre_jugador(string);
    void setColor_jugador(int);
    void setCantidad_Tropas(int);
    void setPaises_jugador(list<Pais>);
    void setCartas_jugador(list<Carta>);

    void agregarPais(Pais);
    void agregarCarta(Carta);
};

#endif // JUGADOR_H
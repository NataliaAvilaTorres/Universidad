#ifndef GRAFO_H
#define GRAFO_H

#include"Jugador.h"
#include<list>

class Grafo
{
private:
    list<Pais> vertices; //Lista de vertices (paises)
public:
    Grafo();
    Grafo(list<Pais>);
    ~Grafo();

    list<Pais>& getVertices();

    list<int> obternerAdyacentes(int); //Obtiene los vertices adyacentes al parametro 'int -'
    int calcularDistancia(int,int); //Calcula el camino mas corto entre dos nodos

    void costoConquista(int,int);
    void imprimirGrafo();
    void ConquistaMasBarata(int);
};

#endif // GRAFO_H
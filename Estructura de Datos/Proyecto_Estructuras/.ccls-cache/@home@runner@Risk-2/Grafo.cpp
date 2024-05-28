#include "Grafo.h"
#include "Pais.h"
#include <map>
#include <queue>
#include <iostream>
#include <climits>
using namespace std;


Grafo::Grafo()
{

}

Grafo::Grafo(list<Pais> vertices)
{
    this->vertices = vertices;
}

Grafo::~Grafo()
{
  
}

list<Pais>& Grafo::getVertices()
{
    return vertices;
}



list<int> Grafo::obternerAdyacentes(int v)
{
    for (list<Pais>::iterator it = vertices.begin(); it != vertices.end(); ++it)
    {
        if ((*it).getId_pais() == v)
        {
            return (*it).getPaises_cercanos();
        }
    }
    // Devuelve una lista vacía si no se encuentra el país
    return list<int>();
}

int Grafo::calcularDistancia(int id_origen, int id_Destino)
{
    map<int, int> distancias;

    for(list<Pais>::iterator it = vertices.begin(); it != vertices.end(); it++)
    {
        distancias[(*it).getId_pais()] = INT_MAX;
    }

    queue<int> cola;
    cola.push(id_origen);
    distancias[id_origen] = 0;

    while(!cola.empty())
    {
        int idActual = cola.front();
        cola.pop();

        //Obtener los vecinos del nodo actual
        list<int> vecinos = obternerAdyacentes(idActual);
        for(list<int>::iterator it = vecinos.begin(); it != vecinos.end(); it++)
        {
            if(distancias[*it] == INT_MAX)
            {
                //Si el vecino no ha sido visitado, actualizar su distancia y añadirlo a la cola
                distancias[*it] = distancias[idActual] + 1;
                cola.push(*it);
            }
        }
    }
    return distancias[id_Destino];
}

void Grafo::costoConquista(int id_terriObjetivo, int id_jugador)
{
    //1. se debe encontrar el territorio controlado mas cercano al objetivo
    int id_terriAtacante = -1;
    int min_Distancia = INT_MAX;
    int validoNoPosee = 0;
    int existe = 0;

    for(list<Pais>::iterator it = vertices.begin(); it != vertices.end(); it++)
    {
        if((*it).getId_pais() == id_terriObjetivo &&(*it).getColor() == id_jugador){
          existe = 1;
          validoNoPosee = 1;
        }
      
        if((*it).getColor() == id_jugador)
        {
          
            //Este territorio es controlado por el jugador, se calcula la distancia al objetivo
            int distancia = calcularDistancia((*it).getId_pais(), id_terriObjetivo);

            if(distancia < min_Distancia)
            {
                min_Distancia = distancia;
                id_terriAtacante = (*it).getId_pais();
            }
            existe = 1;
        }
    }

    //2. Se tiene el territorio desde donde atacar, se procede a realizar el ataque
    if(id_terriAtacante != -1 && validoNoPosee == 0 && existe == 1)
    {
      cout<<endl<<"COSTO CONQUISTA:"<<endl;
        cout<<endl<<"Atacando desde el territorio "<<id_terriAtacante<<" al territorio "<<id_terriObjetivo<<endl;
        //Llamar a la funcion atacar (id_terriAtacante, id_terriObjetivo)
    }
    else
    {
        cout<<endl<<"El jugador "<<id_jugador<<" no controla ningun territorio cercano al objetivo, o bien hace parte de sus territorios."<<endl<<endl;
    }
}

void Grafo::imprimirGrafo()
{
        for (list<Pais>::iterator it = vertices.begin(); it != vertices.end(); ++it) {
        cout << "ID del país: " << (*it).getId_pais() << endl;
        cout << "Nombre del país: " << (*it).getNombre_pais() << endl;
        cout << "Color: " << (*it).getColor() << endl;
        cout << "Cantidad de tropas: " << (*it).getCantidad_Tropas() << endl;
        cout << "Países cercanos: ";
        list<int> paises_cercanos = (*it).getPaises_cercanos();
        for (list<int>::iterator jt = paises_cercanos.begin(); jt != paises_cercanos.end(); ++jt) {
            cout << *jt << " ";
        }
        cout << endl << "------------------------" << endl;
    }
}

void Grafo::ConquistaMasBarata(int id_terriOrigen)
{
  
}

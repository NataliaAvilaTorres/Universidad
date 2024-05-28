#include "Grafo.h"
#include "Pais.h"
#include <climits>
#include <iostream>
#include <map>
#include <queue>
using namespace std;

Risk risk;
Grafo::Grafo() {}

Grafo::Grafo(list<Pais> vertices) { this->vertices = vertices; }

Grafo::~Grafo() {}

list<Pais> &Grafo::getVertices() { return vertices; }

list<int> Grafo::obternerAdyacentes(int v) {
  for (list<Pais>::iterator it = vertices.begin(); it != vertices.end(); ++it) {
    if ((*it).getId_pais() == v) {
      return (*it).getPaises_cercanos();
    }
  }
  // Devuelve una lista vacía si no se encuentra el país
  return list<int>();
}

int Grafo::calcularDistancia(int id_origen, int id_Destino) {
  map<int, int> distancias;

  for (list<Pais>::iterator it = vertices.begin(); it != vertices.end(); it++) {
    distancias[(*it).getId_pais()] = INT_MAX;
  }

  queue<int> cola;
  cola.push(id_origen);
  distancias[id_origen] = 0;

  while (!cola.empty()) {
    int idActual = cola.front();
    cola.pop();

    // Obtener los vecinos del nodo actual
    list<int> vecinos = obternerAdyacentes(idActual);
    for (list<int>::iterator it = vecinos.begin(); it != vecinos.end(); it++) {
      if (distancias[*it] == INT_MAX) {
        // Si el vecino no ha sido visitado, actualizar su distancia y añadirlo
        // a la cola
        distancias[*it] = distancias[idActual] + 1;
        cola.push(*it);
      }
    }
  }
  return distancias[id_Destino];
}

void Grafo::costoConquista(int id_terriObjetivo, int id_jugador) {
  // 1. se debe encontrar el territorio controlado mas cercano al objetivo
  int id_terriAtacante = -1;
  int min_Distancia = INT_MAX;
  int validoNoPosee = 0;
  int existe = 0;

  for (list<Pais>::iterator it = vertices.begin(); it != vertices.end(); it++) {
    if ((*it).getId_pais() == id_terriObjetivo &&
        (*it).getColor() == id_jugador) {
      existe = 1;
      validoNoPosee = 1;
    }

    if ((*it).getColor() == id_jugador) {

      // Este territorio es controlado por el jugador, se calcula la distancia
      // al objetivo
      int distancia = calcularDistancia((*it).getId_pais(), id_terriObjetivo);

      if (distancia < min_Distancia) {
        min_Distancia = distancia;
        id_terriAtacante = (*it).getId_pais();
      }
      existe = 1;
    }
  }

  // 2. Se tiene el territorio desde donde atacar, se procede a realizar el
  // ataque
  if (id_terriAtacante != -1 && validoNoPosee == 0 && existe == 1) {
    cout << endl << "COSTO CONQUISTA:" << endl;
    cout << endl
         << "Atacando desde el territorio " << id_terriAtacante
         << " al territorio " << id_terriObjetivo << endl;
    // Llamar a la funcion atacar (id_terriAtacante, id_terriObjetivo)
  } else {
    cout << endl
         << "El jugador " << id_jugador
         << " no controla ningun territorio cercano al objetivo, o bien hace "
            "parte de sus territorios."
         << endl
         << endl;
  }
}

void Grafo::imprimirGrafo() {
  for (list<Pais>::iterator it = vertices.begin(); it != vertices.end(); ++it) {
    cout << "ID del país: " << (*it).getId_pais() << endl;
    cout << "Nombre del país: " << (*it).getNombre_pais() << endl;
    cout << "Color: " << (*it).getColor() << endl;
    cout << "Cantidad de tropas: " << (*it).getCantidad_Tropas() << endl;
    cout << "Países cercanos: ";
    list<int> paises_cercanos = (*it).getPaises_cercanos();
    for (list<int>::iterator jt = paises_cercanos.begin();
         jt != paises_cercanos.end(); ++jt) {
      cout << *jt << " ";
    }
    cout << endl << "------------------------" << endl;
  }
}

void Grafo::ConquistaMasBarata(list<Jugador>::iterator actual,int id_terriDestino) 
{
    int n = 43; // número de territorios en el juego.

    // Iteramos sobre todos los territorios del juego.
    for (int id_terriOrigen = 1; id_terriOrigen <= n; id_terriOrigen++) {
        vector<int> distancias(n, INT_MAX); // vector para almacenar las distancias minimas desde el territorio de origen.
        vector<int> previos(n, -1); // vector para almacenar los nodos previos en el camino mas corto.
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> cola; /* el pair<int, int> especifica que cada elemento en la cola de prioridad es un par de enteros. El primer entero representa la distancia desde el territorio origen al territorio actual, y el segundo entero representa el id del territorio actual. vector<pair<int, int>>: Este es el contenedor subyacente que se utiliza para almacenar los elementos en la cola de prioridad. En este caso, es un vector de pares de enteros. greater<pair<int, int>>: Esta es la función de comparación que se utiliza para ordenar los elementos en la cola de prioridad. En este caso, greater<pair<int, int>> hace que la cola de prioridad funcione como un montículo mínimo, lo que significa que el elemento con la menor distancia siempre estará en la parte superior de la cola.*/ 
        distancias[id_terriOrigen] = 0; // La distancia al nodo de origen siempre va ser cero. 
        cola.push(make_pair(0, id_terriOrigen)); // Agregamos el nodo de origen a la cola.

        // Mientras la cola no esté vacia.
        while (!cola.empty()) 
        {
            int idActual = cola.top().second; // Obtenemos el nodo con menor distancia.
            cola.pop(); // Eliminamos el nodo con menor distancia.

            // Si llegamos al nodo  destino, se termina el ciclo.
            if (idActual == id_terriDestino) 
            {
                break;
            }
            // Obtenemos los vecinos del nodo actual.
            list<int> vecinos = obternerAdyacentes(idActual);
            for (list<int>::iterator it = vecinos.begin(); it != vecinos.end(); it++) 
            {
                int idVecino = *it; // Obtenemos el ID del vecino.
                //Solo consideramos los vecinos que son válidos según el método vecinitos_correctos.
                if (risk.vecinitos_correctos(actual, idActual, idVecino) == true) 
                {
                    int peso = 1; // los pesos los incializamos en 1.
                    // si encontramos un caminos mas corto al vecino.
                    if (distancias[idVecino] > distancias[idActual] + peso) 
                    {
                        // Actualizamos la distancia.
                        distancias[idVecino] = distancias[idActual] + peso; 
                        // Actualizamos el nodo previo.
                        previos[idVecino] = idActual;
                        // Agregamos el vecino a la cola de prioridad.
                        cola.push(make_pair(distancias[idVecino], idVecino));
                    }
                }
            }
        }

        // Imprimir el camino más corto al nodo de destino
        if (distancias[id_terriDestino] != INT_MAX) 
        {
            cout << "Desde el nodo " << id_terriOrigen<< ", la distancia más corta al territorio " << id_terriDestino << " es "<< distancias[id_terriDestino] << endl;
            cout << "El camino es: ";
            for (int v = id_terriDestino; v != -1; v = previos[v]) 
            {
                cout << v;
                if (v != id_terriOrigen) 
                {
                    cout << " <- ";
                }
            }
            cout << endl;
        } 
        else 
        {
            cout << "Desde el territorio " << id_terriOrigen<< ", no hay un camino válido al nodo " << id_terriDestino << endl;
        }
    }
    cout << endl;
}
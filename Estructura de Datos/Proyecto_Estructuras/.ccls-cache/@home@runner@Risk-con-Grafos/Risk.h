#ifndef RISK_H
#define RISK_H

#include "Continente.h"
#include "Grafo.h"
#include "Jugador.h"
#include <list>
#include <unordered_map>
#include <vector>

class Risk {
private:
  list<Jugador> jugadores;
  list<Continente> continentes;
  list<Carta> cartas;

public:
  Risk(){

  };
  Risk(list<Jugador>, list<Continente>, list<Carta>);
  ~Risk();

  list<Jugador> &getJugadores();
  list<Continente> &getContinentes();
  list<Carta> &getCartas();

  void inicializar(); //
  void turno(int);    //
  void atacar(int idJugador);

  void fortificarEnJugada(int idJugador);
  void fortificar();
  void territorios_ocupados(list<Jugador>::iterator);
  void obtener_UnidadesAdicionales();
  bool unidadesAdi_Conti(list<Pais> &, list<int> &);
  Pais eliminarPaisJugador(int);
  bool verificarGanador();
  void info_jugadores();
  void leerArchivoJugada();
  void leerArchivo();
  int obtenerCodigoColor(string);
  void ObtenerUnidadesParaArchivo(int, int, int);
  void fortificarParaArchivo(int, int, int, int);
  void atacarParaArchivo(int, int, int, int, int, int, int, int, int, int);
  void guardarJugada();
  string obtenerNombreColor(int);
  void fortificarTerritorio(int);

  bool unidades_ejercito(list<Jugador>::iterator);
  bool verificar_Unidades(int);
  bool disminuir_Unidades(int);
  bool verificar_Terri(int, list<Jugador>::iterator);
  vector<int> lanzarDados(int);
  void verificar_vecinos(list<Jugador>::iterator, int);
  bool vecinitos_correctos(list<Jugador>::iterator, int, int);
  void imprimir_vecinos(list<Jugador>::iterator, int);
  void crearGrafo();
};

#endif // RISK_H
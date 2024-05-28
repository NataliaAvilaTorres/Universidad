#include "Risk.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <ctime>
#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <climits>
using namespace std;

Grafo grafo;

Risk::Risk(list<Jugador> jugadores, list<Continente> continentes, list<Carta> cartas)
{
    this->jugadores = jugadores;
    this->continentes = continentes;
    this->cartas = cartas;
}

Risk::~Risk()
{
    //dtor
}

list<Jugador>& Risk::getJugadores()
{
    return jugadores;
}

list<Continente>& Risk::getContinentes()
{
    return continentes;
}

list<Carta>& Risk::getCartas()
{
    return cartas;
}


void Risk::inicializar() //Inicializar
{
    list <int> cercanos;
    list <int> colores_elegidos;
    list <int> paises_elegidos;

    list <int>::iterator c;
    list<Jugador>::iterator it;
    list<Continente>::iterator conti;
    list<Pais>::iterator paises;
    list<int>::iterator p;

    int i = 1, color, num_jugadores, continente, territorio, numTropas,canti;

    string nombre_pais, nombre_jugador;

    cout<<"Ingresa el numero de jugadores: ";
    cin>>num_jugadores;
    cout<<endl;

    jugadores = list<Jugador>(num_jugadores, Jugador()); //Inicializo a todos los (n) jugadores sin ningun dato.

    if (num_jugadores == 3)
    {
        numTropas = 35;
    }
    else if (num_jugadores == 4)
    {
        numTropas = 30;
    }
    else if (num_jugadores == 5)
    {
        numTropas = 25;
    }
    else if (num_jugadores == 6)
    {
        numTropas = 20;
    }

    for(it = jugadores.begin(); it != jugadores.end(); it++) //Preguntar el nombre de los n jugadores
    {
        cout<<"Nombre Jugador "<<i<<":";
        cin>>nombre_jugador;
        (*it).setNombre_jugador(nombre_jugador);
        i++;
    }
    i = 1;

    //Asignar identificador (color) por cada jugador
    for(it = jugadores.begin(); it != jugadores.end(); it++)
    {
        (*it).setCantidad_Tropas(numTropas);

        cout<<endl;
        cout<<"TURNO: "<<(*it).getNombre_jugador()<<endl;
        cout<<endl;

        cout<<"(1). Verde"<<endl;
        cout<<"(2). Azul"<<endl;
        cout<<"(3). Rojo"<<endl;
        cout<<"(4). Amarillo"<<endl;
        cout<<"(5). Negro"<<endl;
        cout<<"(6). Gris"<<endl;

        while(true)
        {
            cout<<"Elige un color: ";
            cin>>color;

            bool valido = true;

            if(color < 0 || color > 6)
            {
                cout<<"Este color no existe. Vuelvalo a intentar"<<endl;
                cout<<endl;
                valido = false;
            }
            else
            {
                for(c = colores_elegidos.begin(); c != colores_elegidos.end(); c++) //Verificar que no se repitan los identificadores (colores).
                {
                    if((*c) == color)
                    {
                        cout<<"Este color ya fue asignado. Elige uno nuevo."<<endl;
                        cout<<endl;
                        valido = false;
                        break;
                    }
                }
            }
            if(valido)
            {
                (*it).setColor_jugador(color);
                colores_elegidos.push_back(color);
                break;
            }
        }
        i++;
        cout<<endl;
    }
    i = 1;

    //Elegir Territorios para cada jugador hasta que se elijan todos
    while(paises_elegidos.size() < 42)
    {
        for(it = jugadores.begin(); it != jugadores.end(); it++)
        {
            cout<<"TURNO: "<<(*it).getNombre_jugador()<<endl;
            cout<<"COLOR: "<<(*it).getColor_jugador()<<endl;
            cout<<endl;

            cout<<"CONTINENTES"<<endl;
            for(conti = continentes.begin(); conti != continentes.end(); conti++) //Imprimo los continentes.
            {
                cout<<"("<<(*conti).getId_continente()<<")"<<" "<<(*conti).getNombre_continente()<<endl;
            }

            bool valido = false;
            while(!valido) //Verifico que el continente elegido exista.
            {
                cout<<"Elige un continente: ";
                cin>>continente;

                valido = false;

                for(conti = continentes.begin(); conti != continentes.end(); conti++)
                {
                    if((*conti).getId_continente() == continente)
                    {
                        bool todosocupados = true;
                        list<Pais> paisesConti = (*conti).getPaises();
                        for(paises = paisesConti.begin(); paises != paisesConti.end(); paises++)
                        {
                            if(find(paises_elegidos.begin(), paises_elegidos.end(),(*paises).getId_pais()) == paises_elegidos.end())
                            {
                                    todosocupados = false;
                                    break;
                            }
                        }
                        if(todosocupados)
                        {
                            cout << "Todos los territorios de este continente ya están ocupados. Intenta con otro continente." << endl;
                            break;
                        }
                        valido = true;
                        break;
                    }
                }
                if(!valido)
                {
                    cout<<"Continente Invalido. Vuelve a intentarlo"<<endl;
                    cout<<endl;
                }
            }
            valido = false;

            Continente elegido;

            for(conti = continentes.begin(); conti != continentes.end(); conti++) //Busco el continente que eligio y imprimo los paises de ese continente.
            {
                if((*conti).getId_continente() == continente)
                {
                    elegido = *conti;
                    list<Pais>paisesConti = elegido.getPaises();

                    cout<<endl;
                    cout<<"PAISES: "<<(*conti).getNombre_continente()<<endl;
                    for(paises = paisesConti.begin(); paises != paisesConti.end(); paises++)
                    {
                        cout<<"("<<(*paises).getId_pais()<<")"<<" "<<(*paises).getNombre_pais()<<endl;
                    }
                }
            }

            bool validoPais = false;
            while(!valido) //Verifico que el pais elegido exista dentro del continente.
            {
                cout<<"Elige un territorio: ";
                cin>>territorio;

                valido = false;
                validoPais = false;

                for(conti = continentes.begin(); conti != continentes.end(); conti++)
                {
                    if((*conti).getId_continente() == continente)
                    {
                        elegido = *conti;
                        list<Pais>paisesConti = elegido.getPaises();

                        for(paises = paisesConti.begin(); paises != paisesConti.end(); paises++)
                        {
                            if((*paises).getId_pais() == territorio)
                            {
                                if(find(paises_elegidos.begin(), paises_elegidos.end(), territorio) != paises_elegidos.end()) //Verifico que el pais no haya sido tomado anteriormente.
                                {
                                    cout<<"Este pais ya ha sido elegido. Elige uno nuevo."<<endl;
                                    cout<<endl;

                                    valido = false;
                                    validoPais = true;
                                    break;
                                }
                                else
                                {
                                    cercanos = (*paises).getPaises_cercanos();
                                    nombre_pais = (*paises).getNombre_pais();
                                    (*paises).setColor((*it).getColor_jugador());
                                    valido = true;
                                    break;
                                }
                            }
                        }
                        if(!valido && !validoPais)
                        {
                            cout<<"Este pais no existe en este continente. Reintentalo."<<endl;
                            cout<<endl;
                        }
                        else
                        {
                            canti = (*it).getCantidad_Tropas();
                            (*it).setCantidad_Tropas(canti -=1);
                            (*it).agregarPais(Pais(territorio, nombre_pais, (*it).getColor_jugador(), 1, {cercanos}));
                            paises_elegidos.push_back(territorio);
                        }
                    }
                }
            }

            i++;
            cout<<endl;
        }
    }
}

void Risk::turno(int idJugador)
{
    bool valido = false;
    while (!valido)
    {
        string accion;
        cout << "\nPor favor seleccione una opción:\n";
        cout << "\033[1;34m1. Obtener Unidades Adicionales\033[0m\n";
        cout << "\033[1;31m2. Atacar\033[0m\n";
        cout << "\033[1;37m3. Fortificar\033[0m\n";
        cout << "\n$ ";
        getline(cin, accion);
        if (accion == "1")
        {
            cout << "\nHas seleccionado 'Obtener Unidades Adicionales'.\n\n";
            fortificarEnJugada(idJugador);
            valido = true;
        }
        else if (accion == "2")
        {
            cout << "\nHas seleccionado 'Atacar'.\n\n";
            atacar(idJugador);
            valido = true;
        }
        else if (accion == "3")
        {
            cout << "\nHas seleccionado 'Fortificar'.\n\n";
            fortificarTerritorio(idJugador);
            valido = true;
        }
        else
        {
            cout << "Opción no válida. Por favor, intenta de nuevo.\n";
        }
    }
}

void Risk::fortificarTerritorio(int idJugador)
{
  bool tieneTerritoriosCercanos = false;
  list<int> posee;
  for(list<Jugador>::iterator it = jugadores.begin(); it != jugadores.end(); it++)
    {
      if ((*it).getColor_jugador() == idJugador) {
        list<Pais>& paisc = (*it).getPaises_jugador();
        for (auto& pais : paisc) {
            list<int> paisescerca = pais.getPaises_cercanos();
            for (auto& paiscer : paisescerca) {
                for (auto& otroPais : paisc) {
                    if (otroPais.getId_pais() == paiscer) {
                        tieneTerritoriosCercanos = true;
                        posee.push_back(pais.getId_pais());
                        break;
                    }
                }
            }
        }
      }
   }

    if (!tieneTerritoriosCercanos) {
        cout << "Usted no tiene territorios que sean cercanos. Intente otra acción en el siguiente turno." << endl;
        return;
    } else {
      ofstream archivo;
      if (!ifstream("jugadas_comprimido.txt"))
      {
          archivo.open("jugadas_comprimido.txt");
      }
      else
      {
          archivo.open("jugadas_comprimido.txt", ios::app);
      }
      bool encontrado = false;
      int paisOrigen, paisDestino, numUnidades;
      for(list<Jugador>::iterator it = jugadores.begin(); it != jugadores.end(); it++)
      {
          if ((*it).getColor_jugador() == idJugador && (*it).getPaises_jugador().size() > 2)
          {
              archivo << obtenerNombreColor((*it).getColor_jugador()) << ";" << "FRT" << ";" ;
              list<Pais>& paisc = (*it).getPaises_jugador();
              cout<<"TURNO: "<<(*it).getNombre_jugador()<<endl;
              territorios_ocupados(it);
              bool validCountry = false;
              while (!validCountry) {
                  cout << "Ingrese el país de Origen: ";
                  cin >> paisOrigen;

                  // Validar que paisOrigen esté en la lista de países que el jugador posee
                  for (auto& it : posee) {
                      if (it == paisOrigen) {
                          // Validar también que el país tiene unidades
                          for (auto& pais : paisc) {
                              if (pais.getId_pais() == paisOrigen && (pais.getCantidad_Tropas() > 0)) {
                                  validCountry = true;
                                  break;
                              }
                          }

                          if (!validCountry) {
                              cout << endl << "El país ingresado no tiene unidades. Por favor, intenta de nuevo." << endl << endl;
                          }
                      }
                  }

                  if (!validCountry) {
                      cout << endl << "El país ingresado no pertenece a tus territorios o no tienes posees sus países cercanos. Por favor, intenta de nuevo." << endl << endl;
                  }
              }
              archivo << paisOrigen << ";";
              bool validDestino = false;
              while (!validDestino)
              {
                cout<<"TERRITORIOS POSIBLES DE FORTIFICAR: "<<endl;
                imprimir_vecinos(it,paisOrigen);
                cout<<endl;
                  cout << endl << "Ingrese el País de Destino: ";
                  cin >> paisDestino;
                  for (auto& pais : paisc)
                  {
                      if (pais.getId_pais() == paisOrigen)
                      {
                          list<int>paisescerca = pais.getPaises_cercanos();
                          for (auto& paiscer : paisescerca)
                          {
                              if (paiscer == paisDestino)
                              {
                                  for (auto& pais : paisc)
                                  {
                                      if (pais.getId_pais() == paisDestino)
                                      {
                                          validDestino = true;
                                          break;
                                      }
                                  }
                              }
                          }
                      }
                  }
                  if (!validDestino)
                  {
                      cout << endl << endl << "No se posee el país de Destino, o no es cercano al origen. Intente nuevamente." << endl << endl;
                  }
              }
              archivo << paisDestino << ";";
              bool validUnid = false;
              while (!validUnid)
              {
                  cout << endl << "Ingrese el número de unidades: ";
                  cin >> numUnidades;
                  for (auto& pais : paisc)
                  {
                      if (pais.getId_pais() == paisOrigen && (pais.getCantidad_Tropas() >= numUnidades))
                      {
                          validUnid = true;
                          break;
                      }
                  }
                  if (!validUnid)
                  {
                      cout << endl << endl << "El número de unidades supera el máximo. Por favor, intenta de nuevo." << endl << endl;
                  }
              }
              archivo << numUnidades << ";;;;;;" << endl;
              for(auto& pais : paisc)
              {
                  if (pais.getId_pais() == paisOrigen)
                      pais.setCantidad_Tropas(pais.getCantidad_Tropas() - numUnidades);
                  if (pais.getId_pais() == paisDestino)
                      pais.setCantidad_Tropas(pais.getCantidad_Tropas() + numUnidades);
              }
              cout << endl << "LA ACCIÓN SE HA REALIZADO EXITOSAMENTE." << endl << endl;
              territorios_ocupados(it);
          }
      }
      archivo.close();
    }
}

int intercambios = 1;
void Risk::obtener_UnidadesAdicionales()
{
    int cantiTerritorios,opera,canti;

    list<int> AmericadelNorte = {1,2,3,4,5,6,7,8,9};
    list<int> AmericadelSur = {10,11,12,13};
    list<int> Europa = {14,15,16,17,18,19,20};
    list<int> Africa = {21,22,23,24,25,26};
    list<int> Asia = {27,28,29,30,31,32,33,34,35,36,37,38};
    list<int> Australia = {39,40,41,42};


    for(list<Jugador>::iterator it = jugadores.begin(); it != jugadores.end(); it++)
    {
        {
            cout<<"JUGADOR: "<<(*it).getNombre_jugador()<<endl;

            list<Pais>& paises_jugador = (*it).getPaises_jugador();
            cantiTerritorios = paises_jugador.size();

            cout<<"CANTIDAD DE TERRITORIOS OCUPADOS: "<<cantiTerritorios<<endl;
            opera = (cantiTerritorios / 3);

            (*it).setCantidad_Tropas(opera);

            cout<<"UNIDADES ADICIONALES: "<<opera<<endl;
            cout<<endl;
        }
    }

    for(list<Jugador>::iterator it = jugadores.begin(); it != jugadores.end(); it++)
    {
        {
            cout<<"JUGADOR: "<<(*it).getNombre_jugador()<<endl;
            list<Pais>& paises_jugador = (*it).getPaises_jugador();

            if(unidadesAdi_Conti(paises_jugador,AmericadelNorte))
            {
                cout<<"El jugador ocupa todos los paises de América del Norte."<<endl;
                canti = (*it).getCantidad_Tropas();
                (*it).setCantidad_Tropas(canti + 5);
                cout<<"UNIDADES ADICIONALES: 5"<<endl;
                cout<<endl;
            }
            else if(unidadesAdi_Conti(paises_jugador,AmericadelSur))
            {
                cout<<"El jugador ocupa todos los paises de America del Sur."<<endl;
                canti = (*it).getCantidad_Tropas();
                (*it).setCantidad_Tropas(canti + 2);
                cout<<"UNIDADES ADICIONALES: 2"<<endl;
                cout<<endl;
            }
            else if(unidadesAdi_Conti(paises_jugador,Europa))
            {
                cout<<"El jugador ocupa todos los paises de Europa."<<endl;
                canti = (*it).getCantidad_Tropas();
                (*it).setCantidad_Tropas(canti + 5);
                cout<<"UNIDADES ADICIONALES: 5"<<endl;
                cout<<endl;
            }
            else if(unidadesAdi_Conti(paises_jugador,Africa))
            {
                cout<<"El jugador ocupa todos los paises de Africa."<<endl;
                canti = (*it).getCantidad_Tropas();
                (*it).setCantidad_Tropas(canti + 3);
                cout<<"UNIDADES ADICIONALES: 3"<<endl;
            }
            else if(unidadesAdi_Conti(paises_jugador,Asia))
            {
                cout<<"El jugador ocupa todos los paises de Asia."<<endl;
                canti = (*it).getCantidad_Tropas();
                (*it).setCantidad_Tropas(canti + 7);
                cout<<"UNIDADES ADICIONALES: 7"<<endl;
                cout<<endl;
            }
            else if(unidadesAdi_Conti(paises_jugador,Australia))
            {
                cout<<"El jugador ocupa todos los paises de Australia."<<endl;
                canti = (*it).getCantidad_Tropas();
                (*it).setCantidad_Tropas(canti + 2);
                cout<<"UNIDADES ADICIONALES: 2"<<endl;
                cout<<endl;
            }
            else
            {
                cout<<"El jugador no ocupa un continente completo. No recibe unidades adicionales."<<endl;
                cout<<endl;
            }
            canti = 0;
        }
    }

    //Fortificar segun cartas
  for(list<Jugador>::iterator it = jugadores.begin(); it != jugadores.end(); it++) //NUEVAS UNIDADES: SEGUN CARTAS
  {
      bool verdadero;
      verdadero = unidades_ejercito(it);

      if(verdadero == true)
      {
          int nuevas;
          if(intercambios <= 5)
          {
              nuevas = 4 + intercambios*2;
          }
          else
          {
              nuevas = 15 + (intercambios - 6)*5;
          }
          cout<<"El jugador completa una combiancion en sus cartas."<<endl;
          cout<<"UNIDADES ADICIONALES: "<<nuevas<<endl;

          canti = (*it).getCantidad_Tropas();
          (*it).setCantidad_Tropas(canti + nuevas);
          intercambios++;
      }
      else
      {
          cout<<"El jugador no tiene alguna combinacion en sus cartas"<<endl;
          cout<<endl;
      }
  }
}

bool Risk::unidades_ejercito(list<Jugador>::iterator actual)
{
    int cont1 = 0, cont2 = 0, cont3 = 0;
    cout<<"JUGADOR: "<<(*actual).getNombre_jugador()<<endl;
    list<Carta>& cartas_jugador = (*actual).getCartas_jugador();

    for(list<Carta>::iterator cartica = cartas_jugador.begin(); cartica != cartas_jugador.end(); cartica++)
    {
        if((*cartica).getFigura() == 1)
        {
            cont1++;
        }
        else if((*cartica).getFigura() == 2)
        {
            cont2++;
        }
        else if((*cartica).getFigura() == 3)
        {
            cont3++;
        }
    }
    if(cont1 >= 3)
    {
        return true;

        for(list<Carta>::iterator cartica = cartas_jugador.begin(); cartica != cartas_jugador.end(); cartica++)
        {
            if((*cartica).getFigura() == 1)
            {
                cartas.push_back(*cartica);
            }
        }
    }
    else if(cont2 >= 3)
    {
        return true;

        for(list<Carta>::iterator cartica = cartas_jugador.begin(); cartica != cartas_jugador.end(); cartica++)
        {
            if((*cartica).getFigura() == 2)
            {
                cartas.push_back(*cartica);
            }
        }
    }
    else if(cont3 >= 3)
    {
        return true;

        for(list<Carta>::iterator cartica = cartas_jugador.begin(); cartica != cartas_jugador.end(); cartica++)
        {
            if((*cartica).getFigura() == 3)
            {
                cartas.push_back(*cartica);
            }
        }
    }
    else
    {
        return false;
    }
}

bool Risk::unidadesAdi_Conti(list<Pais>& paises_jugador, list<int>& paises_conti)
{
    for(list<int>::iterator pc = paises_conti.begin(); pc != paises_conti.end(); pc++)
    {
        bool encontrado = false;
        for(list<Pais>::iterator pai = paises_jugador.begin(); pai != paises_jugador.end(); pai++)
        {
            if((*pai).getId_pais()== (*pc))
            {
                encontrado = true;
                break;
            }
        }
        if(!encontrado)
        {
            return false; //Si no se encontró el ID en la lista, devuelve false
        }
    }
    return true; //Si se encontraron todos los IDs en la lista, devuelve true
}

void Risk::atacar(int idJugador)
{
  int terriAtacante, terriDefensor;
  ofstream archivo;
  if (!ifstream("jugadas_comprimido.txt"))
  {
      archivo.open("jugadas_comprimido.txt");
  }
  else
  {
      archivo.open("jugadas_comprimido.txt", ios::app);
  }
    for(list<Jugador>::iterator it = jugadores.begin(); it != jugadores.end(); it++)
    {
        if ((*it).getColor_jugador() == idJugador) {
          archivo << obtenerNombreColor((*it).getColor_jugador()) << ";ATK;" ;
          cout<<"======================== ATACAR  ========================"<<endl;
          cout<<endl;

          cout<<"TURNO:"<<(*it).getNombre_jugador()<<endl;
          cout<<"COLOR: "<<(*it).getColor_jugador()<<endl;
          cout<<endl;

          territorios_ocupados(it); //Muestra los territorios ocupados por el jugador
          */
          bool seguir = true;
          do {
          seguir = true;
          bool opvalida = false;
          bool verificar2;
          bool cercanos;
          bool Pertenece;
          do {
              verificar2 = false;
              cercanos = false;
              Pertenece = false;
              cout<<"¿Cual país desearía atacar?: ";
              cin>>terriDefensor;
              if (terriDefensor >= 1 && terriDefensor <= 42)
              verificar2 = true;
              for (list<Pais> ::iterator itPais = (*it).getPaises_jugador().begin(); itPais != (*it).getPaises_jugador().end(); itPais++){
                if ((*itPais).getColor() == (*it).getColor_jugador()){
                  for(list<int> ::iterator itCerc = (*itPais).getPaises_cercanos().begin(); itCerc != (*itPais).getPaises_cercanos().end(); itCerc++){
                    if ((*itCerc) == terriDefensor){
                      cercanos = true;
                      for (list<Pais> ::iterator itPais2 = (*it).getPaises_jugador().begin(); itPais2 != (*it).getPaises_jugador().end(); itPais2++){
                        if((*itPais2).getId_pais() == *itCerc) {
                          if((*itPais2).getColor() == (*it).getColor_jugador()) {
                            Pertenece = true;
                          }
                        }
                      }
                        
                    }
                  }
                }
              }
              if(!verificar2)
              {
                cout << "\nElija un país válido.\n\n";
              } else if(!cercanos)
              {
                cout << "\nElija un país del que si sea cercano.\n\n";
              }
                if(Pertenece)
                {
                  cout<<endl<<"Este territorio no puede ser atacado porque le pertenece."<<endl<<endl;
                }
          } while(!verificar2 || !cercanos || Pertenece);
          grafo.costoConquista(terriDefensor,(*it).getColor_jugador());
          do {
          cout << endl << endl << "¿Desea seguir obteniendo información de conquistas? S/n";
          char opcion;
          cout << endl;
          cin >> opcion;
          if (opcion == 'S' || opcion == 's') {
            cout << endl << "Se le seguirán pidiendo datos."<< endl << endl;
            opvalida = true;
          } else if (opcion == 'N' || opcion == 'n') {
            cout << endl << "Proceda a tomar la desición final de ataque."<< endl << endl;
            opvalida = true;
            seguir = false;
          } else {
            cout << endl << "Escriba una opción válida."<< endl;
          }
          } while (!opvalida);
          } while(seguir);
          &
          bool validCountry = false;
          while (!validCountry) {
              cout << "Ingrese el país de Ataque: ";
              cin >> terriAtacante;
                      // Validar también que el país tiene unidades
                      for (auto& pais : (*it).getPaises_jugador()) {
                          if (pais.getId_pais() == terriAtacante) {
                              validCountry = true;
                              break;
                          }
                      }

              if (!validCountry) {
                  cout << endl << "El país ingresado no pertenece a tus territorios. Por favor, intenta de nuevo." << endl << endl;
              }
          }
          archivo << terriAtacante;
          cout<<endl;
          verificar_vecinos(it,terriAtacante); //Verifica que los vecinos de ese territorio no esten ocupados por el jugador actual, ya que no podra atacar a un territorio que el jugador en turno tiene
          cout<<"TERRITORIOS POSIBLES DE ATACAR: "<<endl;
          imprimir_vecinos(it,terriAtacante);
          cout<<endl;
        grafo.ConquistaMasBarata(terriAtacante); 
          bool verificar;
          do {
              cout<<"¿Cual quiere atacar?: ";
              cin>>terriDefensor;
              verificar = vecinitos_correctos(it,terriAtacante,terriDefensor);
              if(!verificar)
              {
                  cout<<"Territorio vecino no se encuentra. Vuelve a intentarlo."<<endl;
              }
          } while(!verificar);
          cout<<endl;
          archivo << terriDefensor << ";";
          vector<int> dadosAtacante = lanzarDados(3);
          vector<int> dadosDefensor = lanzarDados(2);
          for (int i = 0; i < 3; i++) {
              archivo << dadosAtacante[i] << ";";
          }

          for (int i = 0; i < 2; i++) {
              archivo << dadosDefensor[i] << ";";
          }

          sort(dadosAtacante.begin(), dadosAtacante.end(), greater<int>());
          sort(dadosDefensor.begin(), dadosDefensor.end(), greater<int>());

          bool r, v1, v2;
          //Compara los dados y determina las bajas
          for(int i = 0; i < min(dadosAtacante.size(),dadosDefensor.size()); i++)
          {
              r = false;
              v1 = verificar_Unidades(terriDefensor);
              v2 = verificar_Unidades(terriAtacante);

              if(v1 == true || v2 == true) //Primero verifico que el territorio del atacante y defensor tengan tropas para jugar
              {
                  if(v1 == true)
                  {
                      cout<<"*El defensor no tiene tropas en este territorio*"<<endl;
                      break;
                  }
                  else if (v2 == true)
                  {
                      cout<<"*No hay tropas suficientes para atacar*"<<endl;
                      break;
                  }
              }
              else
              {
                  if(dadosAtacante[i] > dadosDefensor[i])
                  {
                      cout<<"DADO ROJO: "<<dadosAtacante[i]<<endl;
                      cout<<"DADO AZUL: "<<dadosDefensor[i]<<endl;
                      cout<<"RESULTADO: Gana el Atacante!!!"<<endl;
                      //El atacante gana, el defensor pierde una unidad
                      int D = terriDefensor;
                      r = disminuir_Unidades(D);

                      if(r == true)
                      {
                          cout<<endl;
                          cout<<"========================="<<endl;
                          cout<<"Territorio Conquistado!!!"<<endl;
                          cout<<"========================="<<endl;
                          //Asignar el territorio conquistado a la lista de territorios del jugador Atacante
                          Pais eliminado = eliminarPaisJugador(terriDefensor);
                          eliminado.setCantidad_Tropas(1);
                          (*it).agregarPais(eliminado);
                          //Asignar una carta al Atcante porque conquisto el territorio
                          int indice = rand()% cartas.size();
                          auto cartica = cartas.begin();

                          advance(cartica,indice);
                          Carta carta = *cartica;

                          cartas.erase(cartica);
                          (*it).agregarCarta(carta);
                          break;
                      } 
                  }
                  else
                  {
                      cout<<"DADO ROJO: "<<dadosAtacante[i]<<endl;
                      cout<<"DADO AZUL: "<<dadosDefensor[i]<<endl;
                      cout<<"RESULTADO: El Atacante pierde."<<endl;

                      //El defensor gana o hay empate, el atacante pierde una unidad
                      int A = terriAtacante;
                      r = disminuir_Unidades(A);
                  }
              }
              cout<<endl;
          }
      }
    }
    archivo << terriDefensor << ";;" << endl;
    archivo.close();
} 

bool Risk::verificar_Unidades(int terri)
{
    for(list<Jugador>::iterator it = jugadores.begin(); it != jugadores.end(); it++)
    {
        list<Pais>& territorios = (*it).getPaises_jugador();
        for(list<Pais>::iterator p = territorios.begin(); p != territorios.end(); p++)
        {
            if((*p).getId_pais() == terri)
            {
                if((*p).getCantidad_Tropas() == 0)
                {
                    return true;
                    break;
                }
                else
                {
                    return false;
                }
            }
        }
    }

}

bool Risk::verificarGanador()
{
    for(list<Jugador>::iterator it = jugadores.begin(); it != jugadores.end(); it++)
    {
        if((*it).getPaises_jugador().size() == 42)
        {
            cout<<"El Jugador "<<(*it).getNombre_jugador()<<" es el ganador!"<<endl;
            return true;
        }
    }
    return false;
}


Pais Risk::eliminarPaisJugador(int terriAtaque)
{
    for(list<Jugador>::iterator j = jugadores.begin(); j != jugadores.end(); j++)
    {
        list<Pais>& territorios = (*j).getPaises_jugador();

        for(list<Pais>::iterator pa = territorios.begin(); pa != territorios.end(); pa++)
        {
            if((*pa).getId_pais() == terriAtaque)
            {
                Pais territorioEliminado = (*pa); //Copia
                territorios.erase(pa);
                return territorioEliminado;
            }
        }
    }
    return Pais(); //Si no lo encuentra, devuelve un objeto Pais vacio
}


vector<int> Risk::lanzarDados(int n)
{
    srand(time(nullptr));

    vector<int> resultados;
    for(int i = 0; i < n; i++)
    {
        int resultado = rand()%6+1;
        resultados.push_back(resultado);
    }
    return resultados;
}

bool Risk::disminuir_Unidades(int terri)
{
    for(list<Jugador>::iterator it = jugadores.begin(); it != jugadores.end(); it++)
    {
        list<Pais>& territorios = (*it).getPaises_jugador();
        for(list<Pais>::iterator p = territorios.begin(); p != territorios.end(); p++)
        {
            if((*p).getId_pais() == terri)
            {
                int canti = (*p).getCantidad_Tropas();
                (*p).setCantidad_Tropas(canti - 1);

                if((*p).getCantidad_Tropas() == 0)
                {
                    return true;
                }
                return false;
            }
        }
    }
}

bool Risk::verificar_Terri(int t, list<Jugador>::iterator actual)
{
    list<Pais>& paises = (*actual).getPaises_jugador();
    for(list<Pais>::iterator p = paises.begin(); p != paises.end(); p++)
    {
        if((*p).getId_pais() == t)
        {
            return true;
        }
        else {
          return false;
        }
    }
}

void Risk::verificar_vecinos(list<Jugador>::iterator actual, int t)
{
    list<Pais>& territoriosJugador = (*actual).getPaises_jugador();
    for(list<Pais>::iterator p = territoriosJugador.begin(); p != territoriosJugador.end(); p++)
    {
        if((*p).getId_pais() == t)
        {
            list<int>& cercanos = (*p).getPaises_cercanos();
            for(list<int>::iterator c = cercanos.begin(); c != cercanos.end();)
            {
                bool found = false;
                for(list<Pais>::iterator pa = territoriosJugador.begin(); pa != territoriosJugador.end(); pa++)
                {
                    if((*c) == (*pa).getId_pais())
                    {
                        found = true;
                        break;
                    }
                }
                if(found)
                {
                    c = cercanos.erase(c);
                }
                else
                {
                    c++;
                }
            }
        }
    }
}

bool Risk::vecinitos_correctos(list<Jugador>::iterator actual, int t, int c)
{
    list<Pais>& paises_jugador = (*actual).getPaises_jugador();
    for(list<Pais>:: iterator p = paises_jugador.begin(); p != paises_jugador.end(); p++)
    {
        if((*p).getId_pais() == t)
        {
            list<int>& cercanos = (*p).getPaises_cercanos();
            for(list<int>:: iterator cer = cercanos.begin(); cer != cercanos.end(); cer++)
            {
                if((*cer) == c)
                {
                    return true;
                }
            }
        }
    }
    return false;
}

void Risk::imprimir_vecinos(list<Jugador>::iterator actual, int t)
{
    list<Pais>& paises_jugador = (*actual).getPaises_jugador();
    for(list<Pais>:: iterator p = paises_jugador.begin(); p != paises_jugador.end(); p++)
    {
        if((*p).getId_pais() == t)
        {
            list<int>& cercanos = (*p).getPaises_cercanos();
            for(list<int>:: iterator cer = cercanos.begin(); cer != cercanos.end(); cer++)
            {
                cout<<"Territorio ("<<(*cer)<<")"<<endl;
            }
        }
    }
}

void Risk::fortificarEnJugada(int idJugador)
{
    int id, canti, cantiT, numUnidades;
    bool hayTropas = true, invalido = true, primera = true;
    string respuesta;
    ofstream archivo;
    if (!ifstream("jugadas_comprimido.txt"))
    {
        archivo.open("jugadas_comprimido.txt");
    }
    else
    {
        archivo.open("jugadas_comprimido.txt", ios::app);
    }

    if (!archivo.is_open())
    {
        cout << "Error al abrir el archivo para escribir." << endl;
        return;
    }

    while(hayTropas)
    {
        hayTropas = false; // Asumimos que no hay tropas hasta que se compruebe lo contrario

        for(list<Jugador>::iterator it = jugadores.begin(); it != jugadores.end(); it++)
        {
          if ((*it).getColor_jugador() == idJugador) {
            if((*it).getCantidad_Tropas() > 0)
            {
                hayTropas = true; //El jugador tiene tropas

                cout<<"TURNO: "<<(*it).getNombre_jugador()<<endl;
                territorios_ocupados(it);
                archivo << obtenerNombreColor((*it).getColor_jugador()) << ";" << "OUD" << ";" ;
                list<Pais>& paises = (*it).getPaises_jugador();
                bool idValido = false;

                while(!idValido) //Verifica que el Id este dentro de la lista de los paises del jugador
                {
                    cout<<"Agregar Unidades Territorio (ID): ";
                    cin>>id;
                    for(list<Pais>::iterator it2 = paises.begin(); it2 != paises.end(); it2++)
                    {
                        if((*it2).getId_pais() == id)
                        {
                            idValido = true;
                        }
                    }
                    if(!idValido)
                    {
                        cout<<"ID no valido. Por favor, elige un ID de uno de tus territorios."<<endl;
                        cout<<endl;
                    }
                }

              bool numValido = false;
              while (!numValido){
                cout<<"Numero de unidades: ";
                cin>>numUnidades;
                if (numUnidades <= (*it).getCantidad_Tropas()){
                  for(list<Pais>::iterator it2 = paises.begin(); it2 != paises.end(); it2++)
                  {
                      if((*it2).getId_pais() == id)
                      {
                          canti = (*it2).getCantidad_Tropas();
                          (*it2).setCantidad_Tropas(canti += numUnidades);

                          cantiT = (*it).getCantidad_Tropas();
                          (*it).setCantidad_Tropas(cantiT -= numUnidades);
                          numValido = true;
                      }
                  }
                } else {
                  cout << endl << "Ingrese un número de unidades válido.";
                }
              }
                archivo << numUnidades << ";" << id  << ";;;;;;;" << endl;
                cout<<endl;
              if (numUnidades < (*it).getCantidad_Tropas()) {
                while (invalido) {
                  cout << "¿Desea seguir fortificando? S/N: ";
                  cin >> respuesta;
                  if (respuesta == "S" || respuesta == "S"){
                    cout << endl;
                    invalido = false;
                  } else if (respuesta == "N" || respuesta == "n"){
                    hayTropas = false;
                    invalido = false;
                  } else {
                    cout << endl << "Ingrese un opción válida.";
                  }
                }
              }
              primera = false;
            } else if (primera) {
              cout << "Usted no cuenta con tropas para realizar esta acción intente otra acción en el siguiente turno.";
            }
          }
        }

    }
    archivo.close();
}

void Risk::fortificar()
{
    ofstream archivo;
    if (!ifstream("jugadas_comprimido.txt"))
    {
        archivo.open("jugadas_comprimido.txt");
    }
    else
    {
        archivo.open("jugadas_comprimido.txt", ios::app);
    }

    if (!archivo.is_open())
    {
        cout << "Error al abrir el archivo para escribir." << endl;
        return;
    }
    int id, canti, cantiT;
    bool hayTropas = true;

    while(hayTropas)
    {
        hayTropas = false; // Asumimos que no hay tropas hasta que se compruebe lo contrario

        for(list<Jugador>::iterator it = jugadores.begin(); it != jugadores.end(); it++)
        {
            if((*it).getCantidad_Tropas() > 0)
            {
                hayTropas = true; //El jugador tiene tropas

                cout<<"TURNO: "<<(*it).getNombre_jugador()<<endl;
                territorios_ocupados(it);
                archivo << obtenerNombreColor((*it).getColor_jugador()) << ";" << "OUD" << ";" ;
                list<Pais>& paises = (*it).getPaises_jugador();
                bool idValido = false;

                while(!idValido) //Verifica que el Id este dentro de la lista de los paises del jugador
                {
                    cout<<"Agrergar Unidades Territorio (ID): ";
                    cin>>id;

                    for(list<Pais>::iterator it2 = paises.begin(); it2 != paises.end(); it2++)
                    {
                        if((*it2).getId_pais() == id)
                        {
                            idValido = true;
                            canti = (*it2).getCantidad_Tropas();
                            (*it2).setCantidad_Tropas(canti += 1);

                            cantiT = (*it).getCantidad_Tropas();
                            (*it).setCantidad_Tropas(cantiT -= 1);
                        }
                    }
                    if(!idValido)
                    {
                        cout<<"ID no valido. Por favor, elige un ID de uno de tus territorios."<<endl;
                        cout<<endl;
                    }
                }

                archivo << "1;" << id  << ";;;;;;;" << endl;
                cout<<endl;
            }

        }
    }
    archivo.close();
}

void Risk::territorios_ocupados(list<Jugador>::iterator actual)
{
    cout<<"TERRITORIOS OCUPADOS: "<<endl;
    cout<<endl;

    cout<<"Tropas Jugador: "<<(*actual).getCantidad_Tropas()<<endl;

    list<Pais>& paises = (*actual).getPaises_jugador();

    for(list<Pais>::iterator it2 = paises.begin(); it2 != paises.end(); it2++)
    {
        cout<<"("<<(*it2).getId_pais()<<")"<<" "<<(*it2).getNombre_pais()<<": "<<(*it2).getCantidad_Tropas()<<endl;
    }
    cout<<endl;
}


void Risk::info_jugadores()
{
    cout<<"INFORMACION JUGADORES"<<endl;
    cout<<endl;

    for(list<Jugador>::iterator it = jugadores.begin(); it != jugadores.end(); ++it)
    {
        cout<<"Nombre Jugador: "<<it->getNombre_jugador()<<endl;
        cout<<"Color del jugador: "<<it->getColor_jugador()<<endl;
        cout<<"Cantidad de tropas: "<<it->getCantidad_Tropas()<<endl;

        cout<<endl;
        cout<<"TERRITORIOS DEL JUGADOR: "<<it->getNombre_jugador()<<endl;
        list<Pais>& paises = it->getPaises_jugador();
        for(list<Pais>::iterator it2 = paises.begin(); it2 != paises.end(); ++it2)
        {
            cout<<"ID del pais: " <<it2->getId_pais()<<endl;
            cout<<"Nombre del pais: "<<it2->getNombre_pais()<<endl;
            cout<<"Color: " <<it2->getColor()<<endl;
            cout<<"Cantidad de tropas: "<<it2->getCantidad_Tropas()<<endl;

            list<int> cercanos = it2->getPaises_cercanos();
            cout<<"Paises cercanos: ";
            for(list<int>::iterator it3 = cercanos.begin(); it3 != cercanos.end(); ++it3)
            {
                cout<<*it3<<" ";
            }
            cout<< endl;
        }
        cout<<endl;
        cout<<"CARTAS DEL JUGADOR: "<<it->getNombre_jugador()<<endl;
        list<Carta>& cartasj = it->getCartas_jugador();
        for(list<Carta>::iterator c = cartasj.begin(); c != cartasj.end(); c++)
        {
            cout<<"ID carta: "<<c->getId_carta()<<endl;
            cout<<"Tipo carta: "<<c->getTipo_carta()<<endl;
            cout<<"Territorio: "<<c->getTerritorio()<<endl;
            cout<<"Figura: "<<c->getFigura()<<endl;
        }
        cout<<endl;
    }
    cout<<endl;
}


int Risk::obtenerCodigoColor(string nombreColor)
{
    if (nombreColor == "Verde")
    {
        return 1;
    }
    else if (nombreColor == "Azul")
    {
        return 2;
    }
    else if (nombreColor == "Rojo")
    {
        return 3;
    }
    else if (nombreColor == "Blanco")
    {
        return 4;
    }
    else if (nombreColor == "Violeta")
    {
        return 5;
    }
    else if (nombreColor == "Gris")
    {
        return 6;
    }
    else
    {
        return 0; // Color desconocido
    }
}

void Risk::leerArchivo()
{
    ifstream archivo("tablero.txt");

    if (!archivo.is_open())
    {
        cout << "Error al abrir el archivo." << endl;
        return;
    }

    int numJugadores;
    archivo >> numJugadores;
    archivo.ignore();  // Ignora el salto de línea después del número de jugadores

    // Limpia la lista de jugadores
    jugadores.clear();

    for (int i = 0; i < numJugadores; i++)
    {
        string nombre;
        string nombreColor;
        int numTerritorios;
        int codigoColor;
        list<Pais> territorios;  // Lista vacia de territorios
        list<Carta> cartas;
        int numCartas;  // Variable para almacenar la cantidad de cartas
        Jugador jugador(nombre, codigoColor, 0, territorios, cartas);
        jugadores.push_back(jugador);
    }

    // Recorrerlo desde los jugadores que ya creamos con el num del archivo
    for (list<Jugador>::iterator itj = jugadores.begin(); itj != jugadores.end(); itj++)
    {
        string nombre;
        string nombreColor;
        int numTerritorios;
        list<Pais> territorios;  // Lista temporal para almacenar los territorios de cada jugador
        list<Carta> cartas;
        int numCartas;  // Variable para almacenar la cantidad de cartas
        getline(archivo, nombre, ';');      // Lee el nombre del jugador hasta el siguiente punto y coma
        (*itj).setNombre_jugador(nombre);
        getline(archivo, nombreColor, ';');  // Lee el nombre del color hasta el siguiente punto y coma
        archivo >> numTerritorios;          // Lee el número de territorios que posee el jugador
        archivo.ignore();                   // Ignora el separador ';'

        int codigoColor = obtenerCodigoColor(nombreColor);
        if (codigoColor == 0)
        {
            cout << "Error: Color desconocido para el jugador " << endl;
            return;
        }

        (*itj).setColor_jugador(codigoColor);

        for (int j = 0; j < numTerritorios; j++)
        {
            int territorioID;
            int numTropas;

            archivo >> territorioID;
            archivo.ignore();  // Ignora el separador ';'
            archivo >> numTropas;
            archivo.ignore();  // Ignora el separador ';'


            for (list<Continente>::iterator it = continentes.begin(); it != continentes.end(); it++)
            {
                list<Pais> paisc = (*it).getPaises();
                for(list<Pais>::iterator it2 = paisc.begin(); it2 != paisc.end(); it2++)
                {
                    if ((*it2).getId_pais() == territorioID)
                    {
                        // Asigna el ID del color del jugador al país
                        (*it2).setColor(codigoColor);
                        (*it2).setCantidad_Tropas(numTropas); // Establece el número de tropas

                        // Agrega el país a la lista temporal de territorios del jugador
                        territorios.push_back((*it2));
                        break;
                    }
                }
            }
        }

        // Lee el número de cartas que tiene el jugador y lo almacena
        archivo >> numCartas;
        archivo.ignore();  // Ignora el salto de línea

        // Configura la lista de territorios para el jugador
        (*itj).setPaises_jugador(territorios);

        cout << "Jugador "  << ": " << (*itj).getNombre_jugador() << " (Color: " << nombreColor << ")" << endl;
        cout << "Número de Territorios de " << (*itj).getNombre_jugador() << ": " << numTerritorios << endl;
        cout << "Territorios de " << (*itj).getNombre_jugador() << ":" << endl;

        // Imprime la lista de territorios (Paises) del jugador
        for (Pais& territorio : (*itj).getPaises_jugador())
        {
            cout << "ID: " << territorio.getId_pais() << ", Nombre: " << territorio.getNombre_pais() << ", Tropas: " << territorio.getCantidad_Tropas() << endl;
        }

        cout << endl << "Cantidad de Cartas de " << nombre << ": " << numCartas << endl;
        cout << endl << " - - - - - - - - - - - - - - - -  - - - - - - - - " << endl << endl;
    }

    archivo.close();
}

void Risk::leerArchivoJugada()
{
    cout<< endl << "JUGADAS PREDETERMINADAS:" << endl << endl;
    ifstream archivo("jugadas.txt"); // Reemplaza "jugadas.txt" con el nombre de tu archivo
    if (!archivo.is_open())
    {
        cout << "Error al abrir el archivo." << endl;
        return;
    }

    string linea;
    int idJugador = 0; // ID del jugador actual

    while (getline(archivo, linea))
    {
        stringstream ss(linea);
        string paso, nombreColor, tOrigen, tDestino, DR1, DR2, DR3, DB1, DB2, Reclama;
        int numUnidades, paisOrigen, paisDestino;
        int paisReclamado = 0, dador1, dador2, dador3, dadob1, dadob2;
        numUnidades = 0;

        // Lee los datos de la línea
        getline(ss, nombreColor, ';');
        getline(ss, paso, ';');
        getline(ss, tOrigen, ';');
        getline(ss, tDestino, ';');
        getline(ss, DR1, ';');
        getline(ss, DR2, ';');
        getline(ss, DR3, ';');
        getline(ss, DB1, ';');
        getline(ss, DB2, ';');
        getline(ss, Reclama, ';');

        // Convierte el nombre del color en ID de jugador
        idJugador = obtenerCodigoColor(nombreColor);

        cout << "ID del jugador: " << idJugador << endl;

        if (paso == "OUD")
        {
            // Leer el número de unidades y el país de destino
            numUnidades = stoi(tOrigen);
            paisDestino = stoi(tDestino);

            cout << "Paso: Obtener Unidades" << endl;
            cout << "Número de Unidades: " << numUnidades << endl;
            cout << "País de Destino: " << paisDestino << endl;
            ObtenerUnidadesParaArchivo(idJugador, numUnidades, paisDestino);
            cout<< endl << "/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/" << endl;
        }
        if (paso == "FRT")
        {
            // Leer el país de origen y el país de destino
            paisOrigen = stoi(tOrigen);
            paisDestino = stoi(tDestino);
            numUnidades = stoi(DR1);

            cout << "Paso: Fortificar" << endl;
            cout << "País de Origen: " << paisOrigen << endl;
            cout << "País de Destino: " << paisDestino << endl;
            cout << "Número de Unidades: " << numUnidades << endl;
            fortificarParaArchivo(idJugador, paisOrigen, paisDestino, numUnidades);
            cout<< endl << "/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/" << endl;
        }
        if (paso == "ATK")
        {
            // Leer el país del atacante, el país del defensor,
            // los dados rojos y blancos
            paisOrigen = stoi(tOrigen);
            paisDestino = stoi(tDestino);
            dador1 = stoi(DR1);
            dador2 = stoi(DR3);
            dador3 = stoi(DR3);
            dadob1 = stoi(DB1);
            dadob2 = stoi(DB2);

            cout << "Paso: Atacar" << endl;
            cout << "País del Atacante: " << paisOrigen << endl;
            cout << "País del Defensor: " << paisDestino << endl;
            cout << "Dados Rojos: " << dador1 << ", "
                 << dador2 << ", " << dador3 << endl;
            cout << "Dados Blancos: " << dadob1
                 << ", " << dadob2 << endl;
            if (!Reclama.empty())
            {
                // Leer el país que va a reclamar el atacante y las unidades que le va a asignar
                paisReclamado = stoi(Reclama);
                getline(ss, tOrigen, ';'); // Leer las unidades que se le van a asignar al país reclamado
                numUnidades = stoi(tOrigen);
                cout << "País Reclamado por el Atacante: "
                     << paisReclamado << endl;
                cout << "Unidades Asignadas al País Reclamado: " << numUnidades << endl;
            }
            atacarParaArchivo(idJugador, paisOrigen, paisDestino, dador1, dador2, dador3, dadob1, dadob2, paisReclamado, numUnidades);
            cout<< endl << "/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/" << endl;
        }

        cout << endl; // Imprimir una línea en blanco para separar las jugadas
    }

    archivo.close();
    cout<< endl << "------- FIN JUGADAS PREDETERMINADAS -------" << endl << endl;
}

void Risk::ObtenerUnidadesParaArchivo(int idJugador, int numUnidades, int paisDestino)
{
  int cantiTerritorios,opera,canti;

  list<int> AmericadelNorte = {1,2,3,4,5,6,7,8,9};
  list<int> AmericadelSur = {10,11,12,13};
  list<int> Europa = {14,15,16,17,18,19,20};
  list<int> Africa = {21,22,23,24,25,26};
  list<int> Asia = {27,28,29,30,31,32,33,34,35,36,37,38};
  list<int> Australia = {39,40,41,42};


  for(list<Jugador>::iterator it = jugadores.begin(); it != jugadores.end(); it++) //NUEVAS UNIDADES: por cantidad de territorios
  {
      if((*it).getColor_jugador() == idJugador) {
        cout<<"JUGADOR: "<<(*it).getNombre_jugador()<<endl;

        list<Pais>& paises_jugador = (*it).getPaises_jugador();
        cantiTerritorios = paises_jugador.size();

        cout<<"CANTIDAD DE TERRITORIOS OCUPADOS: "<<cantiTerritorios<<endl;
        opera = (cantiTerritorios / 3);

        (*it).setCantidad_Tropas(opera);

        cout<<"UNIDADES ADICIONALES: "<<opera<<endl;
        cout<<endl;
      }
  }

  for(list<Jugador>::iterator it = jugadores.begin(); it != jugadores.end(); it++) //NUEVAS UNIDADES: por territorios de un continente
  {
      if((*it).getColor_jugador() == idJugador) {
        cout<<"JUGADOR: "<<(*it).getNombre_jugador()<<endl;
        list<Pais>& paises_jugador = (*it).getPaises_jugador();

        if(unidadesAdi_Conti(paises_jugador,AmericadelNorte))
        {
            cout<<"El jugador ocupa todos los paises de América del Norte."<<endl;
            canti = (*it).getCantidad_Tropas();
            (*it).setCantidad_Tropas(canti + 5);
            cout<<"UNIDADES ADICIONALES: 5"<<endl;
            cout<<endl;
        }
        else if(unidadesAdi_Conti(paises_jugador,AmericadelSur))
        {
            cout<<"El jugador ocupa todos los paises de America del Sur."<<endl;
            canti = (*it).getCantidad_Tropas();
            (*it).setCantidad_Tropas(canti + 2);
            cout<<"UNIDADES ADICIONALES: 2"<<endl;
            cout<<endl;
        }
        else if(unidadesAdi_Conti(paises_jugador,Europa))
        {
            cout<<"El jugador ocupa todos los paises de Europa."<<endl;
            canti = (*it).getCantidad_Tropas();
            (*it).setCantidad_Tropas(canti + 5);
            cout<<"UNIDADES ADICIONALES: 5"<<endl;
            cout<<endl;
        }
        else if(unidadesAdi_Conti(paises_jugador,Africa))
        {
            cout<<"El jugador ocupa todos los paises de Africa."<<endl;
            canti = (*it).getCantidad_Tropas();
            (*it).setCantidad_Tropas(canti + 3);
            cout<<"UNIDADES ADICIONALES: 3"<<endl;
        }
        else if(unidadesAdi_Conti(paises_jugador,Asia))
        {
            cout<<"El jugador ocupa todos los paises de Asia."<<endl;
            canti = (*it).getCantidad_Tropas();
            (*it).setCantidad_Tropas(canti + 7);
            cout<<"UNIDADES ADICIONALES: 7"<<endl;
            cout<<endl;
        }
        else if(unidadesAdi_Conti(paises_jugador,Australia))
        {
            cout<<"El jugador ocupa todos los paises de Australia."<<endl;
            canti = (*it).getCantidad_Tropas();
            (*it).setCantidad_Tropas(canti + 2);
            cout<<"UNIDADES ADICIONALES: 2"<<endl;
            cout<<endl;
        }
        else
        {
            cout<<"El jugador no ocupa un continente completo. No recibe unidades adicionales."<<endl;
            cout<<endl;
        }
        canti = 0;
    }  
  }


  for(list<Jugador>::iterator it = jugadores.begin(); it != jugadores.end(); it++) //NUEVAS UNIDADES: SEGUN CARTAS
  {
    if((*it).getColor_jugador() == idJugador) {
      bool verdadero;
      verdadero = unidades_ejercito(it);

      if(verdadero == true)
      {
          int nuevas;
          if(intercambios <= 5)
          {
              nuevas = 4 + intercambios*2;
          }
          else
          {
              nuevas = 15 + (intercambios - 6)*5;
          }
          cout<<"El jugador completa una combiancion en sus cartas."<<endl;
          cout<<"UNIDADES ADICIONALES: "<<nuevas<<endl;

          canti = (*it).getCantidad_Tropas();
          (*it).setCantidad_Tropas(canti + nuevas);
          intercambios++;
      }
      else
      {
          cout<<"El jugador no tiene alguna combinacion en sus cartas"<<endl;
          cout<<endl;
      }
    }
  }

    for(list<Jugador>::iterator it = jugadores.begin(); it != jugadores.end(); it++)
    {
        if ((*it).getColor_jugador() == idJugador)
        {
            list<Pais>& paisc = (*it).getPaises_jugador();
            for(list<Pais>::iterator it2 = paisc.begin(); it2 != paisc.end(); it2++)
            {
                if ((*it2).getId_pais() == paisDestino)
                {
                    if ((*it).getCantidad_Tropas() < numUnidades)
                    {
                        cout << endl << "EL JUGADOR NO POSEE LAS SUFICIENTES UNIDADES PARA EJECUTAR ESTA ACCIÓN." << endl;
                    }
                    else
                    {
                        int tropas = (*it).getCantidad_Tropas() - numUnidades;
                        (*it).setCantidad_Tropas(tropas);
                        int tropaspais = (*it2).getCantidad_Tropas() + numUnidades;
                        (*it2).setCantidad_Tropas(tropaspais);
                        cout << endl << "Se han agregado " << numUnidades << " unidades al país " << (*it2).getNombre_pais() << endl;
                    }
                }
            }
        }
    }

}

void Risk::fortificarParaArchivo(int idJugador, int paisOrigen, int paisDestino, int numUnidades)
{
    bool encontrado = false;
    for(list<Jugador>::iterator it = jugadores.begin(); it != jugadores.end(); it++)
    {
        if ((*it).getColor_jugador() == idJugador)
        {
            list<Pais>& paisc = (*it).getPaises_jugador();
            for(list<Pais>::iterator it2 = paisc.begin(); it2 != paisc.end(); it2++)
            {
                if ((*it2).getId_pais() == paisOrigen)
                {
                    list<int> paiscerc = (*it2).getPaises_cercanos();
                    for(list<int>::iterator it3 = paiscerc.begin(); it3 != paiscerc.end(); it3++)
                    {
                        if ((*it3) == paisDestino)
                        {
                            list<Pais>& paisesjug = (*it).getPaises_jugador();
                            for(list<Pais>::iterator it4 = paisesjug.begin(); it4 != paisesjug.end(); it4++)
                            {
                                if ((*it4).getId_pais() == paisDestino)
                                {
                                    if ((*it2).getCantidad_Tropas() >= numUnidades)
                                    {
                                        int uniOrigen = (*it2).getCantidad_Tropas() - numUnidades;
                                        (*it2).setCantidad_Tropas(uniOrigen);
                                        int uniDestino = (*it4).getCantidad_Tropas() + numUnidades;
                                        (*it4).setCantidad_Tropas(uniDestino);
                                        cout << endl << "Se han fortificado " << numUnidades << " unidades al país " << (*it4).getNombre_pais() << endl;
                                        encontrado = true;
                                    }
                                }
                            }

                        }
                    }
                }
            }
        }
    }

    if (encontrado == false)
    {
        cout << endl << endl << "NO SE PUEDE REALIZAR ESTA ACCIÓN PORQUE EL JUGADOR NO POSEE EL PAÍS DE DESTINO O NO ES CERCANO."<< endl << endl;
    }
}

void Risk::atacarParaArchivo(int idJugador, int paisOrigen, int paisDestino, int DR1, int DR2, int DR3, int DB1, int DB2, int paisReclamado, int numUnidades)
{
  int terriAtacante, terriDefensor;
    for(list<Jugador>::iterator it = jugadores.begin(); it != jugadores.end(); it++)
    {
        if ((*it).getColor_jugador() == idJugador) {
          cout<<"======================== ATACAR  ========================"<<endl;
          cout<<endl;

          cout<<"TURNO:"<<(*it).getNombre_jugador()<<endl;
          cout<<"COLOR: "<<(*it).getColor_jugador()<<endl;
          cout<<endl;

          territorios_ocupados(it); //Muestra los territorios ocupados por el jugador

          bool validCountry = false;
          terriAtacante = paisOrigen;
          // Validar también que el país tiene unidades
          for (auto& pais : (*it).getPaises_jugador()) {
            if (pais.getId_pais() == terriAtacante) {
                validCountry = true;
                break;
                }
            }

          if (!validCountry) {
            cout << endl << "El país ingresado no pertenece a tus territorios. No se puede realizar la acción." << endl << endl;
            return;
          }

          cout<<endl;
          verificar_vecinos(it,terriAtacante); //Verifica que los vecinos de ese territorio no esten ocupados por el jugador actual, ya que no podra atacar a un territorio que el jugador en turno tiene
          cout<<"TERRITORIOS POSIBLES DE ATACAR: "<<endl;
          imprimir_vecinos(it,terriAtacante);
          cout<<endl;
          bool verificar;
          terriDefensor = paisDestino;
          verificar = vecinitos_correctos(it,terriAtacante,terriDefensor);
              if(!verificar)
              {
                cout<< endl << "Territorio vecino no se encuentra. No se puede realizar la acción." << endl << endl;
                return;
              }
          cout<<endl;
          vector<int> dadosAtacante;
          dadosAtacante.push_back(DR1);
          dadosAtacante.push_back(DR2);
          dadosAtacante.push_back(DR3);
          vector<int> dadosDefensor;
          dadosDefensor.push_back(DB1);
          dadosDefensor.push_back(DB2);

          sort(dadosAtacante.begin(), dadosAtacante.end(), greater<int>());
          sort(dadosDefensor.begin(), dadosDefensor.end(), greater<int>());

          bool r, v1, v2;
          //Compara los dados y determina las bajas
          for(int i = 0; i < min(dadosAtacante.size(),dadosDefensor.size()); i++)
          {
              r = false;
              v1 = verificar_Unidades(terriDefensor);
              v2 = verificar_Unidades(terriAtacante);

              if(v1 == true || v2 == true) //Primero verifico que el territorio del atacante y defensor tengan tropas para jugar
              {
                  if(v1 == true)
                  {
                      cout<<"*El defensor no tiene tropas en este territorio*"<<endl;
                      break;
                  }
                  else if (v2 == true)
                  {
                      cout<<"*No hay tropas suficientes para atacar*"<<endl;
                      break;
                  }
              }
              else
              {
                  if(dadosAtacante[i] > dadosDefensor[i])
                  {
                      cout<<"DADO ROJO: "<<dadosAtacante[i]<<endl;
                      cout<<"DADO AZUL: "<<dadosDefensor[i]<<endl;
                      cout<<"RESULTADO: Gana el Atacante!!!"<<endl;
                      //El atacante gana, el defensor pierde una unidad
                      int D = terriDefensor;
                      r = disminuir_Unidades(D);

                      if(r == true)
                      {
                          cout<<endl;
                          cout<<"========================="<<endl;
                          cout<<"Territorio Conquistado!!!"<<endl;
                          cout<<"========================="<<endl;
                          //Asignar el territorio conquistado a la lista de territorios del jugador Atacante
                          Pais eliminado = eliminarPaisJugador(terriDefensor);
                          eliminado.setCantidad_Tropas(1);
                          (*it).agregarPais(eliminado);
                          //Asignar una carta al Atcante porque conquisto el territorio
                          int indice = rand()% cartas.size();
                          auto cartica = cartas.begin();

                          advance(cartica,indice);
                          Carta carta = *cartica;

                          cartas.erase(cartica);
                          (*it).agregarCarta(carta);
                          break;
                      } 
                  }
                  else
                  {
                      cout<<"DADO ROJO: "<<dadosAtacante[i]<<endl;
                      cout<<"DADO AZUL: "<<dadosDefensor[i]<<endl;
                      cout<<"RESULTADO: El Atacante pierde."<<endl;

                      //El defensor gana o hay empate, el atacante pierde una unidad
                      int A = terriAtacante;
                      r = disminuir_Unidades(A);
                  }
              }
              cout<<endl;
          }
      }
    }
}

void Risk::guardarJugada()
{
    ofstream archivo("tablero_comprimido.txt");

    if (!archivo.is_open())
    {
        cout << "Error al abrir el archivo para guardar la jugada." << endl;
        return;
    }

    // Escribe el número de jugadores en el archivo
    archivo << jugadores.size() << endl;

    // Recorre la lista de jugadores y escribe la información en el archivo
    for (auto itj = jugadores.begin(); itj != jugadores.end(); itj++)
    {
        archivo << (*itj).getNombre_jugador() << ";";
        archivo << obtenerNombreColor((*itj).getColor_jugador()) << ";";
        archivo << (*itj).getPaises_jugador().size() << ";";

        // Recorre los territorios (paises) del jugador y escribe su información
        for (auto it2 = (*itj).getPaises_jugador().begin(); it2 != (*itj).getPaises_jugador().end(); it2++)
        {
            archivo << (*it2).getId_pais() << ";";
            archivo << (*it2).getCantidad_Tropas() << ";";
        }

        // Escribe el número de cartas del jugador
        archivo << (*itj).getCartas_jugador().size() << ";";

        archivo << endl; // Separador para indicar el final de los datos del jugador
    }

    archivo.close();
}

string Risk::obtenerNombreColor(int idColor)
{
    switch (idColor)
    {
    case 1:
        return "Verde";
    case 2:
        return "Azul";
    case 3:
        return "Rojo";
    case 4:
        return "Blanco";
    case 5:
        return "Violeta";
    case 6:
        return "Gris";
    default:
        return "Desconocido"; // Color desconocido
    }
}

void Risk::crearGrafo()
{
    list<Pais>todosLosPaises;
    for(list<Jugador>::iterator c = jugadores.begin(); c != jugadores.end(); c++)
    {
        list<Pais> paises_conti = (*c).getPaises_jugador();

        for(list<Pais>::iterator p = paises_conti.begin(); p != paises_conti.end(); p++)
        {
            todosLosPaises.push_back(*p);
        }
    }
    grafo = Grafo(todosLosPaises);
}
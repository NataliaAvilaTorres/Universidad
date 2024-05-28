#include <iostream>
#include <fstream>
#include"Continente.h"
#include"Jugador.h"
#include"Pais.h"
#include"Risk.h"
#include"Carta.h"
#include"Huffman.h"

#include <list>

using namespace std;

int main()
{
  cout << "\033[1;31m";
  cout << "                    ██████╗ ██╗███████╗██╗  ██╗" << endl;
  cout << "                    ██╔══██╗██║██╔════╝██║ ██╔╝" << endl;
  cout << "                    ███████╔╝██║███████╗█████╔╝ " << endl;
  cout << "                    ██╔══██╗██║╚════██║██╔═██╗ " << endl;
  cout << "                    ██║  ██║██║███████║██║  ██╗" << endl;
  cout << "                    ╚═╝  ╚═╝╚═╝╚══════╝╚═╝  ╚═╝" << endl;

  cout << "       by Natalia Avila, Nicolás Montaño, and Edward Trujillo" << endl;
  cout << "                             ® Hasbro " << endl;
  cout << "\033[0m";

    list<Continente> continentes;
    list<Jugador>jugadores;
    list<Carta>cartas;

    continentes.push_back(Continente(1, "America del Norte", {Pais(1, "Alaska",0,0,{6,32}),
                                                              Pais(2, "Alberta",0,0,{6,7,9}),
                                                              Pais(3, "America Central",0,0,{4,9}),
                                                              Pais(4, "Estados unidos orientales",0,0,{3,7,9}),
                                                              Pais(5, "Groenlandia ",0,0,{6,7,8,15}),
                                                              Pais(6, "Territorio Noroccidental",0,0,{2,5,7}),
                                                              Pais(7, "Ontario",0,0,{2,4,5,8,9}),
                                                              Pais(8, "Quebec",0,0,{4,5,7}),
                                                              Pais(9, "Estados Unidos Occidentales",0,0,{2,3,4})
                                                             }));

    continentes.push_back(Continente(2, "America del Sur", {Pais(10, "Argentina",0,0,{11,12}),
                                                            Pais(11, "Brasil",0,0,{10,12,13,25}),
                                                            Pais(12, "Peru",0,0,{10,11,13}),
                                                            Pais(13, "Venezuela",0,0,{11,12}),
                                                            }));


    continentes.push_back(Continente(3, "Europa", {Pais(14, "Gran Bretana",0,0,{16,17,20}),
                                                   Pais(15, "Islandia",0,0,{14,17}),
                                                   Pais(16, "Europa del Norte",0,0,{20,18,17}),
                                                   Pais(17, "Escandinavia",0,0,{16,14,19}),
                                                   Pais(18, "Europa del Sur",0,0,{20,16,19,23}),
                                                   Pais(19, "Ucrania",0,0,{18,16,17,20,27,37}),
                                                   Pais(20, "Europa Occidental",0,0,{14,25,16,18}),
                                                  }));

    continentes.push_back(Continente(4, "Africa", {Pais(21, "Congo",0,0,{22,26,25}),
                                                   Pais(22, "Africa Oriental",0,0,{21,26,24,23}),
                                                   Pais(23, "Egipto",0,0,{25,22}),
                                                   Pais(24, "Madagascar",0,0,{26,22}),
                                                   Pais(25, "Africa del Norte",0,0,{23,21,22,11}),
                                                   Pais(26, "Africa del Sur",0,0,{21,22,24}),
                                                  }));

    continentes.push_back(Continente(5, "Asia", {Pais(27, "Afghanistan",0,0,{33,29,37,28}),
                                                 Pais(28, "China",0,0,{35,29,27,37,36,34}),
                                                 Pais(29, "India",0,0,{33,35,28,27}),
                                                 Pais(30, "Irkutsk",0,0,{34,38,36}),
                                                 Pais(31, "Japon",0,0,{34,32}),
                                                 Pais(32, "Kamchatka",0,0,{34,30,38,1}),
                                                 Pais(33, "Medio Oriente",0,0,{29,27,19}),
                                                 Pais(34, "Mongolia",0,0,{30,28,31}),
                                                 Pais(35, "Siam",0,0,{29,28,40}),
                                                 Pais(36, "Siberia",0,0,{37,38,30}),
                                                 Pais(37, "Ural",0,0,{27,36,28,19}),
                                                 Pais(38, "Yakutsk",0,0,{36,30,32}),
                                                 }));

    continentes.push_back(Continente(6, "Australia",{Pais(39, "Australia Oriental",0,0,{42,41}),
                                                      Pais(40, "Indonesia",0,0,{35,41}),
                                                      Pais(41, "Nueva Guinea",0,0,{39,42,40}),
                                                      Pais(42, "Australia Occidental",0,0,{39,41}),

                                                    }));



    cartas.push_back(Carta(1,"TR",27,1));
    cartas.push_back(Carta(2,"TR",1,2));
    cartas.push_back(Carta(3,"TR",2,2));
    cartas.push_back(Carta(4,"TR",10,1));
    cartas.push_back(Carta(5,"TR",11,1));
    cartas.push_back(Carta(6,"TR",9,1));
    cartas.push_back(Carta(7,"TR",28,2));
    cartas.push_back(Carta(8,"TR",24,2));
    cartas.push_back(Carta(9,"TR",23,1));
    cartas.push_back(Carta(10,"TR",40,3));
    cartas.push_back(Carta(11,"TR",4,2));
    cartas.push_back(Carta(12,"TR",25,3));
    cartas.push_back(Carta(13,"TR",18,1));
    cartas.push_back(Carta(14,"TR",5,3));
    cartas.push_back(Carta(15,"TR",19,3));
    cartas.push_back(Carta(16,"TR",29,3));
    cartas.push_back(Carta(17,"TR",41,1));
    cartas.push_back(Carta(18,"TR",30,2));
    cartas.push_back(Carta(19,"TR",31,3));
    cartas.push_back(Carta(20,"TR",32,2));
    cartas.push_back(Carta(21,"TR",26,3));
    cartas.push_back(Carta(22,"TR",33,2));
    cartas.push_back(Carta(23,"TR",34,3));
    cartas.push_back(Carta(24,"TR",42,3));
    cartas.push_back(Carta(25,"TR",21,1));
    cartas.push_back(Carta(26,"TR",15,3));
    cartas.push_back(Carta(27,"TR",8,3));
    cartas.push_back(Carta(28,"TR",6,2));
    cartas.push_back(Carta(29,"TR",12,3));
    cartas.push_back(Carta(30,"TR",7,2));
    cartas.push_back(Carta(31,"TR",14,1));
    cartas.push_back(Carta(32,"TR",35,3));
    cartas.push_back(Carta(33,"TR",36,1));
    cartas.push_back(Carta(34,"TR",22,2));
    cartas.push_back(Carta(35,"TR",16,1));
    cartas.push_back(Carta(36,"TR",20,1));
    cartas.push_back(Carta(37,"TR",37,1));
    cartas.push_back(Carta(38,"TR",13,3));
    cartas.push_back(Carta(39,"TR",39,2));
    cartas.push_back(Carta(40,"TR",17,1));
    cartas.push_back(Carta(41,"TR",3,2));
    cartas.push_back(Carta(42,"TR",38,2));

    Risk risk(jugadores,continentes,cartas);

    cout << "\n¡Bienvenido a Risk, el juego de conquistas! El objetivo es simple: los jugadores tienen que conquistar territorios enemigos creando un ejército, moviendo sus tropas y luchando en batallas.\n\n";

  bool valida = false;
  ofstream archivo("jugadas_comprimido.txt");

  while (!valida) {
    cout << "Por favor seleccionen una opción:\n";
    cout << "\033[1;32m1. Inicializar Juego Manualmente\033[0m\n";
    cout << "\033[1;34m2. Inicializar Juego a partir de Archivo Comprimido de Texto\033[0m\n";
    cout << "\n$ ";
    string opcion;
    getline(cin, opcion);

    if (opcion == "1") {
      cout << "\nHan seleccionado 'Inicializar Juego Manualmente'.\n\n";
      valida = true;
      risk.inicializar();
      risk.fortificar();
      risk.obtener_UnidadesAdicionales();
      bool salir = false;
      bool gana = false;
      while (!salir) {
        bool valido3 = false;
        string accion;
        while (!valido3) {
          cout << "\n¿Qué desean hacer a continuación?\n";
          cout << "Por favor seleccionen una opción:\n";
          if (!gana) {
            cout << "\033[1;31m1. Realizar Turnos\033[0m\n";
          }
          cout << "\033[1;34m2. Comprimir Jugada\033[0m\n";
          cout << "\033[1;36m3. Salir\033[0m\n";
          cout << "\n$ ";  // Indicador de línea de comando
          getline(cin, accion);
          if (accion == "1" && gana == false) {
            cout << "\nHan seleccionado 'Realizar Turnos'.";
            cout << endl;
            int cont = 1;
            while (cont != risk.getJugadores().size() && !gana) {
              for (auto& jug : risk.getJugadores()){
                if (jug.getColor_jugador() == cont) {
                  cout << endl << endl << "ES EL TURNO DE: " << jug.getNombre_jugador() << endl;
                  risk.turno(cont);
                  gana = risk.verificarGanador();
                }
              }
              cont++;
            }
          } else if (accion == "2") {
            cout << "\nHan seleccionado 'Comprimir Jugada'.\n\n";
            risk.guardarJugada();
          } else if (accion == "3") {
              cout << "\nHan seleccionado 'Salir'.\n\n";
              salir = true;
              valido3 = true;
          } else {
              cout << "\nOpción no válida. Por favor, intenta de nuevo.\n";
          }
        }
      }
    } else if (opcion == "2") {
      cout << "\nHan seleccionado 'Inicializar Juego a partir de Archivo Comprimido de Texto'.\n\n";
      valida = true;
      risk.leerArchivo();
      list<Continente> continentesR = risk.getContinentes(); 
      risk.crearGrafo(continentesR);
      risk.leerArchivoJugada();
      risk.obtener_UnidadesAdicionales();
      bool salir = false;
      bool gana = false;
      while (!salir) {
        bool valido3 = false;
        string accion;
        while (!valido3) {
          cout << "\n¿Qué desean hacer a continuación?\n";
          cout << "Por favor seleccionen una opción:\n";
          if (!gana) {
            cout << "\033[1;31m1. Realizar Turnos\033[0m\n";
          }
          cout << "\033[1;34m2. Comprimir Jugada\033[0m\n";
          cout << "\033[1;36m3. Salir\033[0m\n";
          cout << "\n$ ";  // Indicador de línea de comando
          getline(cin, accion);
          if (accion == "1" && gana == false) {
            cout << "\nHan seleccionado 'Realizar Turnos'.";
            cout << endl;
            int cont = 1;
            while (cont != risk.getJugadores().size() && !gana) {
              for (auto& jug : risk.getJugadores()){
                if (jug.getColor_jugador() == cont) {
                  cout << endl << endl << "ES EL TURNO DE: " << jug.getNombre_jugador() << endl;
                  risk.turno(cont);
                  gana = risk.verificarGanador();
                }
              }
              cont++;
            }
          } else if (accion == "2") {
            char opcionhuff;
            cout << "\nHan seleccionado 'Comprimir Jugada'.\n\n";
            risk.guardarJugada();
            cout<< "\nSe ha guardado la jugada en el archivo 'tablero_comprimido.txt'.\n";
            cout << "\033[1;34m1. ¿Desea realizar el algoritmo de Huffman para el archivo comprimido? (s/n): \033[0m\n";
            cin>>opcionhuff;
            if (opcionhuff == 's')
            {
              string text;
              ifstream tablero_comprimido("tablero_comprimido.txt");
              string line;
              while (getline(tablero_comprimido, line)) {
                  text += line + "\n";
              }
              tablero_comprimido.close();
              CrearArbol(text);
              string diccionarioArchivo = "huffman_binario.txt";
              string textoArchivo = "jugadas_comprimido.txt";
              string archivoSalida = "comprimido.bin";

              map<string, char> diccionario = leerDiccionario(diccionarioArchivo);
              ifstream textoStream(textoArchivo);
              string texto((istreambuf_iterator<char>(textoStream)), istreambuf_iterator<char>());

              comprimirTexto(diccionario, texto, archivoSalida);

              cout << "Texto comprimido y guardado en " << archivoSalida << endl;
              cout<<"\n Se realizo correctamente el algoritmo de huffman :) \n";
            }
            if (opcionhuff == 'n')
            {
              break;
            }
            else
            {
              cout<<"\nOpción no válida. Por favor, intenta de nuevo.\n";
            }
          } else if (accion == "3") {
              cout << "\nHan seleccionado 'Salir'.\n\n";
              salir = true;
              valido3 = true;
          } else {
              cout << "\nOpción no válida. Por favor, intenta de nuevo.\n";
          }
        }
      }
    } else {
      cout << "\nOpción no válida. Por favor, intenta de nuevo.\n\n";
    }

  }

  cout << "\033[1;31m GRACIAS POR HABER JUGADO RISK. \033[0m\n\n";

  cout << "\033[1;31m";
  cout << "██████╗ ██╗███╗   ██╗" << endl;
  cout << "██╔═══╝ ██║████╗  ██║" << endl;
  cout << "██║████ ██║██╔██╗ ██║" << endl;
  cout << "██╔═══╝ ██║██║╚██╗██║" << endl;
  cout << "██║     ██║██║ ╚████║" << endl;
  cout << "╚═╝     ╚═╝╚═╝  ╚═══╝" << endl;

  cout << "                    ██████╗ ██╗███████╗██╗  ██╗" << endl;
  cout << "                    ██╔══██╗██║██╔════╝██║ ██╔╝" << endl;
  cout << "                    ███████╔╝██║███████╗█████╔╝ " << endl;
  cout << "                    ██╔══██╗██║╚════██║██╔═██╗ " << endl;
  cout << "                    ██║  ██║██║███████║██║  ██╗" << endl;
  cout << "                    ╚═╝  ╚═╝╚═╝╚══════╝╚═╝  ╚═╝" << endl;

  cout << "® Hasbro " << endl;
  cout << "\033[0m";
  return 0;
}
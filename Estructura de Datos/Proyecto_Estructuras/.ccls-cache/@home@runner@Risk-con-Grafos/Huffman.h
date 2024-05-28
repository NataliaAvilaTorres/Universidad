#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <fstream>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <map>

using namespace std;

struct Nodo {
  char simbolo;
  int frecuencia;
  Nodo *izq, *der;
};

Nodo *getNodo(char simbolo, int frecuencia, Nodo *izq, Nodo *der);

struct comparacion {
  bool operator()(Nodo *i, Nodo *d);
};

void encode(Nodo *raiz, string str, unordered_map<char, string> &CodigoHuffman);

void decode(Nodo *raiz, int &index, string str, ofstream &huffman_decodificado);

void CrearArbol(string text);
map<string, char> leerDiccionario(const string& nombreArchivo);
void comprimirTexto(const std::map<std::string, char>& diccionario, const std::string& texto, const std::string& nombreArchivoSalida);
#endif // HUFFMAN_H
#include "Huffman.h"

Nodo *getNodo(char simbolo, int frecuencia, Nodo *izq, Nodo *der) {
  Nodo *nodo = new Nodo();
  nodo->simbolo = simbolo;
  nodo->frecuencia = frecuencia;
  nodo->izq = izq;
  nodo->der = der;
  return nodo;
}

bool comparacion::operator()(Nodo *i, Nodo *d) {
  return i->frecuencia > d->frecuencia;
}

void encode(Nodo *raiz, string str,
            unordered_map<char, string> &CodigoHuffman) {
  if (raiz == nullptr) {
    return;
  }
  if (!raiz->izq && !raiz->der) {
    CodigoHuffman[raiz->simbolo] = str;
  }
  encode(raiz->izq, str + "0", CodigoHuffman);
  encode(raiz->der, str + "1", CodigoHuffman);
}

void decode(Nodo *raiz, int &index, string str,
            ofstream &huffman_decodificado) {
  if (raiz == nullptr) {
    return;
  }
  if (!raiz->izq && !raiz->der) {
    huffman_decodificado << raiz->simbolo;
    return;
  }
  index++;
  if (str[index] == '0')
    decode(raiz->izq, index, str, huffman_decodificado);
  else
    decode(raiz->der, index, str, huffman_decodificado);
}

void CrearArbol(string text) {
  unordered_map<char, int> frecuencia;
  for (char simbolo : text) {
    frecuencia[simbolo]++;
  }
  

  priority_queue<Nodo *, vector<Nodo *>, comparacion> pq;

  for (auto pair : frecuencia) {
    pq.push(getNodo(pair.first, pair.second, nullptr, nullptr));
  }

  while (pq.size() != 1) {
    Nodo *izq = pq.top();
    pq.pop();
    Nodo *der = pq.top();
    pq.pop();
    int sum = izq->frecuencia + der->frecuencia;
    pq.push(getNodo('\0', sum, izq, der));
  }

  Nodo *raiz = pq.top();

  unordered_map<char, string> CodigoHuffman;
  encode(raiz, "", CodigoHuffman);

  ofstream huffman_binario("huffman_binario.txt");
  for (auto pair : CodigoHuffman) {
    huffman_binario << pair.first << " " << pair.second << '\n';
  }
  huffman_binario.close();

  string str = "";
  for (char simbolo : text) {
    str += CodigoHuffman[simbolo];
  }

  ofstream huffman_decodificado("huffman_decodificado.txt");
  int index = -1;
  while (index < (int)str.size() - 2) {
    decode(raiz, index, str, huffman_decodificado);
  }
  huffman_decodificado.close();
}

std::map<std::string, char> leerDiccionario(const std::string& nombreArchivo) {
    std::map<std::string, char> diccionario;
    std::ifstream archivo(nombreArchivo);
    std::string linea;

    while (std::getline(archivo, linea)) {
        if (linea.length() > 1) {
            char caracter = linea[0];
            std::string codigo = linea.substr(2);
            diccionario[codigo] = caracter;
        }
    }

    return diccionario;
}

void comprimirTexto(const std::map<std::string, char>& diccionario, const std::string& texto, const std::string& nombreArchivoSalida) {
    std::string bitsComprimidos;
    std::string codigoActual;

    for (char c : texto) {
        codigoActual += c;
        if (diccionario.count(codigoActual) > 0) {
            bitsComprimidos += diccionario.at(codigoActual);
            codigoActual.clear();
        }
    }

    // Escribir los bits comprimidos en un archivo binario
    std::ofstream archivoBinario(nombreArchivoSalida, std::ios::binary);
    for (size_t i = 0; i < bitsComprimidos.length(); i += 8) {
        std::string byte = bitsComprimidos.substr(i, 8);
        char caracter = static_cast<char>(std::stoi(byte, nullptr, 2));
        archivoBinario.write(&caracter, 1);
    }
}
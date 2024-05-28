#ifndef PAIS_H
#define PAIS_H

#include<list>
#include<string>
using namespace std;

class Pais
{
private:
    int id_pais;
    string nombre_pais;
    int color;
    int cantidad_Tropas;
    list<int>paises_cercanos;

public:
    Pais();
    Pais(int,string,int,int,list<int>);
    ~Pais();

    string getNombre_pais();
    int getId_pais();
    int getColor();
    int getCantidad_Tropas();
    list<int>& getPaises_cercanos();

    void setNombre_pais(string);
    void setId_pais(int);
    void setColor(int);
    void setCantidad_Tropas(int);
    void setPaises_cercanos(list<int>);
};

#endif // PAIS_H
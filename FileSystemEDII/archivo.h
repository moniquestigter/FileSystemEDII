#ifndef ARCHIVO_H
#define ARCHIVO_H


#include <stdio.h>
#include <iostream>

using namespace std;

class Archivo{
public:
    Archivo(char * nombre, long size);
    void abrir();
    char * leer(int pos, int longitud);
    void escribir(char * data,int pos,int longitud);
    void cerrar();
    void setTamano(long pos);
    void formatear();

private:
    FILE * file;
    char * nombre;
};



#endif // ARCHIVO_H

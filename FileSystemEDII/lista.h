#ifndef LISTA_H
#define LISTA_H

#include "fileentry.h"

class Lista
{
public:
    Lista();

    void agregarALista(FileEntry * obj);
    int buscar(char * nombre);
    FileEntry * at(int pos);
    int size();
    FileEntry * inicial;

    int cant;

};

#endif // LISTA_H

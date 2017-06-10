#ifndef BLOQUEFOLDER_H
#define BLOQUEFOLDER_H


#include <stdio.h>
#include <iostream>
#include "Archivo.h"
#include <vector>
#include <QList>
#include "MasterBlock.h"
#include "FileEntry.h"

using namespace std;

class BloqueFolder{
public:
    BloqueFolder(char * nombre, int numB, int tamB,Archivo * archivo);

    int getTamanoBloque();
    void setTamanoBloque(int tB);

    int getNumBloque();
    char * getNombre();

    FileEntry * getFileEntry();
    void setFileEntry(char* n, int fB, int lB, bool isF, int s);
    QList<FileEntry*> getListaEntries();
    void agregarFileEntry(FileEntry * fe);
    void escribirEntries(int pos);
    void imprimirNombre();
    void cargar();
    void setNombre(char * n);
    void setCantArchivos(BloqueFolder * actual);

    BloqueFolder * getSiguiente();
    BloqueFolder * getAnterior();
    void setSiguiente(BloqueFolder * bf);
    void setAnterior(BloqueFolder * bf);
    Archivo * getArchivo();
    int cantArchivos;
    void setCant(BloqueFolder * actual);

private:
    void initFromChar(char * d);
    Archivo * archivo;
    QList<FileEntry*> listaEntries;
    int tamanoBloque;
    int numBloque;
    char * nombre;
    BloqueFolder * siguiente;
    BloqueFolder * anterior;
    FileEntry *fe;
};



#endif // BLOQUEFOLDER_H

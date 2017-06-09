#ifndef API_H
#define API_H

#include <stdio.h>
#include <string.h>
#include "MasterBlock.h"
#include "Archivo.h"
#include "BloqueFolder.h"
#include "DiscoVirtual.h"
#include <vector>

using namespace std;

class API
{
public:
    API();
    void dir();
    void dirFolderActual();
    void printRoot();
    void crearDiscoVirtual();

    BloqueArchivo * crearArchivo(char * nombre, BloqueFolder * actual, char * contenido);
    BloqueFolder * crearFolder(char * nombre,BloqueFolder * actual);

    void escribirEntries(FileEntry *fe,BloqueFolder * actual);
    void addRoot();
    BloqueFolder * root;
    DiscoVirtual * dv;
    int abrirFolder(char * n);
    int leerArchivo(char * n,BloqueFolder * bf);
    int initFromChar(BloqueFolder * actual);
    void guardarEntries();

private:
    int rootSize;

};

#endif // API_H

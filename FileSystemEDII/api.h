#ifndef API_H
#define API_H

#include <stdio.h>
#include <string.h>
#include "MasterBlock.h"
#include "Archivo.h"
#include "BloqueFolder.h"
#include "DiscoVirtual.h"
#include "lista.h"
#include <idxentry.h>
#include <QHash>

using namespace std;

class API
{
public:
    API();

    void crearDiscoVirtual();

    BloqueArchivo * crearArchivo(char * nombre, BloqueFolder * actual, char * contenido);
    BloqueFolder * crearFolder(char * nombre,BloqueFolder * actual);
    void formatear();
    void escribirEntries(FileEntry *fe,BloqueFolder * actual);
    void addRoot();
    BloqueFolder * root;
    DiscoVirtual * dv;
    BloqueFolder * abrirFolder(char * n,BloqueFolder * actual);
    char * leerArchivo(char * n,BloqueFolder * actual);
    int initFromChar(BloqueFolder * actual);
    string Duplicados(string nombre,int tipo);
    vector<char *> nombres;

    int rootSize;

private:
    string duplicadosAux(string nombre, int cant,int tamanoPalabra,int tipo);
    string toLowerCase(string palabra);
};

#endif // API_H

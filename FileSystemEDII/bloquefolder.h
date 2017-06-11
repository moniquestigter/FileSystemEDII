#ifndef BLOQUEFOLDER_H
#define BLOQUEFOLDER_H
#include "Archivo.h"
#include <qtreewidget.h>
#include <vector>
#include "MasterBlock.h"
#include "FileEntry.h"
#include "idxentry.h"
#include "hashtable.h"

class BloqueFolder
{
public:
    BloqueFolder(char * nombre, int numB, int tamB,Archivo * archivo);

    void initFromChar(char * d);
    char * nombre;
    int tamanoBloque;
    int numBloque;
    Archivo * archivo;
    FileEntry *fe;
    HashTable * hashT;
    vector<FileEntry*> listaEntries;

    void setFileEntry(char* n, int fB, int lB, bool isF, int s);
    void agregarFileEntry(FileEntry * fe);
    void escribirEntries(int pos);
    void setTamanoBloque(int tB);
    vector<FileEntry*> getListaEntries();
    BloqueFolder * siguiente;
    BloqueFolder * anterior;
    int cantArchivos;

    void setCantArchivos(BloqueFolder * actual);
    vector<BloqueArchivo*> listaBloqueArchivo;
    vector<BloqueFolder*> listaBloqueFolder;
    void setNumBloquesEnIdx(int cant);
    QTreeWidgetItem * item;

};
#endif // BLOQUEFOLDER_H


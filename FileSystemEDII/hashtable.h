#ifndef HASHTABLE_H
#define HASHTABLE_H
#include <stdio.h>
#include "Archivo.h"
#include "IdxEntry.h"
#include "FileEntry.h"
#include <vector>
#include <QHash>
using namespace std;
class HashTable
{
public:
    HashTable(Archivo * arch);
    QHash<char *, IdxEntry*> hashTable;
    IdxEntry * ie;
    IdxEntry *  hash(char * nombre);
    void imprimirNombre();
    char * nomHash;
    void setNombre(char * nom);
    char * getNombre();
    void agregarIdxEntry(char * nom,int numB, int numE, int size);
    Archivo * archivo;
    int cantArchivos = 0;
};

#endif // HASHTABLE_H

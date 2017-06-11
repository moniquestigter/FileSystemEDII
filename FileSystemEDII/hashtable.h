#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "discovirtual.h"
#include <QHash>
#include "idxentry.h"

class HashTable
{
public:
    HashTable();
    QHash<char *, IdxEntry> hashTable;

    IdxEntry * ie;

    void setIdxEntry(char *n, int nB, int nE);
    void agregarIdxEntry(IdxEntry * ie);
    void addToTable(FileEntry * fe);
    void buscar(FileEntry * fe);

    vector<IdxEntry*> idxListaEntries;
    vector<IdxEntry*> getListaIdxEntries();


    IdxEntry * buscar();
};

#endif // HASHTABLE_H

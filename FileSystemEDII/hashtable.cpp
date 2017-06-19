#include "hashtable.h"

HashTable::HashTable(Archivo * arch)
{
    ie = new IdxEntry();
    archivo = arch;
}

IdxEntry * HashTable::hash(char * nombre){
    IdxEntry * idx = hashTable.value(nombre);
    return idx;
}

void HashTable::agregarIdxEntry(char * nom,int numB, int numE, int size){
    ie->setTodo(nom, numB, numE,size);
    hashTable.insert(nom,ie);
}


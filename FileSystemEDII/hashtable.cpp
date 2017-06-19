#include "hashtable.h"

HashTable::HashTable(Archivo * arch)
{
    ie = new IdxEntry();
    archivo = arch;
}

IdxEntry * HashTable::hash(char * nombre){
    return &hashTable.at(nombre);
}

void HashTable::agregarIdxEntry(char * nom,int numB, int numE){
    ie->setTodo(nom, numB, numE);
    hashTable.insert(std::pair<char * ,IdxEntry>(nom,*ie));
}


#include "hashtable.h"

HashTable::HashTable(Archivo * arch)
{
    ie = new IdxEntry();
    archivo = arch;
}

IdxEntry * HashTable::hash(char * nombre){
    foreach(IdxEntry* idx, hashTable){
        if(idx->getNombre() == nombre)
            return idx;
    }
    return NULL;

    //IdxEntry * idx = hashTable.value(nombre);
   // return idx;
}

void HashTable::agregarIdxEntry(char * nom,int numB, int numE, int size){
    IdxEntry * idx = new IdxEntry();
    idx->setTodo(nom, numB, numE,size);
    hashTable.insert(nom,idx);
    cout<<hash(nom)<<endl;
}


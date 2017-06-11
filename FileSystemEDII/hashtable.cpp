#include "hashtable.h"

HashTable::HashTable()
{
    ie = new IdxEntry();
}

/*void HashTable::setIdxEntry(char *n, int nB, int nE){
    ie->setTodo(n,nB,nE);
}

void HashTable::addToTable(IdxEntry * id){
    hashTable.insert(id->getNombre(),id);
}

IdxEntry * HashTable::agregarIdxEntry(FileEntry * fe){
    ie->setTodo(fe->getNombre(),hash(fe->getNombre()),fe->code);
    return ie;
}

int HashTable::hash(char * nombre){
    IdxEntry * idx = hashTable.value(nombre);
    return idx->getNumBloque();
}

void HashTable::buscar(BloqueFolder * bf, char * nom){
    FileEntry * fiE;
    vector<FileEntry*> lista = bf->getListaEntries();
    for(int a = 0; a<lista.size(); a++){
        if(lista.at(a)->getNombre() == nom){
            fiE = lista.at(a);
        }
    }
    int numB = hash(fiE->getNombre());

}
*/


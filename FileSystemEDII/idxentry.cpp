#include "idxentry.h"

IdxEntry::IdxEntry()
{

}

void IdxEntry::setTodo(char * nom,int nB, int nE){
    nombre = nom;
    numBloque = nB;
    numEntry = nE;
    cantIdxEntries++;
}

void IdxEntry::setNombre(char * nom){
    nombre = nom;
}

void IdxEntry::setNumBloque(int num){
    numBloque = num;
}

void IdxEntry::setNumEntry(int numE){
    numEntry = numE;
}

char * IdxEntry::getNombre(){
    return nombre;
}

int IdxEntry::getNumBloque(){
    return numBloque;
}

int IdxEntry::getNumEntry(){
    return numEntry;
}

int IdxEntry::getCantIdxEntries(){
    return cantIdxEntries;
}

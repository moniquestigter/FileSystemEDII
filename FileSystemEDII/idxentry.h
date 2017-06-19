#ifndef IDXENTRY_H
#define IDXENTRY_H
#include <stdio.h>
#include <iostream>
using namespace std;

class IdxEntry
{
public:
    IdxEntry();
    void setNombre(char * nom);
    void setNumBloque(int num);
    void setNumEntry(int numE);
    void setSizeBloque(int s);
    void setTodo(char * nom,int nB, int nE, int s);

    char * getNombre();
    int getNumBloque();
    int getNumEntry();
    int getCantIdxEntries();
    int getSizeBloque();

    char * nombre;
    int numBloque;
    int numEntry;
    int cantIdxEntries;
    int size;
};

#endif // IDXENTRY_H

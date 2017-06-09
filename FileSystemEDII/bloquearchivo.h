#ifndef BLOQUEARCHIVO_H
#define BLOQUEARCHIVO_H

#include <stdio.h>
#include "MasterBlock.h"
#include "FileEntry.h"
#include "archivo.h"
#include <string.h>

class BloqueArchivo{
public:
    BloqueArchivo(char * nombre, int numB, int tamB,Archivo * archivo);
    int getTamanoBloque();
    int getNumBloque();
    char * getNombre();
    void setNombre(char * nombre);
    FileEntry * getFileEntry();
    void setFileEntry(char* n, int fB, int lB, bool isF, int s);
    bool getEscritura();
    void setEscritura(bool escritura);
    Archivo * getArchivo();
    char * leer();

private:
    void initFromChar(char * d);
    int tamanoBloque;
    int numBloque;
    char * nombre;
    FileEntry *fe;
    Archivo * archivo;

};

#endif // BLOQUEARCHIVO_H

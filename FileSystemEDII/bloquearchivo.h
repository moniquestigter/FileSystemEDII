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
    void setFileEntry(char* n, int fB, int lB, bool isF, int s); 
    char * leer();
    FileEntry *fe;
    int tamanoBloque;
    int numBloque;
    char * nombre;
    Archivo * archivo;
    void initFromChar(char * d);

private:



};

#endif // BLOQUEARCHIVO_H

#ifndef MASTERBLOCK_H
#define MASTERBLOCK_H



#include <stdio.h>
#include "BloqueArchivo.h"
#include "Archivo.h"

class MasterBlock
{
public:
    MasterBlock(Archivo * archivo,int tam, int cantB, int first, int sigDisp);
    int getTamanoBloque();
    int getCantBloques();
    int getPrimerBloque();
    int getSigDisponible();
    void setSiguienteDisponible(int x);
    MasterBlock * cargar();
    void guardar();
    char * masterBlockToChar();
    Archivo * archivo;

    MasterBlock * charToMasterBlock(char * c);

    void initFromChar(char * d);
    int tamanoBloque;
    int cantBloques;
    int primero;
    int sigDisponible;
};


#endif // MASTERBLOCK_H

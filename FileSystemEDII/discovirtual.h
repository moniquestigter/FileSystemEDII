#ifndef DISCOVIRTUAL_H
#define DISCOVIRTUAL_H

#include <stdio.h>
#include <vector>
#include "Archivo.h"
#include "MasterBlock.h"
#include "BloqueFolder.h"
#include "lista.h"
#include "hashtable.h"

class DiscoVirtual{
public:
    DiscoVirtual(Archivo * arch,int tamArc,int tamBlo);

    BloqueFolder * asignarSiguienteBloque(int numeroBloque);
    void formatear();
    void cargar();
    Lista * listarArchivosEnRaiz();

    int getTamanoArchivo();
    int getTamanoBloque();
    BloqueFolder * getFolderActual();
    void setFolderActual(BloqueFolder * bf);
    Archivo * getArchivo();
    MasterBlock * getMasterBlock();
    BloqueFolder * getRaiz();
    void setRaiz(BloqueFolder * bf);

    vector<BloqueArchivo*> listaBloqueArchivo;
    vector<BloqueFolder*> listaBloqueFolder;
    vector<HashTable*> listaHashTables;

    int tamArchivo,tamBloque;
    Archivo * archivo;
    MasterBlock * mb;
    BloqueFolder * raiz;
    BloqueFolder * folderActual;
};

#endif // DISCOVIRTUAL_H

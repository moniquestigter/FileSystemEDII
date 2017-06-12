#ifndef DISCOVIRTUAL_H
#define DISCOVIRTUAL_H
#include "BloqueFolder.h"
#include "BloqueArchivo.h"

class DiscoVirtual{
public:
    DiscoVirtual(Archivo * arch,int tamArc,int tamBlo);


    void formatear();
    void cargar();
    QList<FileEntry*> listarArchivosEnRaiz();

    int getTamanoArchivo();
    int getTamanoBloque();


    BloqueFolder * folderActual;
    Archivo * getArchivo();
    MasterBlock * getMasterBlock();
    vector<HashTable*> listaHashTables;

    int tamArchivo,tamBloque;
    Archivo * archivo;
    MasterBlock * mb;
    BloqueFolder * getFolderActual();
    void setFolderActual(BloqueFolder * bf);
    BloqueFolder * getRaiz();
    void setRaiz(BloqueFolder * bf);
    BloqueFolder * raiz;
    vector<BloqueArchivo*> listaBloqueArchivo;
    vector<BloqueFolder*> listaBloqueFolder;

private:


};

#endif // DISCOVIRTUAL_H

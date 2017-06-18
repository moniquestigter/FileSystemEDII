#include "discovirtual.h"

DiscoVirtual::DiscoVirtual(Archivo * arch,int tamArc,int tamBlo){
    archivo = arch;
    tamArchivo = tamArc;

    tamBloque = tamBlo;
}

BloqueFolder * DiscoVirtual::getFolderActual()
{
    return folderActual;
}

void DiscoVirtual::setFolderActual(BloqueFolder * bf)
{
    folderActual = bf;
}

void DiscoVirtual::formatear()
{
    mb = new MasterBlock(archivo,tamBloque,(tamArchivo/tamBloque),-1,1);
    mb->guardar();
    hashTable = new HashTable(archivo);
    mb->setSiguienteDisponible(7);
    char * mB = mb->masterBlockToChar();
    archivo->escribir(mB,1,strlen(mB));
}

void DiscoVirtual::cargar()
{
    this->hashTable = new HashTable(archivo);
    archivo->abrir();
    mb = new MasterBlock(archivo,tamBloque,(tamArchivo/tamBloque),0,1);
    mb = mb->cargar();
    mb->setSiguienteDisponible(7);
}

BloqueFolder * DiscoVirtual::getRaiz()
{
    return raiz;
}

void DiscoVirtual::setRaiz(BloqueFolder * bf)
{
    raiz = bf;
}

int DiscoVirtual::getTamanoArchivo()
{
    return tamArchivo;
}

int DiscoVirtual::getTamanoBloque()
{
    return tamBloque;
}

Archivo * DiscoVirtual::getArchivo()
{
    return archivo;
}

MasterBlock * DiscoVirtual::getMasterBlock()
{
    return mb;
}

HashTable * DiscoVirtual::getHashTable()
{
    return hashTable;
}



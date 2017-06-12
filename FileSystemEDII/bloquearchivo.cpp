#include "bloquearchivo.h"

BloqueArchivo::BloqueArchivo(char * nombre, int numB,int tamB,Archivo * archivo)
{
    this->nombre = nombre;
    this->numBloque = numB;
    this->tamanoBloque = tamB;
    fe = new FileEntry();
    archivo = archivo;
    item = NULL;
}

void BloqueArchivo::setFileEntry(char* n, int fB, int lB, bool isF, int s)
{
    fe->setFirstBlock(fB);
    fe->setIsFolder(isF);
    fe->setLastBlock(lB);
    fe->setNombre(n);
    fe->setSize(s);
}

void BloqueArchivo::initFromChar(char * d)
{
    int pos = 0;
    memcpy(&nombre, &d[pos], 30);
    pos+=30;
    memcpy(&numBloque, &d[pos], 4);
    pos+=4;
    memcpy(&tamanoBloque, &d[pos], 4);
    pos+=4;
}


char * BloqueArchivo::leer()
{
    char * nombre = {"DiscoVirtual.txt"};
    Archivo * arch = new Archivo(nombre,256*4096);
    char * a = arch->leer(numBloque*4096,tamanoBloque);
    return a;
}


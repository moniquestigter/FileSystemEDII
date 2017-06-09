#include "bloquearchivo.h"

BloqueArchivo::BloqueArchivo(char * nombre, int numB,int tamB,Archivo * archivo)
{
    this->nombre = nombre;
    this->numBloque = numB;
    this->tamanoBloque = tamB;
    fe = new FileEntry();
    archivo = archivo;
}

void BloqueArchivo::setFileEntry(char* n, int fB, int lB, bool isF, int s)
{
    fe->setFirstBlock(fB);
    fe->setIsFolder(isF);
    fe->setLastBlock(lB);
    fe->setNombre(n);
    fe->setSize(s);
}

FileEntry * BloqueArchivo::getFileEntry()
{
    return fe;
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

Archivo * BloqueArchivo::getArchivo()
{
    return archivo;
}

char * BloqueArchivo::getNombre()
{
    return nombre;
}

int BloqueArchivo::getNumBloque()
{
    return numBloque;
}

void BloqueArchivo::setNombre(char * nombre)
{
    this->nombre = nombre;
}

char * BloqueArchivo::leer()
{
    char * nombre = {"DiscoVirtual.txt"};
    Archivo * arch = new Archivo(nombre,256*4096);
    char * a = arch->leer(getNumBloque()*4096,fe->getSize());
    for(int x =0; x<strlen(a)+1;x++)
        cout<<a[x];
    cout<<""<<endl;
    return a;
}

int BloqueArchivo::getTamanoBloque()
{
    return tamanoBloque;
}

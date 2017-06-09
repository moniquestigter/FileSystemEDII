#include "bloquefolder.h"

BloqueFolder::BloqueFolder(char * nombre, int numB,int tamB,Archivo * archivo)
{
    this->nombre = nombre;
    this->numBloque = numB;
    this->tamanoBloque = tamB;
    siguiente = NULL;
    anterior = NULL;
    archivo = archivo;
    fe = new FileEntry();
    cantArchivos = 0;
}

void BloqueFolder::setFileEntry(char* n, int fB, int lB, bool isF, int s)
{
    fe->setFirstBlock(fB);
    fe->setIsFolder(isF);
    fe->setLastBlock(lB);
    fe->setNombre(n);
    fe->setSize(s);
}

void BloqueFolder::setNombre(char * n)
{
    nombre = n;
}


Archivo * BloqueFolder::getArchivo()
{
    return archivo;
}

FileEntry * BloqueFolder::getFileEntry()
{
    return fe;
}

BloqueFolder * BloqueFolder::getSiguiente()
{
    return siguiente;
}

BloqueFolder * BloqueFolder::getAnterior()
{
    return anterior;
}

void BloqueFolder::setSiguiente(BloqueFolder * bf)
{
    siguiente = bf;
}

void BloqueFolder::setAnterior(BloqueFolder * bf)
{
    anterior = bf;
}

void BloqueFolder::setTamanoBloque(int tB)
{
    tamanoBloque += tB;
    fe->setSize(tamanoBloque);
}

void BloqueFolder::agregarFileEntry(FileEntry * fe)
{
    listaEntries.push_back(fe);
}


vector<FileEntry*> BloqueFolder::getListaEntries()
{
    return listaEntries;
}

void BloqueFolder::cargar()
{

}

void BloqueFolder::initFromChar(char * d)
{
    int pos = 0;
    memcpy(&nombre, &d[pos], 30);
    pos+=30;
    memcpy(&numBloque, &d[pos], 4);
    pos+=4;
    memcpy(&tamanoBloque, &d[pos], 4);
    pos+=4;
}
void BloqueFolder::setCantArchivos(BloqueFolder * actual)
{
    char * nombre = {"DiscoVirtual.txt"};
    Archivo * arch = new Archivo(nombre,256*4096);
    cantArchivos++;
    char * cant = new char[4];
    memcpy(&cant[0], &cantArchivos, 4);
    arch->escribir(cant,4096*actual->getFileEntry()->getFirstBLock(),4);
}

void BloqueFolder::setCant(BloqueFolder * actual){
    char * nombre = {"DiscoVirtual.txt"};
    Archivo * arch = new Archivo(nombre,256*4096);
    int cantidad = 0;
    char * cant = new char[4];
    memcpy(&cant[0], &cantidad, 4);
    arch->escribir(cant,4096*actual->getFileEntry()->getFirstBLock(),4);
}

char * BloqueFolder::getNombre()
{
    return nombre;
}

int BloqueFolder::getNumBloque()
{
    return numBloque;
}

int BloqueFolder::getTamanoBloque()
{
    return tamanoBloque;
}


void BloqueFolder::imprimirNombre()
{
    char * n = nombre;
    for(int x = 0;x<strlen(n);x++)
        cout<<n[x];
    cout<<""<<endl;

}

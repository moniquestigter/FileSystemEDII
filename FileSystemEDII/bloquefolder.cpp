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
    item = NULL;
}

void BloqueFolder::setFileEntry(char* n, int fB, int lB, bool isF, int s)
{
    fe->setTodoFileEntry(n,fB,lB,isF,s);

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
    cantArchivos+=1;
    char * nombre = {"DiscoVirtual.txt"};
    Archivo * arch = new Archivo(nombre,256*4096);
    char * cant = new char[4];
    memcpy(&cant[0], &cantArchivos, 4);
    arch->abrir();
    arch->escribir(cant,4096*actual->fe->getFirstBLock(),4);
}




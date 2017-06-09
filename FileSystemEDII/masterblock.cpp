#include "masterblock.h"

MasterBlock::MasterBlock(Archivo * archivo,const int tam, int cantB, int first,int sigDisp){
    this->archivo = archivo;
    tamanoBloque = tam;
    cantBloques = cantB;
    primero = first;
    sigDisponible = sigDisp;
}

void MasterBlock::cargar(){

}

void MasterBlock::guardar()
{
    char * data = new char[tamanoBloque];
    int pos = 0;
    memcpy(&data[pos], &tamanoBloque, 4);
    pos+=4;
    memcpy(&data[pos], &cantBloques, 4);
    pos+=4;
    memcpy(&data[pos], &primero, 4);
    pos+=4;
    memcpy(&data[pos], &sigDisponible, 4);
    pos+=4;
    archivo->escribir(data,0,16);

}

MasterBlock * MasterBlock::charToMasterBlock(char * c){
    int tamB,cantB,first,sigDis = 0;
    int pos = 0;
    memcpy(&tamB, &c[pos], 4);
    pos+=4;
    memcpy(&cantB, &c[pos], 4);
    pos+=4;
    memcpy(&first, &c[pos], 4);
    pos+=4;
    memcpy(&sigDis, &c[pos], 4);
    pos+=4;
    return new MasterBlock(archivo,tamB,cantB,first,sigDis);
}

char * MasterBlock::masterBlockToChar(){
    char * data = new char[tamanoBloque];
    int pos = 0;
    memcpy(&data[pos], &tamanoBloque, 4);
    pos+=4;
    memcpy(&data[pos], &cantBloques, 4);
    pos+=4;
    memcpy(&data[pos], &primero, 4);
    pos+=4;
    memcpy(&data[pos], &sigDisponible, 4);
    pos+=4;
    return data;
}

void MasterBlock::initFromChar(char * d){
    int pos = 0;
    memcpy(&this->tamanoBloque, &d[pos], 4);
    pos+=4;
    memcpy(&this->cantBloques, &d[pos], 4);
    pos+=4;
    memcpy(&this->primero, &d[pos], 4);
    pos+=4;
    memcpy(&this->sigDisponible, &d[pos], 4);
    pos+=4;
}

int MasterBlock::getTamanoBloque()
{
    return tamanoBloque;
}

int MasterBlock::getCantBloques()
{
    return cantBloques;
}

int MasterBlock::getPrimerBloque()
{
    return primero;
}

int MasterBlock::getSigDisponible()
{
    return sigDisponible;
}

void MasterBlock::setSiguienteDisponible(int x)
{
    sigDisponible = x;
}



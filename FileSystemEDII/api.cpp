#include "api.h"

API::API()
{
    rootSize = 0;
}

void API::formatear()
{
    FILE * file = fopen("DiscoVirtual.txt","w");
    fseek(file,4096*256,SEEK_SET);
    fputc('\0',file);
    fclose(file);
    dv->listaBloqueArchivo.clear();
    dv->listaBloqueFolder.clear();
    crearDiscoVirtual();
}

int API::initFromChar(BloqueFolder * actual){
    char * nombre = {"DiscoVirtual.txt"};
    Archivo * arch = new Archivo(nombre,256*4096);

    int pos1 = actual->fe->getFirstBLock()*4096;
    int lon = (actual->fe->getLastBlock() - actual->fe->getFirstBLock()+1)*4096;
    char * data = arch->leer(pos1,lon);


    int pos = 0;
    int cant;
    memcpy(&cant, &(data[pos]), 4);
    cant++;
    pos += 4;

    for(int x = 0;x<cant;x++){

        char * nombre2 = new char[35];
        memcpy(nombre2, &(data[pos]), 35);
        pos += 35;

        int firstBlock;
        memcpy(&firstBlock, &(data[pos]), 4);
        pos += 4;

        int lastBlock;
        memcpy(&lastBlock, &(data[pos]), 4);
        pos += 4;

        bool esFolder;
        memcpy(&esFolder, &(data[pos]), 1);
        pos += 1;

        int size;
        memcpy(&size, &(data[pos]), 4);
        pos += 4;

        if(esFolder == true)
        {
            BloqueFolder * bf = crearFolder(nombre2,actual);
            //return initFromChar(bf);
        }
        else
        {
            char * d = arch->leer(firstBlock*4096,size);
            crearArchivo(nombre2,actual,d);
        }
    }
    return cant;
}

char * API::leerArchivo(char * nombre,BloqueFolder * actual)
{
    char * contenido = {""};
    for(int x = 0;x < actual->listaBloqueArchivo.size();x++)
    {
        char * n = actual->listaBloqueArchivo.at(x)->nombre;

        if(strcmp(n,nombre)==0)
        {
            contenido = actual->listaBloqueArchivo.at(x)->leer();
            return contenido;
        }
    }
    return contenido;
}

BloqueFolder * API::abrirFolder(char * nombre,BloqueFolder * actual)
{
    for(int x = 0;x < actual->listaBloqueFolder.size();x++)
    {
        char * n = actual->listaBloqueFolder.at(x)->nombre;

        if(strcmp(n,nombre)==0)
        {
            dv->setFolderActual(actual->listaBloqueFolder.at(x));
            return actual->listaBloqueFolder.at(x);
        }
    }
    return NULL;
}

void API::crearDiscoVirtual()
{
    char * c = {"DiscoVirtual.txt"};
    Archivo * archivo = new Archivo(c,1048576);
    dv = new DiscoVirtual(archivo,1048576,4096);
    dv->formatear();
    addRoot();
    dv->setFolderActual(root);

}

void API::addRoot(){
    int pos = 1;
    char * ra = {"Raiz"};
    BloqueFolder * bloque = new BloqueFolder(ra,1,0,dv->getArchivo());
    dv->getMasterBlock()->setSiguienteDisponible(pos+3);
    bloque->setFileEntry(ra,1,3,true,0);
    this->root = bloque;
    root->listaBloqueArchivo.clear();
    root->listaBloqueFolder.clear();

}

BloqueArchivo * API::crearArchivo(char * nombre, BloqueFolder * actual, char * contenido)
{
    Archivo * archivo = dv->getArchivo();
    archivo->abrir();
    int pos = dv->getMasterBlock()->getSigDisponible();
    BloqueArchivo * ba = new BloqueArchivo(nombre,pos,strlen(contenido),dv->getArchivo());
    actual->fe->setSize(strlen(contenido));
    int size = strlen(contenido)/4096;

    if(size<1)
    {
        dv->getMasterBlock()->setSiguienteDisponible(pos+1);
        archivo->escribir(contenido,pos*4096,strlen(contenido));
        ba->setFileEntry(nombre,pos,pos,false,strlen(contenido));
        actual->agregarFileEntry(ba->fe);

    }

    else if(size>=1)
    {
        if(strlen(contenido)%4096>0)
            size++;
        dv->getMasterBlock()->setSiguienteDisponible(pos+size);
        archivo->escribir(contenido,pos*4096,strlen(contenido));
        ba->setFileEntry(nombre,pos,pos+size,false,strlen(contenido));
        actual->agregarFileEntry(ba->fe);
    }
    actual->setCantArchivos(actual);
    escribirEntries(ba->fe,actual);
    actual->listaBloqueArchivo.push_back(ba);
    dv->listaBloqueArchivo.push_back(ba);
    return ba;
}

BloqueFolder * API::crearFolder(char * nombre,BloqueFolder * actual)
{
    Archivo * archivo = dv->getArchivo();
    int pos = dv->getMasterBlock()->getSigDisponible();

    BloqueFolder * bf = new BloqueFolder(nombre,pos,0,archivo);
    dv->getMasterBlock()->setSiguienteDisponible(pos+1);

    bf->setFileEntry(nombre,pos,pos,true,0);
    actual->agregarFileEntry(bf->fe);
    escribirEntries(bf->fe,actual);
    actual->listaBloqueFolder.push_back(bf);
    dv->listaBloqueFolder.push_back(bf);
    actual->setCantArchivos(actual);
    return bf;
}

void API::escribirEntries(FileEntry *fe,BloqueFolder * actual)
{

    char * data = new char[48];
    int firstBlock = fe->getFirstBLock();
    int lastBlock = fe->getLastBlock();
    int size = fe->getSize();
    int esFolder = fe->getEsFolder();
    int pos = 0;

    memcpy(&data[pos], fe->getNombre(), 32);
    pos+=35;
    memcpy(&data[pos], &firstBlock,4);
    pos+=4;
    memcpy(&data[pos], &lastBlock, 4);
    pos+=4;
    memcpy(&data[pos], &esFolder, sizeof(bool));
    pos+=1;
    memcpy(&data[pos], &size, 4);
    pos+=4;

    dv->getArchivo()->abrir();
    int x = actual->listaEntries.size();
    dv->getArchivo()->escribir(data,4096*actual->fe->getFirstBLock()+x*48-48+4,48);
}




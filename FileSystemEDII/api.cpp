#include "api.h"

#include <qmessagebox.h>


API::API()
{
    cantIdx = 0;

}

//Funciones para cargar too desde el .txt
BloqueArchivo *  API::initArchivoFromChar(char * nombre, BloqueFolder * actual,int nB,int tB,int lB)
{
    actual->setCantArchivos(actual);
    Archivo * archivo = dv->getArchivo();
    archivo->abrir();
    BloqueArchivo * ba = new BloqueArchivo(nombre,nB,tB,dv->getArchivo());
    ba->setFileEntry(nombre,nB,lB,false,tB);
    actual->agregarFileEntry(ba->fe);
    actual->listaBloqueArchivo.push_back(ba);
    dv->listaBloqueArchivo.push_back(ba);
    nombres.push_back(nombre);
    return ba;
}

BloqueFolder * API::initFolderFromChar(char * nombre, BloqueFolder * actual,int nB,int tB,int lB)
{
    actual->setCantArchivos(actual);
    Archivo * archivo = dv->getArchivo();
    BloqueFolder * bf = new BloqueFolder(nombre,nB,tB,archivo);
    bf->setFileEntry(nombre,nB,lB,true,tB);
    actual->agregarFileEntry(bf->fe);
    actual->listaBloqueFolder.push_back(bf);
    dv->listaBloqueFolder.push_back(bf);
    nombres.push_back(nombre);
    return bf;
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
            BloqueFolder * bf = initFolderFromChar(nombre2,actual,firstBlock,size,lastBlock);

            if(lastBlock > dv->mb->getSigDisponible())
                dv->mb->setSiguienteDisponible(lastBlock+1);

            initFromChar(bf);
        }
        else if(esFolder == false)
        {
            initArchivoFromChar(nombre2,actual,firstBlock,size,lastBlock);
        }
    }
    return 0;
}

//Crear Archivo o Folder

void API::addRoot(){
    char * ra = {"Raiz"};
    BloqueFolder * bloque = new BloqueFolder(ra,1,0,dv->getArchivo());
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
        ba->setFileEntry(nombre,pos,pos,false,strlen(contenido));
    }

    else if(size>=1)
    {
        if(strlen(contenido)%4096>0)
            size++;
        dv->getMasterBlock()->setSiguienteDisponible(pos+size);
        ba->setFileEntry(nombre,pos,pos+size,false,strlen(contenido));
    }

    actual->setCantArchivos(actual);
    archivo->escribir(contenido,pos*4096,strlen(contenido));
    actual->agregarFileEntry(ba->fe);

    dv->getHashTable()->agregarIdxEntry(nombre, ba->numBloque,dv->getHashTable()->ie->getNumEntry(),strlen(contenido));
    IdxEntry * idx = dv->getHashTable()->hash(nombre);
    setCantIdxArchivos();
    escribirIdxEntries(idx);

    escribirEntries(ba->fe,actual);
    actual->listaBloqueArchivo.push_back(ba);
    dv->listaBloqueArchivo.push_back(ba);
    nombres.push_back(nombre);
    return ba;
}

BloqueFolder * API::crearFolder(char * nombre,BloqueFolder * actual)
{
    actual->setCantArchivos(actual);
    Archivo * archivo = dv->getArchivo();
    int pos = dv->getMasterBlock()->getSigDisponible();

    BloqueFolder * bf = new BloqueFolder(nombre,pos,0,archivo);
    dv->getMasterBlock()->setSiguienteDisponible(pos+1);

    bf->setFileEntry(nombre,pos,pos,true,0);
    actual->agregarFileEntry(bf->fe);
    escribirEntries(bf->fe,actual);

    dv->getHashTable()->agregarIdxEntry(nombre, bf->numBloque,dv->getHashTable()->ie->getNumEntry(),0);
    IdxEntry * idx = dv->getHashTable()->hash(nombre);
    setCantIdxArchivos();
    escribirIdxEntries(idx);

    actual->listaBloqueFolder.push_back(bf);
    dv->listaBloqueFolder.push_back(bf);

    nombres.push_back(nombre);
    return bf;
}

string API::duplicadosAux(string nombre, int cant,int tamanoPalabra,int tipo)
{
    string a = nombre;

    for(int x = 0;x<nombres.size();x++)
    {
        char * charTemp = nombres.at(x);
        std::string n(charTemp);
        if(toLowerCase(n) == toLowerCase(nombre))
        {
            string z = to_string(cant);
            if(nombre.size() > tamanoPalabra)
                a = a.substr(0,nombre.size()-2);
            return duplicadosAux(a+"_"+z,cant+1,tamanoPalabra,tipo);
        }
    }
    return nombre;
}

string API::Duplicados(string nombre,int tipo)
{
    return duplicadosAux(nombre,1,nombre.size(),tipo);
}

string API::toLowerCase(string palabra)
{
    locale loc;
    string palabraNueva;
    for (string::size_type i=0; i<palabra.length(); ++i)
        palabraNueva = palabraNueva+tolower(palabra[i],loc);
    return palabraNueva;
}


//Manipular Archivos
char * API::leerArchivo(char * nombre,BloqueFolder * actual)
{
    char * nombre2 = {"DiscoVirtual.txt"};
    cout<<"1"<<endl;
    Archivo * arch = new Archivo(nombre2,256*4096);
    cout<<"2"<<endl;
    char * contenido = {""};
    cout<<"3"<<endl;
    IdxEntry * idx = dv->getHashTable()->hash(nombre);
    cout<<"4"<<endl;
    int tamano = idx->getSizeBloque();
    cout<<"5"<<endl;
    int numBloque = idx->getNumBloque();
    cout<<"6"<<endl;
    contenido = arch->leer(numBloque*4096,256);
    cout<<"7"<<endl;
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


//Crear Disco
void API::crearDiscoVirtual()
{
    char * c = {"DiscoVirtual.txt"};
    Archivo * archivo = new Archivo(c,1048576);
    dv = new DiscoVirtual(archivo,1048576,4096);
    dv->cargar();
    addRoot();
    dv->setFolderActual(root);
    dv->mb->setSiguienteDisponible(7);

}

void API::formatear()
{
    FILE * file = fopen("DiscoVirtual.txt","w");
    fseek(file,4096*256,SEEK_SET);
    fputc('\0',file);
    fclose(file);
    dv->listaBloqueArchivo.clear();
    dv->listaBloqueFolder.clear();
    nombres.clear();
    dv->formatear();
    addRoot();
    dv->setFolderActual(root);
}


//Entries y idxEntries
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
    dv->getArchivo()->escribir(data,(4096*actual->fe->getFirstBLock())+(x*48)-48+4,48);
}

void API::setCantIdxArchivos()
{
    cantIdx++;
    char * nombre = {"DiscoVirtual.txt"};
    Archivo * arch = new Archivo(nombre,256*4096);
    char * cant = new char[4];
    memcpy(&cant[0], &cantIdx , 4);
    arch->escribir(cant,(4096*4),4);
}

void API::escribirIdxEntries(IdxEntry * ie){
    char * data = new char[47];
    int numBlock = ie->getNumEntry();
    int numEnt = ie->getNumEntry();
    int size = ie->getSizeBloque();

    int pos = 0;
    memcpy(&data[pos], ie->getNombre(), 35);
    pos+=35;
    memcpy(&data[pos], &numBlock, 4);
    pos+=4;
    memcpy(&data[pos], &numEnt, 4);
    pos+=4;
    memcpy(&data[pos], &size, 4);
    pos+=4;


    dv->getArchivo()->abrir();
    int x = dv->getHashTable()->hashTable.size();
    dv->getArchivo()->escribir(data,(4096*4)+(x*47)+4,47);
}

void API::initIDX(){
    char * nombre = {"DiscoVirtual.txt"};
    Archivo * arch = new Archivo(nombre,256*4096);

    char * data = arch->leer(4096*4,4096*3);

    int pos = 0;
    int cant;
    memcpy(&cant, &(data[pos]), 4);
    pos += 4;

    for(int x = 0;x<cant;x++){

        char * nombre = new char[35];
        memcpy(nombre, &(data[pos]), 35);
        pos += 35;

        int bloque;
        memcpy(&bloque, &(data[pos]), 4);
        pos += 4;

        int numE;
        memcpy(&numE, &(data[pos]), 4);
        pos += 4;

        int size;
        memcpy(&size, &(data[pos]), 4);
        pos += 4;

        dv->getHashTable()->agregarIdxEntry(nombre, bloque,numE,size);

    }
    cantIdx = cant;
}



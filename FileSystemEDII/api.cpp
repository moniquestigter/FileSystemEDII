#include "api.h"

API::API()
{
    rootSize = 0;
}

int API::initFromChar(BloqueFolder * actual){
    char * nombre = {"DiscoVirtual.txt"};
    Archivo * arch = new Archivo(nombre,256*4096);


    int pos1 = actual->getFileEntry()->getFirstBLock()*4096;
    int lon = ((actual->getFileEntry()->getLastBlock()-actual->getFileEntry()->getFirstBLock())+1)*4096;
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
            BloqueFolder * bf = crearFolder(nombre2,actual);
            return initFromChar(bf);
        }
        else
        {
            char * d = arch->leer(firstBlock*4096,size);
            crearArchivo(nombre2,actual,d);
        }
    }
    return 0;
}

int API::leerArchivo(char * nombre,BloqueFolder * bf)
{
    for(int x = 0;x<dv->listaBloqueArchivo.size();x++)
    {
        char * n = dv->listaBloqueArchivo.at(x)->getNombre();

        if(strcmp(n, nombre)==0){
            cout<<"Contenido del Archivo: ";
            dv->listaBloqueArchivo.at(x)->leer();
            return 0;
        }

    }
    cout<<"Archivo no Existe"<<endl;
    return -1;
}

int API::abrirFolder(char * nombre)
{
    for(int x = 0;x<dv->listaBloqueFolder.size();x++)
    {
        char * n = dv->listaBloqueFolder.at(x)->getNombre();

        if(strcmp(n,nombre)==0)
        {
            dv->setFolderActual(dv->listaBloqueFolder.at(x));
            cout<<"Folder Actual: ";
            dv->listaBloqueFolder.at(x)->imprimirNombre();
            return 0;
        }
    }
    cout<<"No Existe"<<endl;
    return -1;
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
    bloque->setNombre(ra);
    dv->listaBloqueFolder.push_back(bloque);
    this->root = bloque;
}

BloqueArchivo * API::crearArchivo(char * nombre, BloqueFolder * actual, char * contenido)
{
    Archivo * archivo = dv->getArchivo();
    archivo->abrir();
    int pos = dv->getMasterBlock()->getSigDisponible();
    BloqueArchivo * ba = new BloqueArchivo(nombre,pos,strlen(contenido),dv->getArchivo());
    actual->getFileEntry()->setSize(strlen(contenido));
    int size = strlen(contenido)/4096;

    if(size<1)
    {
        dv->getMasterBlock()->setSiguienteDisponible(pos+1);
        archivo->escribir(contenido,pos*4096,strlen(contenido));
        ba->setFileEntry(nombre,pos,pos,false,strlen(contenido));
        actual->agregarFileEntry(ba->getFileEntry());

    }

    else if(size>=1)
    {
        if(strlen(contenido)%4096>0)
            size++;
        dv->getMasterBlock()->setSiguienteDisponible(pos+size);
        archivo->escribir(contenido,pos*4096,strlen(contenido));
        ba->setFileEntry(nombre,pos,pos+size,false,strlen(contenido));
        actual->agregarFileEntry(ba->getFileEntry());
    }
    actual->setCantArchivos(actual);
    ba->setNombre(nombre);
    escribirEntries(ba->getFileEntry(),actual);
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
    actual->agregarFileEntry(bf->getFileEntry());
    escribirEntries(bf->getFileEntry(),actual);
    dv->listaBloqueFolder.push_back(bf);
    bf->setNombre(nombre);
    actual->setCantArchivos(actual);
    bf->setCant(bf);
    return bf;
}

void API::guardarEntries()
{
    vector<BloqueFolder*> lista = dv->listaBloqueFolder;
    for(int x = 0;x<lista.size();x++)
    {
        vector<FileEntry*> listaE = lista[x]->getListaEntries();
        for(int x = 0;x<listaE.size();x++)
            escribirEntries(listaE[x],lista[x]);
    }

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
    int x = actual->getListaEntries().size();
    dv->getArchivo()->escribir(data,4096*actual->getFileEntry()->getFirstBLock()+x*48-48+4,48);
}

void API::dir()
{
    vector<BloqueFolder*> lista = dv->listaBloqueFolder;
    for(int x = 0; x < lista.size();x++)
    {
        vector<FileEntry*> listaE = lista[x]->getListaEntries();
        cout<<"Folder: ";
        lista[x]->imprimirNombre();
        cout<<""<<endl;
        for(int y = 0; y < listaE.size();y++)
        {
            listaE[y]->imprimirEntry();
            cout<<""<<endl;
        }
        cout<<"-------------------------"<<endl;
        cout<<""<<endl;
    }
}

void API::dirFolderActual()
{
    cout<<""<<endl;
    cout<<"-------------------------"<<endl;
    cout<<"Folder Actual: ";
    dv->getFolderActual()->imprimirNombre();
    cout<<"Contenido del Folder: ";
    vector<FileEntry*> lista = dv->getFolderActual()->getListaEntries();
    for(int y = 0; y < lista.size();y++)
    {
        lista[y]->imprimirEntry();
        cout<<""<<endl;
    }
    cout<<"-------------------------"<<endl;
}

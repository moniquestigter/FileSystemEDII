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

    for(int a = 0; a<mb->getCantBloques(); a++)
        asignarSiguienteBloque(a);

    mb->setSiguienteDisponible(1);
    char * mB = mb->masterBlockToChar();
    archivo->escribir(mB,1,strlen(mB));

}

BloqueFolder * DiscoVirtual::asignarSiguienteBloque(int numeroBloque)
{
    return NULL;
}

void DiscoVirtual::cargar(){
    archivo->abrir();
    mb = new MasterBlock(archivo,tamBloque,(tamArchivo/tamBloque),0,1);
    this->mb->cargar();
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


QList<FileEntry*> DiscoVirtual::listarArchivosEnRaiz()
{
    QList<FileEntry*> lista;
    if(mb->getSigDisponible() == 1)
        return lista;

    int numeroDeBloque = mb->getPrimerBloque();

    BloqueFolder * bf = new BloqueFolder("root",numeroDeBloque,0,getArchivo());
    //bf->cargar();
    lista = bf->listaEntries;
    return lista;
}

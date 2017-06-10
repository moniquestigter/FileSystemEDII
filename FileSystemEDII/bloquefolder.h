#ifndef BLOQUEFOLDER_H
#define BLOQUEFOLDER_H
#include "Archivo.h"
<<<<<<< HEAD
=======
#include <vector>
#include <QList>
#include "MasterBlock.h"
>>>>>>> origin/master
#include "FileEntry.h"

#include <vector>

class BloqueFolder
{
public:
    BloqueFolder(char * nombre, int numB, int tamB,Archivo * archivo);

    void imprimirNombre();
    void cargar();
    void initFromChar(char * d);

    Archivo * archivo;

    FileEntry *fe;
    vector<FileEntry *> listaEntries;
    void setFileEntry(char* n, int fB, int lB, bool isF, int s);
<<<<<<< HEAD
=======
    QList<FileEntry*> getListaEntries();
>>>>>>> origin/master
    void agregarFileEntry(FileEntry * fe);
    void escribirEntries(int pos);
    void setTamanoBloque(int tB);

<<<<<<< HEAD
    char * nombre;
=======
private:
    void initFromChar(char * d);
    Archivo * archivo;
    QList<FileEntry*> listaEntries;
>>>>>>> origin/master
    int tamanoBloque;
    int numBloque;

    BloqueFolder * siguiente;
    BloqueFolder * anterior;


    int cantArchivos;
    void setCantArchivos(BloqueFolder * actual);

private:

};
#endif // BLOQUEFOLDER_H


#ifndef FILEENTRY_H
#define FILEENTRY_H


#include <stdio.h>
#include <iostream>
#include <string.h>

using namespace std;

class FileEntry
{
public:
    FileEntry();

    char * getNombre();
    int getFirstBLock();
    int getLastBlock();
    int getCode();
    bool getEsFolder();
    size_t getSize();

    void setFirstBlock(int fB);
    void setLastBlock(int lB);
    void setNombre(char * n);
    void setSize(size_t s);
    void setIsFolder(bool iF);
    void setTodoFileEntry(char * nom, int first,int last, bool iF, size_t size);
    void setIdxInfo(char * nom,)

    void imprimirEntry();

    char* nombre;
    int firstBlock;
    int lastBlock;
    bool isFolder;
    int size;
    int code;
    FileEntry * sig;

};


#endif // FILEENTRY_H

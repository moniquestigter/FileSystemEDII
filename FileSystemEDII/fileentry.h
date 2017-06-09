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
    bool getEsFolder();
    size_t getSize();

    void setFirstBlock(int fB);
    void setLastBlock(int lB);
    void setNombre(char * n);
    void setSize(size_t s);
    void setIsFolder(bool iF);

    void imprimirEntry();

private:
    char* nombre;
    int firstBlock;
    int lastBlock;
    bool isFolder;
    int size;

};


#endif // FILEENTRY_H

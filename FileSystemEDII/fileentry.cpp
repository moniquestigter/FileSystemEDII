#include "fileentry.h"

FileEntry::FileEntry() {
    nombre = {"a"};
    firstBlock = 0;
    lastBlock = 0;
    isFolder = false;
    size = 0;
}
 void FileEntry::setTodoFileEntry(char * nom, int first,int last, bool iF, size_t s){
     nombre = nom;
     firstBlock = first;
     lastBlock = last;
     isFolder = iF;
     size = s;
}

char * FileEntry::getNombre()
{
    return nombre;
}

void FileEntry::setFirstBlock(int fB)
{
    firstBlock = fB;
}

void FileEntry::setLastBlock(int lB)
{
    lastBlock = lB;
}

void FileEntry::setNombre(char * n)
{
    nombre = n;
}

void FileEntry::setSize(size_t s)
{
    size += s;
}

void FileEntry::setIsFolder(bool iF)
{
    isFolder = iF;
}

int FileEntry::getFirstBLock()
{
    return firstBlock;
}

int FileEntry::getLastBlock()
{
    return lastBlock;
}

bool FileEntry::getEsFolder()
{
    return isFolder;
}

size_t FileEntry::getSize()
{
    return size;
}



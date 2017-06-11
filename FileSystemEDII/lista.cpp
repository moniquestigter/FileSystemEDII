#include "lista.h"


Lista::Lista()
{
    inicial == NULL;
    cant = 0;
}

void Lista::agregarALista(FileEntry * obj){
    if(inicial == NULL){
        inicial = obj;
        cant++;
    }
    else{
        FileEntry * temp = inicial;
        while(temp != NULL){
            temp = temp->sig;
        }
        temp = obj;
        cant++;
    }
}

int Lista::size(){
    return cant;
}

int Lista::buscar(char * nombre){
    FileEntry * temp = inicial;
    for(int a = 0; a<cant; a++){
        if(temp->getNombre() != nombre){
            temp = temp->sig;
        }
        return a;
    }
}


FileEntry * Lista::at(int pos){
    FileEntry * temp = inicial;
    for(int a = 0; a<pos; a++){
        temp = temp->sig;
    }
    return temp;
}


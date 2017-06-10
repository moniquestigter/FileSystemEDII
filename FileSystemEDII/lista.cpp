#include "lista.h"

Lista::Lista()
{
    inicial == nullptr;
    sig == nullptr;
    cant = 0;
}

void Lista::agregarALista(T * obj){
    if(inicial == nullptr){
        inicial = obj;
        cant++;
    }
    else{
        temp = inicial->sig;
        while(temp != nullptr){
            temp = temp->sig;
        }
        temp = obj;
        cant++;
    }
}

int Lista::getCant(){
    return cant;
}

int Lista::buscar(T * nombre){
    temp = inicial;
    for(int a = 0; a<cant; a++){
        if(temp->nom != nombre){
            temp = temp->sig;
        }
        return a;
    }
}


#ifndef LISTA_H
#define LISTA_H

template<class T>
class Lista
{
public:
    Lista();

    void agregarALista(T * obj);
    int buscar(T * nombre);
    int getCant();
    T * inicial;
    T * sig;
    T * ant;

    int cant;

};

#endif // LISTA_H

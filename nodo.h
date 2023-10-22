//
// Created by delfi on 22/10/2023.
//

#ifndef PROYECTO_PROGRAMACION_III_NODO_H
#define PROYECTO_PROGRAMACION_III_NODO_H
template <class T> class Nodo { //creamos la clase nodo
private:
    T dato;
    Nodo<T> *siguiente;
public:
    T getDato(){
        return dato;
    }

    void setDato(T d){
        dato=d;
    }
    Nodo<T> *getSiguiente(){
        return siguiente;
    }

    void setSiguiente (Nodo<T> *s) {
        this -> siguiente=s;  //puntero que seniala a la misma clase en si
    }

};
#endif //PROYECTO_PROGRAMACION_III_NODO_H

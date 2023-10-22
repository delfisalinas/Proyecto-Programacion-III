//
// Created by delfi on 22/10/2023.
//

#ifndef PROYECTO_PROGRAMACION_III_HASHENTRYY_H
#define PROYECTO_PROGRAMACION_III_HASHENTRYY_H
template <class K, class T>
class HashEntry
{
private:
    K clave;
    T valor;
public:
    HashEntry(K c, T v){
        clave = c;
        valor = v;
    }

    K getClave(){
        return clave;
    }
    void setClave(K c){
        clave = c;
    }

    T getValor(){
        return valor;
    }
    void setValor(T v){
        valor = v;
    }
};
#endif //PROYECTO_PROGRAMACION_III_HASHENTRYY_H

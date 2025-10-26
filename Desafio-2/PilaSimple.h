#ifndef PILA_SIMPLE_H
#define PILA_SIMPLE_H

#include "ArregloDinamico.h"

template<typename T>
class PilaSimple {
private:
    ArregloDinamico<T> datos;
    int topeMax;
public:
    PilaSimple(int cap=4): topeMax(cap) {}
    bool vacia() const { return datos.tam()==0; }
    int tam() const { return datos.tam(); }
    void push(const T& v){
        if(datos.tam() >= topeMax){
            ArregloDinamico<T> temp;
            for(int i=1;i<datos.tam();++i) temp.agregar(datos[i]);
            datos = temp;
        }
        datos.agregar(v);
    }
    bool pop(T& out){
        int n = datos.tam();
        if(n==0) return false;
        out = datos[n-1];
        datos.eliminarEn(n-1);
        return true;
    }
};

#endif // PILA_SIMPLE_H

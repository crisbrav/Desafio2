// include/ArregloDinamico.h
#ifndef ARREGLO_DINAMICO_H
#define ARREGLO_DINAMICO_H

template<typename T>
class ArregloDinamico {
private:
    T* datos;
    int cantidad;
    int capacidad;
    void asegurar(int nuevaCap) {
        if (nuevaCap <= capacidad) return;
        int cap = (capacidad == 0 ? 4 : capacidad);
        while (cap < nuevaCap) cap <<= 1;
        T* nuevo = new T[cap];
        for (int i = 0; i < cantidad; ++i) nuevo[i] = datos[i];
        delete[] datos;
        datos = nuevo;
        capacidad = cap;
    }
public:
    ArregloDinamico(): datos(nullptr), cantidad(0), capacidad(0) {}
    ArregloDinamico(const ArregloDinamico& o): datos(nullptr), cantidad(0), capacidad(0) {
        asegurar(o.cantidad);
        cantidad = o.cantidad;
        for (int i = 0; i < cantidad; ++i) datos[i] = o.datos[i];
    }
    ArregloDinamico& operator=(const ArregloDinamico& o) {
        if (this == &o) return *this;
        delete[] datos;
        datos = nullptr; cantidad = 0; capacidad = 0;
        asegurar(o.cantidad);
        cantidad = o.cantidad;
        for (int i = 0; i < cantidad; ++i) datos[i] = o.datos[i];
        return *this;
    }
    ~ArregloDinamico(){ delete[] datos; }
    int tam() const { return cantidad; }
    bool vacio() const { return cantidad == 0; }
    T& operator[](int i){ return datos[i]; }
    const T& operator[](int i) const { return datos[i]; }
    void agregar(const T& v){ asegurar(cantidad+1); datos[cantidad++] = v; }
    bool eliminarEn(int idx){
        if (idx < 0 || idx >= cantidad) return false;
        datos[idx] = datos[cantidad-1];
        --cantidad;
        return true;
    }
    int buscarPrimero(const T& v) const {
        for (int i = 0; i < cantidad; ++i) if (datos[i] == v) return i;
        return -1;
    }
};

#endif // ARREGLO_DINAMICO_H

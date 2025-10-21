// ============================================================================
// UDEATUNES - SISTEMA DE STREAMING MUSICAL
// Archivo: Album.cpp
// Descripción: Implementación de la clase Album
// ============================================================================

#include "Album.h"
#include <cstring>

using namespace std;

// Constructor por defecto
Album::Album()
    : identificador(0), duracionTotal(0), numGeneros(0),
    puntuacion(0.0f), canciones(nullptr),
    numCanciones(0), capacidadCanciones(10) {
    nombre[0] = '\0';
    selloDisquero[0] = '\0';
    rutaPortada[0] = '\0';
    canciones = new Cancion*[capacidadCanciones];
}

// Constructor parametrizado
Album::Album(int id, const char* nom)
    : identificador(id), duracionTotal(0),
    numGeneros(0), puntuacion(0.0f),
    numCanciones(0), capacidadCanciones(10) {
    strncpy(nombre, nom, 199);
    nombre[199] = '\0';
    selloDisquero[0] = '\0';
    rutaPortada[0] = '\0';
    canciones = new Cancion*[capacidadCanciones];
}

// Destructor
Album::~Album() {
    for (int i = 0; i < numCanciones; i++) {
        delete canciones[i];
    }
    delete[] canciones;
}

// Establecer ruta de portada del álbum
void Album::setRutaPortada(const char* ruta) {
    strncpy(rutaPortada, ruta, 499);
    rutaPortada[499] = '\0';
}

// Establecer sello disquero
void Album::setSelloDisquero(const char* sello) {
    strncpy(selloDisquero, sello, 199);
    selloDisquero[199] = '\0';
}

// Establecer fecha de lanzamiento
void Album::setLanzamiento(const Fecha& f) {
    lanzamiento = f;
}

// Establecer puntuación
void Album::setPuntuacion(float punt) {
    if (punt >= 1.0f && punt <= 10.0f) {
        puntuacion = punt;
    }
}

// Agregar género musical al álbum
void Album::agregarGenero(GeneroMusical genero) {
    if (numGeneros < 4) {
        generos[numGeneros++] = genero;
    }
}

// Agregar canción al álbum
void Album::agregarCancion(Cancion* cancion) {
    if (numCanciones >= capacidadCanciones) {
        // Redimensionar arreglo dinámico
        capacidadCanciones *= 2;
        Cancion** nuevo = new Cancion*[capacidadCanciones];
        for (int i = 0; i < numCanciones; i++) {
            nuevo[i] = canciones[i];
        }
        delete[] canciones;
        canciones = nuevo;
    }
    canciones[numCanciones++] = cancion;
    duracionTotal += cancion->getDuracion();
}

// Obtener canción por índice
Cancion* Album::obtenerCancion(int index) const {
    if (index >= 0 && index < numCanciones)
        return canciones[index];
    return nullptr;
}

// Mostrar información del álbum
void Album::mostrarInfo() const {
    cout << "\n=== ALBUM: " << nombre << " ===";
    cout << "\nID: " << identificador;
    cout << "\nSello: " << selloDisquero;
    cout << "\nPuntuación: " << puntuacion << "/10";
    cout << "\nCanciones: " << numCanciones;
    cout << "\nDuración total: " << duracionTotal << "s";
}

// Calcular memoria consumida por el álbum
size_t Album::calcularMemoria() const {
    size_t mem = sizeof(Album);
    mem += capacidadCanciones * sizeof(Cancion*);
    for (int i = 0; i < numCanciones; i++) {
        mem += canciones[i]->calcularMemoria();
    }
    return mem;
}

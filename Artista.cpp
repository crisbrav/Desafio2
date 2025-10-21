// ============================================================================
// UDEATUNES - SISTEMA DE STREAMING MUSICAL
// Archivo: Artista.cpp
// Descripción: Implementación de la clase Artista
// ============================================================================

#include "Artista.h"
#include <cstring>

using namespace std;

// Constructor por defecto
Artista::Artista()
    : codigo(0), edad(0), seguidores(0), posicionTendencias(0),
    albumes(nullptr), numAlbumes(0), capacidadAlbumes(5) {
    nombre[0] = '\0';
    paisOrigen[0] = '\0';
    albumes = new Album*[capacidadAlbumes];
}

// Constructor parametrizado
Artista::Artista(int cod, const char* nom, int ed, const char* pais)
    : codigo(cod), edad(ed), seguidores(0), posicionTendencias(0),
    numAlbumes(0), capacidadAlbumes(5) {
    strncpy(nombre, nom, 199);
    nombre[199] = '\0';
    strncpy(paisOrigen, pais, 99);
    paisOrigen[99] = '\0';
    albumes = new Album*[capacidadAlbumes];
}

// Destructor
Artista::~Artista() {
    for (int i = 0; i < numAlbumes; i++) {
        delete albumes[i];
    }
    delete[] albumes;
}

// Establecer número de seguidores
void Artista::setSeguidores(long long seg) {
    seguidores = seg;
}

// Establecer posición en tendencias
void Artista::setPosicionTendencias(int pos) {
    posicionTendencias = pos;
}

// Agregar álbum al catálogo del artista
void Artista::agregarAlbum(Album* album) {
    if (numAlbumes >= capacidadAlbumes) {
        // Redimensionar arreglo dinámico
        capacidadAlbumes *= 2;
        Album** nuevo = new Album*[capacidadAlbumes];
        for (int i = 0; i < numAlbumes; i++) {
            nuevo[i] = albumes[i];
        }
        delete[] albumes;
        albumes = nuevo;
    }
    albumes[numAlbumes++] = album;
}

// Obtener álbum por índice
Album* Artista::obtenerAlbum(int index) const {
    if (index >= 0 && index < numAlbumes)
        return albumes[index];
    return nullptr;
}

// Buscar canción por su identificador
Cancion* Artista::buscarCancionPorId(int idCancion) const {
    for (int i = 0; i < numAlbumes; i++) {
        for (int j = 0; j < albumes[i]->getNumCanciones(); j++) {
            Cancion* c = albumes[i]->obtenerCancion(j);
            if (c && c->getIdentificador() == idCancion)
                return c;
        }
    }
    return nullptr;
}

// Mostrar información del artista
void Artista::mostrarInfo() const {
    cout << "\n=== ARTISTA: " << nombre << " ===";
    cout << "\nCódigo: " << codigo;
    cout << "\nEdad: " << edad;
    cout << "\nPaís: " << paisOrigen;
    cout << "\nSeguidores: " << seguidores;
    cout << "\nPosición tendencias: " << posicionTendencias;
    cout << "\nÁlbumes: " << numAlbumes;
}

// Calcular memoria consumida por el artista
size_t Artista::calcularMemoria() const {
    size_t mem = sizeof(Artista);
    mem += capacidadAlbumes * sizeof(Album*);
    for (int i = 0; i < numAlbumes; i++) {
        mem += albumes[i]->calcularMemoria();
    }
    return mem;
}

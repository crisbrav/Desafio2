// ============================================================================
// UDEATUNES - SISTEMA DE STREAMING MUSICAL
// Archivo: Artista.h
// Descripción: Clase que representa un artista musical
// ============================================================================

#ifndef ARTISTA_H
#define ARTISTA_H

#include "Album.h"
#include <iostream>

class Artista {
private:
    int codigo;
    char nombre[200];
    int edad;
    char paisOrigen[100];
    long long seguidores;
    int posicionTendencias;
    Album** albumes;
    int numAlbumes;
    int capacidadAlbumes;

public:
    // Constructores y destructor
    Artista();
    Artista(int cod, const char* nom, int ed, const char* pais);
    ~Artista();

    // Métodos modificadores
    void setSeguidores(long long seg);
    void setPosicionTendencias(int pos);
    void agregarAlbum(Album* album);

    // Métodos de consulta
    Album* obtenerAlbum(int index) const;
    Cancion* buscarCancionPorId(int idCancion) const;
    void mostrarInfo() const;
    int getCodigo() const { return codigo; }
    const char* getNombre() const { return nombre; }
    int getEdad() const { return edad; }
    int getNumAlbumes() const { return numAlbumes; }
    long long getSeguidores() const { return seguidores; }

    // Medición de recursos
    size_t calcularMemoria() const;
};

#endif // ARTISTA_H

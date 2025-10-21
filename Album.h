// ============================================================================
// UDEATUNES - SISTEMA DE STREAMING MUSICAL
// Archivo: Album.h
// Descripción: Clase que representa un álbum musical
// ============================================================================

#ifndef ALBUM_H
#define ALBUM_H

#include "Cancion.h"
#include "Fecha.h"
#include "Tipos.h"
#include <iostream>

class Album {
private:
    int identificador;
    char nombre[200];
    Fecha lanzamiento;
    int duracionTotal;
    GeneroMusical generos[4];
    int numGeneros;
    char selloDisquero[200];
    char rutaPortada[500];
    float puntuacion;
    Cancion** canciones;
    int numCanciones;
    int capacidadCanciones;

public:
    // Constructores y destructor
    Album();
    Album(int id, const char* nom);
    ~Album();

    // Métodos modificadores
    void setRutaPortada(const char* ruta);
    void setSelloDisquero(const char* sello);
    void setLanzamiento(const Fecha& f);
    void setPuntuacion(float punt);
    void agregarGenero(GeneroMusical genero);
    void agregarCancion(Cancion* cancion);

    // Métodos de consulta
    Cancion* obtenerCancion(int index) const;
    void mostrarInfo() const;
    int getIdentificador() const { return identificador; }
    const char* getNombre() const { return nombre; }
    const char* getRutaPortada() const { return rutaPortada; }
    int getNumCanciones() const { return numCanciones; }
    int getDuracionTotal() const { return duracionTotal; }
    float getPuntuacion() const { return puntuacion; }

    // Medición de recursos
    size_t calcularMemoria() const;
};

#endif // ALBUM_H

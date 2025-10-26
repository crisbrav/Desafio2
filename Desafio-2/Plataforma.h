#ifndef PLATAFORMA_H
#define PLATAFORMA_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <random>
#include <chrono>
#include "Metricas.h"
#include "ArregloDinamico.h"
#include "Tipos.h"
#include "Cancion.h"
#include "Album.h"
#include "Artista.h"
#include "Anuncio.h"
#include "Usuario.h"
#include "PilaSimple.h"
#include "UiReproductor.h"

class Plataforma {
private:
    ArregloDinamico<Usuario> usuarios;
    ArregloDinamico<Artista> artistas;
    ArregloDinamico<Album> albums;
    ArregloDinamico<Cancion> canciones;
    ArregloDinamico<Anuncio> anuncios;

    static bool dividir(const std::string& linea, char sep, ArregloDinamico<std::string>& partes);

    int ultimoAnuncioId;

    void sincronizarSeguidos(Usuario& u);

public:
    Plataforma();
    ~Plataforma();

    void cargarUsuarios(const std::string& ruta);
    void cargarArtistas(const std::string& ruta);
    void cargarAlbums(const std::string& ruta);
    void cargarCanciones(const std::string& ruta);
    void cargarAnuncios(const std::string& ruta);
    void cargarFavoritos(const std::string& ruta);
    void cargarTodo();
    void guardarFavoritos(const std::string& ruta);

    Usuario* buscarUsuario(const std::string& nick);
    Cancion* buscarCancionPorId(int id9);
    Album* buscarAlbumPorIds(int a5, int al2);

    const Anuncio* seleccionarAnuncioPonderado(std::mt19937& rng);

    void reproducirAleatorio(Usuario& u);
    void menuFavoritos(Usuario& u);
};

#endif

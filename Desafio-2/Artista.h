#ifndef ARTISTA_H
#define ARTISTA_H

#include <string>
#include "ArregloDinamico.h"

class Artista {
private:
    int id5;
    int edad;
    std::string pais;
    long seguidores;
    int posTendencia;
public:
    ArregloDinamico<int> idsAlbums;

    Artista();
    Artista(int id, int e, const std::string& p, long seg, int pos);
    ~Artista();

    int id() const;
};

#endif // ARTISTA_H

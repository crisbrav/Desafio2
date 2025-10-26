#include "Artista.h"

Artista::Artista(): id5(0), edad(0), seguidores(0), posTendencia(0) {}
Artista::Artista(int id, int e, const std::string& p, long seg, int pos)
    : id5(id), edad(e), pais(p), seguidores(seg), posTendencia(pos) {}
Artista::~Artista(){}
int Artista::id() const { return id5; }

// src/Anuncio.cpp
#include "Anuncio.h"

Anuncio::Anuncio(): id(0), categoria(CategoriaAnuncio::C) {}

int Anuncio::peso() const {
    switch(categoria){
    case CategoriaAnuncio::C: return 1;
    case CategoriaAnuncio::B: return 2;
    case CategoriaAnuncio::AAA: return 3;
    }
    return 1;
}

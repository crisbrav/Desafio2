#ifndef ANUNCIO_H
#define ANUNCIO_H

#include <string>
#include "Tipos.h"

class Anuncio {
public:
    int id;
    CategoriaAnuncio categoria;
    std::string mensaje;

    Anuncio();
    int peso() const;
};

#endif // ANUNCIO_H

// include/Usuario.h
#ifndef USUARIO_H
#define USUARIO_H

#include <string>
#include "ArregloDinamico.h"

class Usuario {
public:
    std::string nickname;
    bool esPremium;
    std::string ciudad;
    std::string pais;
    std::string fechaAlta;
    ArregloDinamico<int> favoritosIds;
    std::string siguiendoA;

    Usuario();
    Usuario(const std::string& n, bool premium, const std::string& c, const std::string& p, const std::string& f);
    ~Usuario();

    bool agregarFavorito(int idCancion);
    bool agregarFavoritoPorCancion(const int& idCancion);
    bool eliminarFavorito(int idCancion);
};

#endif // USUARIO_H

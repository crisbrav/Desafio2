// src/Usuario.cpp
#include "Usuario.h"

Usuario::Usuario(): esPremium(false) {}
Usuario::Usuario(const std::string& n, bool premium, const std::string& c, const std::string& p, const std::string& f)
    : nickname(n), esPremium(premium), ciudad(c), pais(p), fechaAlta(f) {}
Usuario::~Usuario(){}

bool Usuario::agregarFavorito(int idCancion){
    if (!esPremium) return false;
    if (favoritosIds.buscarPrimero(idCancion) != -1) return false;
    if (favoritosIds.tam() >= 10000) return false;
    favoritosIds.agregar(idCancion);
    return true;
}
bool Usuario::agregarFavoritoPorCancion(const int& idCancion){
    return agregarFavorito(idCancion);
}
bool Usuario::eliminarFavorito(int idCancion){
    int idx = favoritosIds.buscarPrimero(idCancion);
    if (idx == -1) return false;
    return favoritosIds.eliminarEn(idx);
}

#ifndef USUARIO_H
#define USUARIO_H

#include <string>
#include "ArregloDinamico.h"

class Usuario {
private:
    std::string _nickname;
    bool _esPremium;
    std::string _ciudad;
    std::string _pais;
    std::string _fechaAlta;
    ArregloDinamico<int> _favoritosIds;
    ArregloDinamico<bool> _favoritosOrigen;
    std::string _siguiendoA;

public:
    Usuario();
    Usuario(const std::string& n, bool premium, const std::string& c, const std::string& p, const std::string& f);
    ~Usuario();

    // Getters
    const std::string& nickname() const;
    bool esPremium() const;
    const std::string& ciudad() const;
    const std::string& pais() const;
    const std::string& fechaAlta() const;
    const std::string& siguiendoA() const;

    // Setters controlados
    void setCiudad(const std::string& c);
    void setPais(const std::string& p);
    void setSiguiendoA(const std::string& nick);

    // Favoritos (API)
    int cantidadFavoritos() const;
    int favoritoEn(int i) const;
    bool agregarFavorito(int idCancion);
    bool agregarFavoritoPorCancion(const int& idCancion);
    bool eliminarFavorito(int idCancion);
    void marcarOrigenPropio(int idCancion);
    void marcarOrigenSeguido(int idCancion);
    bool esOrigenPropio(int idx) const;
    void limpiarFavoritosSeguidos();

};

#endif // USUARIO_H

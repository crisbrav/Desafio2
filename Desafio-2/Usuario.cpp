#include "Usuario.h"

using namespace std;

Usuario::Usuario(): _esPremium(false) {}
Usuario::Usuario(const string& n, bool premium, const string& c, const string& p, const string& f)
    : _nickname(n), _esPremium(premium), _ciudad(c), _pais(p), _fechaAlta(f) {}
Usuario::~Usuario(){}

const string& Usuario::nickname() const { return _nickname; }
bool Usuario::esPremium() const { return _esPremium; }
const string& Usuario::ciudad() const { return _ciudad; }
const string& Usuario::pais() const { return _pais; }
const string& Usuario::fechaAlta() const { return _fechaAlta; }
const string& Usuario::siguiendoA() const { return _siguiendoA; }

void Usuario::setCiudad(const string& c){ if(!c.empty()) _ciudad = c; }
void Usuario::setPais(const string& p){ if(!p.empty()) _pais = p; }
void Usuario::setSiguiendoA(const string& nick){ _siguiendoA = nick; }

int Usuario::cantidadFavoritos() const { return _favoritosIds.tam(); }
int Usuario::favoritoEn(int i) const { return _favoritosIds[i]; }

bool Usuario::agregarFavorito(int idCancion){
    if (!_esPremium) return false;
    if (_favoritosIds.buscarPrimero(idCancion) != -1) return false;
    if (_favoritosIds.tam() >= 10000) return false;
    _favoritosIds.agregar(idCancion);
    _favoritosOrigen.agregar(true); // por defecto es propio
    return true;
}
bool Usuario::agregarFavoritoPorCancion(const int& idCancion){
    return agregarFavorito(idCancion);
}
bool Usuario::eliminarFavorito(int idCancion){
    int idx = _favoritosIds.buscarPrimero(idCancion);
    if (idx == -1) return false;
    return _favoritosIds.eliminarEn(idx); 
}

void Usuario::marcarOrigenPropio(int idCancion){
    int idx = _favoritosIds.buscarPrimero(idCancion);
    if(idx != -1 && idx < _favoritosOrigen.tam()){
        _favoritosOrigen[idx] = true;
    }
}
void Usuario::marcarOrigenSeguido(int idCancion){
    int idx = _favoritosIds.buscarPrimero(idCancion);
    if(idx != -1 && idx < _favoritosOrigen.tam()){
        _favoritosOrigen[idx] = false;
    }
}
bool Usuario::esOrigenPropio(int idx) const {
    if(idx < 0 || idx >= _favoritosOrigen.tam()) return true;
    return _favoritosOrigen[idx];
}
void Usuario::limpiarFavoritosSeguidos(){
    // elimina todos los que no son origen propio
    for(int i = _favoritosIds.tam()-1; i>=0; --i){
        if(i < _favoritosOrigen.tam() && !_favoritosOrigen[i]){
            _favoritosIds.eliminarEn(i);
            _favoritosOrigen.eliminarEn(i);
        }
    }
}

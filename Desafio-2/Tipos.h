#ifndef TIPOS_H
#define TIPOS_H

#include <string>

enum class Genero { Pop, Rock, Jazz, Clasica, Electronica, HipHop, Reggae, Blues, Latina, Ninguno };
enum class CalidadAudio { K128, K320 };
enum class CategoriaAnuncio { C, B, AAA };

inline Genero parsearGenero(const std::string& s){
    if (s=="Pop") return Genero::Pop;
    if (s=="Rock") return Genero::Rock;
    if (s=="Jazz") return Genero::Jazz;
    if (s=="Música Clásica" || s=="Clasica") return Genero::Clasica;
    if (s=="Electrónica" || s=="Electronica") return Genero::Electronica;
    if (s=="Hip Hop" || s=="HipHop") return Genero::HipHop;
    if (s=="Reggae") return Genero::Reggae;
    if (s=="Blues") return Genero::Blues;
    if (s=="Latina") return Genero::Latina;
    return Genero::Ninguno;
}

#endif // TIPOS_H

#ifndef CANCION_H
#define CANCION_H

#include <string>
#include <iostream>
#include "Tipos.h"

class Cancion {
private:
    int id9;
    std::string nombre;
    int duracionSeg;
    std::string rutaBase;
    int idArtista5;
    int idAlbum2;
    int reproducciones;
public:
    Cancion();
    Cancion(int id9_, const std::string& nom, int dur, const std::string& base, int a5, int al2);
    ~Cancion();

    int id() const;
    const std::string& titulo() const;
    int duracion() const;
    int artistaId() const;
    int albumId() const;
    void incrementarReproduccion();

    std::string rutaAudio(bool premium) const;
    std::string rutaAudio(CalidadAudio cal) const;

    bool operator==(const Cancion& o) const;
    friend std::ostream& operator<<(std::ostream& os, const Cancion& c);
};

#endif // CANCION_H

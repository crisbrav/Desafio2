#ifndef ALBUM_H
#define ALBUM_H

#include <string>
#include <iostream>
#include "Tipos.h"
#include "ArregloDinamico.h"

class Album {
private:
    int artista5;
    int album2;
    std::string nombre;
    std::string fecha;
    int duracionTotal;
    std::string sello;
    std::string rutaPortadaPng;
    int puntuacion;
    Genero generos[4];
public:
    ArregloDinamico<int> idsCanciones;

    Album();
    Album(int a5, int al2, const std::string& nom);
    ~Album();

    int artistaId() const;
    int albumId() const;
    const std::string& portada() const;

    void setMeta(const std::string& f, int dur, const std::string& se, const std::string& ruta, int punt);
    void setGeneros(Genero g0, Genero g1=Genero::Ninguno, Genero g2=Genero::Ninguno, Genero g3=Genero::Ninguno);

    friend std::ostream& operator<<(std::ostream& os, const Album& a);
};

#endif // ALBUM_H

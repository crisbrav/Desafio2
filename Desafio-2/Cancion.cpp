// src/Cancion.cpp
#include "Cancion.h"

using namespace std;

Cancion::Cancion(): id9(0), duracionSeg(0), idArtista5(0), idAlbum2(0), reproducciones(0) {}
Cancion::Cancion(int id9_, const string& nom, int dur, const string& base, int a5, int al2)
    : id9(id9_), nombre(nom), duracionSeg(dur), rutaBase(base), idArtista5(a5), idAlbum2(al2), reproducciones(0) {}
Cancion::~Cancion() {}

int Cancion::id() const { return id9; }
const string& Cancion::titulo() const { return nombre; }
int Cancion::duracion() const { return duracionSeg; }
int Cancion::artistaId() const { return idArtista5; }
int Cancion::albumId() const { return idAlbum2; }
void Cancion::incrementarReproduccion(){ ++reproducciones; }

string Cancion::rutaAudio(bool premium) const {
    return premium ? (rutaBase + "_320.ogg") : (rutaBase + "_128.ogg");
}
string Cancion::rutaAudio(CalidadAudio cal) const {
    return cal == CalidadAudio::K320 ? (rutaBase + "_320.ogg") : (rutaBase + "_128.ogg");
}

bool Cancion::operator==(const Cancion& o) const { return id9 == o.id9; }
ostream& operator<<(ostream& os, const Cancion& c){
    os << "[" << c.id9 << "] " << c.nombre << " (" << c.duracionSeg << "s)";
    return os;
}

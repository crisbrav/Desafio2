#include "Album.h"

using namespace std;

Album::Album(): artista5(0), album2(0), duracionTotal(0), puntuacion(0) {
    generos[0]=generos[1]=generos[2]=generos[3]=Genero::Ninguno;
}
Album::Album(int a5, int al2, const string& nom): artista5(a5), album2(al2), nombre(nom), duracionTotal(0), puntuacion(0) {
    generos[0]=generos[1]=generos[2]=generos[3]=Genero::Ninguno;
}
Album::~Album(){}

int Album::artistaId() const { return artista5; }
int Album::albumId() const { return album2; }
const string& Album::portada() const { return rutaPortadaPng; }

void Album::setMeta(const string& f, int dur, const string& se, const string& ruta, int punt){
    fecha=f; duracionTotal=dur; sello=se; rutaPortadaPng=ruta; puntuacion=punt;
}
void Album::setGeneros(Genero g0, Genero g1, Genero g2, Genero g3){
    generos[0]=g0; generos[1]=g1; generos[2]=g2; generos[3]=g3;
}

ostream& operator<<(ostream& os, const Album& a){
    os << "Album " << a.nombre << " (" << a.artista5 << "-" << a.album2 << ")";
    return os;
}


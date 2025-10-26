#ifndef UI_REPRODUCTOR_H
#define UI_REPRODUCTOR_H

#include <iostream>
#include <string>
#include "Tipos.h"
#include "Cancion.h"
#include "Album.h"
#include "Anuncio.h"
#include "Usuario.h"

inline void mostrarTarjetaReproduccion(const Usuario& u,
                                       const Cancion& c,
                                       const Album* al,
                                       const Anuncio* pub,
                                       bool premium,
                                       bool listarOpciones,
                                       bool esAleatorio) {
    if (pub){
        std::cout << "\"" << pub->mensaje << "\"\n";
        std::cout << "Categoría: "
                  << (pub->categoria==CategoriaAnuncio::AAA? "AAA" : (pub->categoria==CategoriaAnuncio::B? "B" : "C"))
                  << "\n\n";
    }
    std::cout << "Cantante: " << c.artistaId() << "\n";
    std::cout << "Album: " << (al? al->albumId() : 0) << "\n";
    std::cout << "Ruta a la portada del album: " << (al? al->portada() : "(sin portada)") << "\n\n";
    std::cout << "Titulo de la cancion reproducida: " << c.titulo() << "\n";
    std::cout << "Ruta al archivo de audio: "
              << c.rutaAudio(premium? CalidadAudio::K320 : CalidadAudio::K128) << "\n";
    std::cout << "Duracion: " << c.duracion() << " s\n\n";

    if(listarOpciones){
        std::cout << "Opciones de reproduccion:\n";
        if(esAleatorio){
            if(premium){
                std::cout << "1.- Reproducir   2.- Detener   3.- Siguiente   4.- Previa   5.- Repetir   6.- Salir\n";
            } else {
                std::cout << "1.- Reproducir   2.- Detener   6.- Salir\n";
            }
        }else{
            std::cout << "1.- Reproducir   2.- Detener   3.- Siguiente   4.- Previa   5.- Repetir   6.- Salir\n";
        }
    }
}

#endif // UI_REPRODUCTOR_H


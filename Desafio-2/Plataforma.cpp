#include "Plataforma.h"
#include "UiReproductor.h"

Plataforma::Plataforma(): ultimoAnuncioId(-1) {}
Plataforma::~Plataforma(){}

bool Plataforma::dividir(const std::string& linea, char sep, ArregloDinamico<std::string>& partes){
    std::stringstream ss(linea);
    std::string item;
    bool ok=false;
    partes = ArregloDinamico<std::string>();
    while(std::getline(ss, item, sep)){
        partes.agregar(item);
        contar_iter(); // campo parseado = iteracion indirecta
        ok=true;
    }
    return ok;
}

void Plataforma::cargarUsuarios(const std::string& ruta){
    reiniciar_metricas();
    std::ifstream in(ruta);
    std::string line;
    while(std::getline(in, line)){
        ArregloDinamico<std::string> p;
        if(!dividir(line, '|', p) || p.tam()<5) continue;
        usuarios.agregar(Usuario(p[0], p[1]=="premium", p[2], p[3], p[4]));
        contar_iter(); // registro cargado
    }
    imprimir_metricas("Carga usuarios");
}

void Plataforma::cargarArtistas(const std::string& ruta){
    reiniciar_metricas();
    std::ifstream in(ruta); std::string line;
    while(std::getline(in, line)){
        ArregloDinamico<std::string> p; if(!dividir(line,'|',p) || p.tam()<5) continue;
        artistas.agregar(Artista(std::stoi(p[0]), std::stoi(p[1]), p[2], std::stol(p[3]), std::stoi(p[4])));
        contar_iter(); // registro cargado
    }
    imprimir_metricas("Carga artistas");
}

void Plataforma::cargarAlbums(const std::string& ruta){
    reiniciar_metricas();
    std::ifstream in(ruta); std::string line;
    while(std::getline(in, line)){
        ArregloDinamico<std::string> p; if(!dividir(line,'|',p) || p.tam()<9) continue;
        int a5 = std::stoi(p[0]), al2 = std::stoi(p[1]);
        Album al(a5, al2, p[2]);
        al.setMeta(p[3], std::stoi(p[4]), p[5], p[6], std::stoi(p[7]));
        ArregloDinamico<std::string> gs; dividir(p[8], ',', gs);
        Genero g0=Genero::Ninguno,g1=Genero::Ninguno,g2=Genero::Ninguno,g3=Genero::Ninguno;
        if(gs.tam()>0) g0 = parsearGenero(gs[0]);
        if(gs.tam()>1) g1 = parsearGenero(gs[1]);
        if(gs.tam()>2) g2 = parsearGenero(gs[2]);
        if(gs.tam()>3) g3 = parsearGenero(gs[3]);
        al.setGeneros(g0,g1,g2,g3);
        albums.agregar(al);
        contar_iter(); // registro cargado
    }
    imprimir_metricas("Carga albums");
}

void Plataforma::cargarCanciones(const std::string& ruta){
    reiniciar_metricas();
    std::ifstream in(ruta); std::string line;
    while(std::getline(in, line)){
        ArregloDinamico<std::string> p; if(!dividir(line,'|',p) || p.tam()<6) continue;
        int s9 = std::stoi(p[0]), a5 = std::stoi(p[1]), al2 = std::stoi(p[2]);
        Cancion c(s9, p[3], std::stoi(p[4]), p[5], a5, al2);
        canciones.agregar(c);
        contar_iter(); // registro cargado
        // enlazar en album (búsqueda lineal contada)
        for(int i=0;i<albums.tam();++i){
            contar_iter(); // comparacion (a5,al2)
            if(albums[i].artistaId()==a5 && albums[i].albumId()==al2){
                albums[i].idsCanciones.agregar(s9);
                break;
            }
        }
    }
    imprimir_metricas("Carga canciones");
}

void Plataforma::cargarAnuncios(const std::string& ruta){
    reiniciar_metricas();
    std::ifstream in(ruta); std::string line;
    while(std::getline(in, line)){
        ArregloDinamico<std::string> p; if(!dividir(line,'|',p) || p.tam()<3) continue;
        Anuncio a; a.id = std::stoi(p[0]);
        if(p[1]=="C") a.categoria=CategoriaAnuncio::C;
        else if(p[1]=="B") a.categoria=CategoriaAnuncio::B;
        else a.categoria=CategoriaAnuncio::AAA;
        a.mensaje = p[2];
        anuncios.agregar(a);
        contar_iter(); // registro cargado
    }
    imprimir_metricas("Carga anuncios");
}

void Plataforma::cargarFavoritos(const std::string& ruta){
    reiniciar_metricas();
    std::ifstream in(ruta);
    if(!in.good()){ imprimir_metricas("Carga favoritos (vacio)"); return; }
    std::string line;
    while(std::getline(in, line)){
        ArregloDinamico<std::string> p;
        if(!dividir(line,'|',p) || p.tam()<3) continue;
        Usuario* u = buscarUsuario(p[0]);
        if(!u) continue;
        if(!p[2].empty()) u->setSiguiendoA(p[2]);
        std::stringstream ss(p[1]);
        std::string item;
        while(std::getline(ss, item, ',')){
            contar_iter(); // id parseado
            if(!item.empty()) u->agregarFavorito(std::stoi(item));
        }
    }
    imprimir_metricas("Carga favoritos");
}

void Plataforma::cargarTodo(){
    // Esta funcion orquesta y al final imprime su propia métrica (pocas iteraciones)
    reiniciar_metricas();
    cargarUsuarios("./data/usuarios.txt");
    cargarArtistas("./data/artistas.txt");
    cargarAlbums("./data/albums.txt");
    cargarCanciones("./data/canciones.txt");
    cargarAnuncios("./data/anuncios.txt");
    cargarFavoritos("./data/favoritos.txt");
    imprimir_metricas("Carga total");
}

void Plataforma::guardarFavoritos(const std::string& ruta){
    reiniciar_metricas();
    std::ofstream out(ruta);
    for(int i=0;i<usuarios.tam();++i){
        contar_iter(); // usuario examinado
        const auto& u = usuarios[i];
        if(!u.esPremium()) continue;
        out << u.nickname() << "|";
        for(int j=0;j<u.cantidadFavoritos();++j){
            contar_iter(); // id escrito
            if(j) out << ",";
            out << u.favoritoEn(j);
        }
        out << "|" << u.siguiendoA() << "\n";
    }
    imprimir_metricas("Guardar favoritos");
}

Usuario* Plataforma::buscarUsuario(const std::string& nick){
    for(int i=0;i<usuarios.tam();++i){
        contar_iter(); // comparacion nickname
        if(usuarios[i].nickname()==nick) return &usuarios[i];
    }
    return nullptr;
}
Cancion* Plataforma::buscarCancionPorId(int id9){
    for(int i=0;i<canciones.tam();++i){
        contar_iter(); // comparacion id
        if(canciones[i].id()==id9) return &canciones[i];
    }
    return nullptr;
}
Album* Plataforma::buscarAlbumPorIds(int a5, int al2){
    for(int i=0;i<albums.tam();++i){
        contar_iter(); // comparacion (a5,al2)
        if(albums[i].artistaId()==a5 && albums[i].albumId()==al2) return &albums[i];
    }
    return nullptr;
}

const Anuncio* Plataforma::seleccionarAnuncioPonderado(std::mt19937& rng){
    int n = anuncios.tam();
    if(n==0) return nullptr;
    // arreglo temporal de pesos (medir memoria)
    double* pesos = new double[n];
    ajustar_memoria(sizeof(double)*n);
    for(int i=0;i<n;++i){
        contar_iter(); // peso preparado
        pesos[i] = static_cast<double>(anuncios[i].peso());
    }
    std::discrete_distribution<int> dist(pesos, pesos + n);
    // no contar iteraciones dentro de la distribucion (no controlamos su implementacion)
    ajustar_memoria(- (int)sizeof(double)*n);
    delete[] pesos;

    for(int intentos=0; intentos<20; ++intentos){
        contar_iter(); // intento de muestreo
        int idx = dist(rng);
        if(anuncios[idx].id != ultimoAnuncioId){
            ultimoAnuncioId = anuncios[idx].id;
            return &anuncios[idx];
        }
    }
    for(int i=0;i<n;++i){
        contar_iter(); // fallback lineal
        if(anuncios[i].id != ultimoAnuncioId) { ultimoAnuncioId = anuncios[i].id; return &anuncios[i]; }
    }
    return &anuncios[0];
}

void Plataforma::sincronizarSeguidos(Usuario& u){
    if(u.siguiendoA().empty()) return;
    Usuario* seguido = buscarUsuario(u.siguiendoA());
    if(!seguido || !seguido->esPremium()) return;

    // Eliminar canciones del seguido que ya no estan
    for(int i = u.cantidadFavoritos()-1; i>=0; --i){
        contar_iter(); // favorito evaluado
        int idFav = u.favoritoEn(i);
        bool tiene=false;
        for(int j=0; j<seguido->cantidadFavoritos(); ++j){
            contar_iter(); // comparacion en seguido
            if(seguido->favoritoEn(j)==idFav){ tiene=true; break; }
        }
        if(!tiene) u.eliminarFavorito(idFav);
    }
    // Agregar nuevas canciones del seguido
    for(int i=0; i<seguido->cantidadFavoritos(); ++i){
        contar_iter(); // id examinado
        u.agregarFavorito(seguido->favoritoEn(i));
    }
}

void Plataforma::reproducirAleatorio(Usuario& u){
    reiniciar_metricas();
    if(canciones.tam()==0){ std::cout<<"No hay canciones.\n"; imprimir_metricas("Reproducir aleatorio"); return; }

    std::random_device rd; std::mt19937 rng(rd());
    std::uniform_int_distribution<int> distIdx(0, canciones.tam()-1);

    const int K = 5;
    PilaSimple<int> historial(4);
    int ultimaIdx = -1;

    std::cout << "\n=== Reproduccion aleatoria: tanda automatica de " << K << " ===\n";
    for(int i=0;i<K;i++){
        int idx = distIdx(rng); contar_iter(); // decision de siguiente
        Cancion& c = canciones[idx];
        Album* al = buscarAlbumPorIds(c.artistaId(), c.albumId());
        const Anuncio* pub = nullptr;
        if(!u.esPremium() && i>0 && (i%2==0)) pub = seleccionarAnuncioPonderado(rng);

        mostrarTarjetaReproduccion(u, c, al, pub, u.esPremium(), false, true);
        c.incrementarReproduccion();

        auto t0 = std::chrono::steady_clock::now();
        while(std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now()-t0).count() < 3){}

        historial.push(idx); contar_iter(); // transicion registrada
        ultimaIdx = idx;
    }

    std::cout << "\n=== Modo interactivo (uno a uno) ===\n";
    bool salir = false;
    bool repetir = false;
    int idxActual = ultimaIdx;
    while(!salir){
        Cancion& c = canciones[idxActual];
        Album* al = buscarAlbumPorIds(c.artistaId(), c.albumId());
        mostrarTarjetaReproduccion(u, c, al, nullptr, u.esPremium(), true, true);
        c.incrementarReproduccion();

        auto t0 = std::chrono::steady_clock::now();
        while(std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now()-t0).count() < 3){}

        std::cout << "Elige opcion: ";
        int op=1; std::cin >> op;

        if(op==6){ salir=true; break; }
        else if(op==2){
            std::cout << "Detenido. 1=Reproducir 6=Salir: ";
            int o2=1; std::cin >> o2;
            if(o2==6){ salir=true; break; } else continue;
        }
        else if(op==5){
            repetir = !repetir;
            std::cout << (repetir? "🔁 Repetir activado\n" : "🔁 Repetir desactivado\n");
            continue;
        }
        else if(op==4){
            int previo;
            if(historial.pop(previo)){ contar_iter(); idxActual = previo; continue; }
            else { std::cout << "No hay canciones previas (max 4).\n"; }
        }
        if(!repetir){
            historial.push(idxActual); contar_iter();
            idxActual = distIdx(rng); contar_iter();
        }
    }

    imprimir_metricas("Reproducir aleatorio");
}

void Plataforma::menuFavoritos(Usuario& u){
    reiniciar_metricas();
    if(!u.esPremium()){ std::cout<<"Funcion exclusiva premium.\n"; imprimir_metricas("Favoritos"); return; }

    bool salir = false;
    while(!salir){
        sincronizarSeguidos(u);
        std::cout << "Favoritos - Opciones:\n"
                  << "1) Editar\n2) Seguir otra lista\n3) Ejecutar mi lista\n4) Dejar de seguir\n5) Salir\n";
        int op = 0; std::cin >> op;

        if(op==1){
            std::cout << "\n--- Catalogo de canciones (id - titulo) ---\n";
            for(int i=0;i<canciones.tam();++i){
                contar_iter(); // listado de catalogo
                std::cout << canciones[i].id() << " - " << canciones[i].titulo() << "\n";
            }
            std::cout << "\n--- Mis favoritos actuales ---\n";
            if(u.cantidadFavoritos()==0) std::cout << "(Vacio)\n";
            else {
                for(int i=0;i<u.cantidadFavoritos();++i){
                    contar_iter(); // listado de favorito
                    int idFav = u.favoritoEn(i);
                    if(Cancion* cf = buscarCancionPorId(idFav))
                        std::cout << idFav << " - " << cf->titulo() << "\n";
                }
            }
            std::cout << "\nIngrese id de cancion: ";
            int id = 0; std::cin >> id;
            Cancion* c = buscarCancionPorId(id);
            if(!c){
                std::cout << "No existe cancion con id " << id << "\n";
            } else {
                std::cout << "Cancion: " << *c << "\n";
                std::cout << "[A]gregar / [E]liminar / [N]ada: ";
                char acc='N'; std::cin >> acc;
                if(acc=='A'||acc=='a'){
                    if(u.agregarFavorito(id)) std::cout << "Agregada a favoritos.\n";
                    else std::cout << "No se pudo agregar (duplicada o limite alcanzado).\n";
                    guardarFavoritos("./data/favoritos.txt");
                } else if(acc=='E'||acc=='e'){
                    if(u.eliminarFavorito(id)) std::cout << "Eliminada de favoritos.\n";
                    else std::cout << "No estaba en favoritos.\n";
                    guardarFavoritos("./data/favoritos.txt");
                }
            }
        } else if(op==2){
            std::cout << "Ingrese nickname a seguir: ";
            std::string otro; std::cin >> otro;
            Usuario* up = buscarUsuario(otro);
            if(up && up->esPremium()){
                u.setSiguiendoA(up->nickname());
                sincronizarSeguidos(u);
                guardarFavoritos("./data/favoritos.txt");
                std::cout << "Ahora sigues a " << up->nickname() << "\n";
            } else {
                std::cout << "No existe o no es premium.\n";
            }
        } else if(op==3){
            if(u.cantidadFavoritos()==0){ std::cout<<"Sin favoritos.\n"; continue; }
            std::cout << "Modo: [O]riginal / [A]leatorio: ";
            char modo='O'; std::cin >> modo;
            bool aleatorio = (modo=='A'||modo=='a');

            std::random_device rd; std::mt19937 rng(rd());
            std::uniform_int_distribution<int> distFav(0, u.cantidadFavoritos()-1);

            const int K=5, M=6;
            bool repetir=false; int reproducidas=0; bool salir2=false;
            PilaSimple<int> historialFav(M);
            int pos = aleatorio ? distFav(rng) : 0;

            while(!salir2 && reproducidas < K){
                int id = u.favoritoEn(pos);
                Cancion* c = buscarCancionPorId(id);
                if(!c){ std::cout<<"Cancion no encontrada.\n"; break; }
                Album* al = buscarAlbumPorIds(c->artistaId(), c->albumId());
                mostrarTarjetaReproduccion(u, *c, al, nullptr, true, true, false);
                c->incrementarReproduccion();

                auto t0 = std::chrono::steady_clock::now();
                while(std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now()-t0).count() < 3){}

                std::cout << "Elige opcion: ";
                int op2=1; std::cin >> op2;

                if(op2==6){ salir2=true; break; }
                else if(op2==2){
                    std::cout << "Detenido. 1=Reproducir 6=Salir: ";
                    int o2=1; std::cin >> o2;
                    if(o2==6){ salir2=true; break; } else continue;
                }
                else if(op2==5){
                    repetir = !repetir;
                    std::cout << (repetir? " Repetir activado\n" : " Repetir desactivado\n");
                    continue;
                }
                else if(op2==4){
                    int previo;
                    if(historialFav.pop(previo)){ contar_iter(); pos = previo; continue; }
                    else { std::cout << "No hay canciones previas (M="<<M<<")\n"; continue; }
                }
                if(!repetir){
                    historialFav.push(pos); contar_iter();
                    if(aleatorio) pos = distFav(rng); else pos = (pos+1) % u.cantidadFavoritos();
                    ++reproducidas;
                }
            }
            if(reproducidas>=K) std::cout << "\n Limite K="<<K<<" alcanzado\n";
            imprimir_metricas("Reproducir favoritos");
        } else if(op==4){
            if(!u.siguiendoA().empty()){
                std::cout << "Dejando de seguir a " << u.siguiendoA() << "\n";
                u.setSiguiendoA("");
                guardarFavoritos("./data/favoritos.txt");
            } else {
                std::cout << "No sigues a nadie.\n";
            }
        } else {
            salir = true;
        }
    }
    imprimir_metricas("Favoritos (menú)");
}

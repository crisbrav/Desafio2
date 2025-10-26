#include <iostream>
#include "Plataforma.h"

using namespace std;

int main(){
    Plataforma plataforma;
    plataforma.cargarTodo(); // usuarios, artistas, álbumes, canciones, anuncios

    // Login
    cout << "UdeATunes - Login\nIngrese nickname: ";
    string nick;
    cin >> nick;

    Usuario* usuario = plataforma.buscarUsuario(nick);
    if(!usuario){
        cout << "Usuario no encontrado.\n";
        return 0;
    }

    // Menú principal (sin opciones de carga/actualización visibles)
    bool salir=false;
    while(!salir){
        cout << "\nMenu:\n";
        cout << "1) Reproduccion aleatoria\n";
        if(usuario->esPremium()) cout << "2) Mi lista de favoritos\n";
        cout << "3) Salir\nOpcion: ";

        int op = 0;
        cin >> op;

        if(op==1){
            plataforma.reproducirAleatorio(*usuario);
        } else if(op==2 && usuario->esPremium()){
            // IV - Mi lista de favoritos (solo premium)
            plataforma.menuFavoritos(*usuario);
        } else {
            salir=true;
        }
    }

    // La actualización a disco se hace dentro de las funcionalidades (p.ej., guardarFavoritos)
    return 0;
}

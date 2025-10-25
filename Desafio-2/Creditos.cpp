// src/Creditos.cpp
#include "Creditos.h"
#include <iostream>

Creditos::Creditos() {}
Creditos::~Creditos() {}

void Creditos::agregarProductor(const ContribuyenteCredito& cc){ productores.agregar(cc); }
void Creditos::agregarMusico(const ContribuyenteCredito& cc){ musicos.agregar(cc); }
void Creditos::agregarCompositor(const ContribuyenteCredito& cc){ compositores.agregar(cc); }

void imprimirCreditos(const Creditos& c){
    std::cout << "Productores: " << c.productores.tam()
    << " | Músicos: " << c.musicos.tam()
    << " | Compositores: " << c.compositores.tam() << "\n";
}

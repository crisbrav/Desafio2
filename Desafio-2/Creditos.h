// include/Creditos.h
#ifndef CREDITOS_H
#define CREDITOS_H

#include <string>
#include "ArregloDinamico.h"

struct ContribuyenteCredito {
    std::string nombre;
    std::string apellido;
    std::string codigo10;
};

class Creditos {
private:
    ArregloDinamico<ContribuyenteCredito> productores;
    ArregloDinamico<ContribuyenteCredito> musicos;
    ArregloDinamico<ContribuyenteCredito> compositores;
    friend void imprimirCreditos(const Creditos& c);
public:
    Creditos();
    ~Creditos();

    void agregarProductor(const ContribuyenteCredito& cc);
    void agregarMusico(const ContribuyenteCredito& cc);
    void agregarCompositor(const ContribuyenteCredito& cc);
};

void imprimirCreditos(const Creditos& c);

#endif // CREDITOS_H

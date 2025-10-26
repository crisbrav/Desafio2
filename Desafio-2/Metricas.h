#ifndef METRICAS_H
#define METRICAS_H
#include <string>
#include <iostream>
inline unsigned int g_iteraciones = 0U;
inline int g_mem_dinamica_bytes = 0;
inline void contar_iter(){ ++g_iteraciones; }
inline void ajustar_memoria(int delta){ g_mem_dinamica_bytes += delta; }
inline void reiniciar_metricas(){ g_iteraciones = 0U; g_mem_dinamica_bytes = 0; }
inline void imprimir_metricas(const std::string& etiqueta){
    std::cout << "[Metricas] " << etiqueta
              << " -> Iteraciones: " << g_iteraciones
              << " | Memoria dinamica (bytes): " << g_mem_dinamica_bytes << "\n";
}
#endif

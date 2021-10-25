//
// Created by andre on 10/19/21.
//

#ifndef PROYECTO_1_POLIGONO_H
#define PROYECTO_1_POLIGONO_H

#include <vector>
#include <algorithm>
#include <limits>
#include "Arista.h"

/*Clase poligono guarda las aristas y quisieramos también que no fuera mutable una vez inicializado*/
class Poligono {
    std::vector<Arista> _poligono;
    float _max_derecha_x = 1000000.0;
    float epsilon = 0.001;
    enum orientacion { colinear, manecillas, contramanecillas};
    int id;

    /*Dado 3 puntos colineares p, q y r, la función checa si el punto q está en medio de los otros dos*/
    bool EnSegmento(Punto p, Punto q, Punto r)
    {
        auto [p_x, p_y] = p.GetPunto();
        auto [q_x, q_y] = q.GetPunto();
        auto [r_x, r_y] = r.GetPunto();
        if (q_x <= std::max(p_x, r_x) && q_x >= std::min(p_x, r_x) &&
            q_y <= std::max(p_y, r_y) && q_y >= std::min(p_y, r_y))
            return true;
        return false;
    }

    /*Encuentra la orientación del triplete (p, q, r)*/
    orientacion Orientacion(Punto p, Punto q, Punto r)
    {
        auto [p_x, p_y] = p.GetPunto();
        auto [q_x, q_y] = q.GetPunto();
        auto [r_x, r_y] = r.GetPunto();

        // expresión para determinar la orientación
        float val = (q_y - p_y) * (r_x - q_x) -
                  (q_x - p_x) * (r_y - q_y);


        if (std::abs(val) < this->epsilon) return colinear;  // collinear

        return (val > 0)? manecillas: contramanecillas;
    }

    bool IntersectanAristas(Arista arista_1, Arista arista_2){
        auto [p_1, q_1] = arista_1.GetArista();
        auto [p_2, q_2] = arista_2.GetArista();

        // Encuentra orientaciones de todos los tripletes
        orientacion o1 = Orientacion(p_1, q_1, p_2);
        orientacion o2 = Orientacion(p_1, q_1, q_2);
        orientacion o3 = Orientacion(p_2, q_2, p_1);
        orientacion o4 = Orientacion(p_2, q_2, q_1);

        if (o1 != o2 && o3 != o4)
            return true;

        // Casos especiales cuando son colineares checar si están entre metidos

        if (o1 == colinear && EnSegmento(p_1, p_2, q_1)) return true;
        if (o2 == colinear && EnSegmento(p_1, q_2, q_1)) return true;
        if (o3 == colinear && EnSegmento(p_2, p_1, q_2)) return true;
        if (o4 == colinear && EnSegmento(p_2, q_1, q_2)) return true;

        return false; // No es ningún caso
    }


public:
    Poligono() = default;

    explicit Poligono(int id, std::vector<Arista> &lista_aristas): id(id){
        if(lista_aristas.size() < 3) throw std::runtime_error("los polígonos se componen de mas de 3 aristas");
        this->_poligono = std::vector<Arista>(lista_aristas);
    }

    std::vector<Arista> GetPoligono(){
        return std::vector<Arista>(this->_poligono);
    }

    int GetId(){
        return this->id;
    }

    bool PuntoInPoligono(Punto &punto){
        auto [punto_x, punto_y] = punto.GetPunto();
        Punto punto_inf(this->_max_derecha_x, punto_y);
        Arista arista_inf(punto, punto_inf);
        int sum_colisiones = 0;
        for(Arista &arista_poligono: this->_poligono){
            auto [arista_punto_1, arista_punto_2] = arista_poligono.GetArista();

            // Si está en un vertice está adentro
            if((punto == arista_punto_1) || (punto == arista_punto_2))
                return true;

            // Si intersecta entonces está dentro
            if(IntersectanAristas(arista_poligono, arista_inf)) sum_colisiones++;

        }
        return sum_colisiones & 1;
    }
};


#endif //PROYECTO_1_POLIGONO_H

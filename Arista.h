//
// Created by andre on 10/19/21.
//

#ifndef PROYECTO_1_ARISTA_H
#define PROYECTO_1_ARISTA_H

#include <tuple>
#include "Punto.h"

/*Las aristas son pares de vertices que forman una recta perteneciente a un poligono, tampoco queremos que sea mutable*/
class Arista {
    std::tuple<Punto,Punto> _arista = std::tuple<Punto, Punto>();
public:
    Arista(Punto vert_1, Punto vert_2){
        this->_arista = std::tuple<Punto, Punto>(vert_1, vert_2);
    }
    std::tuple<Punto,Punto> GetArista(){
        return std::tuple<Punto,Punto>(this->_arista);
    }
};


#endif //PROYECTO_1_ARISTA_H

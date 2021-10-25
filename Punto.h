//
// Created by andre on 10/19/21.
//

#ifndef PROYECTO_1_PUNTO_H
#define PROYECTO_1_PUNTO_H

#include <tuple>

/*Clase de un punto, queremos que no sea asignable una vez pero no mutable una vez después de asignado*/
class Punto {
    std::tuple<float, float> _punto;
public:
    Punto() = default;
    Punto(float x, float y){
        this->_punto = std::tuple<float, float>(x, y);
    }
    std::tuple<float, float> GetPunto(){
        return std::tuple(this->_punto);
    }
    friend bool operator==(Punto punto_1, Punto punto_2){
        auto [x_1, y_1] = punto_1.GetPunto();
        auto [x_2, y_2] = punto_2.GetPunto();
        return (std::abs(x_1 - x_2) <= 0.001) && (std::abs(y_1 - y_2) <= 0.001);
    }
};


#endif //PROYECTO_1_PUNTO_H

#include <iostream>
#include <ios>
#include <fstream>
#include <sstream>
#include <map>
#include "Punto.h"
#include "Arista.h"
#include "Poligono.h"

int main() {
    // Vector de poligonos
    std::vector<Poligono> poligonos;

    // Leer archivo de poligono
    std::ifstream inputFile("polygon_tot.dat", std::ifstream::in);
    std::string line;
    if(inputFile.is_open()) {
        while (std::getline(inputFile, line)) {
            std::istringstream lineStream(line);

            // Id
            std::string idStream;
            lineStream >> idStream;
            char *ptrID;
            int id = (int) strtol(idStream.c_str(), &ptrID, 10);

            // Número de lados
            std::string noLadosStream;
            lineStream >> noLadosStream;
            char *ptrNoLados;
            int noLados = (int) strtol(noLadosStream.c_str(), &ptrNoLados, 10);

            // Puntos
            std::vector<Punto> puntos;
            for (int verticeIndex = 0; verticeIndex < noLados; ++verticeIndex) {
                std::string xStream;
                std::string yStream;
                float x, y;
                char *xPtr, *yPtr;

                lineStream >> xStream;
                lineStream >> yStream;

                x = (float) strtod(xStream.c_str(), &xPtr);
                y = (float) strtod(yStream.c_str(), &yPtr);

                Punto punto(x,y);

                puntos.push_back(punto);
            }

            // Convertir a poligono
            std::vector<Arista> aristas;
            for (size_t puntoIndex = 0; puntoIndex < noLados; ++puntoIndex) {
                Punto puntoInicial = puntos[puntoIndex];
                Punto puntoFinal = puntos[(puntoIndex + 1)%noLados];
                Arista arista(puntoInicial, puntoFinal);
                aristas.push_back(arista);
            }

            Poligono poligono(id, aristas);

            poligonos.push_back(poligono);
        }
    }
    inputFile.close();

    std::vector<Punto> puntos;

    // Leer archivo de puntos
    std::ifstream inputFilePuntos("puntos_doctor.data", std::ifstream::in);
    std::string linepuntos;
    if(inputFilePuntos.is_open()){
        while (std::getline(inputFilePuntos, linepuntos)) {
            std::istringstream lineStream(linepuntos);
            std::string xStream;
            std::string yStream;
            float x, y;
            char *xPtr, *yPtr;

            lineStream >> xStream;
            lineStream >> yStream;

            x = (float) strtod(xStream.c_str(), &xPtr);
            y = (float) strtod(yStream.c_str(), &yPtr);

            Punto punto(x,y);

            puntos.push_back(punto);
        }
    }
    inputFilePuntos.close();



    // Resultados

    std::map<int, int> info;

    // Inicializar info
    for (auto &poligono: poligonos) {
        info.insert(std::pair<int, int>(poligono.GetId(), 0));
    }

    // Buscar puntos en poligono
    for (auto &punto: puntos) {
        for (auto &poligono: poligonos) {
            if(poligono.PuntoInPoligono(punto))
                info[poligono.GetId()]++;
        }
    }

    // Salida
    std::ofstream outputFile("info_teams.data", std::ofstream::out | std::ofstream::trunc);
    int suma = 0;
    outputFile << "ID\t\tPuntos dentro de ID\n";
    for (auto &infoRow: info) {
        suma += infoRow.second;
        outputFile << infoRow.first << "\t\t" << infoRow.second << "\n";
    }
    outputFile << "Esperado:\t" << puntos.size() << "\n";
    outputFile << "Suma:\t" << suma << "\n";
    outputFile.close();

    return 0;
}

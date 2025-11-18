/*
 * vuelos.h (Avance 3)
 *  Fecha: 18/11/2025
 *  Author: Héctor Alejandro Barrón Tamayo
 *  Matricula: A01713794
 *  - Estructura principal: std::list<Vuelo>
 */

#ifndef VUELOS_H
#define VUELOS_H

#include <iostream>
#include <list>
#include <string>
#include <algorithm>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>

struct Avion {
    std::string modelo;
    std::string fabricante;
    int capacidad;
};

struct Vuelo {
    int id;
    std::string destino;
    std::string fecha; // YYYY-MM-DD
    int asientosDisponibles;
    float precioBase;
    float duracionHoras;
    int kilometros;
    Avion avion;
};

/* -- Utilidades de impresión -- */

inline void imprimirHeaderVuelos() {
    std::cout << std::left << std::setw(6) << "ID"
              << std::setw(12) << "Fecha"
              << std::setw(16) << "Destino"
              << std::setw(10) << "Asientos"
              << std::setw(12) << "Precio"
              << "Avion\n";
    std::cout << std::string(70, '-') << "\n";
}

inline void imprimirVuelo(const Vuelo& v) {
    std::cout << std::left << std::setw(6) << v.id
              << std::setw(12) << v.fecha
              << std::setw(16) << v.destino
              << std::setw(10) << v.asientosDisponibles
              << "$" << std::setw(11) << std::fixed << std::setprecision(2) << v.precioBase
              << v.avion.modelo << "\n";
}

inline void listarVuelos(const std::list<Vuelo>& vuelos) {
    imprimirHeaderVuelos();
    for (const auto& v : vuelos) imprimirVuelo(v);
}

/* -- Carga inicial (semilla en memoria) -- */
inline void inicializarVuelos(std::list<Vuelo>& vuelos) {
    vuelos.push_back({1, "Londres",  "2025-07-01", 120,  680.0f, 10.0f,  8900, {"Boeing 787","Boeing",250}});
    vuelos.push_back({2, "Sidney",   "2025-07-03", 110, 1450.0f, 17.0f, 15000, {"Airbus A380","Airbus",500}});
    vuelos.push_back({3, "Toronto",  "2025-07-05", 140,  720.0f,  9.0f,  7600, {"Boeing 777","Boeing",300}});
    vuelos.push_back({4, "Roma",     "2025-07-07", 130,  670.0f,  8.5f,  7200, {"Airbus A330","Airbus",270}});
    vuelos.push_back({5, "Estambul", "2025-07-10", 100,  790.0f, 10.5f,  9300, {"Boeing 737 MAX","Boeing",200}});
}

/* -- Lectura/Escritura de archivo (CSV) -- */
/* Formato esperado (vuelos.csv):
 * id,destino,fecha,asientos,precio,duracion,km,modelo,fabricante,capacidad
 * 1,Londres,2025-07-01,120,680.0,10.0,8900,Boeing 787,Boeing,250
 */
inline bool cargarVuelosCSV(const std::string& archivo, std::list<Vuelo>& vuelos) {
    std::ifstream file(archivo);
    if (!file.is_open()) return false;

    std::string linea;
    std::list<Vuelo> tmp;
    while (std::getline(file, linea)) {
        if (linea.empty()) continue;
        std::stringstream ss(linea);
        std::string sId, destino, fecha, sAsientos, sPrecio, sDuracion, sKm, modelo, fabricante, sCap;

        if (!std::getline(ss, sId, ',')) continue;
        if (!std::getline(ss, destino, ',')) continue;
        if (!std::getline(ss, fecha, ',')) continue;
        if (!std::getline(ss, sAsientos, ',')) continue;
        if (!std::getline(ss, sPrecio, ',')) continue;
        if (!std::getline(ss, sDuracion, ',')) continue;
        if (!std::getline(ss, sKm, ',')) continue;
        if (!std::getline(ss, modelo, ',')) continue;
        if (!std::getline(ss, fabricante, ',')) continue;
        if (!std::getline(ss, sCap)) continue;

        try {
            Vuelo v;
            v.id = std::stoi(sId);
            v.destino = destino;
            v.fecha = fecha;
            v.asientosDisponibles = std::stoi(sAsientos);
            v.precioBase = std::stof(sPrecio);
            v.duracionHoras = std::stof(sDuracion);
            v.kilometros = std::stoi(sKm);
            v.avion = {modelo, fabricante, std::stoi(sCap)};
            tmp.push_back(v);
        } catch (...) {
            // línea inválida; por lo tanto se ignora
        }
    }
    file.close();
    if (!tmp.empty()) vuelos = std::move(tmp);
    return true;
}

inline bool guardarVuelosCSV(const std::string& archivo, const std::list<Vuelo>& vuelos) {
    std::ofstream out(archivo);
    if (!out.is_open()) return false;
    for (const auto& v : vuelos) {
        out << v.id << ','
            << v.destino << ','
            << v.fecha << ','
            << v.asientosDisponibles << ','
            << v.precioBase << ','
            << v.duracionHoras << ','
            << v.kilometros << ','
            << v.avion.modelo << ','
            << v.avion.fabricante << ','
            << v.avion.capacidad << '\n';
    }
    return true;
}

/* -- Ordenamientos -- */
// Uso std::list::sort (merge sort estable) para ordenar la lista en O(n log n).
inline void ordenarPorPrecio(std::list<Vuelo>& vuelos) {
    vuelos.sort([](const Vuelo& a, const Vuelo& b){ return a.precioBase < b.precioBase; });
    listarVuelos(vuelos);
}

inline void ordenarPorFecha(std::list<Vuelo>& vuelos) {
    vuelos.sort([](const Vuelo& a, const Vuelo& b){ return a.fecha < b.fecha; });
    listarVuelos(vuelos);
}

/* -- Búsquedas -- */
inline bool busquedaBinariaPorId(const std::list<Vuelo>& vuelos, int idBuscado, Vuelo& resultado) {
    if (vuelos.empty()) return false;

    std::vector<Vuelo> copia(vuelos.begin(), vuelos.end());
    std::sort(copia.begin(), copia.end(),
              [](const Vuelo& a, const Vuelo& b){ return a.id < b.id; });

    int low = 0, high = static_cast<int>(copia.size()) - 1;
    while (low <= high) {
        int mid = (low + high) / 2;
        if (copia[mid].id == idBuscado) {
            resultado = copia[mid];
            return true;
        } else if (copia[mid].id < idBuscado) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return false;
}

inline void buscarPorDestinoFecha(const std::list<Vuelo>& vuelos,
                                  const std::string& destino,
                                  const std::string& fecha) {
    bool encontrado = false;
    for (const auto& v : vuelos) {
        bool okDest = destino.empty() || v.destino == destino;
        bool okFecha = fecha.empty() || v.fecha == fecha;
        if (okDest && okFecha) {
            if (!encontrado) imprimirHeaderVuelos();
            imprimirVuelo(v);
            encontrado = true;
        }
    }
    if (!encontrado) std::cout << "No se encontraron vuelos con esos criterios.\n";
}

#endif

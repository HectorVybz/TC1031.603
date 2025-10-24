/*
 * main.cpp
 *
 *  Fecha de actualización: 23/10/2025
 *  Autor: Héctor Alejandro Barrón Tamayo
 *
 */

#include "vuelos.h"
#include <limits>

int main() {
    std::vector<Vuelo> vuelos;

    if (!cargarVuelosCSV("vuelos.csv", vuelos)) {
        inicializarVuelos(vuelos);
    }

    if (vuelos.empty()) {
        std::cout << "No hay vuelos cargados.\n";
        return 0;
    }

    int opcion;
    do {
        std::cout << "\n---- MENU ----\n";
        std::cout << "1. Ordenar por precio\n";
        std::cout << "2. Ordenar por fecha\n";
        std::cout << "3. Buscar por ID (binaria)\n";
        std::cout << "4. Buscar por destino/fecha\n";
        std::cout << "5. Listar todos los vuelos\n";
        std::cout << "6. Salir\n";
        std::cout << "Selecciona una opcion: ";
        std::cin >> opcion;
        std::cin.ignore();

        if (opcion == 1) {
            ordenarPorPrecio(vuelos);
        } else if (opcion == 2) {
            ordenarPorFecha(vuelos);
        } else if (opcion == 3) {
            int id;
            std::cout << "Ingrese el ID de vuelo: ";
            std::cin >> id;
            std::cin.ignore();
            ordenarPorId(vuelos); // ordenar antes de la búsqueda binaria
            int idx = busquedaBinariaPorId(vuelos, id);
            if (idx != -1) {
                imprimirHeaderVuelos();
                imprimirVuelo(vuelos[idx]);
            } else {
                std::cout << "Vuelo no encontrado.\n";
            }
        } else if (opcion == 4) {
            std::cout << "\n--- Destinos disponibles ---\n";
            std::cout << "Londres\nSidney\nToronto\nRoma\nEstambul\n";
            std::cout << "Escribe el destino (o deja vacío para todos): ";
            std::string destino;
            std::getline(std::cin, destino);

            std::cout << "\n--- Fechas disponibles ---\n";
            std::cout << "2025-07-01\n2025-07-03\n2025-07-05\n2025-07-07\n2025-07-10\n";
            std::cout << "Escribe la fecha (YYYY-MM-DD) o deja vacío para todas: ";
            std::string fecha;
            std::getline(std::cin, fecha);

            buscarPorDestinoFecha(vuelos, destino, fecha);
        } else if (opcion == 5) {
            listarVuelos(vuelos);
        } else if (opcion == 6) {
            std::cout << "Saliendo...\n";
        } else {
            std::cout << "Opcion invalida.\n";
        }
    } while (opcion != 6);

    return 0;
}

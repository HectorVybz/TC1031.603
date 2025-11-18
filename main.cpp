/*
 * main.cpp (Avance 3)
 *  Fecha: 18/11/2025
 *  Author: Héctor Alejandro Barrón Tamayo
 *  Matricula: A01713794
 *  - Estructura principal: std::list<Vuelo>
 *  - Los datos se cargan y se guardan desde/ hacia un archivo CSV (vuelos.csv)
 */

#include "vuelos.h"
#include <limits>

int main() {
    std::list<Vuelo> vuelos;

    // 1) Se intenta cargar desde CSV; si no existe, usar la semilla en memoria
    if (!cargarVuelosCSV("vuelos.csv", vuelos)) {
        inicializarVuelos(vuelos);
        // Se crea un CSV inicial para futuras ejecuciones
        guardarVuelosCSV("vuelos.csv", vuelos);
    }

    if (vuelos.empty()) {
        std::cout << "No hay vuelos cargados.\n";
        return 0;
    }

    int opcion;
    do {
        std::cout << "\nMENU \n";
        std::cout << "1. Ordenar por precio (lista)\n";
        std::cout << "2. Ordenar por fecha (lista)\n";
        std::cout << "3. Buscar por ID (busqueda binaria sobre copia ordenada)\n";
        std::cout << "4. Buscar por destino/fecha\n";
        std::cout << "5. Listar todos los vuelos\n";
        std::cout << "6. Guardar vuelos en CSV y salir\n";
        std::cout << "Selecciona una opcion: ";
        std::cin >> opcion;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (opcion == 1) {
            ordenarPorPrecio(vuelos);
        } else if (opcion == 2) {
            ordenarPorFecha(vuelos);
        } else if (opcion == 3) {
            int id;
            std::cout << "Ingrese el ID de vuelo: ";
            std::cin >> id;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            Vuelo resultado;
            bool encontrado = busquedaBinariaPorId(vuelos, id, resultado);
            if (encontrado) {
                imprimirHeaderVuelos();
                imprimirVuelo(resultado);
            } else {
                std::cout << "Vuelo no encontrado.\n";
            }
        } else if (opcion == 4) {
            std::cout << "\nDestinos disponibles\n";
            std::cout << "Londres\nSidney\nToronto\nRoma\nEstambul\n";
            std::cout << "Escribe el destino (o deja vacio para todos): ";
            std::string destino;
            std::getline(std::cin, destino);

            std::cout << "\nFechas disponibles\n";
            std::cout << "2025-07-01\n2025-07-03\n2025-07-05\n2025-07-07\n2025-07-10\n";
            std::cout << "Escribe la fecha (YYYY-MM-DD) o deja vacio para todas: ";
            std::string fecha;
            std::getline(std::cin, fecha);

            buscarPorDestinoFecha(vuelos, destino, fecha);
        } else if (opcion == 5) {
            listarVuelos(vuelos);
        } else if (opcion == 6) {
            if (guardarVuelosCSV("vuelos.csv", vuelos)) {
                std::cout << "Datos guardados correctamente en vuelos.csv. Saliendo...\n";
            } else {
                std::cout << "No se pudo guardar el archivo vuelos.csv, pero se cerrara el programa.\n";
            }
        } else {
            std::cout << "Opcion invalida.\n";
        }
    } while (opcion != 6);

    return 0;
}

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>
using namespace std;
// author: Hector Alejandro Barron tamayo
// fecha: 26/09/2025

// Clases / Estructuras

class Avion {
public:
    string modelo;
    string fabricante;
    int capacidad;

    Avion(string modelo, string fabricante, int capacidad)
        : modelo(modelo), fabricante(fabricante), capacidad(capacidad) {}
};

class Pasajero {
public:
    string nombre;
    string pasaporte;

    Pasajero(string nombre, string pasaporte)
        : nombre(nombre), pasaporte(pasaporte) {}
};

struct Usuario {
    string nombre;
    string correo;
    string contrasena;
    int kilometros;
};

struct Vuelo {
    int id;
    string destino;
    string fecha; // YYYY-MM-DD
    int asientosDisponibles;
    float precioBase;
    float duracionHoras;
    int kilometros;
    Avion avion;
    vector<Pasajero> pasajeros;

    Vuelo(int id, string destino, string fecha, int asientos, float precio,
          float duracionHoras, int km, Avion avion)
        : id(id), destino(destino), fecha(fecha), asientosDisponibles(asientos),
          precioBase(precio), duracionHoras(duracionHoras),
          kilometros(km), avion(avion) {}
};

struct Reservacion {
    string nombreUsuario; // correo
    int idVuelo;
    int cantidadPasajeros;
    float precioFinal;
    int kmFinales;
};

// Datos globales

vector<Usuario> usuarios;
vector<Vuelo>   vuelos;
vector<Reservacion> reservaciones;
Usuario* usuarioActual = nullptr;

// Utilidades

void linea() { cout << string(70, '-') << "\n"; }

void printHeaderVuelos() {
    linea();
    cout << left << setw(6) << "ID"
         << setw(12) << "Fecha"
         << setw(16) << "Destino"
         << setw(10) << "Asientos"
         << setw(12) << "Precio"
         << "Avion\n";
    linea();
}

void printVuelo(const Vuelo& v) {
    cout << left << setw(6) << v.id
         << setw(12) << v.fecha
         << setw(16) << v.destino
         << setw(10) << v.asientosDisponibles
         << "$" << setw(11) << fixed << setprecision(2) << v.precioBase
         << v.avion.modelo << "\n";
}

bool usuarioExiste(const string& correo) {
    for (const auto& u : usuarios) if (u.correo == correo) return true;
    return false;
}

Usuario* obtenerUsuario(const string& correo) {
    for (auto& u : usuarios) if (u.correo == correo) return &u;
    return nullptr;
}

Vuelo* obtenerVueloPorIdLineal(int id) {
    for (auto& v : vuelos) if (v.id == id) return &v;
    return nullptr;
}

// Carga inicial 

void inicializarVuelos() {
    vuelos.push_back({ 1,"Londres" , "2025-07-01",120, 680.0f,10.0f, 8900, Avion("Boeing 787","Boeing",250) });
    vuelos.push_back({ 2,"Sidney"  , "2025-07-03",110,1450.0f,17.0f,15000, Avion("Airbus A380","Airbus",500) });
    vuelos.push_back({ 3,"Toronto" , "2025-07-05",140, 720.0f, 9.0f, 7600, Avion("Boeing 777","Boeing",300) });
    vuelos.push_back({ 4,"Roma"    , "2025-07-07",130, 670.0f, 8.5f, 7200, Avion("Airbus A330","Airbus",270) });
    vuelos.push_back({ 5,"Estambul", "2025-07-10",100, 790.0f,10.5f, 9300, Avion("Boeing 737 MAX","Boeing",200) });
    cout << "Vuelos cargados correctamente.\n";
}

// Sorts (std::sort)

void ordenarVuelosPorPrecio(vector<Vuelo>& vs) {
    sort(vs.begin(), vs.end(),
         [](const Vuelo& a, const Vuelo& b){ return a.precioBase < b.precioBase; });
    printHeaderVuelos();
    for (const auto& v : vs) printVuelo(v);
    linea();
}

void ordenarVuelosPorFecha(vector<Vuelo>& vs) {
    sort(vs.begin(), vs.end(),
         [](const Vuelo& a, const Vuelo& b){ return a.fecha < b.fecha; });
    printHeaderVuelos();
    for (const auto& v : vs) printVuelo(v);
    linea();
}

void ordenarVuelosPorId(vector<Vuelo>& vs) {
    sort(vs.begin(), vs.end(),
         [](const Vuelo& a, const Vuelo& b){ return a.id < b.id; });
}

// Búsquedas

// Filtrado secuencial por destino/fecha (ambos opcionales)
void buscarVuelosInteractivo() {
    string destino, fecha;
    cout << "=== BUSCAR VUELOS ===\n";
    cout << "Destino (vacio = ignorar): ";
    getline(cin, destino);
    cout << "Fecha YYYY-MM-DD (vacio = ignorar): ";
    getline(cin, fecha);

    vector<const Vuelo*> res;
    for (const auto& v : vuelos) {
        bool okDest  = destino.empty() || v.destino == destino;
        bool okFecha = fecha.empty()   || v.fecha   == fecha;
        if (okDest && okFecha) res.push_back(&v);
    }

    if (res.empty()) { cout << "No se encontraron vuelos con esos criterios.\n"; return; }

    printHeaderVuelos();
    for (auto* p : res) printVuelo(*p);
    linea();
}

// Búsqueda binaria por ID
int busquedaBinariaPorId(const vector<Vuelo>& vs, int idBuscado) {
    int low = 0, high = (int)vs.size() - 1;
    while (low <= high) {
        int mid = (low + high) / 2;
        if (vs[mid].id == idBuscado) return mid;
        else if (vs[mid].id < idBuscado) low = mid + 1;
        else high = mid - 1;
    }
    return -1;
}

void buscarPorIdBinariaInteractivo() {
    if (vuelos.empty()) { cout << "No hay vuelos.\n"; return; }
    int id; cout << "Ingresa ID de vuelo: "; cin >> id; cin.ignore();

    ordenarVuelosPorId(vuelos);                 // ordenar antes de binaria
    int idx = busquedaBinariaPorId(vuelos, id); // O(log n)
    if (idx != -1) {
        printHeaderVuelos();
        printVuelo(vuelos[idx]);
        linea();
    } else {
        cout << "Vuelo no encontrado.\n";
    }
}

// Gestión de usuarios / sesión

void agregarUsuario() {
    string nombre, correo, contrasena; int km;
    cout << "Ingrese nombre: ";     getline(cin, nombre);
    cout << "Ingrese correo: ";     getline(cin, correo);
    if (usuarioExiste(correo)) { cout << "El usuario ya existe.\n"; return; }
    cout << "Ingrese contrasena: "; getline(cin, contrasena);
    cout << "Ingrese kilometros acumulados: "; cin >> km; cin.ignore();
    usuarios.push_back({nombre, correo, contrasena, km});
    cout << "Usuario agregado exitosamente.\n";
}

void cerrarSesion() { usuarioActual = nullptr; cout << "Sesion cerrada.\n"; }

// Reservas

void reservarPorDestinoFecha(Usuario* u) {
    if (!u) { cout << "Debe iniciar sesion.\n"; return; }

    cout << "Sugerencia: use 'Buscar vuelos' o 'Ordenar' antes de reservar.\n";
    string destino, fecha; int pasajeros;
    cout << "Destino: "; getline(cin, destino);
    cout << "Fecha (YYYY-MM-DD): "; getline(cin, fecha);

    // búsqueda secuencial exacta por (destino, fecha)
    Vuelo* vuelo = nullptr;
    for (auto& v : vuelos)
        if (v.destino == destino && v.fecha == fecha) { vuelo = &v; break; }

    if (!vuelo) { cout << "Vuelo no encontrado.\n"; return; }

    cout << "Cantidad de pasajeros: "; cin >> pasajeros; cin.ignore();
    if (pasajeros <= 0) { cout << "Cantidad invalida.\n"; return; }
    if (vuelo->asientosDisponibles < pasajeros) { cout << "Asientos insuficientes.\n"; return; }

    float precioTotal = vuelo->precioBase * pasajeros;
    if (u->kilometros > 50000) precioTotal *= 0.8f; // 20% descuento

    cout << "\nResumen:\n"; linea();
    printHeaderVuelos(); printVuelo(*vuelo); linea();
    cout << "Pasajeros: " << pasajeros << "\n";
    cout << "Total a pagar: $" << fixed << setprecision(2) << precioTotal << "\n";
    cout << "Confirmar? (s/n): ";
    char c; cin >> c; cin.ignore();
    if (c!='s' && c!='S') { cout << "Reserva cancelada por el usuario.\n"; return; }

    vuelo->asientosDisponibles -= pasajeros;
    u->kilometros += 1000 * pasajeros;
    reservaciones.push_back({u->correo, vuelo->id, pasajeros, precioTotal, u->kilometros});

    cout << "Reservacion exitosa. KM actuales: " << u->kilometros << "\n";
}

void reservarPorIdBinaria(Usuario* u) {
    if (!u) { cout << "Debe iniciar sesion.\n"; return; }
    if (vuelos.empty()) { cout << "No hay vuelos.\n"; return; }

    int id; cout << "ID de vuelo a reservar: "; cin >> id; cin.ignore();

    ordenarVuelosPorId(vuelos);
    int idx = busquedaBinariaPorId(vuelos, id);
    if (idx == -1) { cout << "Vuelo no encontrado.\n"; return; }

    Vuelo& v = vuelos[idx];
    int pasajeros; cout << "Cantidad de pasajeros: "; cin >> pasajeros; cin.ignore();
    if (pasajeros <= 0) { cout << "Cantidad invalida.\n"; return; }
    if (v.asientosDisponibles < pasajeros) { cout << "Asientos insuficientes.\n"; return; }

    float total = v.precioBase * pasajeros;
    if (u->kilometros > 50000) total *= 0.8f;

    cout << "\nResumen:\n"; linea();
    printHeaderVuelos(); printVuelo(v); linea();
    cout << "Pasajeros: " << pasajeros << "\n";
    cout << "Total a pagar: $" << fixed << setprecision(2) << total << "\n";
    cout << "Confirmar? (s/n): ";
    char c; cin >> c; cin.ignore();
    if (c!='s' && c!='S') { cout << "Reserva cancelada.\n"; return; }

    v.asientosDisponibles -= pasajeros;
    u->kilometros += 1000 * pasajeros;
    reservaciones.push_back({u->correo, v.id, pasajeros, total, u->kilometros});
    cout << "Reservacion exitosa. KM actuales: " << u->kilometros << "\n";
}

void verMisReservaciones(Usuario* u) {
    if (!u) { cout << "Debe iniciar sesion.\n"; return; }
    bool hay = false;
    linea(); cout << "=== MIS RESERVACIONES ===\n";
    for (const auto& r : reservaciones) {
        if (r.nombreUsuario == u->correo) {
            hay = true;
            const Vuelo* v = obtenerVueloPorIdLineal(r.idVuelo);
            cout << "Vuelo ID: " << r.idVuelo
                 << " | Destino: " << (v? v->destino : "N/D")
                 << " | Fecha: "   << (v? v->fecha   : "N/D")
                 << " | Pasajeros: " << r.cantidadPasajeros
                 << " | Pagado: $" << fixed << setprecision(2) << r.precioFinal
                 << " | KM actuales: " << r.kmFinales << "\n";
        }
    }
    if (!hay) cout << "No tienes reservaciones.\n";
    linea();
}

void cancelarReservacionUsuario(Usuario* u) {
    if (!u) { cout << "Debe iniciar sesion.\n"; return; }
    int id; cout << "ID del vuelo a cancelar: "; cin >> id; cin.ignore();

    for (size_t i=0; i<reservaciones.size(); ++i) {
        if (reservaciones[i].nombreUsuario == u->correo &&
            reservaciones[i].idVuelo == id) {
            Vuelo* v = obtenerVueloPorIdLineal(id);
            if (v) v->asientosDisponibles += reservaciones[i].cantidadPasajeros;
            reservaciones.erase(reservaciones.begin()+i);
            cout << "Reservacion cancelada.\n";
            return;
        }
    }
    cout << "Reservacion no encontrada.\n";
}

// Listados

void listarTodosLosVuelos() {
    printHeaderVuelos();
    for (const auto& v : vuelos) printVuelo(v);
    linea();
}

// Menús

void menuPublico() {
    cout << "\n=== MENU (PUBLICO) ===\n";
    cout << "1. Agregar usuario\n";
    cout << "2. Iniciar sesion\n";
    cout << "3. Buscar vuelos (destino/fecha)\n";
    cout << "4. Listar todos los vuelos\n";
    cout << "5. Salir\n";
    cout << "Seleccione opcion: ";
}

void menuUsuario() {
    cout << "\n=== MENU (USUARIO) ===\n";
    cout << "1. Buscar vuelos (destino/fecha)\n";
    cout << "2. Listar todos los vuelos\n";
    cout << "3. Ordenar por precio (ascendente)\n";
    cout << "4. Ordenar por fecha  (ascendente)\n";
    cout << "5. Buscar vuelo por ID (binaria)\n";
    cout << "6. Reservar por destino/fecha\n";
    cout << "7. Reservar por ID (binaria)\n";
    cout << "8. Ver mis reservaciones\n";
    cout << "9. Cancelar una reservacion\n";
    cout << "10. Cerrar sesion\n";
    cout << "Seleccione opcion: ";
}

void iniciarSesion() {
    string correo, contrasena;
    cout << "Ingrese correo: "; getline(cin, correo);
    Usuario* u = obtenerUsuario(correo);
    if (!u) { cout << "Usuario no existe.\n"; return; }

    cout << "Ingrese contrasena: "; getline(cin, contrasena);
    if (u->contrasena != contrasena) { cout << "Contrasena incorrecta.\n"; return; }

    usuarioActual = u;
    cout << "Acceso concedido. Bienvenido, " << u->nombre << "!\n";

    int op = 0;
    do {
        menuUsuario();
        cin >> op; cin.ignore();
        switch (op) {
            case 1: buscarVuelosInteractivo(); break;
            case 2: listarTodosLosVuelos(); break;
            case 3: ordenarVuelosPorPrecio(vuelos); break;
            case 4: ordenarVuelosPorFecha(vuelos); break;
            case 5: buscarPorIdBinariaInteractivo(); break;
            case 6: reservarPorDestinoFecha(usuarioActual); break;
            case 7: reservarPorIdBinaria(usuarioActual); break;
            case 8: verMisReservaciones(usuarioActual); break;
            case 9: cancelarReservacionUsuario(usuarioActual); break;
            case 10: cerrarSesion(); break;
            default: cout << "Opcion no valida.\n";
        }
    } while (usuarioActual != nullptr);
}

// main

int main() {
    inicializarVuelos();

    int opcion;
    while (true) {
        menuPublico();
        cin >> opcion; cin.ignore();

        switch (opcion) {
            case 1: agregarUsuario(); break;
            case 2: iniciarSesion(); break;
            case 3: buscarVuelosInteractivo(); break;
            case 4: listarTodosLosVuelos(); break;
            case 5: cout << "Saliendo...\nHasta luego!!!"; return 0;
            default: cout << "Opcion no valida.\n";
        }
    }
}

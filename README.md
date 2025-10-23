# Reservación de vuelos
Autor: Héctor Alejandro Barrón Tamayo

Proyecto de consola para gestionar búsqueda, ordenamiento y reservaciones de vuelos. Maneja usuarios con acumulación de kilómetros, aplica descuentos y diferencia entre menú público y menú de usuario tras iniciar sesión.

## Avance de proyecto
### Estructuras y datos
- **Usuario:** nombre, correo, contraseña, kilómetros.
- **Vuelo:** id, destino, fecha (YYYY-MM-DD), asientos disponibles, precio base, duración, km, datos del avión.
- **Reservación:** correo del usuario, id de vuelo, pasajeros, precio final, km acumulados.
> Los vuelos se inicializan en memoria al arrancar el programa, no se requieren archivos externos.

### Funcionalidad actual
- **Búsqueda** (lineal) por destino y/o fecha (opcionales).
- **Listados** tabulares de vuelos.
- **Ordenamientos** con `std::sort`:
  - Por **precio** (ascendente).
  - Por **fecha** (ascendente).
- **Búsqueda binaria por ID** (O(log n)) previa ordenación por ID.
- **Autenticación** con menú diferenciado y flujo de compra:
  - Reservar por destino/fecha o por ID.
  - Confirmación de compra, ver/cancelar reservaciones, descuento 20% si km > 50,000.

### Retroalimentación atendida
1. Se puede **buscar** antes de reservar.
2. **Menú de usuario** distinto al público (flujo claro).

---

## Uso del programa
1. **Compilar y ejecutar**
   ```bash
   g++ -std=c++17 main.cpp -o vuelos
   ./vuelos

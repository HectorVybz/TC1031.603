# Reservación de vuelos
**Autor:** Héctor Alejandro Barrón Tamayo  
**Proyecto:** Sistema de reservación de vuelos  
**Materia:** Programación de estructuras de datos y algoritmos fundamentales (Avance 1)  
**Fecha:** Septiembre 2025  

El proyecto permite gestionar un sistema de reservaciones aéreas desde consola.  
Incluye registro de usuarios, inicio de sesión, búsqueda y ordenamiento de vuelos, compra con descuento y manejo de reservaciones.  
Los datos se almacenan en memoria y el usuario puede acceder a menús distintos dependiendo si está autenticado o no.

---

## Descripción general del funcionamiento

- **Usuarios**: nombre, correo, contraseña, kilómetros acumulados.  
- **Vuelos**: id, destino, fecha (YYYY-MM-DD), asientos disponibles, precio, duración, kilómetros y datos del avión.  
- **Reservaciones**: correo del usuario, id del vuelo, pasajeros, precio final, kilómetros acumulados.

### Flujo del programa
1. En el menú público se puede registrar usuario, iniciar sesión, buscar vuelos o listarlos.  
2. Al iniciar sesión, se muestra un menú de usuario con opciones para:
   - Buscar vuelos (por destino y/o fecha)
   - Ordenar por precio o por fecha
   - Buscar por ID (binaria)
   - Reservar vuelo (por destino/fecha o por ID)
   - Ver y cancelar reservaciones
3. Se aplica **descuento del 20%** si el usuario acumula más de 50 000 km.  
4. Se actualizan los asientos y los kilómetros después de cada compra.  

---

## SICT0301B: Evalúa los componentes

### Presenta casos de prueba correctos y completos

Se probaron las siguientes funcionalidades:
- **Registro e inicio de sesión**: se validó que no se puedan registrar usuarios duplicados.  
- **Búsqueda lineal por destino y/o fecha**: verifica resultados correctos con entradas vacías o parciales.  
- **Ordenamiento de vuelos** por precio y fecha, confirmando salida ascendente.  
- **Búsqueda binaria por ID**: localiza vuelos en `O(log n)` después de ordenar.  
- **Reservación y cancelación**: valida descuento, disponibilidad y actualización de asientos/kilómetros.

---

### Análisis de complejidad

| Operación | Descripción | Complejidad temporal | Complejidad espacial |
|------------|--------------|----------------------|----------------------|
| **Búsqueda secuencial** | Comparación por destino y/o fecha | O(n) | O(1) |
| **Búsqueda binaria por ID** | Divide el vector ordenado | O(log n) | O(1) |
| **Ordenamiento (`std::sort`)** | Usa *introsort* (mezcla quicksort, heapsort e insertion sort) | O(n log n) | O(log n) |
| **Reservar/cancelar** | Localiza vuelo + actualización | O(log n) + O(1) | O(1) |
| **Listar todos** | Muestra tabla completa | O(n) | O(1) |

**Análisis detallado de `std::sort`:**
- Basado en **introsort**, que combina:
  - **Quicksort** (caso promedio rápido)
  - **Heapsort** (respaldo en caso desfavorable)
  - **Insertion sort** (subarreglos pequeños)
- Promedio y peor caso: `O(n log n)`  
- Estable: (no estable)  
- In-place: (`O(log n)` de espacio)

---

## SICT0302B: Toma decisiones

### Selecciona y usa estructuras adecuadas
- **`std::vector`**: principal para almacenar usuarios, vuelos y reservaciones.  
  Permite acceso aleatorio `O(1)` y compatibilidad directa con `std::sort`.  
- **`std::map` / `std::set` (a futuro)**: planeadas para búsquedas más rápidas o categorías únicas.  

### Selecciona un algoritmo de ordenamiento adecuado
- Elegí `std::sort` en lugar de algoritmos simples (Selection o Bubble Sort `O(n²)`) porque necesito eficiencia con listas de vuelos que crecen dinámicamente.  
- **Comparativa**:  
  - Selection/Insertion Sort → lentos (`O(n²)`)  
  - Merge Sort → estable pero usa más memoria  
  - **Introsort (`std::sort`)** → mejor rendimiento práctico `O(n log n)` y adaptable a cualquier tamaño.

### Justificación de decisiones
- El menú diferenciado (público / usuario) mejora la experiencia del flujo lógico: **explorar → decidir → reservar**.  
- Las funciones de reserva y cancelación integran validaciones de negocio (asientos, descuentos, confirmación).  
- El uso de memoria se mantiene bajo al evitar estructuras redundantes o duplicadas.  

---

## SICT0303B: Implementa acciones científicas

### Implementa mecanismos de consulta útiles
- **Buscar vuelos:** filtra dinámicamente por destino/fecha.  
- **Ordenar vuelos:** muestra resultados inmediatos organizados.  
- **Ver reservaciones:** lista vuelos reservados por cada usuario.

### Implementa mecanismos de almacenamiento adecuados
- Los vuelos se **inicializan en memoria** mediante `inicializarVuelos()` sin necesidad de archivos externos.  
- Se propone agregar persistencia en formato `.csv` o `.json` en un siguiente avance.

### Implementa validaciones correctas
- Validación de entradas (asientos > 0, usuario existente).  
- Confirmación antes de compra/cancelación.  
- Actualización automática de kilómetros acumulados.

---

## Próximas mejoras

1. Modularizar completamente el programa en archivos `.h` y `.cpp`.  
2. Sustituir variables globales por una clase `FlightApp`.  
3. Implementar persistencia (guardar usuarios y reservaciones).  
4. Ampliar filtros: búsqueda por rango de fechas o precios.  

---

## Ejecución

```bash
g++ -std=c++17 main.cpp -o vuelos
./vuelos

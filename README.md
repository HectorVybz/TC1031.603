# Reservación de vuelos  
**Autor:** Héctor Alejandro Barrón Tamayo  
**Proyecto:** Sistema de reservación de vuelos  
**Materia:** Programación de estructuras de datos y algoritmos fundamentales (Avance 1)  
**Fecha:** Octubre 2025  

El proyecto implementa un sistema de **gestión de vuelos** desde consola, con funciones para **buscar, ordenar y consultar** información de vuelos disponibles.  
Los datos se almacenan en memoria, sin necesidad de archivos externos, y el diseño modular permite escalar el proyecto para incluir más funciones (reservaciones, usuarios, persistencia, etc.).  

---

## Descripción general del funcionamiento

- **Vuelos:** id, destino, fecha (YYYY-MM-DD), asientos disponibles, precio base, duración, kilómetros y datos del avión (modelo, fabricante, capacidad).  

El programa se divide en dos archivos:
- `vuelos.h` → contiene las estructuras, ordenamientos, búsquedas y utilidades de impresión.  
- `main.cpp` → implementa el menú principal y la interacción con el usuario.  

### Flujo del programa
1. El programa carga los vuelos en memoria con `inicializarVuelos()`.  
2. Desde el menú, el usuario puede:
   - Ordenar por precio, fecha o ID.  
   - Buscar vuelos por destino y/o fecha (con listados de opciones disponibles).  
   - Buscar un vuelo específico por ID (búsqueda binaria).  
   - Listar todos los vuelos disponibles.  
3. Los resultados se muestran en tablas con formato y alineación.  

---

## SICT0301B: Evalúa los componentes

### Presenta casos de prueba correctos y completos

Se realizaron pruebas sobre todas las funciones principales:
- **Ordenamiento por precio y fecha:** se validó que los resultados aparezcan en orden ascendente.  
- **Búsqueda por destino/fecha:** muestra correctamente los vuelos que coinciden con los criterios.  
- **Búsqueda binaria por ID:** encuentra vuelos de forma rápida en `O(log n)` tras ordenar el vector.  
- **Listado general:** imprime todos los vuelos con formato de tabla.  

También se probó que los listados de destinos y fechas se muestren antes de las búsquedas, mejorando la experiencia del usuario.

---

### Análisis de complejidad

| Operación | Descripción | Complejidad temporal | Complejidad espacial |
|------------|--------------|----------------------|----------------------|
| **Búsqueda secuencial** | Filtrado por destino/fecha | O(n) | O(1) |
| **Búsqueda binaria por ID** | Vector previamente ordenado | O(log n) | O(1) |
| **Ordenamiento (`std::sort`)** | Usa *Introsort* (mezcla quicksort, heapsort e insertion sort) | O(n log n) | O(log n) |
| **Listar vuelos** | Imprime todos los registros | O(n) | O(1) |

**Análisis detallado de `std::sort`:**
- Basado en **Introsort**, que combina:
  - **Quicksort** (rápido en promedio)  
  - **Heapsort** (respaldo en caso desfavorable)  
  - **Insertion sort** (subarreglos pequeños)  
- Complejidad promedio y peor caso: `O(n log n)`  
- No estable (puede reordenar iguales)  
- In-place (`O(log n)` de espacio adicional)

---

## 💡 SICT0302B: Toma decisiones

### Selecciona y usa estructuras adecuadas
- **`std::vector`**: estructura principal para almacenar los vuelos.  
  Permite acceso aleatorio en `O(1)` y compatibilidad directa con algoritmos STL.  

### Selecciona un algoritmo de ordenamiento adecuado
- Elegí `std::sort` sobre algoritmos básicos (como Selection o Bubble Sort `O(n²)`) por su eficiencia y optimización.  
- **Comparativa de alternativas:**  
  - *Bubble/Selection Sort* → lentos en grandes conjuntos (`O(n²)`)  
  - *Merge Sort* → estable, pero usa más memoria  
  - **`std::sort` (Introsort)** → mejor rendimiento práctico, adaptable a cualquier tamaño  

### Justificación de decisiones
- El diseño modular con header (`vuelos.h`) y fuente (`main.cpp`) mejora la organización y legibilidad.  
- Se agregaron listados previos de **destinos y fechas** para que el usuario no necesite recordar los valores exactos.  
- Se minimiza el uso de memoria extra, trabajando directamente sobre estructuras dinámicas (`std::vector`).  

---

##  SICT0303B: Implementa acciones científicas

### Implementa mecanismos de consulta útiles
- **Ordenar vuelos:** por precio o fecha de forma ascendente.  
- **Buscar vuelos:** por destino y/o fecha (filtros flexibles).  
- **Buscar por ID:** búsqueda binaria rápida.  
- **Listar todos los vuelos:** despliega tabla con formato y alineación.

### Implementa mecanismos de almacenamiento adecuados
- Los datos se **inicializan en memoria** con `inicializarVuelos()` al arrancar el programa.  
- No se requieren archivos externos, pero se deja abierta la posibilidad de agregar persistencia (`.csv` o `.json`) en siguientes avances.  

### Implementa validaciones correctas
- Control de entradas vacías o inválidas.  
- Validación en búsquedas (vuelos no encontrados).  
- Menú interactivo con opciones controladas para evitar errores de ejecución.  

---

## Próximas mejoras

1. Agregar manejo de usuarios y reservaciones (inicio de sesión, acumulación de kilómetros, descuentos).  
2. Implementar persistencia en archivos externos (`.csv` o `.json`).  
3. Incluir más filtros (por rango de fechas, precio máximo o duración).  
4. Modularizar aún más el código creando clases separadas (`Vuelo`, `Usuario`, `Reservacion`).  

---

## Ejecución

Compilar y ejecutar con:
```bash
g++ -std=c++17 main.cpp -o vuelos
./vuelos

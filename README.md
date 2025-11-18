# Sistema de Gestión de Vuelos  
**Autor:** Héctor Alejandro Barrón Tamayo – A01713794  
**Fecha:** 16/11/2025  

Este proyecto permite almacenar, ordenar y acceder a datos de vuelos de una aerolínea.  
Cada vuelo incluye un **ID, destino, fecha, asientos disponibles, precio base, duración estimada, kilómetros de viaje y datos del avión** (modelo, fabricante y capacidad).  
El objetivo es organizar la información de forma eficiente y poder consultarla según diferentes criterios.

---

## Descripción del avance del proyecto

### Funcionalidad principal

El programa carga la información de los vuelos desde un archivo **`vuelos.csv`**  
(que puede generarse exportando una hoja de Excel a CSV), donde cada línea contiene un vuelo con los campos:

```
id,destino,fecha,asientos,precio,duracion,km,modelo,fabricante,capacidad
```

### Ejemplo:

```
1,Londres,2025-07-01,120,680.0,10.0,8900,Boeing 787,Boeing,250
2,Sidney,2025-07-03,110,1450.0,17.0,15000,Airbus A380,Airbus,500
3,Toronto,2025-07-05,140,720.0,9.0,7600,Boeing 777,Boeing,300
```

Los datos de los vuelos se guardan en un **`std::list<Vuelo>`**, una estructura dinámica que permite almacenar registros de forma flexible y recorrerlos con iteradores para ordenarlos o buscarlos fácilmente.

---

## Opciones disponibles en el menú principal

### **1. Ordenar por precio (lista)**  
Ordena la lista de vuelos de menor a mayor precio utilizando `list::sort()`  
y muestra los resultados en una tabla.

### **2. Ordenar por fecha (lista)**  
Ordena los vuelos cronológicamente por fecha (`YYYY-MM-DD`) y los muestra en pantalla.

### **3. Buscar por ID (búsqueda binaria)**  
Crea una copia de la lista en un `std::vector`, lo ordena con `std::sort()` (Introsort)  
y realiza una búsqueda binaria para encontrar el vuelo solicitado.

### **4. Buscar por destino/fecha**  
Filtra vuelos por destino, fecha o ambos utilizando búsqueda secuencial.

### **5. Listar todos los vuelos**  
Imprime todos los vuelos en un formato tabular alineado.

### **6. Guardar vuelos en CSV y salir**  
Escribe todos los datos actuales al archivo `vuelos.csv` y finaliza el programa.

---

## Instrucciones de uso

1. Colocar el archivo `vuelos.csv` en la misma carpeta que `main.cpp` y `vuelos.h`.  
   El formato debe ser:

```
id,destino,fecha,asientos,precio,duracion,km,modelo,fabricante,capacidad
```

2. Compilar:

```bash
g++ -std=c++17 main.cpp -o vuelos
```

3. Ejecutar:

```bash
./vuelos
```

4. Seleccionar una opción del menú y seguir las instrucciones.  
   La opción **6** guarda los datos en el CSV.

---

# SICT0301: Evalúa los componentes

## Análisis de complejidad

### **Estructura principal: `std::list<Vuelo>`**

| Operación                        | Tiempo | Espacio |
|----------------------------------|--------|---------|
| Inserción al inicio/fin         | O(1)   | O(1)    |
| Eliminación al inicio/fin       | O(1)   | O(1)    |
| Recorrido completo              | O(n)   | O(1)    |
| Acceso por posición (recorrido) | O(n)   | O(1)    |

---

## Ordenamiento de la lista — `std::list::sort()`  
Implementa internamente **Merge Sort**:

| Algoritmo  | Mejor caso | Promedio | Peor caso |
|------------|------------|----------|-----------|
| Merge Sort | O(n log n) | O(n log n) | O(n log n) |

✔ Estable  
✔ No requiere memoria adicional grande  
✔ Ideal para listas enlazadas  

Se usa en:

- `ordenarPorPrecio()`
- `ordenarPorFecha()`

---

## Ordenamiento y búsqueda por ID — `std::sort` + binaria

1. Copia la lista a un vector → **O(n)**  
2. Ordena con `std::sort()` (Introsort) → **O(n log n)**  
3. Búsqueda binaria → **O(log n)**  

### Introsort combina:

| Algoritmo     | Mejor caso | Promedio | Peor caso |
|---------------|------------|----------|-----------|
| Quicksort     | O(n log n) | O(n log n) | O(n²)    |
| Heapsort      | O(n log n) | O(n log n) | O(n log n) |
| InsertionSort | O(n)       | O(n²)     | O(n²)    |

**Resultado final de std::sort → `O(n log n)` garantizado**

---

## Búsquedas

| Tipo            | Método                         | Mejor | Promedio | Peor |
|-----------------|--------------------------------|--------|----------|------|
| ID              | Binaria                        | O(1)   | O(log n) | O(log n) |
| Destino/fecha   | Secuencial                     | O(1)   | O(n)     | O(n) |

---

## Complejidad final del programa

### **Mejor caso**
Solo lectura y listado → **O(n)**

### **Caso promedio**
Un ordenamiento + filtros → **O(n log n)**

### **Peor caso**
Múltiples ordenamientos y búsquedas → **O(n log n)**

---

# SICT0302: Toma decisiones

## Selección de estructura: `std::list<Vuelo>`

- Estructura dinámica avanzada (cumple requisito del profesor)  
- Inserciones/eliminaciones O(1)  
- Recorridos secuenciales eficientes  
- Perfecta para Merge Sort de `list::sort()`  

### Comparación con otras estructuras
- `vector` → inserciones O(n)  
- `deque` → no ideal para inserciones intermedias  
- `list` → la más flexible para este proyecto  

---

## Selección de algoritmos de ordenamiento

### 1. `list::sort()`  
- Merge Sort  
- O(n log n) siempre  
- Estable  

### 2. `std::sort()` en vector  
- Introsort  
- O(n log n)  
- Ideal para búsqueda binaria  

---

# SICT0303: Acciones científicas

### Consultas implementadas
- Ordenamiento por precio  
- Ordenamiento por fecha  
- Búsqueda por ID  
- Filtro por destino/fecha  
- Listado tabular  

### Lectura de CSV  
`cargarVuelosCSV()`:
- Usa `getline`,  
- Parsea con `stringstream`,  
- Convierte campos numéricos,  
- Carga en `std::list<Vuelo>`.

### Escritura de CSV  
`guardarVuelosCSV()`:
- Recorre la lista  
- Escribe cada vuelo en formato CSV

---


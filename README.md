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

El análisis de complejidad del proyecto se desglosa en cada módulo del sistema.  
Cada tabla presenta explícitamente **mejor caso**, **caso promedio** y **peor caso**, incluso cuando coinciden.

---

# **1. Complejidad de la estructura principal — `std::list<Vuelo>`**

| Operación                              | Mejor caso | Caso promedio | Peor caso |
|----------------------------------------|------------|---------------|-----------|
| Inserción al inicio/fin                | O(1)       | O(1)          | O(1)      |
| Eliminación al inicio/fin              | O(1)       | O(1)          | O(1)      |
| Acceso a un elemento (recorriendo)     | O(1)       | O(n)          | O(n)      |
| Recorrido completo de la lista         | O(n)       | O(n)          | O(n)      |

---

# **2. Ordenamiento de la lista — `list::sort()` (Merge Sort)**

| Algoritmo  | Mejor caso | Caso promedio | Peor caso |
|------------|------------|---------------|-----------|
| Merge Sort | O(n log n) | O(n log n)    | O(n log n)|

---

# **3. Ordenamiento y búsqueda binaria por ID (`std::sort()` + vector)**

### 3.1 Copiar la lista al vector

| Operación | Mejor caso | Caso promedio | Peor caso |
|-----------|------------|---------------|-----------|
| Copia de lista a vector | O(n) | O(n) | O(n) |

### 3.2 Ordenamiento del vector (`std::sort()` — Introsort)

| Algoritmo  | Mejor caso | Caso promedio | Peor caso |
|------------|------------|---------------|-----------|
| Introsort  | O(n log n) | O(n log n)    | O(n log n)|

### 3.3 Búsqueda binaria

| Operación | Mejor caso | Caso promedio | Peor caso |
|-----------|------------|---------------|-----------|
| Búsqueda binaria | O(1) | O(log n) | O(log n) |

**Complejidad total:**  
O(n log n)

---

# **4. Búsqueda por destino y/o fecha**

| Operación | Mejor caso | Caso promedio | Peor caso |
|-----------|------------|---------------|-----------|
| Búsqueda secuencial | O(1) | O(n) | O(n) |

---

# **5. Lectura del archivo CSV (`cargarVuelosCSV`)**

### Complejidad por operación interna:

| Suboperación | Complejidad |
|--------------|-------------|
| Leer línea | O(1) |
| Separar campos | O(1) |
| Convertir valores | O(1) |
| Insertar a lista | O(1) |

### Complejidad total:

| Operación | Mejor caso | Caso promedio | Peor caso |
|-----------|------------|---------------|-----------|
| Lectura CSV | O(n) | O(n) | O(n) |

---

# **6. Escritura del archivo CSV (`guardarVuelosCSV`)**

| Operación | Mejor caso | Caso promedio | Peor caso |
|-----------|------------|---------------|-----------|
| Escritura CSV | O(n) | O(n) | O(n) |

---

# **7. Complejidad total del programa**

| Escenario | Complejidad | Explicación |
|-----------|-------------|-------------|
| Mejor caso | O(n) | Solo lectura y listado |
| Caso promedio | O(n log n) | Un ordenamiento + búsquedas |
| Peor caso | O(n log n) | Múltiples ordenamientos |

---

# SICT0302: Toma decisiones

(… contenido que generamos antes …)

---

# SICT0303: Acciones científicas

(… contenido que generamos antes …)


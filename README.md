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

El análisis de complejidad del proyecto se realiza considerando los algoritmos y estructuras de datos utilizadas, evaluando **mejor caso**, **caso promedio** y **peor caso** según corresponda. El objetivo es justificar formalmente el desempeño del sistema bajo diferentes patrones de uso.

---

## **1. Estructura principal: `std::list<Vuelo>`**

`std::list` es una lista doblemente enlazada. Su comportamiento temporal es:

| Operación                        | Mejor | Promedio | Peor |
|----------------------------------|--------|----------|---------|
| Inserción al inicio/fin         | O(1)   | O(1)     | O(1)    |
| Eliminación al inicio/fin       | O(1)   | O(1)     | O(1)    |
| Recorrido completo              | O(n)   | O(n)     | O(n)    |
| Acceso por posición (recorrido) | O(n)   | O(n)     | O(n)    |

Esta estructura es adecuada para almacenar y recorrer vuelos sin necesidad de acceso aleatorio directo.

---

## **2. Ordenamientos con `std::list::sort()` (Merge Sort)**

La lista se ordena con su método interno `.sort()`, que implementa **Merge Sort estable**.  
Su complejidad es:

| Caso | Complejidad |
|------|-------------|
| Mejor caso | **O(n log n)** |
| Caso promedio | **O(n log n)** |
| Peor caso | **O(n log n)** |

Merge Sort mantiene esta complejidad en todos los escenarios porque siempre divide la lista en mitades y realiza fusiones lineales.

Se utiliza para:

- `ordenarPorPrecio()`  
- `ordenarPorFecha()`

---

## **3. Ordenamiento y búsqueda binaria (`std::sort()` + vector temporal)**

Para buscar por ID se realiza:

1) Copiar la lista al vector  
**O(n)**  

2) Ordenar el vector con `std::sort()`  
(`std::sort()` usa **Introsort**: combinación de QuickSort, HeapSort y InsertionSort adaptativo)  

| Caso | Complejidad |
|------|-------------|
| Mejor caso | **O(n log n)** |
| Promedio | **O(n log n)** |
| Peor caso | **O(n log n)** |

> Gracias a Introsort, el programa nunca cae en O(n²) en el peor caso.

3) Búsqueda binaria  
| Caso | Complejidad |
|------|-------------|
| Mejor | **O(1)** |
| Promedio | **O(log n)** |
| Peor | **O(log n)** |

---

## **4. Búsqueda secuencial por destino/fecha**

Se revisa cada elemento de la lista una vez.

| Caso | Complejidad |
|------|-------------|
| Mejor caso | **O(1)** (primer elemento coincide) |
| Promedio | **O(n)** |
| Peor caso | **O(n)** |

---

## **5. Lectura y escritura del archivo CSV**

Estas funciones procesan cada vuelo una sola vez.

### Lectura (`cargarVuelosCSV()`)
- Leer línea → O(1)  
- Parsear → O(1)  
- Insertar en lista → O(1)  

Total por n vuelos: **O(n)**

### Escritura (`guardarVuelosCSV()`)
Recorrido lineal de toda la lista → **O(n)**

---

## **6. Complejidad total del sistema**

Las operaciones del sistema dependen de las acciones del usuario, pero la operación más costosa es siempre el **ordenamiento**, ya sea sobre lista o sobre vector:

T(n) = **O(n log n)**

Escenarios:

### **Mejor caso**
El usuario solo realiza:  
- Lectura del CSV  
- Listado de vuelos  

T(n) = **O(n)**

### **Caso promedio**
El usuario realiza un ordenamiento + filtrado/búsqueda:  

T(n) = **O(n log n)**

### **Peor caso**
El usuario invoca múltiples ordenamientos + búsquedas en la misma sesión:

T(n) = **O(n log n)**



# SICT0302: Toma decisiones

En esta sección justifico las decisiones sobre **estructuras de datos** y **algoritmos de ordenamiento** utilizadas en el sistema.

## Selección de estructura: `std::list<Vuelo>`

La estructura principal del programa es `std::list<Vuelo>`, una lista doblemente enlazada. Se eligió por las siguientes razones:

- Es una estructura **dinámica**: no necesito conocer de antemano el número de vuelos.
- Inserciones y eliminaciones al inicio/fin en **O(1)**.
- Recorridos secuenciales eficientes para listar, filtrar y ordenar.
- Compatible con `list::sort()` (Merge Sort estable).

### Comparación con otras estructuras
- `vector` → inserciones O(n).  
- `deque` → no ideal para inserciones intermedias.  
- `list` → la más adecuada para ordenamientos y recorridos frecuentes.

---

## Selección de algoritmos de ordenamiento

### 1. `list::sort()`  
- Implementa Merge Sort.  
- O(n log n) en todos los casos.  
- Estable y eficiente para listas enlazadas.

### 2. `std::sort()` en vector  
- Implementa Introsort (QuickSort + HeapSort + InsertionSort).  
- O(n log n) incluso en el peor caso.  
- Ideal para búsquedas binarias posteriores.



# SICT0303: Acciones científicas

Esta sección describe los mecanismos concretos que permiten consultar y manipular la información en el programa.

---

## Mecanismos para consultar información

- `listarVuelos()` → recorre la lista y muestra los vuelos. O(n).
- `ordenarPorPrecio()` → Merge Sort interno de la lista. O(n log n).
- `ordenarPorFecha()` → igual que el anterior.
- `busquedaBinariaPorId()` → copia a vector, ordena con std::sort y busca. O(n log n).
- `buscarPorDestinoFecha()` → filtrado secuencial. O(n).

---

## Mecanismos de lectura de archivos

### `cargarVuelosCSV()`
- Lee línea por línea.  
- Parsea con stringstream.  
- Crea objetos Vuelo e inserta en la lista.  
- O(n).

---

## Mecanismos de escritura de archivos

### `guardarVuelosCSV()`
- Recorre la lista y escribe cada vuelo en formato CSV.  
- O(n).

---

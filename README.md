#Sistema de Gestión de Vuelos
Héctor Alejandro Barrón Tamayo – A01713794
Fecha: 16/11/2025

Este proyecto permite almacenar, ordenar y acceder a datos de vuelos de una aerolínea.
Cada vuelo incluye un ID, un destino, una fecha, asientos disponibles, precio base,
duración estimada, kilómetros de viaje y los datos del avión (modelo, fabricante y capacidad).
El objetivo es organizar la información de forma eficiente y poder consultarla según
diferentes criterios.

##Descripción del avance del proyecto
###Funcionalidad principal
El programa carga la información de los vuelos desde un archivo vuelos.csv
(que puede generarse exportando una hoja de Excel a CSV), donde cada línea contiene
un vuelo con los siguientes campos:

id,destino,fecha,asientos,precio,duracion,km,modelo,fabricante,capacidad

Ejemplo:

1,Londres,2025-07-01,120,680.0,10.0,8900,Boeing 787,Boeing,250
2,Sidney,2025-07-03,110,1450.0,17.0,15000,Airbus A380,Airbus,500
3,Toronto,2025-07-05,140,720.0,9.0,7600,Boeing 777,Boeing,300

Los datos de los vuelos se guardan en un std::list<Vuelo>, una estructura dinámica que
permite almacenar de manera flexible los registros y recorrerlos con iteradores para
ordenarlos y consultarlos de diferentes formas.

###Opciones disponibles en el menú principal

1. Ordenar por precio (lista)
   Ordena la lista de vuelos de menor a mayor precio utilizando list::sort()
   y muestra el resultado en formato de tabla.

2. Ordenar por fecha (lista)
   Ordena los vuelos cronológicamente por fecha (YYYY-MM-DD) y los muestra
   en pantalla.

3. Buscar por ID (búsqueda binaria sobre copia ordenada)
   Crea una copia de los vuelos en un std::vector, la ordena por ID usando std::sort()
   (Introsort) y realiza una búsqueda binaria para localizar un vuelo específico.

4. Buscar por destino/fecha
   Permite filtrar vuelos por destino, por fecha o por ambos criterios a la vez
   usando una búsqueda secuencial.

5. Listar todos los vuelos
   Muestra todos los vuelos en una tabla con columnas: ID, fecha, destino,
   asientos disponibles, precio y modelo del avión.

6. Guardar vuelos en CSV y salir
   Escribe todos los vuelos actuales en el archivo vuelos.csv y termina
   la ejecución del programa.

##Instrucciones de uso

1. Colocar el archivo vuelos.csv en la misma carpeta donde están main.cpp y vuelos.h.
   El archivo debe seguir el formato:

   id,destino,fecha,asientos,precio,duracion,km,modelo,fabricante,capacidad

2. Compilar el programa:

   g++ -std=c++17 main.cpp -o vuelos

3. Ejecutar el programa:

   ./vuelos

4. Seleccionar una opción del menú principal e ingresar los valores solicitados
   (ID, destino, fecha, etc.). Al elegir la opción 6 se guardan los datos en el CSV.

##SICT0301: Evalúa los componentes

###Análisis de complejidad

####Estructura de datos principal: std::list<Vuelo>

Operación                        Complejidad temporal   Complejidad espacial
Inserción al inicio/fin         O(1)                   O(1)
Eliminación al inicio/fin       O(1)                   O(1)
Recorrido completo              O(n)                   O(1)
Acceso por posición (recorrido) O(n)                   O(1)

####Ordenamiento de la lista (std::list::sort – Merge Sort)

std::list::sort() implementa una variante de Merge Sort estable sobre listas enlazadas:

Algoritmo     Mejor caso       Caso promedio      Peor caso
Merge Sort    O(n log n)       O(n log n)         O(n log n)

####Propiedades relevantes:

- Estable (no cambia el orden relativo de elementos con claves iguales).
- No requiere almacenamiento adicional grande, ya que reacomoda punteros de la lista.
- Complejidad de tiempo O(n log n) en todos los casos.

####Esta función se usa en:

- ordenarPorPrecio() → ordena la lista por precio base.
- ordenarPorFecha() → ordena la lista por fecha.

####Ordenamiento y búsqueda para el ID (std::sort + búsqueda binaria)

Para la opción “Buscar por ID” se realiza:

1. Copia de la lista a un std::vector<Vuelo> → O(n) tiempo, O(n) espacio.
2. Ordenamiento del vector con std::sort() → utiliza Introsort internamente.
3. Búsqueda binaria sobre el vector ordenado → O(log n).

####Introsort combina tres algoritmos:

Algoritmo     Mejor caso       Caso promedio      Peor caso
Quicksort     O(n log n)       O(n log n)         O(n^2)
Heapsort      O(n log n)       O(n log n)         O(n log n)
InsertionSort O(n)             O(n^2)             O(n^2)

Introsort inicia con Quicksort y, cuando la profundidad de recursión se vuelve grande,
cambia a Heapsort para garantizar que el peor caso sea O(n log n). En subarreglos muy
pequeños usa InsertionSort para optimizar el rendimiento.

Por lo tanto, la complejidad final de std::sort es:

- Mejor caso:    O(n log n)
- Caso promedio: O(n log n)
- Peor caso:     O(n log n)

####Búsquedas

Tipo                  Método                         Mejor   Promedio   Peor
Por ID de vuelo       Binaria sobre vector ordenado  O(1)    O(log n)  O(log n)
Por destino/fecha     Secuencial en la lista         O(1)    O(n)      O(n)

La búsqueda secuencial es adecuada cuando se permite filtrar por varios criterios
(destino y/o fecha) sin necesidad de ordenar previamente la estructura.

####Complejidad final del programa

Considerando las operaciones principales:

- Lectura de vuelos desde el CSV → O(n)
- Escritura en el CSV (guardar) → O(n)
- Recorridos para listar y filtrar → O(n)
- Ordenamientos de la lista (Merge Sort) → O(n log n)
- Búsqueda por ID (copia + sort + binaria) → O(n log n)

Mejor caso:
~ Solo lectura del archivo y listado simple de vuelos.
Complejidad aproximada: O(n)

Caso promedio:
~ Una o varias operaciones de ordenamiento y algunas búsquedas secuenciales.
Complejidad aproximada: O(n log n)

Peor caso:
~ Varias operaciones de ordenamiento y múltiples búsquedas por ID y filtrados,
  además de lectura y escritura del archivo.
Todos los algoritmos de ordenamiento utilizados son O(n log n),
por lo que la complejidad final sigue siendo:

O(n log n)

##SICT0302: Toma decisiones

###Selecciona una estructura de datos adecuada al problema y la usa correctamente

Elegí std::list<Vuelo> como estructura principal para almacenar los vuelos porque:

1. Es una estructura dinámica “avanzada”
   A diferencia de un arreglo estático, la lista puede crecer y reducirse en tiempo
   de ejecución sin necesidad de conocer el número de vuelos desde el inicio.

2. Inserciones y eliminaciones en tiempo constante
   std::list permite insertar o eliminar nodos en cualquier posición donde se tenga
   un iterador en tiempo O(1), ya que solo se actualizan punteros.
   Esto es útil para un sistema que, en versiones futuras, podría agregar o cancelar
   vuelos sin reacomodar toda la memoria.

3. Recorridos flexibles con iteradores
   Para ordenar, buscar y listar, es suficiente recorrer los elementos secuencialmente.
   No es necesario acceder por índice, por lo que una lista se adapta bien al tipo de
   operaciones que realiza el programa.

En comparación:

- std::vector<Vuelo> ofrece acceso aleatorio O(1), pero insertar o eliminar en medio
  puede implicar mover muchos elementos (O(n)).
- std::deque<Vuelo> permite inserciones rápidas en ambos extremos, pero no está tan
  orientado a inserciones en posiciones intermedias como la lista.

Para este proyecto, donde se priorizan recorridos secuenciales, ordenamientos y
posible edición futura de vuelos, std::list es una opción adecuada y cumple con el
requerimiento de utilizar una estructura dinámica avanzada.

###Selecciona un algoritmo de ordenamiento adecuado al problema

Se utilizan dos estrategias de ordenamiento:

1. std::list::sort() (Merge Sort) para ordenar la lista directamente
   - Se usa cuando se requiere ordenar por precio o por fecha.
   - Ventajas:
     - Complejidad O(n log n) en todos los casos.
     - Estable: conserva el orden relativo de vuelos con el mismo precio/fecha.
     - No necesita grandes bloques de memoria extra.

2. std::sort() (Introsort) sobre un vector auxiliar para la búsqueda por ID
   - Se crea un std::vector<Vuelo> temporal, se ordena por ID con std::sort()
     y luego se realiza una búsqueda binaria.
   - Ventajas:
     - Excelente rendimiento práctico.
     - Complejidad O(n log n) en el peor caso gracias a la combinación
       Quicksort + Heapsort + InsertionSort.
     - Permite aplicar fácilmente una búsqueda binaria eficiente O(log n).

Comparación con otros algoritmos más simples:

- Bubble Sort, Selection Sort e Insertion Sort tienen complejidad O(n^2)
  en el caso promedio y peor, lo que los hace poco eficientes para listas grandes.
- Merge Sort es estable y siempre O(n log n), pero requiere más cuidado
  para implementarse sobre arreglos; para listas, std::list::sort ya lo ofrece.
- Introsort (std::sort) aprovecha lo mejor de Quicksort, Heapsort e InsertionSort,
  por lo que es una gran opción cuando se trabaja con vectores.

##SICT0303: Implementa acciones científicas

###Implementa mecanismos para consultar información de las estructuras

El programa incluye un menú que permite:

- Ordenar vuelos por precio o por fecha.
- Buscar vuelos por ID con búsqueda binaria.
- Filtrar vuelos por destino, por fecha o por ambos.
- Mostrar todos los vuelos en formato de tabla alineada.

Cada operación está implementada de forma modular en funciones dentro de vuelos.h,
lo que facilita pruebas y mantenimiento.

###Implementa mecanismos de lectura de archivos

La función cargarVuelosCSV:

- Abre el archivo vuelos.csv con ifstream.
- Lee cada línea con std::getline.
- Divide los campos por comas usando std::stringstream.
- Convierte los valores numéricos con std::stoi y std::stof.
- Guarda los registros en un std::list<Vuelo> temporal y luego los asigna
  a la lista principal.

Así, todos los datos quedan cargados en la estructura dinámica antes
de realizar ordenamientos o búsquedas.

###Implementa mecanismos de escritura de archivos para guardar los datos de las estructuras

La función guardarVuelosCSV:

- Abre vuelos.csv con ofstream.
- Recorre la lista de vuelos y escribe cada uno en formato CSV:
  id,destino,fecha,asientos,precio,duracion,km,modelo,fabricante,capacidad
- Se llama al elegir la opción “Guardar vuelos en CSV y salir”.

De esta forma, vuelos.csv actúa como el archivo persistente de la aplicación,
y puede ser abierto o editado desde Excel siempre que se mantenga el formato.

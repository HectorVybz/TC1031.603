# Reservación de vuelos

Es un proyecto de consola para gestionar búsqueda, ordenamiento y reservaciones de vuelos. Maneja usuarios con acumulación de kilómetros, aplica descuentos y diferencia entre menú público y menú de usuario tras iniciar sesión.

## Avance de proyecto
### Estructuras y datos

Usuario: nombre, correo, contraseña, kilómetros.

Vuelo: id, destino, fecha (YYYY-MM-DD), asientos disponibles, precio base, duración, km y datos del avión.

Reservación: correo del usuario, id de vuelo, pasajeros, precio final, km acumulados.

Los vuelos se inicializan en memoria al arrancar el programa (inicializarVuelos()), por lo que no necesitas archivos externos.

### Búsquedas y ordenamientos

Buscar vuelos (filtro) por destino y/o fecha (ambos opcionales).
Muestra tabla con ID, fecha, destino, asientos y precio.

Ordenar vuelos con std::sort:

Por precio (ascendente).

Por fecha (ascendente).

Búsqueda binaria por ID: se ordena por ID y se localiza el vuelo en O(log n).
Permite también reservar por ID directamente.

### Inicio de sesión con menú distinto

Tras validar credenciales, el sistema muestra un menú de usuario diferente al público:

Buscar vuelos

Listar todos los vuelos

Ordenar por precio

Ordenar por fecha

Buscar por ID (binaria)

Reservar por destino/fecha

Reservar por ID (binaria)

Ver mis reservaciones

Cancelar reservación

Cerrar sesión

Retroalimentación atendida:
(1) Se puede buscar antes de reservar.
(2) Menú distinto al ingresar (flujo de usuario claro).

### Reglas de negocio y validaciones

Confirmación de compra con resumen previo (vuelo, pasajeros, total).

Verificación de asientos y entradas válidas.

Descuento del 20% cuando el usuario tiene > 50,000 km.

Actualización de asientos y kilómetros al confirmar.

## Menú
### Menú público

Agregar usuario

Iniciar sesión

Buscar vuelos (destino/fecha)

Listar todos los vuelos

Salir

### Menú de usuario (después de iniciar sesión)

Buscar vuelos (destino/fecha)

Listar todos los vuelos

Ordenar por precio (asc)

Ordenar por fecha (asc)

Buscar vuelo por ID (binaria)

Reservar por destino/fecha

Reservar por ID (binaria)

Ver mis reservaciones

Cancelar una reservación

Cerrar sesión

## Uso del programa

1) Compilar y ejecutar
Compila con g++ y ejecuta el binario. No requiere archivos CSV.

2) Flujo sugerido

En el menú público:

(1) Agregar usuario (si no existe).

(2) Iniciar sesión con correo y contraseña.

En el menú de usuario:

(1)/(2) Explora vuelos (búsqueda/listado).

(3)/(4) Ordena por precio o por fecha.

(5) Busca por ID (binaria) y revisa los detalles.

(6) o (7) Reserva (por destino/fecha o por ID).

(8) Consulta tus reservaciones; (9) cancela si es necesario.

(10) Cierra sesión.

3) Ejemplos rápidos

Ordenar por precio → muestra todos los vuelos ascendentes por costo.

Buscar por ID (binaria) → ingresa un ID (ej. 4) y se imprime ese vuelo.

Reservar por ID → ingresa el ID y la cantidad de pasajeros; confirma el resumen para completar.

## Cómo cumplo los indicadores de sub-competencias
### SICT0301: Evalúa los componentes

### Análisis de complejidad (tiempo):

Ordenar por precio/fecha (std::sort): O(n log n) en promedio y peor caso (introsort: mezcla quicksort, heapsort e insertion sort).

Búsqueda binaria por ID: O(log n) (requiere vector ordenado por ID).

Filtro por destino/fecha: O(n) (recorrido lineal; ambos criterios opcionales).

Listar todos: O(n).

Reservar/Cancelar: localizar vuelo y actualizar asientos/registro → O(log n) si se usa binaria por ID, o O(n) si se hace lineal; actualizaciones son O(1).

Ver mis reservaciones: O(r) con r = reservaciones del usuario.

Espacio adicional: O(1) (in-place) para std::sort (salvo optimizaciones del compilador) y estructuras en memoria.

### SICT0302: Toma decisiones

Elección de algoritmos:

std::sort para ordenar por precio y fecha → consultas comparativas y visualización ordenada.

Binaria por ID para accesos directos rápidos (O(log n)), útil al reservar/cancelar.

Secuencial para filtros flexibles (destino/fecha) donde no hay un criterio único fijo.

Diseño de experiencia: separación menú público/menú de usuario guía el flujo (explorar → decidir → reservar/gestionar).

Consistencia de negocio: descuento por >50k km centralizado en la rutina de compra; confirmación explícita antes de pagar; validaciones de entradas.

## Notas y posibles extensiones

Agregar ordenar por destino o por duración.

Persistencia en archivo/CSV o JSON para conservar usuarios y reservaciones entre ejecuciones.

Búsqueda por rango de fechas y precio máximo.

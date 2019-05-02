#ifndef DBL_LIST
#define DBL_LIST
#include <stdlib.h>
typedef struct datos
{
	int id; // Identificador para la estructura
	char nombre[31]; // Nombre de 30 caracteres y el caracter nulo '\0'
	struct datos* next; // Siguiente del nodo actual
	struct datos* prev; // Previo al nodo actual

	
} datos;

// Funcion que verifica si una lista está vacía
int esta_vacia(datos* cabeza);

// Función que recibe un entero y un string y construye un nodo aislado con estos datos.
datos* crear_nodo(int id, char* nombre);

// Insercion a la cabeza. Conocida como "Alta al frente"
void insercion_adelante(datos** cabeza, datos* nodo);

#ifdef VERSION_CON_DOS_ARGUMENTOS
// Inserción al final de la lista enlazada doble. Versión recursiva con dos argumentos
void insercion_atras(datos** cabeza, datos* nodo);
#else
// Inserción al final de la lista enlazada doble. Versión recursiva dada en clases
void insercion_atras(datos** cabeza, datos* nodo, datos* actual);
#endif

// Función que dado un id, borra el primer nodo que lo tenga.
void borrar_primera_ocurrencia(datos** cabeza, int id, datos* actual);

// Función que dado un id, borrar TODAS las ocurrencias de los nodos que lo tengan.
void borrar_todas_las_ocurrencias(datos** cabeza, int id, datos* actual);

// Función que destruye la lista (Borra todo de memoria).
void destruir_lista(datos** cabeza);
#endif
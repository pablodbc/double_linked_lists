#include "lista_doble.h" // Archivos en la misma carpeta se incluyen con "" en vez de <>
#include <stdlib.h>
#include <string.h>

int esta_vacia(datos* cabeza) { return cabeza == NULL; }

datos* crear_nodo(int id, char* nombre)
{
	// Creacion
	datos* nuevo_nodo = (datos*) malloc(sizeof(datos));
	
	// Asignacion
	nuevo_nodo->id = id;
	strcpy(nuevo_nodo->nombre, nombre);
	
	// Aislamos el nuevo nodo haciendo que apunte a la nada en ambos lados;
	nuevo_nodo->next = NULL;
	nuevo_nodo->prev = NULL;

	// Retorno
	return nuevo_nodo;

}

void insercion_adelante(datos** cabeza, datos* nodo)
{
	// Caso lista vacía
	if (esta_vacia(*cabeza))
	{
		*cabeza = nodo;
		return ;
	}


	(*cabeza)->prev = nodo; // El previo a la cabeza ahora será el nuevo nodo.
	nodo->next = *cabeza; // El siguiente del nuevo nodo será la cabeza.
	*cabeza = nodo; // La cabeza es ahora el nuevo nodo.
}

#ifdef VERSION_CON_DOS_ARGUMENTOS
// Version con dos argumentos. Es un poco más tricky porque mantenemos el actual usando el doble puntero.
void insercion_atras(datos** cabeza, datos nodo)
{
	// Caso lista vacía
	if (esta_vacia(*cabeza))
	{
		*cabeza = nodo;
		return ;
	}

	// Si estamos en el último nodo, se realiza la inserción
	if((*cabeza)->next == NULL)
	{
		(*cabeza)->next = nodo;
		nodo->prev = *cabeza;
		return ;
	}

	insercion_atras(&((*cabeza)->next), nodo);
}
#else
// Version con tres argumentos (Dada en clases)
void insercion_atras(datos** cabeza, datos* nodo, datos* actual)
{
	// Caso lista vacía
	if (esta_vacia(*cabeza))
	{
		*cabeza = nodo;
		return ;
	}

	// Si estamos en el último nodo, se realiza la inserción
	if(actual->next == NULL)
	{
		actual->next = nodo;
		nodo->prev = *cabeza;
		return ;
	}

	insercion_atras(cabeza, nodo, actual->next);
}
#endif

void borrar_primera_ocurrencia(datos** cabeza, int id, datos* actual)
{
	// Caso lista vacía
	if (esta_vacia(*cabeza))
	{
		return ;
	}

	// Si la cabeza es la primera ocurrencia, hay que actualizarla.
	if((*cabeza)->id == id)
	{
		datos* vieja_cabeza = *cabeza; // Guardamos la dirección de la cabeza.
		*cabeza = (*cabeza)->next; // Movemos la cabeza hacia adelante
		
		// ATENCION: Hay que verificar si despues de esto, la lista no quedó vacía (No dado en clases, pido disculpas)
		if(!esta_vacia(*cabeza))
		{
			(*cabeza)->prev = NULL;
		}

		free(vieja_cabeza); // Liberamos la memoria ocupada por la vieja cabeza
		return ; // Ya eliminamos la primera ocurrencia, podemos terminar.

	}

	// La cabeza no fue eliminada, así que podemos seguir

	if( actual->id == id)
	{
		actual->prev->next = actual->next; // El siguiente al previo del actual es ahora el siguiente del actual.
		actual->next->prev = actual->prev; // El previo del siguiente del actual es ahora el previo del actual.
		free(actual); // Liberamos el nodo actual.
		return ; // Ya eliminamos la primera ocurrencia, podemos terminar.
	}

	// Si no era la cabeza ni el nodo actual, entonces avanzamos.
	borrar_primera_ocurrencia(cabeza, id, actual->next);
}

void borrar_todas_las_ocurrencias(datos** cabeza, int id, datos* actual)
{
	// Caso lista vacía
	if (esta_vacia(*cabeza))
	{
		return ;
	}

	// Si hay que eliminar la cabeza, hay que tratarla de forma distinta.
	if((*cabeza)->id == id)
	{
		datos* vieja_cabeza = *cabeza; // Guardamos la dirección de la vieja cabeza.
		*cabeza = (*cabeza)->next; // Movemos la cabeza hacia adelante.
		actual = *cabeza; // Actualizamos el actual a la nueva cabeza.
		free(vieja_cabeza); // Liberamos la memoria ocupada por la vieja cabeza.

		
		// ATENCION: Hay que verificar si despues de esto, la lista no quedó vacía (No dado en clases, pido disculpas)
		if(!esta_vacia(*cabeza))
		{
			(*cabeza)->prev = NULL; // Hacemos que el previo de la nueva cabeza apunte a NULL
		}
		
		borrar_todas_las_ocurrencias(cabeza, id, actual); // Hacemos el llamado con los datos actualizados
		return ;

	}

	// La cabeza no fue eliminada, así que podemos seguir

	if( actual->id == id)
	{
		actual->prev->next = actual->next; // El siguiente al previo del actual es ahora el siguiente del actual.
		actual->next->prev = actual->prev; // El previo del siguiente del actual es ahora el previo del actual.
		datos* next = actual->next; // Guardamos el siguiente del actual antes de borrarlo para poder avanzar.
		free(actual); // Liberamos el nodo actual.
		borrar_todas_las_ocurrencias(cabeza, id, next); // Llamamos a la función reemplazando el actual por el siguiente (Equivalente a avanzar).

	}

	// Si no era la cabeza ni el nodo actual, entonces avanzamos.
	borrar_todas_las_ocurrencias(cabeza, id, actual->next);
}


void destruir_lista(datos** cabeza)
{
	// Condición de parada
	if (esta_vacia(*cabeza))
	{
		return ;
	}

	datos* vieja_cabeza = *cabeza; // Guardamos la vieja cabeza.
	*cabeza = (*cabeza)->next; // Movemos la cabeza hacia adelante.
	free(vieja_cabeza); // Liberamos el espacio que ocupa la vieja cabeza.
	destruir_lista(cabeza); // Avanzamos

}
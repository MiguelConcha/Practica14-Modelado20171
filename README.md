# Practica14-Modelado20171

__Implementando Listas genéricas ligadas en C__ 

Una Lista es un doble apuntador a Elemento para poder modificar siempre la misma lista. Un Elemento tiene dos campos: un apuntador a un siguiente Elemento y un apuntador de tipo void —para que se agenérica la lista— a su valor. 

Las funciones que se incluyen son: 

* `int cmp_int(const void* a, const void* b);` : Función comparadora.

* `void ordena_lista(Lista, int(*cmp)(const void*, const void*));` : Nos apoyamos en qsort().

* `void borra_lista(Lista);` : Recupera la memoria que fue dada por malloc para la Lita.

* `Elemento *quita_elemento(Lista, size_t posicion);` : Dada una posición válida dentro de la Lista, el Elemento en dicha posición es eliminado y devuelto a la función.

* `void imprime_lista_int(Lista lista);` : Se imprimen todos los valores que corresponden a los Elementos de la Lista como enteros. 

* `Lista crea_lista();` : Se solicita el espacio en memoria dinámicamente necesaria para la Lista.

* `int inserta_elemento(Lista lista, void *valor);` : Se crea un nuevo Elemento y se añade a la Lista.

* `size_t longitud(Lista lista);` : Devuelve el número de elementos que conforman la Lista.

#include "main.h" /*Se incluye el archivo de cabecera que define   
                    las funciones a implementar e incluye a su 
                    vez los demás archivos de cabecera que se requieren. */

/*Función que inserta números aleatorios en una lista*/
void inserta_datos_de_prueba(Lista lista);

int main()
{
    // Se crea la lista
    Lista lista = crea_lista();
    printf("La lista tiene %d elementos\n", longitud(lista));

    // Se insertan datos de prueba
    inserta_datos_de_prueba(lista);
    printf("La lista tiene %d elementos\n", longitud(lista));

    // Se remueve un elemento de la lista
    Elemento *borrado = quita_elemento(lista, 0);
    if (borrado != NULL) {free(borrado->valor);}
    free(borrado);
    printf("La lista tiene %d elementos\n", longitud(lista));

    // Se remueve un elemento que no existe en la lista
    quita_elemento(lista, longitud(lista));
    printf("La lista tiene %d elementos\n", longitud(lista));

    //Se imprime la lista antes de ordenar
    imprime_lista_int(lista);
    ordena_lista(lista, &cmp_int);

    //Se imprime la lista después de ordenar
    imprime_lista_int(lista);

    //Se libera la memoria ocupada
    borra_lista(lista);
}

/*
* Función comparadora de Elementos.
* ---------------------------------
* Devuelve un entero positivo si el primer valor 
* es mayor que el segundo, uno negativo si ocurre lo 
* contrario; devuelve cero si son iguales. 
*/
int cmp_int(const void* a, const void* b)
{
    Elemento* e_1 = (Elemento*)a; //Los apuntadores a void los convertimos a apuntadores a Elementos.
    Elemento* e_2 = (Elemento*)b;
    int entero_1 = *(int*)e_1->valor; /*Y para cada uno de esos
                                        Elementos, obtenemos su valor
                                        entero que llevan por valor. Para
                                        esto tenemos que convertir su apuntdor de valor
                                        que es void, por uno de entero y luego redeferenciarlo.*/
    int entero_2 = *(int*)e_2->valor;
    return entero_1 - entero_2; //Y la trictomía del order puede ser evaluada en una sola línea.
}

/*
* NUEVA LISTA
* -----------
* Se obtiene memoria en el 'heap' dinámicamente
* a partir del tamaño de una Lista y se devuelve el 
* apuntador que nos da 'malloc'. Una lista es un apuntador
* a un apuntador de elementos. 
*/
Lista crea_lista()
{
    Lista list = malloc(sizeof(Lista)); //Reservamos la memoria y asignamos el apuntador a la variable.
    return list; //Devolvemos el apuntador a la función.
}

/*
* AGREGAR ELEMENTO A LA LISTA
* ----------------------------
* En caso de que el valor dado como parámetro sea 
* válido (no nulo), creamos un nuevo elemento con dicho 
* valor y lo añadimos a la lista, al comiendo de ésta.
* En clase se discutió que el orden de agregado no 
* era importante en esta práctica.
*/
int inserta_elemento(Lista lista, void *valor)
{
    if (valor != NULL){ 
        Elemento *new_element = malloc(sizeof(Elemento)); //Pedimos memoria para el nuevo elemento dinámicamente.
        new_element->valor = valor; //Le damos el valor que se da como parámetro de la función.
        new_element->siguiente = *lista; //El elemento al que apunta el que fue creado es el primero de la lista.
        *lista = new_element; //Luego la lista apunta al nuevo elemento que fue creado y todo ya quedó enlazado.
    }
    return longitud(lista); //La función nos pide devolver la longitud de la lista, misma que se calcula con la función que es para este motivo.
}

/*
* ¿CUÁNTOS ELEMENTOS HAY EN LA LISTA?
* ----------------------------------
* Dado que la Lista no tiene un atributo de longitud
* porque es simplemente un doble apuntador a Elemento, 
* tenemos que iterar toda la lista para poder contar
* el número de Elementos que la conforman.
*/
size_t longitud(Lista lista)
{
    size_t length = 0; //Variable donde almacenamos la longitud de la lista.
    Elemento* current_element = *lista; //Redeferenciamos una vez la lista, entonces es un apuntador a Elemento, y apunta el primero de ésta.
    while(current_element != NULL){ //Recorremos toda la lista.
        current_element = current_element -> siguiente; //El apuntador va actualizándose para apuntar en cada iteración el siguiente Elemento.
        length++; //Y en cada iteración incrementamos el contador del número de elementos.
    }
    return length; 
}

/*
* Imprime los valores de la lista como 
* enteros.
*/
void imprime_lista_int(Lista lista)
{
    int i;
    size_t length = longitud(lista); //Almacenamos el tamaño de la lista para ver asta dónde tenemos que recorrer de la misma.
    Elemento *current_element = *lista; //Tenemos un apuntador al primer elemento de la lista.
    printf("\n( "); //Imprimiendo delimitador por motivos visuales.
    for(i = 0; i<length; i++){ //Iteramos la lista de Elementos.
        printf("%d  ", *(int*)current_element -> valor); /*Para cada elemento, su valor, que es
                                                            un apuntador a void porque es genérica,
                                                            lo 'casteamos' a un apuntador de entero
                                                            y luego lo redeferenciamos para obtener el 
                                                            valor concreto en memoria. Se imprime este valor.*/
        current_element = current_element -> siguiente; //Y luego apuntamos al siguiente elemento de la lista para seguirla recorriendo.
    }
    printf("%s\n\n", ")"); //Imprimiendo delimitador por motivos visuales.
}

/*
* ELIMINA ELEMENTOS DE LA LISTA.
* --------------------------------
* Dado una posición en la lista, se elemina el elemento que está 
* ubicado en esa posición, reacomodando las relaciones entre los demás 
* elementos.
*/
Elemento *quita_elemento(Lista lista, size_t posicion)
{   
    /*Verificamos que la lista no sea Nula (el apuntador al apuntador de Elemento).
    Tampoco queremos que la posición sea negativa o mayor al número de elementos en la lista
    porque no podríamos acceder a ésta. Es inválido y regresamos NULL.*/
    if(*lista == NULL || posicion < 0 || posicion >= longitud(lista)){
        return NULL;
    }
    /*QUITAR LA CABEZA.*/
    if(posicion == 0){ 
        Elemento* head = *lista; //Apuntamos al primer elemento de la lista: la cabeza.
        Elemento* second_node = head->siguiente; //Apuntamos al segundo elemento.
        *lista = second_node; //Decimos que el primer elemento de la lista es el segundo elemento.
        return head; //Devolvemos a la función el elemento que fue quitado, i.e., la cabeza. 
    }
    /*QUITAR LA COLA.*/
    else if(posicion == longitud(lista)-1){
        Elemento *curr = *lista;
        int i;
        for(i = 0; i<longitud(lista)-2; i++){ //Con un apuntador de elementos recorremos la lista hasta llegar al elemento previo a la cola.
            curr = curr-> siguiente;
        }
        Elemento *temp2 = curr->siguiente; //Apuntamos a la cola.
        Elemento *adevolver = temp2; //Almacenamos una referencia al Elemento que será eliminado.
        curr->siguiente = NULL;  //El siguiente del que previamente era el penúltimo elemento ahora es la cola, por lo que su siguiente Elemento es NULL.
        return adevolver; //Devolvemos la cola, pues fue el Elemento eliminado.
    }
    /*QUITAR UN ELEMENTO ENMEDIO DE LA LISTA (CASO GENERAL).*/
    else{
        Elemento *curr = *lista;
        int i;
        for(i = 0; i<posicion-1; i++){ //Con un apuntador de elementos recorremos la lista hasta llegar al elemento que queremos quitar.
            curr = curr-> siguiente;
        }
        Elemento *temp2 = curr->siguiente; //Apuntamos al que le sigue al elemento actual, que es el que será removido.
        Elemento *adevolver = temp2; //Almacenamos un apuntador al elemento que será quitado.
        curr->siguiente = temp2->siguiente; //El siguiente elemento del anterior al que está siendo quitado apunta al siguiente Elemento del que está siendo quitado.
        return adevolver; //Devolvemos el elemento que fue removido de la Lista.
    }
}

/*
* DESOCUPA LA MEMORIA QUE FUE ASIGNADA POR MALLOC PARA LA LISTA.
* --------------------------------------------------------------
* Libera la memoria que ocupa: la lista, sus elementos que la conforman 
* y los valores que tiene cada uno de sus elementos.
*/
void borra_lista(Lista lista)
{
    size_t length = longitud(lista); //Vemos cuántas veces vamos a tener que repetir la instrucción.
    int i;
    for(i = 0; i < length; i++){ //Incrementamos el contador.
        Elemento *curr_removed_element = quita_elemento(lista, 0); /*Quitamos la cabeza de la vista
                                                                    tantas veces como sea necesario
                                                                    hasta que ya no haya elementos en ella.
                                                                    Cada elemento que está siendo removido 
                                                                    lo podemos referenciar con un apuntador a Elemento.*/
        if (curr_removed_element != NULL){ //Ahora, si dicho Elemento es no nulo: 
            free(curr_removed_element->valor); //Liberamos la memoria que ocupa su valor.
            free(curr_removed_element); //Y el elemento en sí.
        }
    }
    free(lista); //Al final de todo, liberamos la memoria que ocupada la Lista (apuntador a apuntador de Elemento).
}

/*
* Se encarga de ordenar de forma genérica una lista ligada genérica.
* Se recibe una lista y una función comparadora.
*/
void ordena_lista(Lista lista, int(*cmp)(const void*, const void*))
{
    size_t tam = longitud(lista); //Almacenamos esta variable para saber hasta donde iterar. También para saber qué tan grande será el arreglo.
    Elemento* next= *lista; //Apuntamos a la cabeza de la lista.
    Elemento* arreglo = malloc(sizeof(Elemento) * tam); //Creamos un arreglo de Elementos. Es necesario un arreglo para poder llamar a la función qsort().
    for(int i= 0; i < tam; i++){
        arreglo[i]= *next; //En cada posición del arreglo metemos el Elemento. Como no queremos el apuntador al Elemento, tenemos que redeferenciar.
        next= next -> siguiente; //Y vamos haciendo que apunte cada vez al siguiente Elemento de la Lista.
    }
    qsort(arreglo, tam, sizeof(Elemento), *cmp); /*Mandamos llamar a qsort() con la dirección de la cabeza del arreglo (podemos pasar 
                                                equivalentemente el arreglo), el número de elementos del arreglo (que es el mismo 
                                                que de Elementos en la lista), el tamaño de los saltos que tendrán que efectuarse a partir de
                                                los tipos contenidos en el arreglo, y una función comparadora.*/
    Elemento* next_2= *lista; //Ahora, volvemos a apuntar a la cabeza de la Lista.
    for(int i= 0; i < tam; i++){
        next_2 -> valor = arreglo[i].valor;  //Y cada valor de los Elementos del arreglo los ponemos como campo de valor a los apuntadores de Elemento de la Lista.
        next_2= next_2 -> siguiente; //Y vamos recorriendo toda la estructura.
    }
}

void inserta_datos_de_prueba(Lista lista)
{
    srand(time(NULL));
    int *num_a_insertar;
    int indice;
    for (indice = 0; indice < 20; ++indice) {
        num_a_insertar = malloc(sizeof(int));
        *num_a_insertar = rand() % 100;
        inserta_elemento(lista, num_a_insertar);
    };
}

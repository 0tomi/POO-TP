// Es una estructura de datos lineal, a diferencia de las anteriores, FIFO Y FILO esta tiene menos limitaciones a comparacion de las dos ultimas. Esta aunque sea lineal puede o no ser destructiva

#include <iostream>
#include <stdlib.h>
#include <ctime>
using namespace std;


struct nodo_listaSE{
    int dato;
    nodo_listaSE* link;
};
void agregar_dato(nodo_listaSE* &inicio, int dato_agregar){
    nodo_listaSE* aux = new nodo_listaSE;
    aux->dato = dato_agregar;
    aux->link = inicio;
    inicio = aux;
}
void listaSE_mostrar(nodo_listaSE* inicio){
    
    while (inicio != NULL)
    {
        cout << inicio->dato << " -> ";
        inicio = inicio->link;
    }
    cout << "NULL" << endl; 
}


void agregar_al_final(nodo_listaSE* listase, int ndato){
    nodo_listaSE* nuevo_nodo = new nodo_listaSE;
    nuevo_nodo->dato = ndato;
    nuevo_nodo->link = NULL; 

    
    if (listase == NULL) {
        listase = nuevo_nodo;
    } else {
        nodo_listaSE* ultimo = listase;
        while (ultimo->link != NULL) {
            ultimo = ultimo->link;
        }
        ultimo->link = nuevo_nodo;
    }
};

void eliminar_ocurrencias(nodo_listaSE* &listase, int ndato){
    nodo_listaSE* anterior = NULL;
    nodo_listaSE* actual = listase;
    int cant_ocurrencias = 0;
    while (actual != NULL){
        if(actual->dato == ndato){
            if(anterior == NULL){ 
                listase = actual->link;
            }
            else anterior->link = actual->link;
            nodo_listaSE* eliminar = actual;
            actual = actual->link;
            delete eliminar;
            cant_ocurrencias++;
        }    
        else{
            anterior = actual;
            actual =  actual->link;
        }
    }
    cout << "Se han eliminado " << cant_ocurrencias << " ocurrencias" << endl; 
};
void datos_aleatorios(nodo_listaSE* &listase){
    int datos;
    cout << "Ingrese la cantidad de datos que desea generar: ";
    cin >> datos;
    for (int i = 0; i < datos; i++)
    {
        int number = rand()%100 + 1;
        agregar_dato(listase,number);
        cout << number << " ";
    }
    cout << endl;

}
void eliminar_lista(nodo_listaSE* &listase){
    nodo_listaSE* aux = listase;
    while (listase != NULL)
    {
        listase = listase->link;
        delete aux;
        aux = listase;
    }
    cout << "Se ha eliminado la lista completa" << endl;
}
int main()
{
    nodo_listaSE* listase = NULL;
    srand(time_t(nullptr));
    int opcion;
    int dato;
    do
    {
        cout << "*************************************************************************************" << endl;
        cout << "Ingrese que accion desea realizar: " << endl;
        cout << "1- agregar un dato" << endl;
        cout << "2- agregar un dato al final" << endl;
        cout << "3- mostrar la lista" << endl;
        cout << "4- eliminar las ocurrencias de la lista" << endl;
        cout << "5- para aniadir n datos aleatorios" << endl; 
        cout << "6- eliminar la lista completa" << endl;
        cout << "0- para salir del programa" << endl;
        cout << "*************************************************************************************" << endl;
        cin >> opcion;
        cout << endl;
        cout << endl;
        switch (opcion)
        {
        case 1:
            cout << "Ingrese el dato que desea agregar a la lista: ";
            cin >> dato;
            agregar_dato(listase,dato);
            cout << "Se ha agregado el valor " << dato << endl;
            break;
        case 2:
            cout << "Ingrese el dato que desea agregar al final de la lista: ";
            cin >> dato;
            agregar_al_final(listase,dato);
            cout << "Se ha agregado el valor " << dato << " al final de la lista" << endl;
            break;
        case 3: 
            listaSE_mostrar(listase);
            break;
        case 4:
            cout << "Ingrese que ocurrencias desea eliminar: ";
            cin >> dato;
            eliminar_ocurrencias(listase,dato);
            break;
        case 5:
            datos_aleatorios(listase);
            break;
        case 6:
            eliminar_lista(listase);
            break;
        case 0:
            cout << "Saliendo del programa...";
            break;
        default:
            cout << "Ha ingresado una opcion invalida" << endl;
            break;
        }
        cout << endl;
        cout << endl;
        cout << endl;
    } while (opcion != 0);
    
    
    
    return 0;
}



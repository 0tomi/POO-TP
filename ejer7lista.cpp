#include <iostream>
#include <fstream>
#include <string>

using namespace std;

/*7) Se requiere desarrollar un programa en C++ que gestione registros de personas
almacenados en un archivo de texto llamado datos.txt. Cada línea del archivo contiene la información de una persona en el siguiente formato:
212589 1991 Lucas Jorge<eoln>
219221 1977 Salvador Bila<eoln>
213533 1982 Pedro Pico<eoln>
216554 1996 Jose Perez<eoln>
214221 1994 Dora Duarte<eoln>
213994 1981 Pedro Pica<eoln>
215514 2001 Manuel Maina<eoln>
219853 1994 Juan Morgan<eoln>
215303 1986 Pablo Jaco<eoln>
<eoln>
El programa debe realizar las siguientes operaciones:
1- Leer los datos del archivo datos.txt y almacenarlos en un array dinámico de
registros de personas.
2 - Determinar y mostrar por pantalla el año de nacimiento mínimo, el año de
nacimiento máximo y el total de registros leídos.*/

struct listade{
    long dni;
    int anio;
    string nombre;
    listade *siguiente = NULL;
};

void agregar_dato(listade* &inicio, long dni, int anio, string nombre){
    listade* aux = new listade;
    aux->anio = anio;
    aux->dni = dni;
    aux->nombre = nombre;
    aux->siguiente = inicio;   
    inicio = aux;
}
int* calcular_min_max(listade* inicio){
    if (inicio == NULL){
        return NULL;
    }
    int max = inicio->anio;
    int min = inicio->anio;
    inicio = inicio->siguiente;
    while (inicio != NULL)
    {

        if (max < inicio->anio)
        {
            max = inicio->anio;
        }
        if (min > inicio->anio)
        {
            min = inicio->anio;
        }
        inicio = inicio->siguiente;
    }
    int *aux = new int[2];
    aux[0] = max;
    aux[1] = min;
    return aux;
}
void eliminar_lista(listade* &inicio){
    listade* aux = inicio;
    while (inicio != NULL){
        inicio = inicio->siguiente;
        delete aux;
        aux = inicio;
    }
}


int main(int argc, char const *argv[])
{
    listade* inicio = NULL;
    string auxnombre;
    int anio, cant_registros = 0;
    long dni;
    ifstream archivo;
    archivo.open("../ejer7_datos.txt");
    if (archivo.fail()){
        return 1;
    }
    while (archivo >> dni >> anio)
    {
        archivo.ignore();
        getline(archivo,auxnombre);
        agregar_dato(inicio,dni,anio,auxnombre);
        cant_registros++; // punto 3
    }
    int *minmax = calcular_min_max(inicio);

    if(minmax != NULL){
        cout << "El anio de nacimiento minimo es: " << minmax[1] << " y el maximo es de: " << minmax[0] << endl;
        cout << "Se han leido " << cant_registros << " registros";
    }
    else cout << "La lista esta vacia";    
    delete[] minmax;
    eliminar_lista(inicio);
    return 0;
    
}

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

/*
	7) Se requiere desarrollar un programa en C++ que gestione registros de personas
	almacenados en un archivo de texto llamado datos.txt.
	El programa debe realizar las siguientes operaciones:
	1- Leer los datos del archivo datos.txt y almacenarlos en un array dinámico de
		registros de personas.
	2 - Determinar y mostrar por pantalla el año de nacimiento mínimo, el año de
		nacimiento máximo y el total de registros leídos.

	# EJ7, Inspirado el concepto de <vector> según lo que me encontré en internet
*/

struct nodoP{
	string dni;
	int anio;
	string nya;

    nodoP* link = NULL;
};

void eliminarNodos(nodoP* &inicio){
	nodoP* aux;
	while (inicio != NULL){
		cout << "\nentro";
		inicio->link = aux; 
		delete inicio;
		inicio = aux;
	}
}

nodoP* push(nodoP* inicio, nodoP datos){
    nodoP* nuevoNodo = new nodoP;
    *nuevoNodo = datos;

    if (inicio == NULL)	// si la lista esta vacía 
		return nuevoNodo;
       
	nuevoNodo->link = inicio;
	return nuevoNodo;
}

int main(int argc, char *argv[]) {
    int contador = 0;
	nodoP aux;
    nodoP* lista = NULL;

	// Lectura
	ifstream file; file.open("./datos.txt");
	if (file.fail()){
		cout << "ERROR: archivo no encontrado";
		return 404;
	}
	while (file >> aux.dni >> aux.anio){
		file.ignore();
		getline(file,aux.nya);
		lista = push(lista,aux);
        contador++;
	}
	file.close();
	
	// Calcular minimo
	int aniomin = lista->anio; 
    int aniomax = lista->anio;
    nodoP* auxP = lista->link;
	while (auxP->link != NULL){
		if (aniomin > auxP->anio)
			aniomin = auxP->anio;
		else if (aniomax < auxP->anio)
			aniomax = auxP->anio;
		auxP = auxP->link;
	}
	
	cout << "\n Anio minimo de nacimiento: " << aniomin
		<< "\n Anio maximo de nacimiento: " << aniomax
		<< "\n Total de registros leidos: " << contador;

	eliminarNodos(lista);

	if (lista == NULL)
		cout << "\nlista vacía";

	return 0;
}

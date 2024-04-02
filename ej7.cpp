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

struct persona{
	string dni;
	int anio;
	string nya;
};

persona *vectorTrucho(persona* v, int max, int contador){
	persona* aux = new persona[max];

	if (aux == NULL)
		return aux;

	for (int i = 0; i < contador; i++)
		aux[i] = v[i];

	delete[] v;
	return aux;
}

// Esta funcion retorna true si la operación se pudo completar	
bool empujar_atras(persona* &p, persona aux, int &max, int cont){
	if (cont == max){
		max *= 2;
		p = vectorTrucho(p,max,cont);
	}
	if (p == NULL)
		return false;
	
	p[cont] = aux;
	return true;
}	
	
int main(int argc, char *argv[]) {
	int contador = 0;
	int max = 2;
	persona* p = new persona[max];
	persona aux;
	
	// Lectura
	ifstream file; file.open("./datos.txt");
	if (file.fail()){
		cout << "ERROR: archivo no encontrado";
		return 404;
	}
	while (file >> aux.dni >> aux.anio){
		file.ignore();
		getline(file,aux.nya);
		if (empujar_atras(p,aux,max,contador))
			contador++;
		else 
			cout << "\nERROR: No hay mas memoria disponible para guardar el arreglo";
	}
	file.close();

	// Eliminemos los espacios del vector sin utilizar
	if (contador < max){
		max = contador;
		p = vectorTrucho(p,max,contador);
	}

	for (int i = 0; i < contador; i++)
		cout << "|" << p[i].anio << "|" << p[i].dni << "|" << p[i].nya << endl;		

	// Para darle uso al vector vamos a hacer la consigna 2 aca abajo
	int aniomin = p[0].anio, aniomax = p[0].anio;
	for (int i = 1; i < contador; i++)
		if (aniomin > p[i].anio)
			aniomin = p[i].anio;
		else if (aniomax < p[i].anio)
			aniomax = p[i].anio;
	
	cout << "\n Anio minimo de nacimiento: " << aniomin
		<< "\n Anio maximo de nacimiento: " << aniomax
		<< "\n Total de registros leidos: " << contador;
	
	delete[] p; 
	return 0;
}


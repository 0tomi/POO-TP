#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct persona{
	string dni;
	int anio;
	string nya;
};

void expand(persona* &v, int &max, int contador){
	persona* aux = new persona[max*2];
	for (int i = 0; i < contador; i++)
		aux[i] = v[i];

	max *= 2;
	delete[] v;
	v = aux;
}

bool empujar_atras(persona* &p, int &max, int cont, string nya, string dni, int anio){
	if (cont == max)
		expand(p,max,cont);
	if (p == NULL)
		return false;
	
	p[cont].nya = nya;
	p[cont].dni = dni;
	p[cont].anio = anio;
	return true;
}	
	
int main(int argc, char *argv[]) {
	int contador = 0;
	int max = 2;
	int anio;
	string nombre, dni;
	
	// Lectura
	persona* p = new persona[max];
	ifstream file; file.open("./datos.txt");
	if (file.fail()){
		cout << "archivo no encontrado";
		return 404;
	}
	while (file >> dni >> anio){
		file.ignore();
		getline(file,nombre);
		if (empujar_atras(p,max, contador, nombre, dni, anio))
			contador++;
		else 
			cout << "\nERROR: No hay más memoria disponible para guardar el arreglo";
	}
//	cout << "\nsize of p: " << max;
	
	delete[] p; 
	return 0;
}


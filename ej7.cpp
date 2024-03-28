#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct persona{
	string dni;
	int anio;
	string nya;
};

int vectorTrucho(persona* &v, int max, int contador){
	persona* aux = new persona[max];
	for (int i = 0; i < contador; i++)
		aux[i] = v[i];

	delete[] v;
	v = aux;

	return max;
}

// Esta funcion retorna true si la operación se pudo completar	
bool empujar_atras(persona* &p, persona aux, int &max, int cont){
	if (cont == max)
		max = vectorTrucho(p,max*2,cont);
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

	// Eliminemos los espacios del vector sin utilizar
	if (contador < max)
		max = vectorTrucho(p,contador,contador);

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


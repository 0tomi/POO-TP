#include <iostream>
#include <fstream>

using namespace std;
/*
	Ej1: Usando recursividad para indicar lineas de un archivo 
	CA01: La consigna no indica el nombre que debe tener el archivo, ni donde debe estar, asi que 
	le pediremos el nombre del archivo de texto al usuario.
*/

int contarlineas(ifstream &f){
	string text;
	if (getline(f,text))
		return 1 + contarlineas(f);
	return 0;
}

int main(int argc, const char** argv) {
	string direccion;
	cout << "Indique el nombre del archivo: ";
	getline(cin,direccion);
	direccion = "./" + direccion + ".txt";

	ifstream file; file.open(direccion);
	if (file.fail()){
		cout << "\nNo se ha podido encontrar el archivo. \nIntente poner el mismo en la misma carpeta donde esta el programa.";
		return 404;
	}
	int contador = contarlineas(file);
	cout << "\nCantidad de lineas: " << contador;
	return 0;
}

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <conio.h>

/*
    Programa que contiene la resolución de los 7 ejercicios
    (Recopilación)
*/

using namespace std;

void ej1(){
	
}
void ej2(){
	
}
void ej3(){
	
}
void ej4(){
	
}
void ej5(){
	
}
void ej6(){
	
}
void ej7(){
	
}

int main(int argc, char const *argv[])
{
    system("Title Resolucion total del trabajo practico");
    char menu;
    do{
        system("cls");
        cout << "        ====[ Trabajo practico de POO ]====\n"
        << "\x1B[31m" << "\nPulse el NUMERO indicado para acceder a los distintos menus" << "\x1b[0m"
        << "\n[\x1B[31m1\x1b[0m] Indicar cuantas lineas tiene un archivo de texto"
        << "\n[\x1B[31m2\x1b[0m] Contar cantidad de caracteres ingresados por el usuario en un archivo de texto"
        << "\n[\x1B[31m3\x1b[0m] Modificar un archivo de texto de forma que cada oracion comience con una nueva"
		<< "\n[\x1B[31m4\x1b[0m] Reemplazar un caracter ingresado por el usuario, por otro caracter tambien ingresado por el mismo en un archivo de texto"	
		<< "\n[\x1B[31m5\x1b[0m] Obtener cuantos alumnos nacieron antes del a�o 1995"	
		<< "\n[\x1B[31m6\x1b[0m] Indicar una palabra y obtener su definicion (desde un archivo de texto)"
		<< "\n[\x1B[31m7\x1b[0m] Obtener anio de nacimiento minimo, maximo y total de registros de un archivo"
		<< "\n\nPulse [\x1B[38;2;53;149;240m0\x1b[0m] para salir del programa\n";
		menu = getch();
		
		switch(menu){
			case '1': ej1();
				break;
			case '2': ej2();
				break;
			case '3': ej3();
				break;
			case '4': ej4();
				break;
			case '5': ej5();
				break;
			case '6': ej6();
				break;
			case '7': ej7();
				break;
		}
    }while(menu != '0');
    return 0;
}

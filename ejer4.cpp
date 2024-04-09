/*4) Escriba un programa que reemplace un carácter ingresado por el usuario por otro carácter
también ingresado por el usuario en un archivo de texto, indique en cuantas líneas lo
reemplazó.*/

#include <iostream>
#include <string>
#include <fstream>

using namespace std;
string reemplaza(char c1, char c2, string renglon, int &l){
	
	for (char& c : renglon) {
		if (c == c1) {
			c=c2;
			l++;
			
		}
	}
	return  renglon;
}
int main(int argc, char const *argv[])
{
    string direccion, renglon, texto, linea;
		string  texo ="";
		char car, car2;
		int a=0;
		cout << "Indique el nombre del archivo: ";
		getline(cin,direccion);
		direccion = "./" + direccion + ".txt";
		ifstream arc;
		arc.open(direccion);
		
		if (arc.fail()){
			cout<<"Error en la apertura del archivo. ";
		}
		else {
			cout<<"Ingrese caracter a buscar: "<<endl;
			cin>>car;
			cout<<"Ingrese caracter oara reemplazar: "<<endl;
			cin>>car2;
			
			while(getline(arc, renglon)){
				int l=0;
				linea=reemplaza(car, car2, renglon, l);
				texto +=linea+"\n";
				cout<<"Linea "<<a<<" "<<l<<" veces reemplazada"<<endl;
				a++;
			}
			ofstream file;
			file.open(direccion);
			file<<texto<<endl;
			file.close();
		}
		arc.close();
		
    return 0;
}

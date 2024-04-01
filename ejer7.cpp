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

#include <iostream>
#include <fstream>
#include <string>

using namespace std;


struct datos{
    int codigo_referencia;
    int anio_nacimiento;
    string nya;
};

int main(int argc, char const *argv[])
{

    ifstream archivo;
    archivo.open("C:/Users/Usuario/Desktop/tp_poo/ejer7_datos.txt");
    if (archivo.fail()){
        cout << "Error al abrir el archivo";
        return 1;
    }
    int size = 0, i = 0;
    string aux;
    while (getline(archivo,aux)){
        size++;
    }
    datos *personas = new datos[size];
    archivo.clear();
    archivo.seekg(0,ios::beg); // para colocar el puntero al inicio del archivo
    while (archivo >> personas[i].codigo_referencia >> personas[i].anio_nacimiento ){
        archivo.ignore();
        getline(archivo,personas[i].nya);
        i++;
    }

    int anio_minimo = 9999;
    int anio_maximo = 0;
    
    for (int k = 0; k < i; k++)
    {
        if (personas[k].anio_nacimiento > anio_maximo){
            anio_maximo = personas[k].anio_nacimiento;
        }
        
        if (personas[k].anio_nacimiento < anio_minimo){
            anio_minimo = personas[k].anio_nacimiento;
        }
    }
    
    archivo.close();

    cout << "El anio de nacimiento minimo es: " << anio_minimo << " y el maximo es de: " << anio_maximo << endl;
    cout << "Se leyeron : " << i << " registros";
    delete[] personas;
    


    return 0;
}

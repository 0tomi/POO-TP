/*5) Considere que se dispone de un archivo datos.txt donde se almacena en cada línea: un
número de orden(un entero), un año de nacimiento (un entero), un nombre y un apellido
separados por un espacio. Escribir un programa para indicar cuántos alumnos nacieron
antes del año 1995.
Por ejemplo: Si el archivo datos.txt es
281230 1999 Lucas Perez<eoln>
214221 1994 Salvador Rodriguez<eoln>
213533 1982 Pedro Pico<eoln>
<eof>
se deberá indicar: “2 alumnos nacieron antes del año 1995”
*/

#include <iostream>
#include <fstream>
#include <string>

using namespace std;
struct datos{
    int numero_orden;
    int anio_nacimiento;
    string nya;
};
datos* incrementar_tamanio(datos* informacion, int cont){
    datos* aux = new datos[cont + 1];
    for (int i = 0; i < cont; i++)
    {
        aux[i] = informacion[i];
    }
    delete[] informacion;
    return aux;
}
int main(int argc, char const *argv[])
{
    const int anio = 1995;
    int  i = 0, alumnos_1995 = 0; // cuantos alumnos nacieron antes del 95
    ifstream archivo;
    datos *informacion = new datos[1];
    archivo.open("C:/Users/Usuario/Desktop/tp_poo/ejer5_datos.txt");
    if(archivo.fail()){
        cout << "Error al abrir el archivo";
        return 1;
    }
    archivo >> informacion[i].numero_orden;
    archivo >> informacion[i].anio_nacimiento;
    archivo.ignore();
    while (getline(archivo,informacion[i].nya)){
        i++;
        informacion = incrementar_tamanio(informacion,i);
        archivo >> informacion[i].numero_orden;
        archivo >> informacion[i].anio_nacimiento;
        archivo.ignore();
    }
    archivo.close();
    for (int j = 0; j < i; j++)
    {
        if (informacion[j].anio_nacimiento < anio){
            alumnos_1995++;
        }
    }
    delete[] informacion;
    cout << "La cantidad de alumnos que nacieron antes de 1995 es de: " << alumnos_1995; 
    return 0;
}

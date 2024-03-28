#include <iostream>
#include <fstream>

using namespace std;

/*
    5) Considere que se dispone de un archivo datos.txt donde se almacena en cada línea: un
    número de orden(un entero), un año de nacimiento (un entero), un nombre y un apellido
    separados por un espacio. Escribir un programa para indicar cuántos alumnos nacieron
    antes del año 1995.
    se deberá indicar: “2 alumnos nacieron antes del año 1995”

    Sin usar arrays, porque no se ve necesario, y de forma recursiva
*/

int contador(ifstream &f){
    int nro;
    string text;
    if (f >> nro >> nro){
        getline(f,text);
        if (nro < 1995)
            return 1 + contador(f);
        return contador(f);
    }
    return 0;
}

int main(int argc, const char** argv) {
    int cantidad = 0;
    ifstream file; file.open("./datos.txt");
    if (file.fail()){
        cout << "ERROR: Al abrir el archivo datos.txt";
        return 404;
    }
    cantidad = contador(file);
    cout << cantidad << " alumnos nacieron antes del anio 1995";
    file.close();
    return 0;
}

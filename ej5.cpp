#include <iostream>
#include <fstream>

/*
    EJ5, sin usar arrays, porque no se ve necesario, y de forma recursiva
*/

using namespace std;

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
    return 0;
}

#include "Juego.cpp"
#include <iostream>

// usando ../ nos movemos 1 directorio para atras

int main(int argc, char const *argv[])
{
    Juego test;
    reglas* test2 = test.getReglas();

    
    int max;
    int* arrayTest3 = test2->getPaisesPermitidos(max);

    for (int i = 0; i < max; i++)
    {
        cout<< arrayTest3[i] << endl;
    }
    
    return 0;
}

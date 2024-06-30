#include "Juego.cpp"
#include <iostream>

int main(int argc, char const *argv[])
{
    Juego test;
    int max;

    reglas* test2 = test.getReglas();
    int* arrayTest3 = test2->getPaisesPermitidos(max);

    for (int i = 0; i < max; i++)
    {
        cout<< arrayTest3[i] << endl;
    }
    
    return 0;
}

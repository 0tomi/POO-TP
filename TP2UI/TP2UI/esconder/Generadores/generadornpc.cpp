#ifndef GENERADORNPC_CPP
#define GENERADORNPC_CPP

#include "generadornpc.h"
#include "../lectorarchivos.h"
#include <stdlib.h>

GeneradorNPC::GeneradorNPC(){
    // Leemos el archivo que contiene las direcciones con las imagenes de las caras, y luego las guardamos.
    LectorArchivos lector("../NPC/direccionesCaras.txt");
    this->LinksImagenesNPCS = lector.getArray();
    this->topeLinksImagenes = lector.getTopeArray();
}


// Esto necesita rework a futuro para distinguir entre caras de Mujeres y Hombres
NPC* GeneradorNPC::getNPC(){
    srand(1); // luego esto hay que cambiarlo por time null
    // Pickeamos un genero
    int valorCentinela2 = rand()%3;
    // Pickeamos una cara
    int valorCentinela = rand()%(this->topeLinksImagenes);


    // Generamos NPC y lo retornamos
    this->NPC2create = new NPC(this->LinksImagenesNPCS[valorCentinela], this->generos[valorCentinela2]);
    return this->NPC2create;
}

#endif

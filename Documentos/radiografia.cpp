#include "radiografia.h"

radiografia::radiografia(vector<ParDatos> &Elements): Documentacion()
{
    this->Elementos = Elements;
}

vector<ParDatos>& radiografia::GetVector()
{
    return this->Elementos;
}

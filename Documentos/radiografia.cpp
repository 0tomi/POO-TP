#include "radiografia.h"

radiografia::radiografia(vector<ParDatos> &Elements)
{
    this->Elementos = Elements;
}

vector<ParDatos>radiografia::GetVector() const
{
    return this->Elementos;
}

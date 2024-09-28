#include "reglasnivel3.h"

ReglasNivel3::ReglasNivel3()
{
    rand.seed(QTime::currentTime().msec());
}

void ReglasNivel3::generar_MaxAcompaniantes()
{
    this->maxAcompaniantes = rand.bounded(4);
}

void ReglasNivel3::set_MaxAcompaniantes(int max)
{
    if (max < 0 || max > 3){
        generar_MaxAcompaniantes();
        return;
    }

    this->maxAcompaniantes = max;
}

int ReglasNivel3::getMaxAcompaniantes() const
{
    return maxAcompaniantes;
}

#include "reglasnivel3.h"
#include <QTime>

ReglasNivel3::ReglasNivel3(): Random(QTime::currentTime().msec())
{

}

void ReglasNivel3::generar_MaxAcompaniantes()
{
    this->maxAcompaniantes = Random.bounded(4);
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

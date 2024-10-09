#include "generador_paisresidencia.h"

generador_paisresidencia::generador_paisresidencia(): Generar_pasaporte()
{
    this->locura = new LocuraCaracteres(&this->rand);
}

generador_paisresidencia::~generador_paisresidencia()
{
    delete locura;
}

void generador_paisresidencia::Inicializar(ReglasNivel1* rules1, ReglasNivel2 * rules2, quint32 seed, int dificultad)
{
    this->setSeed(seed);
    this->rules = rules1;
    this->ruleslvl2 = rules2;

    paisesValidos = ruleslvl2->getPaisesValidos();
    paisesInvalidos = ruleslvl2->getPaisesInvalidos();

    this->dificultad = dificultad;

    switch (dificultad){
        // Modo facil
    case 1: Probabilidades = 7;
        break;
        // Modo demonio
    case 3: Probabilidades = 3;
        break;
        // Modo normal
    default: Probabilidades = 5;
        break;
    }
}

PaisResidencia *generador_paisresidencia::generar(Pasaporte *Pasaporte2copy, bool valido)
{
    for (int i = 0; i < 3; ++i){
        this->camposValidos[i] = true;
        this->camposLocura[i] = true;
    }

    this->Pasaporte2Copy = Pasaporte2copy;


    if(valido){
        QString PaisResidenciaGenerado = this->generar_paisresidencia(valido);
        this->PaisResidenciaCreado = new PaisResidencia(this->Pasaporte2Copy->getnombre(), this->Pasaporte2Copy->getfecha_nacimiento(), PaisResidenciaGenerado);
    } else{
        this->CamposLocura(Probabilidades);
        generar_camposValidos(valido,Probabilidades);
        QString nuevoNombre = this->generar_nombre(this->Pasaporte2Copy->getgenero());
        QString nuevaFecha = this->generar_fecha(this->camposValidos[1]);
        QString nuevoPaisResidencia = this->generar_paisresidencia(this->camposValidos[2]);
        this->PaisResidenciaCreado = new PaisResidencia(nuevoNombre,nuevaFecha,nuevoPaisResidencia);
    }

    return this->PaisResidenciaCreado;
}

QString generador_paisresidencia::generar_nombre(char genero)
{
    QString nombre_generado = this->Pasaporte2Copy->getnombre(); // string con el nombre que se va a pickear

    if (!this->camposValidos[0]){
        if (this->camposLocura[0]){
            nombre_generado = this->locura->CambiarCadena(this->dificultad,this->Pasaporte2Copy->getnombre());
        }else{
            do{
                switch (genero){
                case 'H':

                    nombre_generado = this->nombre_hombres[this->rand.bounded(this->nombre_hombres.size())];
                    break;
                case 'M':
                    nombre_generado = this->nombre_mujeres[this->rand.bounded(this->nombre_mujeres.size())];
                    break;
                case 'X':

                    nombre_generado = this->nombre_x[this->rand.bounded(this->nombre_x.size())];
                }
            }while(nombre_generado != this->Pasaporte2Copy->getnombre());
        }
        nombre_generado += " " + this->apellidos[this->rand.bounded(this->apellidos.size())];
    }
    return nombre_generado;
}

QString generador_paisresidencia::generar_paisresidencia(bool valido)
{
    QString nacionalidad_generada;
    if (valido){
        nacionalidad_generada = generarPaisValido();
    } else {
        nacionalidad_generada = generarPaisInvalido();
    }

    return nacionalidad_generada;
}

QString generador_paisresidencia::generarPaisValido()
{
    int sorteo = rand.bounded(10);
    auto nacionalidad = Pasaporte2Copy->getnacionalidad();
    if (sorteo <= Probabilidades && checkearSiEsValido(nacionalidad))
        return nacionalidad;

    QString NuevoPais = paisesValidos[rand.bounded(paisesValidos.size())];
    return NuevoPais;
}

QString generador_paisresidencia::generarPaisInvalido()
{
    QString paisGenerado;

    if (this->camposLocura[2]){
        paisGenerado = this->Pasaporte2Copy->getnacionalidad();
        paisGenerado = this->locura->CambiarCadena(this->dificultad, paisGenerado);
        return paisGenerado;
    }

    int sorteo = this->rand.bounded(paisesInvalidos.size());
    paisGenerado = this->paisesInvalidos[sorteo];

    return paisGenerado;
}

QString generador_paisresidencia::generar_fecha(bool valido)
{
    int generar_anio , generar_mes , generar_dia , cant_dias ;  // cant dias es porque no todos los meses tienen la misma cantidad de dias
    int fecha_min  = this->rules->getFechaMinPermitida();
    int fecha_max = this->rules->getFechaMaxPermitida();
    QString fecha = this->Pasaporte2Copy->getfecha_nacimiento();
    if(!valido){
        if (camposLocura[1]){
            QString fecha_pasaporte = this->Pasaporte2Copy->getfecha_nacimiento();
            fecha = this->locura->CambiarCadena(this->dificultad, fecha_pasaporte);
        }else{
            if (this->rand.bounded(2) == 0) {
                generar_anio = fecha_min - 1 - this->rand.bounded(10); // genera un anio menor que fechamin, hasta 10 años menos
            } else {
                generar_anio = fecha_max + 1 + this->rand.bounded(10); // genera un anio mayor a fechamax, hasta 10 años mas
            }
            generar_mes = 1 + this->rand.bounded(12);
            cant_dias = obt_dias(generar_mes,generar_anio);
            generar_dia = 1 + this->rand.bounded(cant_dias);
            fecha = QString::number(generar_dia) + "/" +  QString::number(generar_mes) + "/" +  QString::number(generar_anio);
        }
    }

    return fecha;
}

void generador_paisresidencia::CamposLocura(int Probabilidades)
{
    int cantidadCamposInvalidos = 0;
    int sorteo;

    while (!cantidadCamposInvalidos){
        for (int i = 0; i < 3; ++i){
            sorteo = this->rand.bounded(10);
            if (sorteo < Probabilidades){
                this->camposLocura[i] = false;
                cantidadCamposInvalidos++;
            }
        }
    }
}

void generador_paisresidencia::setSeed(quint32 seed)
{
    rand.seed(seed);
    locura->setSeed(seed);
}

bool generador_paisresidencia::checkearSiEsValido(QString paisAevaluar)
{
    for (const auto& pais: paisesValidos)
        if (paisAevaluar == pais)
            return true;
    return false;
}

#include "generador_paisresidencia.h"


generador_paisresidencia::generador_paisresidencia(ReglasNivel1 * rules) : Generar_pasaporte(rules) {
    this->rules = rules;
    this->rand = new QRandomGenerator;
    quint32 Semilla = static_cast<quint32>(time(NULL));
    this->rand->seed(Semilla);
    this->locura = new LocuraCaracteres(this->rand);
}

PaisResidencia *generador_paisresidencia::CrearPaisResidencia(Pasaporte *Pasaporte2copy, bool valido, int dificultad)
{
    this->Pasaporte2Copy = Pasaporte2copy;
    this->dificultad = dificultad;
    int Probabilidades;
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
    if(valido){
        QString PaisResidenciaGenerado = this->generar_nacionalidad(valido);
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
    int valor_centinela; //para pickear indice
    if (!this->camposValidos[0]){
        if (this->camposLocura[0]){
            nombre_generado = this->locura->CambiarCadena(this->dificultad,this->Pasaporte2Copy->getnombre());
        }else{
            do{
                switch (genero){
                case 'H':
                    valor_centinela = this->rand->bounded(this->max_hombres);
                    nombre_generado = this->nombre_hombres[valor_centinela];
                    break;
                case 'M':
                    valor_centinela = this->rand->bounded(this->max_mujeres);
                    nombre_generado = this->nombre_mujeres[valor_centinela];
                    break;
                case 'X':
                    valor_centinela = this->rand->bounded(this->max_x);
                    nombre_generado = this->nombre_x[valor_centinela];
                }
            }while(nombre_generado != this->Pasaporte2Copy->getnombre());
        }
        nombre_generado += " " + this->apellidos[this->rand->bounded(this->max_apellidos)];
    }
    return nombre_generado;
}

QString generador_paisresidencia::generar_paisresidencia(bool valido)
{
    int tamanio;
    int indice_generar; //para usar rand y elegir alguno de los indices;
    QString nacionalidad_generada = this->Pasaporte2Copy->getnacionalidad();
    if (!valido){
        if (this->camposLocura[2]){
            QString nacionalidad_pasaporte = this->Pasaporte2Copy->getnacionalidad();
            nacionalidad_generada = this->locura->CambiarCadena(this->dificultad,nacionalidad_pasaporte);
        } else{
            indice_generar = this->rand->bounded(this->max_nacionalidades - tamanio);
            nacionalidad_generada = this->nacionalidades[indice_generar];
        }
    }

    return nacionalidad_generada;
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
            if (this->rand->bounded(2) == 0) {
                generar_anio = fecha_min - 1 - this->rand->bounded(10); // genera un anio menor que fechamin, hasta 10 años menos
            } else {
                generar_anio = fecha_max + 1 + this->rand->bounded(10); // genera un anio mayor a fechamax, hasta 10 años mas
            }
            generar_mes = 1 + this->rand->bounded(12);
            cant_dias = obt_dias(generar_mes,generar_anio);
            generar_dia = 1 + this->rand->bounded(cant_dias);
            fecha = QString::number(generar_dia) + "/" +  QString::number(generar_mes) + "/" +  QString::number(generar_anio);
        }
    }

    return fecha;
}

void generador_paisresidencia::CamposLocura(int Probabilidades)
{
    int cantidadCamposInvalidos = 0;
    int sorteo;
    // Hasta no generarse por lo menos 1 campo valido, no sale del while.
    qDebug() << "Bucle de generar campos invalidos pasaporte";
    while (!cantidadCamposInvalidos){
        for (int i = 0; i < 3; ++i){
            sorteo = this->rand->bounded(10);
            if (sorteo < Probabilidades){
                this->camposLocura[i] = false;
                cantidadCamposInvalidos++;
            }
        }
    }
}

void generador_paisresidencia::resetRules(ReglasNivel1 *rules)
{
    this->rules = rules;
}

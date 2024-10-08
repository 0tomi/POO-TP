#include "../Generadores/generador_pasaporte.h"
#include <QDebug>
#include <QTime>

Generar_pasaporte::Generar_pasaporte() {
    LectorArchivos archivo(":/Resources/ArchivosTexto/mujeres.txt");
    this->nombre_mujeres = archivo.getVector();
    this->max_mujeres = archivo.getTopeArray();

    archivo.LeerArchivoNuevo(":/Resources/ArchivosTexto/hombres.txt");
    this->nombre_hombres = archivo.getVector();
    this->max_hombres = archivo.getTopeArray();

    archivo.LeerArchivoNuevo(":/Resources/ArchivosTexto/x.txt");
    this->nombre_x = archivo.getVector();
    this->max_x = archivo.getTopeArray();

    archivo.LeerArchivoNuevo(":/Resources/ArchivosTexto/apellidos.txt");
    this->apellidos = archivo.getVector();
    this->max_apellidos = archivo.getTopeArray();

    quint32 Semilla = QTime::currentTime().msec();;
    this->rand.seed(Semilla);
}

void Generar_pasaporte::Inicializar(ReglasNivel1 *rules, quint32 seed)
{
    this->setSeed(seed);
    this->rules = rules;
    this->nacionalidades = this->rules->getPaises();
}

// Función para obtener el número de días en un mes y año dados
int Generar_pasaporte::obt_dias(int mes, int año) {
    switch (mes) {
    case 1:  // Enero
    case 3:  // Marzo
    case 5:  // Mayo
    case 7:  // Julio
    case 8:  // Agosto
    case 10: // Octubre
    case 12: // Diciembre
        return 31;
    case 4:  // Abril
    case 6:  // Junio
    case 9:  // Septiembre
    case 11: // Noviembre
        return 30;
    case 2:  // Febrero
        // Verificar si es año bisiesto
        if ((año % 4 == 0 && año % 100 != 0) || (año % 400 == 0))
            return 29;
        else
            return 28;
    default:
        throw ("mes invalido");
    }
}

// como generar documentos validos o no
QString Generar_pasaporte::generar_fecha(bool valido){
    int generar_anio , generar_mes , generar_dia , cant_dias ;  // cant dias es porque no todos los meses tienen la misma cantidad de dias
    int fecha_min  = this->rules->getFechaMinPermitida();
    int fecha_max = this->rules->getFechaMaxPermitida();
    if (valido){ //genera una fecha valida
        generar_anio = this->rand.bounded(fecha_min ,fecha_max + 1) ;
        generar_mes = 1 + this->rand.bounded(12);
        cant_dias = obt_dias(generar_mes,generar_anio);
        generar_dia = 1 + this->rand.bounded(cant_dias);
    } else{ // genera una fecha invalida
        if (this->rand.bounded(2) == 0) {
            generar_anio = fecha_min - 1 - this->rand.bounded(10); // genera un anio menor que fechamin, hasta 10 años menos
        } else {
            generar_anio = fecha_max + 1 + this->rand.bounded(10); // genera un anio mayor a fechamax, hasta 10 años mas
        }
        generar_mes = 1 + this->rand.bounded(12);
        cant_dias = obt_dias(generar_mes,generar_anio);
        generar_dia = 1 + this->rand.bounded(cant_dias);
    }
    QString fecha = QString::number(generar_dia) + "/" +  QString::number(generar_mes) + "/" +  QString::number(generar_anio);
    return fecha;
}

void Generar_pasaporte::setSeed(quint32 seed)
{
    rand.seed(seed);
}

void Generar_pasaporte::generar_camposValidos(bool valido, int Probabilidad){
    if (valido){
        for (int i = 0; i < 3; ++i)
            this->campos_validos[i] = true;
    } else {
        int cantidadCamposInvalidos = 0;
        int sorteo;
        // Hasta no generarse por lo menos 1 campo valido, no sale del while.
        while (!cantidadCamposInvalidos)
            for (int i = 0; i < 3; ++i){
                sorteo = this->rand.bounded(10);
                if (sorteo < Probabilidad){
                   this->campos_validos[i] = false;
                    cantidadCamposInvalidos++;
                }
            }
    }
}

QString Generar_pasaporte::generar_nacionalidad(bool valido){
    if(valido){ // genera una nacionalidad valida
        vector<QString>PaisesValidos = this->rules->getPaisesPermitidos();
        return PaisesValidos[this->rand.bounded(PaisesValidos.size())];
    } else{
        vector<QString>PaisesInvalidos = this->rules->getPaisesInvalidos();
        return PaisesInvalidos[this->rand.bounded(PaisesInvalidos.size())];
    }
}
QString Generar_pasaporte::generar_estado_civil(char genero, bool valido){
    int valorCentinela; // para guardar el valor del rand;
    QString estado_civil_generado;
    if(valido) { // generar estado civil valido;
        vector<QString> estados_civiles_validos = this->rules->getEstadoCivilPermitido();
        valorCentinela = this->rand.bounded(estados_civiles_validos.size());
        estado_civil_generado = estados_civiles_validos[valorCentinela];
    } else{ // genera estado civil invalido
        vector<QString> estados_civiles_invalidos = this->rules->getEstadoCivilInvalido();
        valorCentinela = this->rand.bounded(estados_civiles_invalidos.size());
        estado_civil_generado = estados_civiles_invalidos[valorCentinela];
    }
    switch (genero){
    case 'H': // hombre
        estado_civil_generado += "o";
        break;
    case 'M': // mujer
        estado_civil_generado += "a";
        break;
    case 'X': // ni idea
        estado_civil_generado += "x";
        break;
    }
    return estado_civil_generado;
}
QString Generar_pasaporte::generar_nombre(char genero){
    QString nombre_generado; // string con el nombre que se va a pickear
    int valor_centinela; //para pickear indice
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
    nombre_generado += " " + this->apellidos[this->rand.bounded(this->max_apellidos)];
    return nombre_generado;
}

Pasaporte * Generar_pasaporte::crear_pasaporte(bool Validez, NPCcomun * InfoNPC, int dificultad){
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

    generar_camposValidos(Validez, Probabilidades);

    QString fecha_generada = generar_fecha(this->campos_validos[0]);
    QString nacionalidad_generada = generar_nacionalidad(this->campos_validos[1]);
    QString estado_civil_generado = generar_estado_civil(InfoNPC->getGenero(), this->campos_validos[2]);
    QString nombre_generado = generar_nombre(InfoNPC->getGenero());

    this->Pasaporte_generado = new Pasaporte(nombre_generado,fecha_generada,InfoNPC->getGenero(),nacionalidad_generada,estado_civil_generado);
    // Seteamos la Skin
    Pasaporte_generado->setSkinNPC(InfoNPC->getSkinDocs());

    return this->Pasaporte_generado;
}

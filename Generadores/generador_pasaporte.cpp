#include "../Generadores/generador_pasaporte.h"



Generar_pasaporte::Generar_pasaporte(ReglasNivel1 * rules, AtributosComunes * atributos) {
    LectorArchivos archivo(":/Resources/ArchivosTexto/hombres.txt");
    this->nombre_mujeres = archivo.getArray();
    this->max_mujeres = archivo.getTopeArray();
    archivo.LeerArchivoNuevo(":/Resources/ArchivosTexto/hombres.txt");
    this->nombre_hombres = archivo.getArray();
    this->max_hombres = archivo.getTopeArray();
    archivo.LeerArchivoNuevo(":/Resources/ArchivosTexto/hombres.txt");
    this->nombre_x = archivo.getArray();
    this->max_x = archivo.getTopeArray();
    this->rules = rules;
    this->atributos = atributos;
    this->nacionalidades = atributos->getPaises(this->max_nacionalidades);
}
// Función para obtener el número de días en un mes y año dados
int obt_dias(int mes, int año) {
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
    int generar_anio, generar_mes, generar_dia, cant_dias;  // cant dias es porque no todos los meses tienen la misma cantidad de dias
    int fecha_min  = this->rules->getFechaMinPermitida();
    int fecha_max = this->rules->getFechaMaxPermitida();
    if (valido){ //genera una fecha valida

        int generar_anio =  1 + fecha_min + rand() %  (fecha_max - fecha_min - 1) ;
        int generar_mes = 1 + rand() % 12;
        cant_dias = obt_dias(generar_mes,generar_anio);
        generar_dia = 1 + rand() % cant_dias;
    } else{ // genera una fecha invalida

        generar_anio = (fecha_min - 10) + rand() % (fecha_min - (fecha_min - 10)) ;
        int generar_mes = 1 + rand() % 12;
        cant_dias = obt_dias(generar_mes,generar_anio);
        generar_dia = 1 + rand() % cant_dias;
    }
    QString fecha = QString::number(generar_dia) + "/" +  QString::number(generar_mes) + "/" +  QString::number(generar_anio);
    return fecha;
}
//me llega si es valido, reglas, genero
QString Generar_pasaporte::generar_nacionalidad(bool valido){
    int tamanio; // supongo que getnacionalidades que devuelve un array de enteros por referencia "devuelve" el tamanio
    int * indices_paises = this->rules->getPaisesPermitidos(tamanio); // para conseguir las nacionalidades permitidas
    int indice_generar; //para usar rand y elegir alguno de los indices;
    QString nacionalidad_generada; // lo que se devuelve que es la nacionalidad, valida o no
    if(valido){ // genera una nacionalidad invalida
        indice_generar = rand() % tamanio;
        nacionalidad_generada = nacionalidades[indices_paises[indice_generar]];
    } else{
        indice_generar = tamanio + rand() % (this->max_nacionalidades - tamanio);
        nacionalidad_generada = this->nacionalidades[indice_generar];
    }
    return nacionalidad_generada;
}
QString Generar_pasaporte::generar_estado_civil(char genero, bool valido){
    int tamanio; // cant de estados civiles
    int tamanio2; // cant de estados civiles validos
    int valorCentinela; // para guardar el valor del rand;
    QString * estados_civiles = this->atributos->getEstadosCiviles(tamanio); // para conseguir estados civiles
    QString * estados_civiles_validos = this->rules->getEstadoCivilPermitido(tamanio2);
    QString estado_civil_generado;
    if(valido) { // generar estado civil valido;
        valorCentinela = rand() % tamanio2;

        estado_civil_generado = estados_civiles[valorCentinela];

    } else{ // genera estado civil invalido
        valorCentinela = tamanio2 + rand() % (tamanio - tamanio2);

        estado_civil_generado = estados_civiles[valorCentinela];
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
        valor_centinela = rand() % this->max_hombres;
        nombre_generado = this->nombre_hombres[valor_centinela];
        break;
    case 'M':
        valor_centinela = rand() % this->max_mujeres;
        nombre_generado = this->nombre_mujeres[valor_centinela];
        break;
    case 'X':
        valor_centinela = rand() % this->max_x;
        nombre_generado = this->nombre_x[valor_centinela];
    }
    return nombre_generado;
}
Pasaporte * Generar_pasaporte::crear_pasaporte(bool valido, char genero){
    bool fecha_valida = valido;
    bool nacionalidad_valida = valido;
    bool estado_civil_valido = valido;

    if (!valido) {
        int atributos_invalidos = 0;

        // elige para que no todos sean invalidos
        fecha_valida = (rand() % 2 == 0);
        if (!fecha_valida) atributos_invalidos++;

        nacionalidad_valida = (rand() % 2 == 0);
        if (!nacionalidad_valida) atributos_invalidos++;

        estado_civil_valido = (rand() % 2 == 0);
        if (!estado_civil_valido) atributos_invalidos++;

        // para que al menos uno sea invalido
        if (atributos_invalidos == 0) {
            int atributo_a_invalidar = rand() % 3;
            switch (atributo_a_invalidar) {
            case 0:
                fecha_valida = false;
                break;
            case 1:
                nacionalidad_valida = false;
                break;
            case 2:
                estado_civil_valido = false;
                break;
            }
        }
    }
    QString fecha_generada = generar_fecha(fecha_valida);
    QString nacionalidad_generada = generar_nacionalidad(nacionalidad_valida);
    QString estado_civil_generado = generar_estado_civil(genero, estado_civil_valido);
    QString nombre_generado = generar_nombre( genero);

    this->Pasaporte_generado = new Pasaporte(nombre_generado,fecha_generada,genero,nacionalidad_generada,estado_civil_generado);
    return this->Pasaporte_generado;

}

void Generar_pasaporte::restartReglas(ReglasNivel1 *rules)
{
    this->rules = rules;
}

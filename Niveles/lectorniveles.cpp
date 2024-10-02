#include "lectorniveles.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>

// Constructor que inicializa la ruta del archivo
LectorNiveles::LectorNiveles(): expNumeros(R"(.*: (\d+))"), expPaises(R"(Nombres de paises validos: (.+))")
{

}

LectorNiveles::LectorNiveles(const QString& rutaArchivo)
    : rutaArchivo(rutaArchivo), expNumeros(R"(.*: (\d+))"), expPaises(R"(Nombres de paises validos: (.+))") {}

void LectorNiveles::actualizarRuta(const QString &NEWrutaArchivo)
{
    rutaArchivo = NEWrutaArchivo;
}

// Método que lee el archivo y extrae los datos
bool LectorNiveles::leerDatos() {
    paisesValidos.clear();
    datos.clear();                  // Limpiamos el mapa cada que se lee un nuevo archivo
    QFile archivo(rutaArchivo);
    if (!archivo.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "No se puede abrir el archivo:" << rutaArchivo;
        return false;
    }

    QTextStream in(&archivo);
    while (!in.atEnd()) {
        QString linea = in.readLine();
        matchNumeros = expNumeros.match(linea);

        if (matchNumeros.hasMatch()) {
            QString clave = linea.section(':', 0, 0).trimmed();  // Obtener el texto antes de los dos puntos
            int valor = matchNumeros.captured(1).toInt();               // Obtener el valor numérico después de los dos puntos
            datos.insert(clave, valor);                          // Insertar en el mapa
        }

        // Capturar los nombres de países
        matchPaises = expPaises.match(linea);
        if (matchPaises.hasMatch()) {
            QString paises = matchPaises.captured(1);            // Obtener la lista de países como una cadena
            paisesValidos = paises.split(' ', Qt::SkipEmptyParts);  // Separar por espacios y almacenar en la lista
        }
    }

    archivo.close();
    return true;
}

bool LectorNiveles::leerDatos(const QString &ruta)
{
    rutaArchivo = ruta;
    return leerDatos();
}

// Método para obtener un valor dado su clave
int LectorNiveles::obtenerValor(const QString& clave) const {
    if (datos.contains(clave)) {
        return datos.value(clave);
    }
    return -1;  // Retorna -1 si la clave no existe
}

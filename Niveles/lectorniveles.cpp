#include "lectorniveles.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>

// Constructor que inicializa la ruta del archivo
LectorNiveles::LectorNiveles()
{

}

LectorNiveles::LectorNiveles(const QString& rutaArchivo)
    : rutaArchivo(rutaArchivo) {}

void LectorNiveles::actualizarRuta(const QString &NEWrutaArchivo)
{
    rutaArchivo = NEWrutaArchivo;
}

// Método que lee el archivo y extrae los datos
bool LectorNiveles::leerDatos() {
    datos.clear();                  // Limpiamos el mapa cada que se lee un nuevo archivo
    QFile archivo(rutaArchivo);
    if (!archivo.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "No se puede abrir el archivo:" << rutaArchivo;
        return false;
    }

    QTextStream in(&archivo);
    QRegularExpression regex(R"(.*: (\d+))");  // Expresión regular para capturar el número después de los dos puntos

    while (!in.atEnd()) {
        QString linea = in.readLine();
        match = regex.match(linea);

        if (match.hasMatch()) {
            QString clave = linea.section(':', 0, 0).trimmed();  // Obtener el texto antes de los dos puntos
            int valor = match.captured(1).toInt();               // Obtener el valor numérico después de los dos puntos
            datos.insert(clave, valor);                          // Insertar en el mapa
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

#ifndef LECTOR_NIVELES_H
#define LECTOR_NIVELES_H

#include <QString>
#include <QMap>
#include <QRegularExpression>
#include <list>
#include <QStringList> // Usamos QStringList porque es mucho mas sencillo para la lectura de datos

class LectorNiveles {
public:
    // Constructor que recibe la ruta del archivo
    LectorNiveles();
    LectorNiveles(const QString& rutaArchivo);
    void actualizarRuta(const QString& rutaArchivo);

    // Método para leer el archivo y extraer los datos
    bool leerDatos();
    bool leerDatos(const QString& ruta);

    // Método para obtener un valor asociado a una clave
    int obtenerValor(const QString& clave) const;
    std::list<QString> getListaPaisesValidos() const;

private:
    QRegularExpressionMatch matchNumeros;      // Para ubicar la informacion despues de los 2 puntos
    QRegularExpressionMatch matchPaises;
    QString rutaArchivo;               // Ruta del archivo de texto
    QMap<QString, int> datos;          // Mapa que almacena las claves y valores
    QStringList paisesValidos;
};

#endif // LECTOR_NIVELES_H

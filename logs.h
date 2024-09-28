#ifndef LOGS_H
#define LOGS_H

#include <QString>
#include <QDateTime>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QCoreApplication>
#include <vector>
#include <QDebug>
#include <QDir>
using namespace std;
class Logs : public QObject
{
    Q_OBJECT
private:
    int cantLogs;
    vector<QString>VectorLogs;
    const QString DireccionTXT = QCoreApplication::applicationDirPath() + "/logs";
    const QString CantLogsTXT = QCoreApplication::applicationDirPath() + "/cantlogs.txt";
    const QString DireccionCarpeta = QCoreApplication::applicationDirPath();
public:
    Logs();
    void SaveLogs();
    ~Logs();
public slots:
    void RecibirLogs(QString Log);

};
#endif // LOGS_H

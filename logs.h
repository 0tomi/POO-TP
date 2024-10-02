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
    const QString BuildPath = QCoreApplication::applicationDirPath();
    const QString DireccionCarpeta = BuildPath + "/logs";
    const QString CantLogsTXT = DireccionCarpeta + "/cantlogs.txt";
public:
    Logs();
    void SaveLogs();
    ~Logs();
public slots:
    void RecibirLogs(QString Log);

};
#endif // LOGS_H

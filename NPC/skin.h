#ifndef SKIN_H
#define SKIN_H
#include <QString>

class Skin
{
public:
    Skin();
    ~Skin();

    QString getCaraURL() const;
    void setCara(const QString &newCara);

    QString getCejasURL() const;
    void setCejas(const QString &newCejas);

    QString getOjosURL() const;
    void setOjos(const QString &newOjos);

    QString getNarizURL() const;
    void setNariz(const QString &newNariz);

    QString getBocaURL() const;
    void setBoca(const QString &newBoca);

    QString getPelo() const;
    void setPelo(const QString &newPelo);

    QString getGorro() const;
    void setGorro(const QString &newGorro);

private:
    QString gorro, pelo, cara, cejas, ojos, nariz, boca;
};

#endif // SKIN_H

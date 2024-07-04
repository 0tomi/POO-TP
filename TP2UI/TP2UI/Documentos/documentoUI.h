#ifndef DOCUMENTOUI_H
#define DOCUMENTOUI_H

#include <QWidget>

namespace Ui {
class Documento;
}

class Documento : public QWidget
{
    Q_OBJECT

public:
    explicit Documento(QWidget *parent = nullptr);
    ~Documento();

private:
    virtual void clickIzqEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    QPoint m_dragStartPosition;

private:
    Ui::Documento *ui;
};

#endif // DOCUMENTOUI_H

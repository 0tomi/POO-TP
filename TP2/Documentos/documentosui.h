#ifndef DOCUMENTOSUI_H
#define DOCUMENTOSUI_H

#include <QWidget>

namespace Ui {
class DocumentosUI;
}

class DocumentosUI : public QWidget
{
    Q_OBJECT

public:
    explicit DocumentosUI(QWidget *parent = nullptr);
    ~DocumentosUI();

protected:
    virtual void clickIzqEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    QPoint m_dragStartPosition;

private:
    Ui::DocumentosUI *ui;
};

#endif // DOCUMENTOSUI_H

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
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    QPoint m_dragStartPosition;

private:
    Ui::DocumentosUI *ui;
};

#endif // DOCUMENTOSUI_H

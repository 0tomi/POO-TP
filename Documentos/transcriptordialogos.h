#ifndef TRANSCRIPTORDIALOGOS_H
#define TRANSCRIPTORDIALOGOS_H

#include <QWidget>

namespace Ui {
class TranscriptorDialogos;
}

class TranscriptorDialogos : public QWidget
{
    Q_OBJECT

public:
    explicit TranscriptorDialogos(QWidget *parent = nullptr);
    ~TranscriptorDialogos();

private:
    Ui::TranscriptorDialogos *ui;
};

#endif // TRANSCRIPTORDIALOGOS_H


#ifndef VARTABCLASS_H
#define VARTABCLASS_H

#include <QWidget>
#include <QString>
#include "globalvariables.h"

namespace Ui {
class VarTabClass;
}

class VarTabClass : public QWidget
{
    Q_OBJECT

public:
    explicit VarTabClass(QWidget *parent = 0);
    ~VarTabClass();
    int id;
    QString ButtonText;
    int NumberOfOutcomes;

signals:
    void deleteit(int idd);
    void SendButtonText(int btnnum, QString txt);
    void SendNumberOfOutcomes(int btnnum, int NOO);
private slots:
    void on_DeleteBranch_clicked();

    void on_Yes_clicked();

    void on_No_clicked();

    void on_ButtonText_textChanged(const QString &arg1);

    void on_NumberOfOutcomes_valueChanged(int arg1);

    void slotfillbuttonText(QString txt, int neededid);

    void slotfillNumberOfOutcomes(int NOO, int neededid);

private:
    Ui::VarTabClass *ui;
};

#endif // VARTABCLASS_H

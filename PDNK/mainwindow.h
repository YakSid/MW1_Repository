#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore>
#include <QtGui>
#include <QMessageBox>
#include "GlobalVariables.h"
#include "infonode.h"
#include "picturenode.h"
#include "startwindow.h"
#include "vartabclass.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
    void fillButtonText(QString txt);
    void fillNumberOfOutcomes(int NOO);
private slots:
    void on_needMOfficer_stateChanged(int arg1);

    void on_needSOfficer_stateChanged(int arg1);

    void on_needBoss_stateChanged(int arg1);

    void on_spinBoxAmount_valueChanged(int arg1);

    void on_spinBoxMOfficer_valueChanged(int arg1);

    void on_spinBoxSOfficer_valueChanged(int arg1);

    void on_spinBoxBoss_valueChanged(int arg1);

    void on_POleft_valueChanged(int arg1);

    void on_POright_valueChanged(int arg1);

    void on_SaveQuest_clicked();

    void on_UpdateButton_clicked();

    void on_NodeDescription_textChanged();

    void on_NodeFormulas_textChanged();

    void on_AmountOfFirstNodes_valueChanged(int arg1);

    void slotFromPictureNode();

    void slotHide(bool Hide);

    void slotMyNumIs(int smth);

    void slotsetScrolls(int prev, int next);

    void on_AmountOfSelectableVariants_valueChanged(int arg1);

    void on_TESTBUTTON_clicked();

    void TabDelete(int ind);

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    PictureNode *circle;
    InfoNode *info;
    VarTabClass *vart;
};

#endif // MAINWINDOW_H

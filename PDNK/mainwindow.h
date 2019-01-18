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
    //Переменные
    QString FileDBName;
    QString WriterName;
    QString questcount; // string analog of QuestsCounter
    int QuestsCounter;
    QString IDQuest;
    //info global
    QString OrderDepartment;
    QString OrderName;
    QString OrderDescription;
    bool OrderIsInner; //1 - vnutrenniy, 0 - vneshniy
    int POleft; int POright; //uslovie1
    QString AdditionalConditions; //ostal'nie usloviya. Temporally in string
    int AllAmount;
    int NumberOrdinary, NumberMOfficer, NumberSOfficer, NumberBoss;
    QString AdditionalConditionsForStaff; // Temporally in string
    int AmountOfFirstNodes = 1;
    //
    QVector <InfoNode*> infoItems;
    QVector <PictureNode*> Items;
    QVector < QVector <QString> > Node;
    QVector <QString> tmpLine;
    QString tmpName;
    int SelectableVariantsOld=0;
    int tmpSize; // for updating QuestsCounter
    int CNNTickets=0; //ChekedNewNodeTicket Сколько раз можно избежать цикла инкрементации при создании нового вартаба
    bool FirstLaunching=true;
    //

signals:
    void fillButtonText(QString txt, int neededid, int idnode);
    void fillNumberOfOutcomes(int NOO, int neededid, int idnode);
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

    void on_AmountOfSelectableVariants_valueChanged(int arg1);

    void on_TESTBUTTON_clicked();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    PictureNode *circle;
    InfoNode *info;
    VarTabClass *vart;
};

#endif // MAINWINDOW_H

#ifndef INFONODE_H
#define INFONODE_H

#include <QFile>
#include <QTextStream>
#include <QObject>
#include "GlobalVariables.h"

class InfoNode : public QObject
{
    Q_OBJECT
public:
    explicit InfoNode(QObject *parent = 0);
    InfoNode(int n);
    ~InfoNode();

    int lvl,num; //Уровень, на котором находится узел и его номер в уровне
    int itemnum; //Порядковый номер узла
    //Общая информация
    QString NodeID; //Имя, пока заменяется порядковым номером itemnum
    QString NodeDescription;
    QString NodeFormulas; // Temporally in string
    int AmountOfSelectableVariants; // - количество кнопок, которое является идентификатором в массивах
    //Блок данных с кнопок
    QString text[7]; //текст на каждой кнопке
    int NumberOfOutcomes[7]; //Количество исходов на каждой кнопке
    int NextNodeID[7][7]; //Вместо ID - itemnum //[В этой кнопке][Этот айди ауткома]
    int AllNextNodesAmount; // формулу для вычисления НАПИСАТЬ
    int PrevNodeID;
    //
    void PrepareLinks(QVector <InfoNode*> links, QVector <QString> ids);
    void SaveToFile(QString dbname);
    void FillInformation(int btnnum, QString txt, int NumOfOut, QVector<int> nxt, int prv);
private slots:
    void setButtonText(int btnnum, QString txt);
    void setNumberOfOutcomes(int btnnum, int NOO);
};

#endif // INFONODE_H

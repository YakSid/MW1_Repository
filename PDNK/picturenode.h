#ifndef PICTURENODE_H
#define PICTURENODE_H

#include "GlobalVariables.h"
#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QDebug>

class PictureNode : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit PictureNode(QObject *parent = 0);
    PictureNode(int x, int y, int lvl, int num, int ki);
    ~PictureNode();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    /*enum {Type = UserType+1};
    int type() const
    {
        return Type;
    }*/

    int lvl,num; //Уровень, на котором находится узел и его номер в уровне
    int itemnum; //Порядковый номер узла
    int x,y; //coordinates on graphicscene
    bool Selected; // paint it yellow
    bool Extreme; // blue. It is final if AmountOfSelectableVariants is 0, or first
    bool Empty; // white
    bool Editing; // red
    bool Done; // green

    void deselect();
    void setExtreme();
    void setEmpty();
    void setEditing();
    void setDone();
signals:
    void signal1();
    void signalHide(bool Hide);
    void MyNumIs(int smth);
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
};

#endif // PICTURENODE_H

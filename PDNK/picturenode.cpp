#include "picturenode.h"

PictureNode::PictureNode(int x, int y, int lvl, int num, int ki)
{
    Selected = false;
    Extreme = false;
    Empty = true;
    Editing = false;
    Done = false;
    this->x=x; this->y=y;
    this->lvl=lvl; this->num=num;
    this->itemnum=ki;
}

PictureNode::PictureNode(QObject *parent)
    : QObject(parent), QGraphicsItem()
{

}

PictureNode::~PictureNode()
{

}

QRectF PictureNode::boundingRect() const
{
    return QRectF(x,y,10,10);
}

void PictureNode::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rec = boundingRect();
    QBrush brush(Qt::white);

    if (Selected)
    {
        brush.setColor(Qt::yellow);
    }
    else
    {
        if (Extreme)
        {
            brush.setColor(Qt::blue);
        }
        if (Empty)
        {
            brush.setColor(Qt::white);
        }
        if (Editing)
        {
            brush.setColor(Qt::red);
        }
        if (Done)
        {
            brush.setColor(Qt::green);
        }
    }

    QPen pen(Qt::black, 2);
    painter->setPen(pen);
    painter->drawEllipse(rec);
    QPainterPath path;
    path.addEllipse(x,y,10,10);
    painter->fillPath(path, brush);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}


void PictureNode::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (!Selected)
    {
        emit signal1();
        if (this->itemnum==0) emit signalHide(true);
        else emit signalHide(false);
        Selected = true;
        selectedlvl = this->lvl;
        selectednum = this->num;
        selectedk = this->itemnum;
        emit MyNumIs(itemnum);
    }
    else
    {
        Selected = false;
        emit signalHide(true);
    }
    update();
    QGraphicsItem::mousePressEvent(event);
}


void PictureNode::deselect()
{
    Selected = false;
    update();
}

void PictureNode::setExtreme()
{
    Extreme = true;
    if (Empty) Empty = false;
    if (Editing) Editing = false;
    if (Done) Done = false;
    update();
}

void PictureNode::setEmpty()
{
    Empty = true;
    if (Extreme) Extreme = false;
    if (Editing) Editing = false;
    if (Done) Done = false;
    update();
}

void PictureNode::setEditing()
{
    Editing = true;
    if (Extreme) Extreme = false;
    if (Editing) Editing = false;
    if (Done) Done = false;
    update();
}

void PictureNode::setDone()
{
    Done = true;
    if (Empty) Empty = false;
    if (Editing) Editing = false;
    if (Extreme) Extreme = false;
    update();
}

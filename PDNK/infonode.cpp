#include "infonode.h"

InfoNode::InfoNode(int n, int plvl, int pnum)
{
    AmountOfSelectableVariants = 0;
    AllNextNodesAmount = 0;
    this->itemnum=n;
    lvl = plvl;
    num = pnum;
    for (int i=0; i<7; i++)
    {
        NumberOfOutcomes[i] = 0;
        text[i] = "";
        for (int j=0; j<7; j++)
            NextNodeID[i][j]=0;
    }
}

InfoNode::InfoNode(QObject *parent)
    : QObject(parent)
{

}

InfoNode::~InfoNode()
{
}

void InfoNode::PrepareLinks(QVector <InfoNode*> links, QVector <QString> ids)
{
    for (int i=0; i<links.size(); i++)
    {
        ids[i]=links[i]->NodeID;
    }
}

void InfoNode::SaveToFile(QString dbname) // ПЕРЕДЕЛАТЬ, УЖЕ НЕ АКТУАЛЬНО
{
    /*QFile db(dbname);
    PrepareLinks(PreviousNode, PreviousNodeID);
    db.open(QIODevice::Append | QIODevice::Text);
    QTextStream writeStream(&db);
    writeStream << endl << "NodeID $" << NodeID << endl;
    writeStream << "NodeDescription $" << NodeDescription << "#" << endl;
    writeStream << "NodeFormulas $" << NodeFormulas << "#" << endl;
    writeStream << "AmountOfSelectableVariants $" << AmountOfSelectableVariants << endl;
    for (int i=0; i<Variants.size(); i++)
    {
        PrepareLinks(Variants[i].NextNode, Variants[i].NextNodeID);
        writeStream << "Variant" << i << "text $" << Variants[i].text << endl;
        writeStream << "Variant" << i << "NumberOfOutcomes $" << Variants[i].NumberOfOutcomes << endl;
        for (int j=0; j<Variants[i].NextNodeID.size(); j++)
        {
            writeStream << "Variant" << i << "NextNodeID" << j << " $" << Variants[i].NextNodeID[j] << endl;
        }
    }
    writeStream << "AllNextNodesAmount $" << AllNextNodesAmount << endl;
    for (int i=0; i<PreviousNodeID.size(); i++)
    {
        writeStream << "PreviousNodes" << i << " $" << PreviousNodeID[i] << endl;
    }
    db.close();*/
}

void InfoNode::setButtonText(int btnnum, QString txt)
{
    text[btnnum] = txt;
}

void InfoNode::setNumberOfOutcomes(int btnnum, int NOO)
{
    NumberOfOutcomes[btnnum] = NOO;
}

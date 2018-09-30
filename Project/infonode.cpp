#include "infonode.h"

InfoNode::InfoNode(int n)
{
    AmountOfSelectableVariants = 0;
    AllNextNodesAmount = 0;
    this->itemnum=n;
    //connect(vart,SIGNAL(SendButtonText(QString)), this, SLOT(GetButtonText(QString)));
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

void InfoNode::FillInformation(int btnnum, QString txt, int NumOfOut, QVector<int> nxt, int prv)
{
    text[btnnum]=txt;
    NumberOfOutcomes[btnnum]=NumOfOut;
    //ЗАПОЛНИТЬ
    PrevNodeID = prv;
}

void InfoNode::GetButtonText(int btnnum, QString txt)
{
    text[btnnum] = txt;
}

void InfoNode::GetNumberOfOutcomes(int btnnum, int NOO)
{
}

#include "mainwindow.h"
#include "ui_mainwindow.h"

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
int k=0; //kolvo nodes
//QString ABC  = "abcdefghijkl";
QVector < QVector <QString> > Node;
QVector <QString> tmpLine;
QString tmpName;
int selectedlvl=-1;
int selectednum=-1;
int selectedk = -1;
int SelectableVariantsOld=0;
int tmpSize; // for updating QuestsCounter

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //QTextCodec::setCodecForCStrings(QTextCodec::codecForName("cp1251"));

    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);

    ui->TabVariant->setVisible(false);

    QFile login("LoginInfo.txt");
    if (!login.exists())
    {
        StartWindow mStartWindow;
        mStartWindow.setModal(true);
        mStartWindow.exec();
    }
    login.open(QIODevice::ReadOnly);
    QTextStream in(&login);
    while (!in.atEnd())
    {
        WriterName = in.readLine();
        if (WriterName.contains("WriterName"))
        {
            for (int i=0; i<WriterName.size(); i++)
            {
                if (WriterName.at(i) == '$')
                {
                    WriterName.remove(0,i+1);
                    FileDBName = WriterName;
                    FileDBName += "'s_Quests_Database.txt";
                    ui->writerlabel->setText(WriterName);
                }
            }
        }
        questcount = in.readLine();
        if (questcount.contains("QuestsCounter"))
        {
            for (int i=0; i<questcount.size(); i++)
            {
                if (questcount.at(i) == '$')
                {
                    questcount.remove(0,i+1);
                    QuestsCounter = questcount.toInt();
                    ui->IDQuest->setText(WriterName + "'s_" + questcount);
                }
            }
        }
    }
    login.close();

    ui->NodeID->setVisible(false);
    ui->label_20->setVisible(false);
    ui->scrollAreaPrev->setVisible(false);
    ui->scrollAreaNext->setVisible(false);
    ui->label_21->setVisible(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_needMOfficer_stateChanged(int arg1)
{
    ui->spinBoxMOfficer->setEnabled(arg1);
    if (arg1)
    {
        ui->spinBoxMOfficer->setValue(1);
        ui->spinBoxMOfficer->setMinimum(1);
    }
    else
    {
        ui->spinBoxMOfficer->setMinimum(0);
        ui->spinBoxMOfficer->setValue(0);
    }
}

void MainWindow::on_needSOfficer_stateChanged(int arg1)
{
    ui->spinBoxSOfficer->setEnabled(arg1);
    if (arg1)
    {
        ui->spinBoxSOfficer->setValue(1);
        ui->spinBoxSOfficer->setMinimum(1);
    }
    else
    {
        ui->spinBoxSOfficer->setMinimum(0);
        ui->spinBoxSOfficer->setValue(0);
    }
}

void MainWindow::on_needBoss_stateChanged(int arg1)
{
    ui->spinBoxBoss->setEnabled(arg1);
    if (arg1)
    {
        ui->spinBoxBoss->setValue(1);
        ui->spinBoxBoss->setMinimum(1);
    }
    else
    {
        ui->spinBoxBoss->setMinimum(0);
        ui->spinBoxBoss->setValue(0);
    }
}

void MainWindow::on_spinBoxAmount_valueChanged(int arg1)
{
    int newAm = arg1 - ui->spinBoxMOfficer->value() - ui->spinBoxSOfficer->value() - ui->spinBoxBoss->value();
    QString newAmString = QString::number(newAm);
    ui->OrdinaryAmount->setText(newAmString);
}

void MainWindow::on_spinBoxMOfficer_valueChanged(int arg1)
{
    ui->spinBoxAmount->setMinimum(ui->spinBoxMOfficer->value()
                                  + ui->spinBoxSOfficer->value()
                                  + ui->spinBoxBoss->value());
    QString tstr = QString::number(ui->spinBoxAmount->value() - arg1
                                   - ui->spinBoxSOfficer->value()
                                   - ui->spinBoxBoss->value());
    ui->OrdinaryAmount->setText(tstr);
}

void MainWindow::on_spinBoxSOfficer_valueChanged(int arg1)
{
    ui->spinBoxAmount->setMinimum(ui->spinBoxMOfficer->value()
                                  + ui->spinBoxSOfficer->value()
                                  + ui->spinBoxBoss->value());
    QString tstr = QString::number(ui->spinBoxAmount->value() - arg1
                                   - ui->spinBoxMOfficer->value()
                                   - ui->spinBoxBoss->value());
    ui->OrdinaryAmount->setText(tstr);
}

void MainWindow::on_spinBoxBoss_valueChanged(int arg1)
{
    ui->spinBoxAmount->setMinimum(ui->spinBoxMOfficer->value()
                                  + ui->spinBoxSOfficer->value()
                                  + ui->spinBoxBoss->value());
    QString tstr = QString::number(ui->spinBoxAmount->value() - arg1
                                   - ui->spinBoxMOfficer->value()
                                   - ui->spinBoxSOfficer->value());
    ui->OrdinaryAmount->setText(tstr);
}

void MainWindow::on_POleft_valueChanged(int arg1)
{
    ui->POright->setMinimum(arg1+1);
}

void MainWindow::on_POright_valueChanged(int arg1)
{
    ui->POleft->setMaximum(arg1-1);
}

void MainWindow::on_SaveQuest_clicked()
{
    WriterName = ui->writerlabel->text();
    QFile db(FileDBName);

    db.open(QIODevice::Append | QIODevice::Text);
    QTextStream writeStream(&db);
    IDQuest = ui->IDQuest->text();
    OrderDepartment = ui->OrderDepartment->currentText();
    OrderName = ui->OrderName->text();
    OrderDescription = ui->OrderDescription->toPlainText();
    if (ui->Inner->isChecked()) OrderIsInner = true;
    else OrderIsInner = false;
    POleft = ui->POleft->value();
    POright = ui->POright->value();
    AdditionalConditions = ui->AdditionalConditions->toPlainText();
    AllAmount = ui->spinBoxAmount->value();
    NumberOrdinary = ui->OrdinaryAmount->text().toInt();
    NumberMOfficer = ui->spinBoxMOfficer->value();
    NumberSOfficer = ui->spinBoxSOfficer->value();
    NumberBoss = ui->spinBoxBoss->value();
    AdditionalConditionsForStaff = ui->AdditionalconditionsForStaff->toPlainText();
    AmountOfFirstNodes = ui->AmountOfFirstNodes->value();

    writeStream << "IDQuest $" << IDQuest << endl;
    writeStream << "OrderDepartment $" << OrderDepartment << endl;
    writeStream << "OrderName $" << OrderName << endl;
    writeStream << "OrderDescription $" << OrderDescription << "#" << endl;
    writeStream << "OrderIsInner $" << OrderIsInner << endl;
    writeStream << "POleft $" << POleft << endl;
    writeStream << "POright $" << POright << endl;
    writeStream << "AdditionalConditions $" << AdditionalConditions << "#" << endl;
    writeStream << "AllAmount $" << AllAmount << endl;
    writeStream << "NumberOrdinary $" << NumberOrdinary << endl;
    writeStream << "NumberMOfficer $" << NumberMOfficer << endl;
    writeStream << "NumberSOfficer $" << NumberSOfficer << endl;
    writeStream << "NumberBoss $" << NumberBoss << endl;
    writeStream << "AdditionalConditionsForStaff $" << AdditionalConditionsForStaff << "#" << endl;
    writeStream << "AmountOfFirstNodes $" << AmountOfFirstNodes << endl;
    writeStream << "================================" << endl << endl;
    db.close();
    QuestsCounter++;
    QString newquestcount = QString::number(QuestsCounter);

    QFile logfile("LoginInfo.txt");
    logfile.open(QIODevice::ReadWrite | QIODevice::Text);
    QTextStream in2(&logfile);
    while (!in2.atEnd())
    {
        questcount = in2.readLine();
        if (questcount.contains("QuestsCounter"))
        {
            tmpSize = questcount.size();
            for (int i=0; i<tmpSize; i++)
            {
                if (questcount.at(i) == '$')
                {
                    int bufsize; // razmer simvolov posle $ iznachal'no
                    bufsize = tmpSize-i;

                    if (QuestsCounter != 10)
                    {
                        in2.seek(in2.pos() - questcount.length()-2);
                        questcount.replace(i+1,questcount.size()-i,newquestcount);
                        in2 << questcount;
                    }
                    if (QuestsCounter == 10 || QuestsCounter == 100)
                    {
                        in2.seek(in2.pos() - questcount.length()-2);
                        questcount.replace(i+1,questcount.size()-i,newquestcount);
                        in2 << questcount;
                        in2 << endl;
                    }

                    questcount.remove(0,i+1);
                    ui->IDQuest->setText(WriterName + "'s_" + questcount);
                    i=tmpSize;
                }
            }
            in2.seek(logfile.size());
        }
    }
    logfile.close();
}

void MainWindow::on_UpdateButton_clicked()
{
    ui->AmountOfFirstNodes->setMinimum(AmountOfFirstNodes);
    ui->NodeID->setVisible(false);
    ui->label_20->setVisible(false);
    ui->scrollAreaPrev->setVisible(false);
    //Очистка сцены и очистка графического массива
    scene->clear();
    Items.clear();
    k=0;
    //Создание начального звена
    circle = new PictureNode(0,0,0,0,k);
    info = new InfoNode(k);
    infoItems.push_back(info);
    connect(circle,SIGNAL(signal1()),this, SLOT(slotFromPictureNode()));
    connect(circle,SIGNAL(signalHide(bool)),this, SLOT(slotHide(bool)));
    connect(circle,SIGNAL(MyNumIs(int)), this, SLOT(slotMyNumIs(int)));
    connect(circle,SIGNAL(setScrolls(int,int)), this, SLOT(slotsetScrolls(int,int)));
    Items.append(circle);
    Items[k]->setExtreme();
    k++;
    //Если не хватает инфоНодов
    if (infoItems.count()<AmountOfFirstNodes || infoItems.count() == 1)
    {
        //то генерирует инфоНоды
        for (int i=infoItems.count(); i<=AmountOfFirstNodes; i++)
        {
            //tmpName = ABC[i];
            //tmpLine.append(tmpName);
            info = new InfoNode(i);
            infoItems.push_back(info);
        }
        //Node.append(tmpLine);
    }
    else
    {
        //
    }
    //Инициализация графических элементов
    for (int i=1; i<=AmountOfFirstNodes; i++)
    {
        int deltaY=20*(AmountOfFirstNodes-1)/2;
        circle = new PictureNode(40,-deltaY+20*(i-1),1,i-1,k);
        scene->addLine(10,5,45,-deltaY+20*(i-1)+5,QPen(Qt::black));
        connect(circle,SIGNAL(signal1()),this, SLOT(slotFromPictureNode()));
        connect(circle,SIGNAL(signalHide(bool)),this, SLOT(slotHide(bool)));
        connect(circle,SIGNAL(MyNumIs(int)), this, SLOT(slotMyNumIs(int)));
        connect(circle,SIGNAL(setScrolls(int,int)), this, SLOT(slotsetScrolls(int,int)));
        Items.append(circle);
        k++;
    }
    //Размещает инициализированные графические элементы
    for (int i=0; i<k; i++)
        scene->addItem(Items[i]);

    //QGraphicsSceneHelpEvent и setToolTip() для подсказок
}

//ИнфоАйтем0 - пустой. Нужен для того, чтобы первый инфонод был равен первому граф.ноду по идентификатору
void MainWindow::on_NodeDescription_textChanged()
{
    infoItems[selectedk]->NodeDescription = ui->NodeDescription->toPlainText();
}

void MainWindow::on_NodeFormulas_textChanged()
{
    infoItems[selectedk]->NodeFormulas = ui->NodeFormulas->toPlainText();
}

void MainWindow::on_AmountOfFirstNodes_valueChanged(int arg1)
{
    AmountOfFirstNodes = arg1;
}

void MainWindow::slotFromPictureNode()
{
    //QString j = QString::number(Items[1]->lvl);
    //QMessageBox::information(this,"gotovo", j);
    if (selectedk==0)
    {
        Items[selectedk]->deselect();
    }
    else if (selectedk>0)
    {
        if (!ui->NodeID->isVisible()) ui->NodeID->setVisible(true);
        Items[selectedk]->deselect();
    }
}

void MainWindow::slotHide(bool Hide)
{
    if (Hide)
    {
        if (ui->NodeID->isVisible())
        {
            ui->NodeID->setVisible(false);
            ui->label_20->setVisible(false);
            ui->scrollAreaPrev->setVisible(false);
        }
    }
    else
    {
        if (!ui->NodeID->isVisible())
        {
            ui->NodeID->setVisible(true);
            ui->label_20->setVisible(true);
            ui->scrollAreaPrev->setVisible(true);
        }
    }
}

bool FirstLaunching=true;
void MainWindow::slotMyNumIs(int smth)
{
    //Установка имени тайтла
    QString NodeIDName = "Этап ";
    NodeIDName += QString::number(smth);
    ui->NodeID->setTitle(NodeIDName);
    //Очистка scrollArea
    if (FirstLaunching) FirstLaunching=false;
    else
    {
        //
    }
    //Установка scrollArea

    QVBoxLayout * lay = new QVBoxLayout(this);
    for (int i=0; i<8; i++) {
         QPushButton *button = new QPushButton("");
         button->setEnabled(false);
         lay->addWidget(button);
    }
    ui->scrollContents->setLayout(lay);

    QVBoxLayout * lay2 = new QVBoxLayout(this);
    for (int i=0; i<8; i++) {
         QPushButton *button = new QPushButton("");
         button->setEnabled(false);
         lay2->addWidget(button);
    }
    ui->scrollContents_2->setLayout(lay2);


    //Заполнение данных из infoNode
    ui->NodeDescription->setText(infoItems[selectedk]->NodeDescription);
    ui->NodeFormulas->setText(infoItems[selectedk]->NodeFormulas);
    ui->AmountOfSelectableVariants->setMinimum(infoItems[selectedk]->AmountOfSelectableVariants);
    ui->AmountOfSelectableVariants->setValue(infoItems[selectedk]->AmountOfSelectableVariants);
    SelectableVariantsOld = infoItems[selectedk]->AmountOfSelectableVariants;
    //Загрузка кнопок из infoNode
    //1. Удалить табы
    for (int i=0; i<SelectableVariantsOld; i++)
        ui->TabVariant->removeTab(i);
    ui->TabVariant->clear();
    if (infoItems[selectedk]->AmountOfSelectableVariants == 0)
        ui->TabVariant->setVisible(false);
    else
        ui->TabVariant->setVisible(true);
    //2. Создать новые загрузив информацию из inoda
    for (int i=0; i<infoItems[selectedk]->AmountOfSelectableVariants; i++)
    {
        vart = new VarTabClass();
        vart->id=i;    //ИСПРАВИТЬ ЧТОБЫ ЗДЕСЬ БЫЛ УНИКАЛЬНЫЙ ID
        connect(this, SIGNAL(fillButtonText(QString, int)), vart, SLOT(slotfillbuttonText(QString, int)));
        ui->TabVariant->addTab(vart, QString("Вариант %0").arg(vart->id+1));
        emit fillButtonText(infoItems[selectedk]->text[i], i);
        connect(this, SIGNAL(fillNumberOfOutcomes(int, int)), vart, SLOT(slotfillNumberOfOutcomes(int, int)));
        emit fillNumberOfOutcomes(infoItems[selectedk]->NumberOfOutcomes[i], i);
        connect(vart, SIGNAL(SendButtonText(int, QString)), infoItems[selectedk], SLOT(setButtonText(int, QString)));
        connect(vart, SIGNAL(SendNumberOfOutcomes(int, int)), infoItems[selectedk], SLOT(setNumberOfOutcomes(int, int)));
    }
}

void MainWindow::on_AmountOfSelectableVariants_valueChanged(int arg1)
{
    if (AmountOfFirstNodes > 0)
        ui->TabVariant->setVisible(true);//Изначально скрыт, нужно сделать видимым при создании первой кнопки
    if (arg1 > SelectableVariantsOld)//Если добавляется новая кнопка
    {
        vart = new VarTabClass();
        connect(this, SIGNAL(fillButtonText(QString, int)), vart, SLOT(slotfillbuttonText(QString, int)));
        connect(this, SIGNAL(fillNumberOfOutcomes(int, int)), vart, SLOT(slotfillNumberOfOutcomes(int, int)));
        connect(vart, SIGNAL(SendButtonText(int, QString)), infoItems[selectedk], SLOT(setButtonText(int, QString)));
        connect(vart, SIGNAL(SendNumberOfOutcomes(int, int)), infoItems[selectedk], SLOT(setNumberOfOutcomes(int, int)));
        //connect(vart,SIGNAL(deleteit(int)),this,SLOT(TabDelete(int)));//Что это? Пока не используется, но не забыть об этом
        vart->id=arg1-1;    //ИСПРАВИТЬ ЧТОБЫ ЗДЕСЬ БЫЛ УНИКАЛЬНЫЙ ID
        ui->TabVariant->addTab(vart, QString("Вариант %0").arg(vart->id+1));
        /*ui->TabVariant->setCurrentIndex(ui->TabVariant->count()-1);
        Можно реализовать эту возможность в настройках. Тогда будет фокусироваться на последней добавленной кнопке*/
        SelectableVariantsOld = arg1;
        ui->AmountOfSelectableVariants->setMinimum(arg1);//Ограничение на удаление
    }
    else//Если уменьшается количество кнопок
    {
        //Если уменьшается количество
    }
    //Заполнение инфоНода данными нового количества кнопок
    infoItems[selectedk]->AmountOfSelectableVariants = arg1;
}

void MainWindow::on_TESTBUTTON_clicked()
{
    QMessageBox msgBox;
    for (int i=1; i<3; i++)
    for (int j=0; j<2; j++){
    QString status = QString("Текст варианта %1 в этапе %2 равен: %3")
            //.arg(i+1).arg(selectedk).arg(infoItems[selectedk]->text[i]);
    .arg(j+1).arg(i).arg(infoItems[i]->text[j]);
    //QString status = QString("Выбран элемент %0")
            //.arg(selectedk);
    msgBox.setText(status);
    msgBox.exec();
    }
}

void MainWindow::TabDelete(int ind)
{
    /*ui->TabVariant->removeTab(ind);
    arVarTab.remove(ind);
    for (int i=ind; i<ui->TabVariant->count();i++)
    {
        arVarTab[i]->id--;
    }
    ui->AmountOfSelectableVariants->setMinimum(ui->AmountOfSelectableVariants->minimum()-1);
    ui->AmountOfSelectableVariants->setValue(ui->AmountOfSelectableVariants->value()-1);
    SelectableVariantsOld--;*/
}

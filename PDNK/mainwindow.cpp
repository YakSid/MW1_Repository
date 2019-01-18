#include "mainwindow.h"
#include "ui_mainwindow.h"

int selectedlvl=-1;
int selectednum=-1;
int selectedk = -1;

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
    //Создание начального звена
    circle = new PictureNode(0,0,0,0,0);
    if (infoItems.count()==0)
    {
        info = new InfoNode(0,0,1);
        infoItems.push_back(info);
    }
    connect(circle,SIGNAL(signal1()),this, SLOT(slotFromPictureNode()));
    connect(circle,SIGNAL(signalHide(bool)),this, SLOT(slotHide(bool)));
    connect(circle,SIGNAL(MyNumIs(int)), this, SLOT(slotMyNumIs(int)));
    Items.append(circle);
    Items[0]->setExtreme();
    //Создание начальных через AmountOfFirstNodes
    if (infoItems.count()==1)
        for (int i=1; i<=AmountOfFirstNodes; i++)//создание iнодов
        {
            info = new InfoNode(i,1,i);
            infoItems.push_back(info);
        }
    for (int i=0; i<AmountOfFirstNodes; i++)//создание gнодов
    {
        int deltaY=10*(AmountOfFirstNodes-1);
        circle = new PictureNode(40,-deltaY+20*i,1,i,Items.count());
        scene->addLine(10,5,40+5,-deltaY+20*i+5,QPen(Qt::black));//Сделать, чтобы он шел от нода родителя
        connect(circle,SIGNAL(signal1()),this, SLOT(slotFromPictureNode()));
        connect(circle,SIGNAL(signalHide(bool)),this, SLOT(slotHide(bool)));
        connect(circle,SIGNAL(MyNumIs(int)), this, SLOT(slotMyNumIs(int)));
        Items.append(circle);
    }
    //Нахождение глубины в info
    int Maxlvl=1;//Количество уровней или иначе - существующая глубина дерева которые уже существуют
    for (int i=1; i<infoItems.count(); i++)//Нахождение количества уровней
        if (infoItems[i]->lvl > Maxlvl)
            Maxlvl = infoItems[i]->lvl;
    //Проход по каждому уровню начиная с 1(уровень начальных)
    for (int lvl=1; lvl<Maxlvl; lvl++)
    {
        int NodesInLvl=0;
        //Нахождение количества элементов в уровне
        for (int inod=1; inod<infoItems.count(); inod++)
        {
            if (infoItems[inod]->lvl == lvl)
                NodesInLvl++;
        }
        //Проход по каждому звену
        for (int inod=1; inod<infoItems.count(); inod++)
        {
            if (infoItems[inod]->lvl == lvl)//в уровне
            //Провека узла на существование указанных детей (сравниваем указанное количество с существующими наследниками)
            {
                for (int button=0; button<7; button++)//проход по каждой кнопке
                {
                    int ExistingChildren=0; //Количество существующих детей. (будем сравнивать с количеством указанных - NumberOfOutcomes
                    for (int out=0; out<7; out++)//Проход по всему возможному количеству исходов
                    {
                        if (infoItems[inod]->NextNodeID[button][out] != 0)//Считаем количество существующих наследников
                            ExistingChildren++;
                    }
                    if (infoItems[inod]->NumberOfOutcomes[button] > ExistingChildren)//Если указано больше, чем есть, то
                    {
                        //инициализировать новые iноды
                        int newnod=0;
                        for (int out=0; out<7; out++)//Проход по всему возможному количеству исходов
                        {//Если место свободное и если ещё нужно записать, то записываем id нода сюда, если нет идем дальше - ищем свободное место
                            if (infoItems[inod]->NextNodeID[button][out] == 0 && newnod<infoItems[inod]->NumberOfOutcomes[button]-ExistingChildren)
                            {
                                info = new InfoNode(infoItems.count(),lvl+1,out);//Точно ли out?
                                infoItems.push_back(info);
                                infoItems[infoItems.count()]->PrevNodeID = inod;//Записываем в созданный нод, кто его родитель
                                infoItems[inod]->NextNodeID[button][out] = infoItems.count(); //Записал в свободное место количество iнодов - сейчас это id нового нода
                                newnod++;
                            }
                        }
                    }
                }
                int deltaY=10*(NodesInLvl-1);
                circle = new PictureNode(40*lvl,-deltaY+20*200,lvl,100,Items.count());//100 - это номер в группе, 200 это номер в уровне ЗАМЕНИТЬ
                scene->addLine(10,5,40*lvl+5,-deltaY+20+5,QPen(Qt::black));//Сделать, чтобы он шел от нода родителя
                //circle = new PictureNode(40*lvl,-deltaY+20*(i-1),lvl,i-1,Items.count());//i - это номер в группе
                //scene->addLine(10,5,40*lvl+5,-deltaY+20*(i-1)+5,QPen(Qt::black));//Сделать, чтобы он шел от нода родителя
                connect(circle,SIGNAL(signal1()),this, SLOT(slotFromPictureNode()));
                connect(circle,SIGNAL(signalHide(bool)),this, SLOT(slotHide(bool)));
                connect(circle,SIGNAL(MyNumIs(int)), this, SLOT(slotMyNumIs(int)));
                Items.append(circle);
            }
        }
    }
    //Размещает инициализированные графические элементы
    for (int i=0; i<Items.count(); i++)
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
    CNNTickets = infoItems[selectedk]->AmountOfSelectableVariants - ui->TabVariant->count();
    if (CNNTickets < 0)
        CNNTickets=0;
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
        vart->parentid=selectedk;
        connect(this, SIGNAL(fillButtonText(QString, int, int)), vart, SLOT(slotfillbuttonText(QString, int, int)));
        ui->TabVariant->addTab(vart, QString("Вариант %0").arg(vart->id+1));
        emit fillButtonText(infoItems[selectedk]->text[i], i, selectedk);
        connect(this, SIGNAL(fillNumberOfOutcomes(int, int, int)), vart, SLOT(slotfillNumberOfOutcomes(int, int, int)));
        emit fillNumberOfOutcomes(infoItems[selectedk]->NumberOfOutcomes[i], i, selectedk);
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
        vart->parentid=selectedk;
        ui->TabVariant->addTab(vart, QString("Вариант %0").arg(vart->id+1));
        /*ui->TabVariant->setCurrentIndex(ui->TabVariant->count()-1);
        Можно реализовать эту возможность в настройках. Тогда будет фокусироваться на последней добавленной кнопке*/
        SelectableVariantsOld = arg1;
        ui->AmountOfSelectableVariants->setMinimum(arg1);//Ограничение на удаление
        if (CNNTickets==0)
            infoItems[selectedk]->NumberOfOutcomes[arg1-1]++;
        else
            CNNTickets--;
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
    /*QMessageBox msgBox;
    QString status = QString("")
    .arg();
    msgBox.setText(status);
    msgBox.exec();*/
}

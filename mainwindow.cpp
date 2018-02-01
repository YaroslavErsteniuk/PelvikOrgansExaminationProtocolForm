#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace std;
using namespace PelvikOrgansExaminationProtocolForm;

MainWindow::MainWindow(const QStringList &askKeywords, QWidget *parent) :
    AbstractMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    if (!initializeComboBox())
        throw InvalidInitialization("MainWindow::initializeComboBox failed");

    ui->foliculusRightOvaryEdit->setText("Візуалізуються антральні фолікули, ");
    ui->recommendationPatientEdit->setText("огляд через 1 рік");

    ui->dateOMPatientEdit->setDate(QDate::currentDate().addDays(-10));
    ui->dateFormEdit->setDate(QDate::currentDate());
    ui->datePatientEdit->setDate(QDate::currentDate());
}

MainWindow::~MainWindow()
{
    delete ui;
}

//function return false and doing nothing
bool MainWindow::addAsk(AskType ask, QString inputKey) noexcept
{
    return AbstractMainWindow::addAsk(ask, inputKey);
}

//function return false and doing nothing
bool MainWindow::addAsk(AskType ask, QString inputKey, QString askText) noexcept
{
    return AbstractMainWindow::addAsk(ask, inputKey, askText);
}

//function return false and doing nothing
bool MainWindow::addAsk(AskType ask, QString inputKey, QString group) noexcept
{
    return AbstractMainWindow::addAsk(ask, inputKey, group);
}

//function return false and doing nothing
bool MainWindow::addAsk(AskType ask, QString inputKey, QString group, QString askText)  noexcept
{
    return AbstractMainWindow::addAsk(ask, inputKey, group, askText);
}

//function return false and doing nothing
bool MainWindow::addAsk(AskType ask, QRect place, QString inputKey)  noexcept
{
    return AbstractMainWindow::addAsk(ask, place, inputKey);
}

//function return false and doing nothing
bool MainWindow::addAsk(AskType ask, QRect place, QString inputKey, QString askText)  noexcept
{
    return AbstractMainWindow::addAsk(ask, place, inputKey, askText);
}

//function return false and doing nothing
bool MainWindow::addFormTemplate(QString htmlTempl) noexcept
{
    return AbstractMainWindow::addFormTemplate(htmlTempl);
}

//function return false and doing nothing
bool MainWindow::setFormTemplate(QString htmlTempl) noexcept
{
    return AbstractMainWindow::setFormTemplate(htmlTempl);
}

bool MainWindow::initializeComboBox() noexcept
{

    ui->metodicComboBox->setInsertPolicy(QComboBox::InsertAlphabetically);
    ui->metodicComboBox->setEditable(true);
    ui->metodicComboBox->addItems(QStringList("УЗД - ТВ"));

    if (!initializeUterus())
        return false;

    if (!initializeOvary(ui->vizualizationLeftOvaryComboBox, ui->conturLeftOvaryComboBox,
                    ui->bordersLeftOvaryComboBox, ui->formationLeftOvaryComboBox,
                    ui->contentsLeftOvaryComboBox, ui->sizeLeftOvaryDoubleSpinBox1,
                    ui->sizeLeftOvaryDoubleSpinBox2, ui->sizeLeftOvaryDoubleSpinBox3,
                    ui->foliculusLeftOvaryEdit, ui->diametrLeftOvaryDoubleSpinBox))
        return false;

    if (!initializeOvary(ui->vizualizationRightOvaryComboBox, ui->conturRightOvaryComboBox,
                    ui->bordersRightOvaryComboBox, ui->formationRightOvaryComboBox,
                    ui->contentsRightOvaryComboBox, ui->sizeRightOvaryDoubleSpinBox1,
                    ui->sizeRightOvaryDoubleSpinBox2, ui->sizeRightOvaryDoubleSpinBox3,
                    ui->foliculusRightOvaryEdit, ui->diametrRightOvaryDoubleSpinBox))
        return false;

    ui->fallopianTubesPatientComboBox->setInsertPolicy(QComboBox::InsertAlphabetically);
    ui->fallopianTubesPatientComboBox->setEditable(true);
    ui->fallopianTubesPatientComboBox->addItems(QStringList("не візуалізуються"));

    ui->liquidComboBox->setInsertPolicy(QComboBox::InsertAlphabetically);
    ui->liquidComboBox->setEditable(true);
    ui->liquidComboBox->addItems(QStringList({
                                                 "Вільної рідини в порожнині малого тазу немає.",
                                                 "Візуалізація вільної рідини в порожнині малого тазу.",
                                             }));

    return true;
}

bool MainWindow::initializeUterus() noexcept
{
    ui->positionUterusComboBox->setInsertPolicy(QComboBox::InsertAlphabetically);
    ui->positionUterusComboBox->setEditable(true);
    ui->positionUterusComboBox->addItems(QStringList({
                                                            "антефлексіо",
                                                            "ретрофлексіо",
                                                        }));

    ui->formUterusComboBox->setInsertPolicy(QComboBox::InsertAlphabetically);
    ui->formUterusComboBox->setEditable(true);
    ui->formUterusComboBox->addItems(QStringList({
                                                            "грушевидна",
                                                            "куляста",
                                                            "неправильна",
                                                        }));

    ui->conturUterusComboBox->setInsertPolicy(QComboBox::InsertAlphabetically);
    ui->conturUterusComboBox->setEditable(true);
    ui->conturUterusComboBox->addItems(QStringList({
                                                            "чіткі",
                                                            "нечіткі",
                                                        }));

    ui->vizualizationUterusEndometriumComboBox->setInsertPolicy(QComboBox::InsertAlphabetically);
    ui->vizualizationUterusEndometriumComboBox->setEditable(true);
    ui->vizualizationUterusEndometriumComboBox->addItems(QStringList({
                                                            "Візуалізується на всьому протязі",
                                                            "Візуалізація не чітка",
                                                        }));
    ui->layersUterusEndometriumComboBox->setInsertPolicy(QComboBox::InsertAlphabetically);
    ui->layersUterusEndometriumComboBox->setEditable(true);
    ui->layersUterusEndometriumComboBox->addItems(QStringList({
                                                            "одношаровий",
                                                            "двошаровий",
                                                            "трьохшаровий",
                                                        }));

    ui->vizualizationUterusCervicusCanalComboBox->setInsertPolicy(QComboBox::InsertAlphabetically);
    ui->vizualizationUterusCervicusCanalComboBox->setEditable(true);
    ui->vizualizationUterusCervicusCanalComboBox->addItems(QStringList({
                                                            "візуально не змінений",
                                                        }));

    ui->echostructureUterusCervicusCanalComboBox->setInsertPolicy(QComboBox::InsertAlphabetically);
    ui->echostructureUterusCervicusCanalComboBox->setEditable(true);
    const QStringList enoughEchostructureInfo={"однорідна", "неоднорідна"};
    const QStringList notEnoughEchostructureInfo={"неоднорідна за рахунок "};
    ui->echostructureUterusCervicusCanalComboBox->addItems(enoughEchostructureInfo+notEnoughEchostructureInfo);
    list<QWidget*> tmpList;
    tmpList.clear();
    tmpList.push_back(ui->echostructureUterusCervicusCanalEdit);
    auto echostructureIt=dependentWidgets.insert(dependentWidgets.end(),tmpList);
    auto echostructureDependentedWidgetsChange=[&](const QString& comboBoxValue)
    {
        if (notEnoughEchostructureInfo.contains(comboBoxValue,Qt::CaseInsensitive))
        {
            setDependentWidgetsEnabling(echostructureIt,false);
        }
        else
        {
            setDependentWidgetsEnabling(echostructureIt,true);
        }
    };
    auto echostructureDependentedWidgetsEditableChange=[&](QWidget* widget_, bool isEditable_)
        {
                if (widget_==ui->echostructureUterusCervicusCanalComboBox)
                {
                    auto casted=qobject_cast<QComboBox*>(widget_);
                    if (!(isEditable_ && casted))
                    {
                        setDependentWidgetsEnabling(echostructureIt,false);
                    }
                    else
                    {
                        echostructureDependentedWidgetsChange(casted->currentText());
                    }
                }
        };
    connect(ui->echostructureUterusCervicusCanalComboBox,QOverload<QString>::of(&QComboBox::currentIndexChanged),
            echostructureDependentedWidgetsChange);
    connect(this,MainWindow::widgetEnable,echostructureDependentedWidgetsEditableChange);
    connect(this,MainWindow::widgetVisible,echostructureDependentedWidgetsEditableChange);

    return true;
}


bool MainWindow::initializeOvary(QComboBox* vizualizationOvaryComboBox, QComboBox*  conturOvaryComboBox,
                                 QComboBox*  bordersOvaryComboBox, QComboBox* formationOvaryComboBox,
                                 QComboBox* contentsOvaryComboBox, QDoubleSpinBox* sizeOvaryDoubleSpinBox1,
                                 QDoubleSpinBox* sizeOvaryDoubleSpinBox2, QDoubleSpinBox* sizeOvaryDoubleSpinBox3,
                                 QLineEdit* foliculusOvaryEdit, QDoubleSpinBox* diametrOvaryDoubleSpinBox) noexcept
{
    list<QWidget*> tmpList;
    {
        vizualizationOvaryComboBox->setInsertPolicy(QComboBox::InsertAlphabetically);
        vizualizationOvaryComboBox->setEditable(true);
        const QStringList enoughVizualization={"задовільна","незадовільна"};
        const QStringList notVizualization={"не візуалізується","видалений оперативно"};
        vizualizationOvaryComboBox->addItems(enoughVizualization+notVizualization);
        tmpList.clear();
        tmpList.push_back(bordersOvaryComboBox);
        tmpList.push_back(conturOvaryComboBox);
        tmpList.push_back(sizeOvaryDoubleSpinBox1);
        tmpList.push_back(sizeOvaryDoubleSpinBox2);
        tmpList.push_back(sizeOvaryDoubleSpinBox3);
        tmpList.push_back(foliculusOvaryEdit);
        tmpList.push_back(formationOvaryComboBox);
        auto vizualizationIt=dependentWidgets.insert(dependentWidgets.end(),tmpList);
        auto vizualizationDependentedWidgetsChange=[&](const QString& comboBoxValue)
        {
            if (notVizualization.contains(comboBoxValue,Qt::CaseInsensitive))
            {
                setDependentWidgetsEnabling(vizualizationIt,false);
            }
            else
            {
                setDependentWidgetsEnabling(vizualizationIt,true);
            }
        };
        auto vizualizationDependentedWidgetsEditableChange=[&](QWidget* widget_, bool isEditable_)
            {
                    if (widget_==vizualizationOvaryComboBox)
                    {
                        auto casted=qobject_cast<QComboBox*>(widget_);
                        if (!(isEditable_ && casted))
                        {
                            setDependentWidgetsEnabling(vizualizationIt,false);
                        }
                        else
                        {
                            vizualizationDependentedWidgetsChange(casted->currentText());
                        }
                    }
            };
        connect(vizualizationOvaryComboBox,QOverload<QString>::of(&QComboBox::currentIndexChanged),
                vizualizationDependentedWidgetsChange);
        connect(this,MainWindow::widgetEnable,vizualizationDependentedWidgetsEditableChange);
        connect(this,MainWindow::widgetVisible,vizualizationDependentedWidgetsEditableChange);
    }

    conturOvaryComboBox->setInsertPolicy(QComboBox::InsertAlphabetically);
    conturOvaryComboBox->setEditable(true);
    conturOvaryComboBox->addItems(QStringList("рівні"));

    bordersOvaryComboBox->setInsertPolicy(QComboBox::InsertAlphabetically);
    bordersOvaryComboBox->setEditable(true);
    bordersOvaryComboBox->addItems(QStringList("чіткі"));

    {
        formationOvaryComboBox->setInsertPolicy(QComboBox::InsertAlphabetically);
        formationOvaryComboBox->setEditable(true);
        const QString echoFormation="Ехо \"-\" утвір,";
        const QString giperehogeniousFormation="Гіперехогенний утвір,";
        formationOvaryComboBox->addItems(QStringList({
                                                                 "",
                                                                 echoFormation,
                                                                 giperehogeniousFormation
                                                             }));
        tmpList.clear();
        tmpList.push_back(diametrOvaryDoubleSpinBox);
        tmpList.push_back(contentsOvaryComboBox);
        auto it1=dependentWidgets.insert(dependentWidgets.end(),tmpList);
        tmpList.clear();
        tmpList.push_back(diametrOvaryDoubleSpinBox);
        auto it2=dependentWidgets.insert(dependentWidgets.end(),tmpList);
        auto dependentedWidgetsChange=[&](const QString& comboBoxValue)
        {
            if (comboBoxValue==echoFormation)
            {
                setDependentWidgetsEnabling(it2,false);
                setDependentWidgetsEnabling(it1,true);
            }
            else if (comboBoxValue==giperehogeniousFormation)
            {
                setDependentWidgetsEnabling(it1,false);
                setDependentWidgetsEnabling(it2,true);
            }
            else
            {
                setDependentWidgetsEnabling(it1,false);
                setDependentWidgetsEnabling(it2,false);
            }
        };
        auto dependentedWidgetsEditableChange=[&](QWidget* widget_, bool isEditable_)
            {
                    if (widget_==formationOvaryComboBox)
                    {
                        auto casted=qobject_cast<QComboBox*>(widget_);
                        if (!(isEditable_ && casted))
                        {
                            setDependentWidgetsEnabling(it1,false);
                            setDependentWidgetsEnabling(it2,false);
                        }
                        else
                        {
                            dependentedWidgetsChange(casted->currentText());
                        }
                    }
            };
        connect(formationOvaryComboBox,QOverload<QString>::of(&QComboBox::currentIndexChanged),
                dependentedWidgetsChange);
        connect(this,MainWindow::widgetEnable,dependentedWidgetsEditableChange);
        connect(this,MainWindow::widgetVisible,dependentedWidgetsEditableChange);
    }

    contentsOvaryComboBox->setInsertPolicy(QComboBox::InsertAlphabetically);
    contentsOvaryComboBox->setEditable(true);
    contentsOvaryComboBox->addItems(QStringList({
                                                            "з однорідним вмістом",
                                                            "з павутиноподібним вмістом",
                                                            "з гетерогенним вмістом"
                                                        }));

    return true;
}

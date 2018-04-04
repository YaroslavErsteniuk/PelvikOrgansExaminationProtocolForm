#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QComboBox>
#include <QDoubleSpinBox>
#include <QLineEdit>
#include <QtPrintSupport/qtprintsupportglobal.h>
#include <QTextDocument>
#include <QPrinter>
#include <QFileDialog>
#include <QPrintDialog>

#include <QtWebKitWidgets/QWebView>

using namespace std;
using namespace PelvikOrgansExaminationProtocolForm;

/*Initialize  predefined hard-coded input interface.
 * GUI created by Qt-design tool.
 * @askKEywords is a list of keywords to reduce number of "magic" constant.
 * Should be getted from object of KeyParser class.
 */
MainWindow::MainWindow(const QStringList &askKeywords, QWidget *parent) :
    AbstractMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->scrollAreaWidgetContents->setMinimumSize(961,1171);
    if (!initializeComboBox())
        throw InvalidInitialization("MainWindow::initializeComboBox failed");

    ui->foliculusRightOvaryEdit->setText("Візуалізуються антральні фолікули, ");
    ui->foliculusLeftOvaryEdit->setText("Візуалізуються антральні фолікули, ");
    ui->recommendationPatientEdit->setText("огляд через 1 рік");

    ui->dateOMPatientEdit->setDate(QDate::currentDate().addDays(-10));
    ui->dateFormEdit->setDate(QDate::currentDate());
    ui->datePatientEdit->setDate(QDate::currentDate());

    if (!initializeWidgets(askKeywords))
         throw InvalidInitialization("MainWindow::initializeComboBox failed");

   connect(ui->printPushButton,&QPushButton::clicked,this,&MainWindow::printForm);
   connect(ui->pdfPushButton,&QPushButton::clicked,this,&MainWindow::toPdfForm);
   connect(ui->htmlPushButton,&QPushButton::clicked,this,&MainWindow::toHtmlForm);

   if (!fileMenu)
   {
       fileMenu=new QMenu(tr("File"), this);
   }
   menuBar()->addMenu(fileMenu);
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
                    ui->volumeLeftOvaryDoubleSpinBox,
                    ui->foliculusLeftOvaryEdit, ui->diametrLeftOvaryDoubleSpinBox))
        return false;

    if (!initializeOvary(ui->vizualizationRightOvaryComboBox, ui->conturRightOvaryComboBox,
                    ui->bordersRightOvaryComboBox, ui->formationRightOvaryComboBox,
                    ui->contentsRightOvaryComboBox, ui->sizeRightOvaryDoubleSpinBox1,
                    ui->sizeRightOvaryDoubleSpinBox2, ui->sizeRightOvaryDoubleSpinBox3,
                    ui->volumeRightOvaryDoubleSpinBox,
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
    connect(ui->echostructureUterusCervicusCanalComboBox,QOverload<const QString &>::of(&QComboBox::currentIndexChanged),
            echostructureDependentedWidgetsChange);
    connect(this,&MainWindow::widgetEnable,echostructureDependentedWidgetsEditableChange);
    connect(this,&MainWindow::widgetVisible,echostructureDependentedWidgetsEditableChange);

    return true;
}


bool MainWindow::initializeOvary(QComboBox* vizualizationOvaryComboBox, QComboBox*  conturOvaryComboBox,
                                 QComboBox*  bordersOvaryComboBox, QComboBox* formationOvaryComboBox,
                                 QComboBox* contentsOvaryComboBox, QDoubleSpinBox* sizeOvaryDoubleSpinBox1,
                                 QDoubleSpinBox* sizeOvaryDoubleSpinBox2, QDoubleSpinBox* sizeOvaryDoubleSpinBox3,
                                 QDoubleSpinBox* volumeOvaryDoubleSpinBox,
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
        tmpList.push_back(volumeOvaryDoubleSpinBox);
        tmpList.push_back(foliculusOvaryEdit);
        tmpList.push_back(formationOvaryComboBox);
        auto vizualizationIt=dependentWidgets.insert(dependentWidgets.end(),tmpList);
        auto vizualizationDependentedWidgetsChange=[&,vizualizationIt, notVizualization](const QString& comboBoxValue)
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
        auto vizualizationDependentedWidgetsEditableChange=[&,vizualizationOvaryComboBox,
                vizualizationIt,vizualizationDependentedWidgetsChange](QWidget* widget_, bool isEditable_)
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
        connect(vizualizationOvaryComboBox,QOverload<const QString &>::of(&QComboBox::currentIndexChanged),
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
        auto dependentedWidgetsChange=[&,echoFormation,it2,it1,giperehogeniousFormation](const QString& comboBoxValue)
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
        dependentedWidgetsChange(formationOvaryComboBox->currentText());
        auto dependentedWidgetsEditableChange=[&,formationOvaryComboBox, it1, it2, dependentedWidgetsChange ]
           (QWidget* widget_, bool isEditable_)
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
        connect(formationOvaryComboBox,QOverload<const QString &>::of(&QComboBox::currentIndexChanged),
                dependentedWidgetsChange);
        connect(this,&MainWindow::widgetEnable,dependentedWidgetsEditableChange);
        connect(this,&MainWindow::widgetVisible,dependentedWidgetsEditableChange);
    }

    contentsOvaryComboBox->setInsertPolicy(QComboBox::InsertAlphabetically);
    contentsOvaryComboBox->setEditable(true);
    contentsOvaryComboBox->addItems(QStringList({
                                                            "з однорідним вмістом",
                                                            "з павутиноподібним вмістом",
                                                            "з гетерогенним вмістом"
                                                        }));
    formationOvaryComboBox->setCurrentIndex(0);

    return true;
}

 bool MainWindow::initializeWidgets(const QStringList& askKeywords) noexcept
 {
    auto cBeginIt=cbegin(askKeywords);
    widgets.insert({*(cBeginIt++),QPair<AskTypeEnum,QWidget*>(stringAskType,ui->snfPatientEdit)});
    widgets.insert({*(cBeginIt++),QPair<AskTypeEnum,QWidget*>(enumAskType,ui->metodicComboBox)});
    widgets.insert({*(cBeginIt++),QPair<AskTypeEnum,QWidget*>(numberAskType,ui->yearPatientBox)});
    widgets.insert({*(cBeginIt++),QPair<AskTypeEnum,QWidget*>(dateAskType,ui->datePatientEdit)});
    widgets.insert({*(cBeginIt++),QPair<AskTypeEnum,QWidget*>(dateAskType,ui->dateOMPatientEdit)});
    widgets.insert({*(cBeginIt++),QPair<AskTypeEnum,QWidget*>(enumAskType,ui->positionUterusComboBox)});
    widgets.insert({*(cBeginIt++),QPair<AskTypeEnum,QWidget*>(enumAskType,ui->formUterusComboBox)});
    widgets.insert({*(cBeginIt++),QPair<AskTypeEnum,QWidget*>(enumAskType,ui->conturUterusComboBox)});
    widgets.insert({*(cBeginIt++),QPair<AskTypeEnum,QWidget*>(floatAskType,ui->sizeUterusBodyDoubleSpinBox1)});
    widgets.insert({*(cBeginIt++),QPair<AskTypeEnum,QWidget*>(floatAskType,ui->sizeUterusBodyDoubleSpinBox2)});
    widgets.insert({*(cBeginIt++),QPair<AskTypeEnum,QWidget*>(floatAskType,ui->sizeUterusBodyDoubleSpinBox3)});
    widgets.insert({*(cBeginIt++),QPair<AskTypeEnum,QWidget*>(floatAskType,ui->volumeUterusBodyDoubleSpinBox)});
    widgets.insert({*(cBeginIt++),QPair<AskTypeEnum,QWidget*>(floatAskType,ui->thicknessUterusEndometriumDoubleSpinBox)});
    widgets.insert({*(cBeginIt++),QPair<AskTypeEnum,QWidget*>(enumAskType,ui->vizualizationUterusEndometriumComboBox)});
    widgets.insert({*(cBeginIt++),QPair<AskTypeEnum,QWidget*>(enumAskType,ui->layersUterusEndometriumComboBox)});
    widgets.insert({*(cBeginIt++),QPair<AskTypeEnum,QWidget*>(floatAskType,ui->sizeUterusCervixDoubleSpinBox1)});
    widgets.insert({*(cBeginIt++),QPair<AskTypeEnum,QWidget*>(floatAskType,ui->sizeUterusCervixDoubleSpinBox2)});
    widgets.insert({*(cBeginIt++),QPair<AskTypeEnum,QWidget*>(floatAskType,ui->volumeUterusCervixDoubleSpinBox)});
    widgets.insert({*(cBeginIt++),QPair<AskTypeEnum,QWidget*>(enumAskType,ui->vizualizationUterusCervicusCanalComboBox)});
    widgets.insert({*(cBeginIt++),QPair<AskTypeEnum,QWidget*>(enumAskType,ui->echostructureUterusCervicusCanalComboBox)});
    widgets.insert({*(cBeginIt++),QPair<AskTypeEnum,QWidget*>(stringAskType,ui->echostructureUterusCervicusCanalEdit)});

    widgets.insert({*(cBeginIt++),QPair<AskTypeEnum,QWidget*>(enumAskType,ui->vizualizationRightOvaryComboBox)});
    widgets.insert({*(cBeginIt++),QPair<AskTypeEnum,QWidget*>(enumAskType,ui->conturRightOvaryComboBox)});
    widgets.insert({*(cBeginIt++),QPair<AskTypeEnum,QWidget*>(enumAskType,ui->bordersRightOvaryComboBox)});
    widgets.insert({*(cBeginIt++),QPair<AskTypeEnum,QWidget*>(floatAskType,ui->sizeRightOvaryDoubleSpinBox1)});
    widgets.insert({*(cBeginIt++),QPair<AskTypeEnum,QWidget*>(floatAskType,ui->sizeRightOvaryDoubleSpinBox2)});
    widgets.insert({*(cBeginIt++),QPair<AskTypeEnum,QWidget*>(floatAskType,ui->sizeRightOvaryDoubleSpinBox3)});
    widgets.insert({*(cBeginIt++),QPair<AskTypeEnum,QWidget*>(floatAskType,ui->volumeRightOvaryDoubleSpinBox)});
    widgets.insert({*(cBeginIt++),QPair<AskTypeEnum,QWidget*>(stringAskType,ui->foliculusRightOvaryEdit)});
    widgets.insert({*(cBeginIt++),QPair<AskTypeEnum,QWidget*>(enumAskType,ui->formationRightOvaryComboBox)});
    widgets.insert({*(cBeginIt++),QPair<AskTypeEnum,QWidget*>(floatAskType,ui->diametrRightOvaryDoubleSpinBox)});
    widgets.insert({*(cBeginIt++),QPair<AskTypeEnum,QWidget*>(enumAskType,ui->contentsRightOvaryComboBox)});

    widgets.insert({*(cBeginIt++),QPair<AskTypeEnum,QWidget*>(enumAskType,ui->vizualizationLeftOvaryComboBox)});
    widgets.insert({*(cBeginIt++),QPair<AskTypeEnum,QWidget*>(enumAskType,ui->conturLeftOvaryComboBox)});
    widgets.insert({*(cBeginIt++),QPair<AskTypeEnum,QWidget*>(enumAskType,ui->bordersLeftOvaryComboBox)});
    widgets.insert({*(cBeginIt++),QPair<AskTypeEnum,QWidget*>(floatAskType,ui->sizeLeftOvaryDoubleSpinBox1)});
    widgets.insert({*(cBeginIt++),QPair<AskTypeEnum,QWidget*>(floatAskType,ui->sizeLeftOvaryDoubleSpinBox2)});
    widgets.insert({*(cBeginIt++),QPair<AskTypeEnum,QWidget*>(floatAskType,ui->sizeLeftOvaryDoubleSpinBox3)});
    widgets.insert({*(cBeginIt++),QPair<AskTypeEnum,QWidget*>(floatAskType,ui->volumeLeftOvaryDoubleSpinBox)});
    widgets.insert({*(cBeginIt++),QPair<AskTypeEnum,QWidget*>(stringAskType,ui->foliculusLeftOvaryEdit)});
    widgets.insert({*(cBeginIt++),QPair<AskTypeEnum,QWidget*>(enumAskType,ui->formationLeftOvaryComboBox)});
    widgets.insert({*(cBeginIt++),QPair<AskTypeEnum,QWidget*>(floatAskType,ui->diametrLeftOvaryDoubleSpinBox)});
    widgets.insert({*(cBeginIt++),QPair<AskTypeEnum,QWidget*>(enumAskType,ui->contentsLeftOvaryComboBox)});

    widgets.insert({*(cBeginIt++),QPair<AskTypeEnum,QWidget*>(enumAskType,ui->fallopianTubesPatientComboBox)});
    widgets.insert({*(cBeginIt++),QPair<AskTypeEnum,QWidget*>(enumAskType,ui->liquidComboBox)});
    widgets.insert({*(cBeginIt++),QPair<AskTypeEnum,QWidget*>(stringAskType,ui->recommendationPatientEdit)});
    widgets.insert({*(cBeginIt++),QPair<AskTypeEnum,QWidget*>(dateAskType,ui->dateFormEdit)});
    widgets.insert({*(cBeginIt++),QPair<AskTypeEnum,QWidget*>(stringAskType,ui->doctorEdit)});
    return true;
 }

 /* Function for registering @action in UI.
  * If registering is impossible return false
  * else return true.
  */
 bool MainWindow::registerAction(MyAction *action) noexcept override
 //Add action in the menu and for some of them add a shortcut
 {
    if (!fileMenu)
       fileMenu=new QMenu(tr("File"), this);
     fileMenu->addAction(action);
 }

 /* Function for ending registration of actions in UI.
  * If all ok return true, otherwise return false.
  * Used for adding a menu to main window.
  */
 bool MainWindow::allActionsRegistered() noexcept override
 {
     ui->menuBar->addMenu(fileMenu);
     return true;
 }

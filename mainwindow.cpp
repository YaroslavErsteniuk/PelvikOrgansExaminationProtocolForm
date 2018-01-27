#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace PelvikOrgansExaminationProtocolForm;

MainWindow::MainWindow(QWidget *parent) :
    AbstractMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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

    ui->fallopianTubesPatientComboBox->setInsertPolicy(QComboBox::InsertAlphabetically);
    ui->fallopianTubesPatientComboBox->setEditable(true);
    ui->fallopianTubesPatientComboBox->addItems(QStringList("не візуалізуються"));

}

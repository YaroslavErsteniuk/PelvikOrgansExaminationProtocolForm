#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace PelvikOrgansExaminationProtocolForm;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

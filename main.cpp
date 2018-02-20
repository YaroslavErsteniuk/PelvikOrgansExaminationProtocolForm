#include <QApplication>
#include "mainapplication.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PelvikOrgansExaminationProtocolForm::MainApplication ma;
    ma.show();
    return a.exec();
}

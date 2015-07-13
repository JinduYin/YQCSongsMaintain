#include "mainwidget.h"
#include <QApplication>
#include <QFile>
#include <QTextCodec>
#include "curlupload.h"

int main(int argc, char *argv[])
{
    QTextCodec *utf8 = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForLocale(utf8);
    QApplication a(argc, argv);

    MainWidget w;
    w.show();

    return a.exec();
}

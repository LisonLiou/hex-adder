#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QVector>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("HEX助手 v"+QApplication::applicationVersion());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_FORMAT_clicked()
{
    QString strHex = ui->textEdit->toPlainText();

    if(strHex.length()==0) return;
    ui->plainTextEdit_FORMATRESULT->setPlainText(fmt(strHex));
}

void MainWindow::on_pushButton_Add_clicked()
{
    QString strHex = ui->textEdit->toPlainText();

    if(strHex.length()==0) return;

    qint16 result  = 0;
    QString hex = fmt(strHex);
    for(QString &h:hex.split(" ")){
        if(h.length()==0) continue;

        bool ok;
        QByteArray data= h.toLocal8Bit();
        result+=data.toInt(&ok,16);
    }

    ui->plainTextEdit_ADDRESULT->setPlainText(QString::number(result, 16).toUpper());
}

void MainWindow::on_pushButton_CONCAT_clicked()
{
    QString format = ui->plainTextEdit_FORMATRESULT->toPlainText();
    format = format.trimmed();

    QString result = ui->plainTextEdit_ADDRESULT->toPlainText().trimmed();
    if(result.length()!=0&&result.length()%2!=0){
        result = "0"+result;
    }

    QList<QString> list;
    while(result.length()!=0){
        qDebug()<<"length: "<<result.length();
        list.append(result.right(2));
        result.chop(2);
    }

    //逆序遍历
    for (QList<QString>::iterator i = --list.end();i != --list.begin();i--){
        format+=" "+ *(i);
    }

    ui->plainTextEdit_FORMATRESULT->setPlainText(fmt(format+result));
}

QString MainWindow::fmt(QString s)
{
    QRegExp rx("([0-9A-Fa-f]{1,2})");

    int pos(0);
    QStringList strList;
    while ((pos = rx.indexIn(s, pos)) != -1)
    {
        strList.push_back(rx.capturedTexts().at(0));
        pos += rx.matchedLength();
    }
    return strList.join(" ").toUpper();
}


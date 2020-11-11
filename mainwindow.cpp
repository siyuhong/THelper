#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    init();
}

MainWindow::~MainWindow()
{
    delete mBaidutranslate;
    translateThread->quit();
    translateThread->wait();
    delete ui;
}

void MainWindow::init(){

    translateThread = new QThread;
    mBaidutranslate = new BaiduTranslateAPI;

    mBaidutranslate->moveToThread(translateThread);

    connect(translateThread, &QThread::finished, mBaidutranslate, &QObject::deleteLater);

    connect(this,SIGNAL(SendRequested(QString,QString,QString)),mBaidutranslate,SLOT(slot_SendRequested(QString,QString,QString)));
    connect(mBaidutranslate,SIGNAL(TranslationReturn(QString)),this,SLOT(slot_TranslationReturn(QString)));

    translateThread->start();
}

void MainWindow::getLanguage(QString languagename,QString &languagecode)
{
    if("自动检测" == languagename){
        languagecode = "auto";
    }
    if("中文" == languagename){
        languagecode = "zh";
    }
    if("英语" == languagename){
        languagecode = "en";
    }
    if("粤语" == languagename){
        languagecode = "yue";
    }
}

void MainWindow::on_pushButton_translate_clicked()
{
    // 待翻译文本
    QString strInput = ui->textEdit_intputtext->toPlainText();

    QString fromlanguagecode = "auto";
    getLanguage(ui->comboBox_fromlanguage->currentText(),fromlanguagecode);
    QString tolanguagecode = "zh";
    getLanguage(ui->comboBox_tolanguage->currentText(),tolanguagecode);

    emit SendRequested(strInput,fromlanguagecode,tolanguagecode);
}

void MainWindow::slot_TranslationReturn(QString stroutput){

    ui->textBrowser_outputtext->setText(stroutput);
}

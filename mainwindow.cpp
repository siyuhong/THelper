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
    delete mTencenttranslate;
    translateThread->quit();
    translateThread->wait();
    delete ui;
}

void MainWindow::init(){

    //ui
    ui->radioButton_BaiduAPI->setChecked(true);

    translateThread = new QThread;
    mBaidutranslate = new BaiduTranslateAPI;
    mTencenttranslate = new TencentTranslateAPI;

    mBaidutranslate->moveToThread(translateThread);
    mTencenttranslate->moveToThread(translateThread);

    connect(translateThread, &QThread::finished, mBaidutranslate, &QObject::deleteLater);

    connect(mBaidutranslate,SIGNAL(TranslationReturn(QString)),this,SLOT(slot_TranslationReturn(QString)));
    connect(mTencenttranslate,SIGNAL(TranslationReturn(QString)),this,SLOT(slot_TranslationReturn(QString)));

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
    if("英文" == languagename){
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
    QString tolanguagecode = "zh";
    getLanguage(ui->comboBox_fromlanguage->currentText(),fromlanguagecode);
    getLanguage(ui->comboBox_tolanguage->currentText(),tolanguagecode);

    qDebug() << "fromlanguagecode" << fromlanguagecode;
    qDebug() << "tolanguagecode" << tolanguagecode;

    //发送信号
    if(ui->radioButton_BaiduAPI->isChecked()){
        emit mBaidutranslate->SendRequested(strInput,fromlanguagecode,tolanguagecode);
    }
    if(ui->radioButton_TencentAPI->isChecked()){
        emit mTencenttranslate->SendRequested(strInput,fromlanguagecode,tolanguagecode);
    }
}

void MainWindow::slot_TranslationReturn(QString stroutput){

    ui->textBrowser_outputtext->setText(stroutput);
}

void MainWindow::on_radioButton_BaiduAPI_clicked()
{
    ui->comboBox_fromlanguage->clear();
    ui->comboBox_fromlanguage->addItem("自动检测");
    ui->comboBox_fromlanguage->addItem("英文");
    ui->comboBox_fromlanguage->addItem("中文");
    ui->comboBox_fromlanguage->addItem("粤语");

    ui->comboBox_tolanguage->clear();
    ui->comboBox_tolanguage->addItem("中文");
    ui->comboBox_tolanguage->addItem("粤语");
    ui->comboBox_tolanguage->addItem("英文");

    ui->textBrowser_outputtext->clear();

}

void MainWindow::on_radioButton_TencentAPI_clicked()
{
    ui->comboBox_fromlanguage->clear();
    ui->comboBox_fromlanguage->addItem("英文");
    ui->comboBox_fromlanguage->addItem("中文");

    ui->comboBox_tolanguage->clear();
    ui->comboBox_tolanguage->addItem("中文");
    ui->comboBox_tolanguage->addItem("英文");

     ui->textBrowser_outputtext->clear();
}

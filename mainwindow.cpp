#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //容易尝试 无响应主因
    QMetaObject::Connection connRet = QObject::connect(&mNetworkManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(requestFinished(QNetworkReply*)));
    Q_ASSERT(connRet);
}

MainWindow::~MainWindow()
{
    delete ui;
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

void MainWindow::getRAND(int &rand){

    QTime time;
    time= QTime::currentTime();
    qsrand(time.msec()+time.second()*1000);
    //rang: [0,99]
    rand = qrand() % 100;
}

void MainWindow::on_pushButton_translate_clicked()
{
    // 待翻译文本
    QString strInput = ui->textEdit_intputtext->toPlainText();

    QString fromlanguagecode = "auto";
    getLanguage(ui->comboBox_fromlanguage->currentText(),fromlanguagecode);
    QString tolanguagecode = "zh";
    getLanguage(ui->comboBox_tolanguage->currentText(),tolanguagecode);

    //随机数
    int mrand = 0;
    getRAND(mrand);

    //MD5 - 签名
    QString str_noencrypt  = APPID.toUtf8() + strInput.toUtf8() + QString::number(mrand).toUtf8() + Key.toUtf8();
    QString signature = QCryptographicHash::hash(str_noencrypt.toUtf8(),QCryptographicHash::Md5).toHex();

    //请求拼接
    QString str_request = "http://api.fanyi.baidu.com/api/trans/vip/translate?q="+ strInput.toUtf8().toPercentEncoding()
            + "&from=" + fromlanguagecode
            + "&to=" + tolanguagecode
            + "&appid="+ APPID
            + "&salt=" + QString::number(mrand)
            +"&sign=" + signature;

//    request->setUrl(QUrl(str_request));

    qDebug() << str_request;

    mNetworkManager.get(QNetworkRequest(QString(str_request)));

    qDebug() << "on_pushButton_translate_clicked" << QTime::currentTime();

}

void MainWindow::requestFinished(QNetworkReply *reply){

    qDebug() << "requestFinished()" << QTime::currentTime();

    QString transresulttext;

    if  (reply->error() == QNetworkReply::NoError)
    {
        QByteArray jsonbytearray = reply->readAll();

        qDebug() << jsonbytearray;

         QJsonParseError jsonpe;
         QJsonDocument jsonfile = QJsonDocument::fromJson(jsonbytearray, &jsonpe);

         if  (jsonpe.error == QJsonParseError::NoError)
         {
             QJsonObject jsobj = jsonfile.object();

             if(jsobj.contains( "trans_result")){

                 QJsonValue transresultValue = jsobj.value("trans_result");

                 if(transresultValue.isArray()){
                     QJsonArray transresultArray = transresultValue.toArray();

                     qDebug() << "transresultArray Size:" << transresultArray.size();

                     for (int i = 0; i < transresultArray.size(); i++) {

                         //JS Object
                         QJsonValue itemArray = transresultArray.at(i);
                         QJsonObject item = itemArray.toObject();

                         QString src = item["src"].toString();
                         QString dst = item["dst"].toString();

                         qDebug() << "src:" << src << "    " << "dst:"  << dst;

                         transresulttext.append(dst);
                     }

                     ui->textBrowser_outputtext->setText(transresulttext);
                 }
             }
         }else{
             qDebug() << "[Error] Js parse error.";
         }
     }
     else
     {
         qDebug() <<  "[Error] Request error.";
     }

    reply->deleteLater();

}

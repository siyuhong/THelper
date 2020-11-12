#include "BaiduTranslateAPI.h"
#include <QDebug>

BaiduTranslateAPI::BaiduTranslateAPI(QObject *parent) : QObject(parent)
{
}

void BaiduTranslateAPI::getRAND(int &rand){

    QTime time;
    time= QTime::currentTime();
    qsrand(time.msec()+time.second()*1000);
    //rang: [0,99]
    rand = qrand() % 100;
}

void BaiduTranslateAPI::slot_SendRequested(QString strinput,QString fromlanguage,QString tolanguage){

    QNetworkAccessManager *mnetwork_Manager = new QNetworkAccessManager;

    QMetaObject::Connection connRet = QObject::connect(mnetwork_Manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(requestFinished(QNetworkReply*)));
    Q_ASSERT(connRet);

    //随机数
    int mrand = 0;
    getRAND(mrand);

    //MDK5 - 签名
    QString str_noencrypt  = APPID.toUtf8() + strinput + QString::number(mrand).toUtf8() + Key.toUtf8();
    QString signature = QCryptographicHash::hash(str_noencrypt.toUtf8(),QCryptographicHash::Md5).toHex();

    //请求拼接
    QString str_request = "http://api.fanyi.baidu.com/api/trans/vip/translate?q="+ strinput.toUtf8().toPercentEncoding()
            + "&from=" + fromlanguage
            + "&to=" + tolanguage
            + "&appid="+ APPID
            + "&salt=" + QString::number(mrand)
            +"&sign=" + signature;

    qDebug() << str_request;

    mnetwork_Manager->get(QNetworkRequest(QString(str_request)));

}


void BaiduTranslateAPI::requestFinished(QNetworkReply *reply){

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

                     for (int i = 0; i < transresultArray.size(); ++i) {

                         //JS Object
                         QJsonValue itemArray = transresultArray.at(i);
                         QJsonObject item = itemArray.toObject();

                         QString src = item["src"].toString();
                         QString dst = item["dst"].toString();

                         qDebug() << "src:" << src << "    " << "dst:"  << dst;

                         transresulttext.append(dst);
                     }
                     emit TranslationReturn(transresulttext);
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


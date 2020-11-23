#include "TencentTranslateAPI.h"

TencentTranslateAPI::TencentTranslateAPI()
{

}

void TencentTranslateAPI::getSign(QMap<QString,QString> lexicographicalmap,QString appkey,QString &sign){

    QString str_noencrypt;

    for(int i = 0; i < lexicographicalmap.size(); i++){
        str_noencrypt.append(lexicographicalmap.keys().at(i));
        qDebug() << "lexicographicalmap.keys().at(i): " << lexicographicalmap.keys().at(i);
        str_noencrypt.append("=");

        QTextCodec *utf8 = QTextCodec::codecForName("utf-8");
        QByteArray valuearray = utf8->fromUnicode(lexicographicalmap.values().at(i)).toPercentEncoding();

        //应腾讯API要求，将 " "(空格%20)转为"+"
        QString value = QString(valuearray);
        int count  = value.count("%20");
        for(int i = 0;i < count;i++){
            int index = value.indexOf("%20",0);
            if(index != -1){
                value.replace(index,3,"+");
            }
        }

        str_noencrypt.append(value);
        qDebug() << "value: " << value;
        str_noencrypt.append("&");
    }

    str_noencrypt.append("app_key=");
    str_noencrypt.append(appkey);

    qDebug() << "str_noencrypt :" << str_noencrypt;

    //MD5
    sign = QCryptographicHash::hash(str_noencrypt.toUtf8(),QCryptographicHash::Md5).toHex().toUpper();

    qDebug() << "sign: " << sign;

}

void TencentTranslateAPI::slot_SendRequested(QString strinput,QString fromlanguage,QString tolanguage){

    static QNetworkAccessManager *mnetwork_Manager = new QNetworkAccessManager;

    QObject::disconnect(mnetwork_Manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(requestFinished(QNetworkReply*)));
    QMetaObject::Connection connRet = QObject::connect(mnetwork_Manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(requestFinished(QNetworkReply*)));
    Q_ASSERT(connRet);

    //获取时间戳
    QString timestamp;
    getTimestamp(timestamp);

    //获取随机字符
    QString noncestr;
    getNoncestr(noncestr,32);

    QString source = fromlanguage;
    QString target = tolanguage;

    //SIGN 签名
    QMap<QString,QString> testmap;
    testmap.insert("app_id",APPID.toUtf8());
    testmap.insert("time_stamp",timestamp.toUtf8());
    testmap.insert("nonce_str",noncestr.toUtf8());
    testmap.insert("text",strinput.toUtf8());
    testmap.insert("source",source.toUtf8());
    testmap.insert("target",target.toUtf8());

    QString sign;
    getSign(testmap,APPKEY,sign);

    //请求拼接
    QString strrequest;
    strrequest.append("https://api.ai.qq.com/fcgi-bin/nlp/nlp_texttranslate?");
    strrequest.append("&app_id=");
    strrequest.append(APPID.toUtf8());
    strrequest.append("&time_stamp=");
    strrequest.append(timestamp.toUtf8());
    strrequest.append("&nonce_str=");
    strrequest.append(noncestr.toUtf8());
    strrequest.append("&sign=");
    strrequest.append(sign.toUtf8());
    strrequest.append("&text=");
    strrequest.append(strinput.toUtf8().toPercentEncoding());
    strrequest.append("&source=");
    strrequest.append(source.toUtf8());
    strrequest.append("&target=");
    strrequest.append(target.toUtf8());

    qDebug() << "strrequest:" << strrequest;

    QNetworkReply * reply = mnetwork_Manager->get(QNetworkRequest(QString(strrequest)));
    QReplyTimeout * timeoutreply = new QReplyTimeout(reply,timeout_ms);
    connect(timeoutreply,QReplyTimeout::Timeout,this,[=]{
        reply->abort();
        reply->deleteLater();
        qDebug() << "Timeout";
    });

}

void TencentTranslateAPI::requestFinished(QNetworkReply *reply){

    if  (reply->error() == QNetworkReply::NoError)
    {
        QByteArray jsonbytearray = reply->readAll();

        qDebug() << jsonbytearray;

         QJsonParseError jsonpe;
         QJsonDocument jsonfile = QJsonDocument::fromJson(jsonbytearray, &jsonpe);

         if  (jsonpe.error == QJsonParseError::NoError)
         {
             QJsonObject jsobj = jsonfile.object();

             qDebug() << "ret:" << jsobj["ret"].toInt() << "msg:" << jsobj["msg"].toString();

             if(jsobj.contains( "data")){

                 QJsonValue transresultValue = jsobj.value("data");

                     QJsonObject transresultObject = transresultValue.toObject();

                     if(transresultObject.contains("target_text")){
                         QString target_text = transresultObject["target_text"].toString();

                         qDebug() << "target_text:" << target_text;

                         emit TranslationReturn(target_text);
                     }
             }
         }
         else
         {
             qDebug() << "[Error] Js parse error.";
         }
   }
   else
   {
       qDebug() <<  "[Error] Request error.";
   }

   reply->deleteLater();

}



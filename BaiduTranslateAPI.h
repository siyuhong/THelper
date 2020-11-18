#ifndef BAIDUTRANSLATEAPI_H
#define BAIDUTRANSLATEAPI_H

#include <QString>
#include <QTime>
#include <QCryptographicHash>

#include <QObject>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QNetworkAccessManager>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include "TranslatObject.h"

class BaiduTranslateAPI : public TranslatObject
{
    Q_OBJECT
public:
    explicit BaiduTranslateAPI();

public slots:
    void slot_SendRequested(QString strinput,QString fromlanguage,QString tolanguage);
    void requestFinished(QNetworkReply* reply);

private:
    /* Baidu API: APPID & Key*/
    QString APPID = "20190829000330465";
    QString Key = "ooYCad_Jup1cFlcmy66A";

};

#endif // BAIDUTRANSLATEAPI_H

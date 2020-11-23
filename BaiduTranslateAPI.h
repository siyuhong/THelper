#ifndef BAIDUTRANSLATEAPI_H
#define BAIDUTRANSLATEAPI_H

#include "TranslatObject.h"
#include "QReplyTimeout.h"

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
    QString APPKEY = "ooYCad_Jup1cFlcmy66A";
    int timeout_ms = 500;
};

#endif // BAIDUTRANSLATEAPI_H

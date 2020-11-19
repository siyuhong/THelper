#ifndef TENCENTTRANSLATEAPI_H
#define TENCENTTRANSLATEAPI_H

#include <QObject>
#include <QMap>
#include <QString>
#include <QByteArray>
#include <QTextCodec>
#include "TranslatObject.h"

class TencentTranslateAPI : public TranslatObject
{
    Q_OBJECT
public:
    explicit TencentTranslateAPI();

public slots:
    void slot_SendRequested(QString strinput,QString fromlanguage,QString tolanguage);
    void requestFinished(QNetworkReply* reply);

private:
    /* Tencent API: APPID & Key*/
    QString APPID = "2159696347";
    QString APPKEY = "yMJYG71yhVulJSdu";

    void getSign(QMap<QString,QString> lexicographicalmap,QString appkey,QString &sign);
};

#endif // TENCENTTRANSLATEAPI_H

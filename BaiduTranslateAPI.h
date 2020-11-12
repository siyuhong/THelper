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

class BaiduTranslateAPI : public QObject
{
    Q_OBJECT
public:
    explicit BaiduTranslateAPI(QObject *parent = nullptr);

signals:
    void TranslationReturn(QString translation);

public slots:
    void slot_SendRequested(QString strinput,QString fromlanguage,QString tolanguage);
    void requestFinished(QNetworkReply* reply);

private:
    /* Baidu API: APPID & Key*/
    QString APPID = "20190829000330465";
    QString Key = "ooYCad_Jup1cFlcmy66A";

    void init();
    void getRAND(int &rand);
};

#endif // BAIDUTRANSLATEAPI_H

#ifndef TRANSLATOBJECT_H
#define TRANSLATOBJECT_H

#include <QObject>

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

class TranslatObject : public QObject
{
    Q_OBJECT
public:
    explicit TranslatObject(QObject *parent = nullptr);
    //提供给子类的一些工具方法
    void getRAND(int &randm,int max);
    void getNoncestr(QString &noncestr,int len);
    void getTimestamp(QString &timestamp);

signals:
    //对外交互接口
    void SendRequested(QString strinput,QString fromlanguage,QString tolanguage);
    void TranslationReturn(QString translation);

public slots:
    virtual  void slot_SendRequested(QString strinput,QString fromlanguage,QString tolanguage);
    virtual  void requestFinished(QNetworkReply* reply);
};

#endif // TRANSLATOBJECT_H

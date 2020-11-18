#include "TranslatObject.h"

TranslatObject::TranslatObject(QObject *parent) : QObject(parent)
{
    connect(this,SIGNAL(SendRequested(QString,QString,QString)),this,SLOT(slot_SendRequested(QString,QString,QString)));
}

void TranslatObject::slot_SendRequested(QString strinput,QString fromlanguage,QString tolanguage){
}


void TranslatObject::requestFinished(QNetworkReply *reply){
}

/**
 * @brief TranslatObject::getRAND
 * @param randm
 * randm in [0,max).
 */
void TranslatObject::getRAND(int &randm,int max){

    QTime time;
    time= QTime::currentTime();
    qsrand(time.msec()+time.second()*1000);
    randm = qrand() % max;
}

/**
 * @brief getNoncestr
 * @param noncestr
 * @param len
 * len size noncestr.
 */
void TranslatObject::getNoncestr(QString &noncestr,int len){

    const char chrs[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    int chrs_size = sizeof(chrs);

    int randomx = 0;
    for (int i = 0; i < len; ++i)
    {
        randomx= rand() % (chrs_size - 1);
        noncestr.append(chrs[randomx]);
    }
}

/**
 * @brief getTimestamp
 * @param timestamp
 */
void TranslatObject::getTimestamp(QString &timestamp){
   timestamp =  QString::number(QDateTime::currentMSecsSinceEpoch() / 1000);
}

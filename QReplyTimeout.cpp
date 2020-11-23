#include "QReplyTimeout.h"

QReplyTimeout::QReplyTimeout(QNetworkReply *parent,int timeout) : QObject(parent)
{
    if(parent && parent->isRunning()){
        mTimeoutTimer = new QTimer;
        mTimeoutTimer->setSingleShot(true);

        connect(mTimeoutTimer,&QTimer::timeout,this,&QReplyTimeout::TimeoutWork);

        mTimeoutTimer->start(timeout);
    }
}

void QReplyTimeout::TimeoutWork(){
    QNetworkReply *reply = static_cast<QNetworkReply*>(parent());

    if(reply->isRunning()){
        reply->abort();
        reply->deleteLater();

        emit Timeout();
    }
}

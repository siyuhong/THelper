#ifndef QREPLYTIMEOUT_H
#define QREPLYTIMEOUT_H

#include <QObject>
#include <QTimer>
#include <QNetworkReply>

class QReplyTimeout : public QObject
{
    Q_OBJECT
public:
    explicit QReplyTimeout(QNetworkReply *parent,int timeout);

signals:
    void Timeout();

private slots:
    void TimeoutWork();

private:
    QTimer* mTimeoutTimer;
};

#endif // QREPLYTIMEOUT_H

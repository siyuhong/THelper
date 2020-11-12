#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

//#include <QThread>
//#include <BaiduTranslateAPI.h>
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

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_translate_clicked();
    void requestFinished(QNetworkReply* reply);

private:
    Ui::MainWindow *ui;
    QNetworkAccessManager mNetworkManager;

    /* Baidu API: APPID & Key*/
    QString APPID = "20190829000330465";
    QString Key = "ooYCad_Jup1cFlcmy66A";

    void getLanguage(QString languagename,QString &languagecode);
    void getRAND(int &rand);
};

#endif // MAINWINDOW_H

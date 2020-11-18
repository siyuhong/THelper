#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QThread>
#include <BaiduTranslateAPI.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
    void SendRequested(QString requested,QString fromlanguage,QString tolanguage);

private slots:
    void on_pushButton_translate_clicked();
    void slot_TranslationReturn(QString stroutput);
    void on_radioButton_BaiduAPI_clicked();

    void on_radioButton_TencentAPI_clicked();

private:
    Ui::MainWindow *ui;
    QThread *translateThread = NULL;
    BaiduTranslateAPI *mBaidutranslate;

    void init();
    void getLanguage(QString languagename,QString &languagecode);
};

#endif // MAINWINDOW_H

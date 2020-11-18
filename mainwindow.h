#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QThread>
#include "BaiduTranslateAPI.h"
#include "TencentTranslateAPI.h"

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
    void on_radioButton_BaiduAPI_clicked();
    void on_radioButton_TencentAPI_clicked();

    void slot_TranslationReturn(QString stroutput);

private:
    Ui::MainWindow *ui;
    QThread *translateThread = NULL;
    BaiduTranslateAPI *mBaidutranslate;
    TencentTranslateAPI *mTencenttranslate;

    void init();
    void getLanguage(QString languagename,QString &languagecode);
};

#endif // MAINWINDOW_H

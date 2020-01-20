#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QList>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QSslError>
#include <QUrl>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class QSslError;

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QNetworkAccessManager manager;
    QList<QNetworkReply *> currentDownloads;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void downloadFinished(QNetworkReply *reply);
    void sslErrors(const QList<QSslError> &errors);
    void on_pushButtonDownload_clicked();

private:
    void doDownload(const QUrl &url);
    void calc(const QString &text);
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H

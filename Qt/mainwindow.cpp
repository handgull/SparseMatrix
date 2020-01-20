#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QRegularExpression>
#include <QString>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(&manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(downloadFinished(QNetworkReply*)));
    ui->labelFrasi->setText("");
    ui->labelParole->setText("");
    ui->labelCaratteri->setText("");
    ui->labelCaratteri2->setText("");
    ui->labelParagrafi->setText("");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButtonDownload_clicked()
{
    qDebug() << ui->lineEditURL->displayText();
    doDownload(QUrl(ui->lineEditURL->displayText()));

}

void MainWindow::calc(const QString &text){
    ui->textEditDownloadedData->setText(text);
    QRegularExpression NonWhitespaceChar("\\S");
    QRegularExpression Words("[^\\s^-]+");  //greedy re doesn't work?
    QRegularExpression Paragraphs(".+");    //greedy re doesn't work?
    QRegularExpression PhrasesAndEndParagraph("\\.|\\n");
    QRegularExpression EndindPhrases("\\.\\n|\\n\\n|\\n\\n\\n");
    QRegularExpression separatorWords("(\\s|\\n|-)");
    QRegularExpression separatorParagraphs("(\\n)");
    ui->labelParole->setText("numero di parole: " + QString::number(text.split(separatorWords, QString::SkipEmptyParts).length()));
    ui->labelCaratteri->setText("numero di caratteri: " + QString::number(text.length() - 1));
    ui->labelCaratteri2->setText("numero di caratteri senza spazi: " + QString::number(text.count(NonWhitespaceChar)));
    ui->labelFrasi->setText("numero di frasi: " + QString::number(text.count(PhrasesAndEndParagraph) - text.count(EndindPhrases)));
    ui->labelParagrafi->setText("numero di paragrafi: " + QString::number(text.split(separatorParagraphs, QString::SkipEmptyParts).length()));
}

// Constructs a QList of QNetworkReply
void MainWindow::doDownload(const QUrl &url)
{
    QNetworkRequest request(url);
    QNetworkReply *reply = manager.get(request);

#ifndef QT_NO_SSL
    connect(reply, SIGNAL(sslErrors(QList<QSslError>)), SLOT(sslErrors(QList<QSslError>)));
#endif

    // List of reply
    currentDownloads.append(reply);
}

void MainWindow::downloadFinished(QNetworkReply *reply)
{
    QUrl url = reply->url();
    if (reply->error()) {
        fprintf(stderr, "Download of %s failed: %s\n",
                url.toEncoded().constData(),
                qPrintable(reply->errorString()));
    } else {
        calc(QString(reply->readAll()));
    }

    currentDownloads.removeAll(reply);
    reply->deleteLater();
}

void MainWindow::sslErrors(const QList<QSslError> &sslErrors)
{
#ifndef QT_NO_SSL
    foreach (const QSslError &error, sslErrors)
        fprintf(stderr, "SSL error: %s\n", qPrintable(error.errorString()));
#else
    Q_UNUSED(sslErrors);
#endif
}

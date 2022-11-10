#ifndef BANKHOLIDAYGETTER_H
#define BANKHOLIDAYGETTER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QEventLoop>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUrl>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QString>
#include <QDate>

class BankHolidayGetter : public QObject
{
    Q_OBJECT
public:
    explicit BankHolidayGetter(QObject *parent = nullptr);
    std::vector<QDate> getBankHolidays(int year, bool target=false);

private:
    QNetworkReply* sendReq(QString url);
    std::vector<QDate> parseDatesFromJson(QJsonDocument jsonDoc);

    QNetworkAccessManager manager;

signals:

};

#endif // BANKHOLIDAYGETTER_H

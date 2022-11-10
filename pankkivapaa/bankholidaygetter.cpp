#include "bankholidaygetter.h"

BankHolidayGetter::BankHolidayGetter(QObject *parent)
    : QObject{parent}, manager(new QNetworkAccessManager(this))
{

}

std::vector<QDate> BankHolidayGetter::getBankHolidays(int year, bool target)
{
    QString typeString = "BankHolidays?";
    if (target){
        typeString = "NonTargetDates?";
    }
    QString yearString = "&year=" + QString::number(year);
    QString pageNum = "&pageNumber=1";
    // There's max 11 bank holidays so page size 100 should be enough:
    QString pageSize = "&pageSize=100";

    QString url = "https://api.boffsaopendata.fi/bankingcalendar/v1/api/v1/" + typeString + yearString + pageNum + pageSize;
    QNetworkReply* reply = sendReq(url);
    QJsonDocument jsonDoc = QJsonDocument::fromJson(reply->readAll());
    auto specialDates = parseDatesFromJson(jsonDoc);
    reply->deleteLater();

    return specialDates;
}

QNetworkReply* BankHolidayGetter::sendReq(QString url)
{
    QEventLoop loop;
    connect(&manager, SIGNAL(finished(QNetworkReply*)), &loop, SLOT(quit()));
    QNetworkReply* reply = manager.get(QNetworkRequest(QUrl(url)));
    loop.exec();

    return reply;
}

std::vector<QDate> BankHolidayGetter::parseDatesFromJson(QJsonDocument jsonDoc)
{
    std::vector<QDate> specialDates;
    QString dateFormat = "dd.MM.yyyy";
    QJsonArray jsonDates = jsonDoc.object().value("specialDates").toArray();
    for (auto date : jsonDates){
        QDate specialDate = QDate::fromString(QString(date.toObject().value("date").toString()), dateFormat);
        specialDates.push_back(specialDate);
    }
    return specialDates;
}



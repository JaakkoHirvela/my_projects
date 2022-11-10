#ifndef BANKHOLIDAYCHECKER_H
#define BANKHOLIDAYCHECKER_H

#include <QObject>
#include <bankholidaygetter.h>
#include <QDate>

class BankHolidayChecker : public QObject
{
    Q_OBJECT
public:
    explicit BankHolidayChecker(QObject *parent = nullptr);
    std::vector<QDate> getSpecialDates();
    void setSpecialDates(int year, bool target=false);
    bool isBankHoliday(QDate date);
    QDate getNextBankDay(QDate date);

private:
    bool isSpecialDate(QDate date);

    std::vector<QDate> specialDates;
    BankHolidayGetter bankHolidayGetter = BankHolidayGetter(this);
    int currentYear = 0;

};

#endif // BANKHOLIDAYCHECKER_H

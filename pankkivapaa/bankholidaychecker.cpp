#include "bankholidaychecker.h"

BankHolidayChecker::BankHolidayChecker(QObject *parent)
    : QObject{parent}
{

}

std::vector<QDate> BankHolidayChecker::getSpecialDates()
{
    return specialDates;
}

void BankHolidayChecker::setSpecialDates(int year, bool target)
{
    specialDates = bankHolidayGetter.getBankHolidays(year, target);
}

bool BankHolidayChecker::isBankHoliday(QDate date)
{
    if(date.year() != currentYear){
        setSpecialDates(date.year());
        currentYear = date.year();
    }
    // Check if saturday or sunday:
    if (date.dayOfWeek() == 6 || date.dayOfWeek() == 7){
        return true;
    }
    else if (isSpecialDate(date)){
        return true;
    }
    else{
        return false;
    }
}

QDate BankHolidayChecker::getNextBankDay(QDate date)
{
    if (!isBankHoliday(date)){
        return date;
    }
    else{
        QDate nextDay = date.addDays(1);
        if (nextDay.year() != currentYear){
            setSpecialDates(nextDay.year());
            currentYear = nextDay.year();
        }
        return getNextBankDay(nextDay);
    }
}

// private
bool BankHolidayChecker::isSpecialDate(QDate date)
{
    for (QDate specialDate : specialDates){
        if (specialDate == date){
            return true;
        }
    }
    return false;
}


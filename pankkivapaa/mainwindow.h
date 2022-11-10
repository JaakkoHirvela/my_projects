#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QJsonObject>
#include <QJsonArray>
#include <bankholidaygetter.h>
#include <bankholidaychecker.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void init();
    void checkDate();
    void setInfoLabel(QString text);
    bool isDataValid();

    Ui::MainWindow *ui;
    BankHolidayChecker holidayChecker = BankHolidayChecker(this);
};
#endif // MAINWINDOW_H

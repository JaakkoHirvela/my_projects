#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    init();
}

MainWindow::~MainWindow()
{
    delete ui;
}

// private
void MainWindow::init()
{
    ui->dateEdit->setDate(QDate::currentDate());
    holidayChecker.setSpecialDates(QDate::currentDate().year());
    connect(ui->okPushButton, &QPushButton::clicked, this, &MainWindow::checkDate);
}

void MainWindow::checkDate()
{
    QString infoText;
    if (holidayChecker.isBankHoliday(ui->dateEdit->date())){
        QDate nextBankDay = holidayChecker.getNextBankDay(ui->dateEdit->date());
        infoText = ui->dateEdit->date().toString("dd.MM.yyyy") + " on pankkivapaapäivä.\n"
                   "Seuraava pankkipäivä on " + nextBankDay.toString("dd.MM.yyyy");
    }
    else{
        infoText = ui->dateEdit->date().toString("dd.MM.yyyy") + " ei ole pankkivapaapäivä.\n";
    }
    if (isDataValid()){
        setInfoLabel(infoText);
    }
    else{
        setInfoLabel("Jotain meni pieleen, tarkista nettiyhteys.\n");
    }
}

void MainWindow::setInfoLabel(QString text)
{
    ui->infoLabel->setText(text);
}

bool MainWindow::isDataValid()
{
    if (holidayChecker.getSpecialDates().size() == 0){
        return false;
    }
    else{
        return true;
    }
}


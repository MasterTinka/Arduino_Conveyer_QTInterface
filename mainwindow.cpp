#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    on_reloadSerialbutton_clicked();
    connect(&serialPort, &QSerialPort::readyRead, this, &MainWindow::on_serialPortReadyRead);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void sleep(qint64 msec)
{
    QEventLoop loop;
    QTimer::singleShot(msec, &loop, SLOT(quit()));
    loop.exec();
}

void MainWindow::on_serialPortReadyRead()
{
    sleep(100);
    QByteArray message = serialPort.readAll();
    qDebug() << message;
    if(message.contains("CONVEYERS STARTED"))
    {
        ui->indicatorButton->setStyleSheet("background-color: green;"
                                           "border-style: outset;"
                                           "border-width: 1px;"
                                           "border-radius: 18px;"
                                           "padding: 6px;");
        ui->startButton->setDisabled(true);
        ui->stopButton->setEnabled(true);
    }
    else if(message.contains("CONVEYERS GONE"))
    {
        ui->label->setPixmap(QPixmap(":/new/prefix1/Resources/standing_conveyers.png"));
        ui->indicatorButton->setStyleSheet("background-color: red;"
                                           "border-style: outset;"
                                           "border-width: 1px;"
                                           "border-radius: 18px;"
                                           "padding: 6px;");
        ui->stopButton->setDisabled(true);
        ui->startButton->setEnabled(true);
    }

    if (message.contains("CONVEYER0 STARTED"))
    {
        ui->label->setPixmap(QPixmap());
        ui->label->setMovie(oneConveyer);
        oneConveyer->start();
    }
    else if (message.contains("CONVEYER1 STARTED"))
    {
        ui->label->setMovie(twoConveyers);
        twoConveyers->start();
    }
    else if (message.contains("CONVEYER2 STARTED"))
    {
        ui->label->setMovie(threeConveyers);
        threeConveyers->start();
    }

    if(message.contains("ACCIDENT STARTED"))
    {
        ui->stopButton->setDisabled(true);
        ui->startButton->setDisabled(true);

        ui->accidentButton->setStyleSheet("background-color: rgb(255, 0 , 0"
                                          ");");
    }
    else if(message.contains("ACCIDENT GONE"))
    {
        ui->startButton->setEnabled(true);
        ui->accidentButton->setStyleSheet("");
    }
}

void MainWindow::on_reloadSerialbutton_clicked()
{
    ui->SerialList->repaint();
    QStringList ports;
    serialPorts.clear();
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        ports.push_back(info.portName() + " \"" + info.description() + "\"");
        serialPorts.push_back(info);
    }
    ui->SerialList->addItems(ports);
}

void MainWindow::on_startButton_clicked()
{
    serialPort.write("START");
}

void MainWindow::on_SerialList_currentIndexChanged(int index)
{
    serialPort.close();
    serialPort.setPort(serialPorts.at(index));
    serialPort.setBaudRate(115200);
    serialPort.open(QIODevice::ReadWrite);
}

void MainWindow::on_stopButton_clicked()
{
    serialPort.write("STOP");
}

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QtDebug>
#include <QTimer>
#include <QMovie>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
        Q_OBJECT

    public:
        MainWindow(QWidget *parent = nullptr);
        ~MainWindow();

    private slots:
        void on_reloadSerialbutton_clicked();

        void on_startButton_clicked();

        void on_SerialList_currentIndexChanged(int index);

        void on_stopButton_clicked();

        void on_accidentButton_clicked();

        void on_serialPortReadyRead();

        void on_cancelAccidentButton_clicked();

    private:
        Ui::MainWindow *ui;

        QSerialPort serialPort;

        QList<QSerialPortInfo> serialPorts;

        QMovie *oneConveyer = new QMovie(":/new/prefix1/Resources/one-coveyer.gif");
        QMovie *twoConveyers = new QMovie(":/new/prefix1/Resources/two-conveyers.gif");
        QMovie *threeConveyers = new QMovie(":/new/prefix1/Resources/three-conveyers.gif");

};
#endif // MAINWINDOW_H

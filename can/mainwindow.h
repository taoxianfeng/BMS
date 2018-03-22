
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QCanBusDevice> // for CanBusError

#include <QMainWindow>

//txf 2018.3.5
class BMS;
class bmswindow;

class ConnectDialog;

QT_BEGIN_NAMESPACE

class QCanBusFrame;
class QLabel;

namespace Ui {
class MainWindow;
}

QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private Q_SLOTS:
    void checkMessages();
    void sendMessage() const;
    void receiveError(QCanBusDevice::CanBusError) const;
    void connectDevice();
    void disconnectDevice();
    void framesWritten(qint64);
    //txf
    void displaybmswindow();

protected:
    void closeEvent(QCloseEvent *event);

private:
    void showStatusMessage(const QString &message);
    void initActionsConnections();
    void interpretError(QString &, const QCanBusFrame &);

    Ui::MainWindow *m_ui;
    QLabel *m_status;
    ConnectDialog *m_connectDialog;
    QCanBusDevice *m_canDevice;

    //BMS
    bmswindow *m_bms;
};

#endif // MAINWINDOW_H

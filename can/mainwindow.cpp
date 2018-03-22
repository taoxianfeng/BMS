//txf 2018/3/3

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "connectdialog.h"
#include "bmswindow.h"    //txf

#include <QCanBusFrame>
#include <QCanBus>
#include <QCloseEvent>
#include <QTimer>

#include <QtCore/qbytearray.h>
#include <QtCore/qvariant.h>
#include <QtCore/qdebug.h>


static QByteArray dataFromHex(const QString &hex);

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    m_ui(new Ui::MainWindow),   //init m_ui
    m_canDevice(nullptr)
{
    m_ui->setupUi(this);

    m_connectDialog = new ConnectDialog; // init variable

    //txf
    m_bms=new bmswindow;

    m_status = new QLabel;
    m_ui->statusBar->addWidget(m_status);

    m_ui->sendMessagesBox->setEnabled(false);

    initActionsConnections();
    QTimer::singleShot(50, m_connectDialog, &ConnectDialog::show); //display connectDialogs

 //   QTimer::singleShot(50, m_bms, &bmswindow::show); //display connectDialog
    connect(m_ui->sendButton, &QPushButton::clicked, this, &MainWindow::sendMessage);


}

MainWindow::~MainWindow()
{
    delete m_canDevice;

    delete m_connectDialog;
    delete m_ui;
}

void MainWindow::showStatusMessage(const QString &message)
{
    m_status->setText(message);
}

void MainWindow::initActionsConnections()
{
    m_ui->actionConnect->setEnabled(true);
    m_ui->actionDisconnect->setEnabled(false);
    m_ui->actionQuit->setEnabled(true);
//signal & Slot
    connect(m_ui->actionConnect, &QAction::triggered, m_connectDialog, &ConnectDialog::show);  //
    connect(m_connectDialog, &QDialog::accepted, this, &MainWindow::connectDevice);  //
    connect(m_ui->actionDisconnect, &QAction::triggered, this, &MainWindow::disconnectDevice);//
    connect(m_ui->actionQuit, &QAction::triggered, this, &QWidget::close);//
    connect(m_ui->actionAboutQt, &QAction::triggered, qApp, &QApplication::aboutQt);//

//    connect(m_ui->actionAboutQt, &QAction::triggered, qApp, &QApplication::aboutQt);//
     connect(m_ui->parseButton, &QPushButton::clicked, this, &MainWindow::displaybmswindow);
}

void MainWindow::receiveError(QCanBusDevice::CanBusError error) const
{
    switch (error) {
    case QCanBusDevice::ReadError:
    case QCanBusDevice::WriteError:
    case QCanBusDevice::ConnectionError:
    case QCanBusDevice::ConfigurationError:
    case QCanBusDevice::UnknownError:
        qWarning() << m_canDevice->errorString();
    default:
        break;
    }
}

void MainWindow::connectDevice()
{
    const ConnectDialog::Settings p = m_connectDialog->settings();
    //createDevice
    m_canDevice = QCanBus::instance()->createDevice(p.backendName.toLocal8Bit(), p.deviceInterfaceName);
    if (!m_canDevice) {
        showStatusMessage(tr("Error creating device: %1").arg(p.backendName));
        return;
    }

    connect(m_canDevice, &QCanBusDevice::errorOccurred,   //siganl
            this, &MainWindow::receiveError);
    connect(m_canDevice, &QCanBusDevice::framesReceived,   //signal
            this, &MainWindow::checkMessages);
    connect(m_canDevice, &QCanBusDevice::framesWritten,   //sigal
            this, &MainWindow::framesWritten);

    if (p.useConfigurationEnabled) {
        foreach (const ConnectDialog::ConfigurationItem &item, p.configurations)
            m_canDevice->setConfigurationParameter(item.first, item.second);
    }

    if (!m_canDevice->connectDevice()) {
        showStatusMessage(tr("Connection error: %1").arg(m_canDevice->errorString()));

        delete m_canDevice;
        m_canDevice = nullptr;
    } else {
        m_ui->actionConnect->setEnabled(false);
        m_ui->actionDisconnect->setEnabled(true);

        m_ui->sendMessagesBox->setEnabled(true);

        QVariant bitRate = m_canDevice->configurationParameter(QCanBusDevice::BitRateKey);
        if (bitRate.isValid()) {
            showStatusMessage(tr("Backend: %1, connected to %2 at %3 kBit/s")
                    .arg(p.backendName).arg(p.deviceInterfaceName)
                    .arg(bitRate.toInt() / 1000));
        } else {
            showStatusMessage(tr("Backend: %1, connected to %2")
                    .arg(p.backendName).arg(p.deviceInterfaceName));
        }
    }
}

void MainWindow::disconnectDevice()
{
    if (!m_canDevice)
        return;

    m_canDevice->disconnectDevice();
    delete m_canDevice;
    m_canDevice = nullptr;

    m_ui->actionConnect->setEnabled(true);
    m_ui->actionDisconnect->setEnabled(false);

    m_ui->sendMessagesBox->setEnabled(false);

    showStatusMessage(tr("Disconnected"));
}

void MainWindow::framesWritten(qint64 count)
{
    qDebug() << "Number of frames written:" << count;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    m_connectDialog->close();
    event->accept();
}

static QByteArray dataToHex(const QByteArray &data)
{
    QByteArray result = data.toHex().toUpper();

    for (int i = 0; i < result.size(); i += 3)
        result.insert(i, ' ');

    return result;
}

void MainWindow::checkMessages()
{
    if (!m_canDevice)
        return;

    const QCanBusFrame frame = m_canDevice->readFrame(); //


    //txf try 2018.3.4
    QString parseview;
    if(frame.frameId()==0x1826F456)//CHM
    {
      //  QByteArray data={0x10,0x29,0x00,0x06,0xff,0x00,0x03,0x00};
       // QString data="0x10 0x29 0x00 0x06 0xff 0x00 0x03 0x00";
/*
        QString datastring="10 29 00 06 ff 00 03 00";  //
        QByteArray data=dataFromHex(datastring);
        //QCanBusFrame sendframe = new QCanBusFrame(0x1cec56f4,data);
        QCanBusFrame sendframe(0x1cec56f4,data);
        sendframe.setExtendedFrameFormat(true);
        sendframe.setFrameType(QCanBusFrame::DataFrame);
      //  m_canDevice->writeFrame(sendframe);
*/

         QByteArray CHM=frame.payload();
         if(CHM[0]=0x01&&CHM[1]==0x01&&CHM[2]==0x00)
         {
             parseview="CHN Verson :V1.1";
          //   m_ui->parseList->addItem(parseview);
         }

    }

   else if(frame.frameId()==0x1801F456)//CRM
    {
       // QString parseview;
        QByteArray CRM=frame.payload();
        if(CRM.size()==8)
        {
            if(CRM[0]==0x00)
            {
                parseview="CRM,识别请求";

            }
            else if(CRM[0]==0xAA)
            {
                parseview="CRM,识别成功";

            }
            else
            {
                parseview="CRM,error";
            }

        }
        else
        {
         parseview="CRM,error";
        }

        // m_ui->parseList->addItem(parseview);

    }

    else if (frame.frameId()==0x1808F456) //CML
    {
        QByteArray CML=frame.payload();
        float Vmax=0;
        float Vmin=0;
        float Imax=0;
        float Imin=0;
        if(CML.size()==8)  //or 6
        {
                Vmax= (CML[0]+CML[1]*256)/10;
                parseview = QLatin1String(" Vmax=");
                parseview += QString::number(Vmax, 'f',1);

                Vmin=( CML[2]+CML[3]*256)/10;
                parseview += QLatin1String(" Vmin=");
                parseview += QString::number(Vmin, 'f',1);

                Imax= 400-(CML[4]+CML[5]*256)/10;
                parseview += QLatin1String(" Imax=");
                parseview += QString::number(Imax, 'f',1);

                Imin= 400-(CML[6]+CML[7]*256)/10;
                parseview += QLatin1String(" Imin=");
                parseview += QString::number(Imin, 'f',1);

        }
        else
        {
         parseview="CML,error";
        }

    }
    else if (frame.frameId()==0x1812F456) //CCS
    {
        QByteArray CCS=frame.payload();
        float Vout=0;
        float Iout=0;
        qint16 Tcharge=0;
        //float Imin=0;
        if(CCS.size()==7)  //
        {
                Vout= (CCS[0]+CCS[1]*256)*0.1;
                parseview = QLatin1String(" Vout=");
                parseview += QString::number(Vout, 'f',1);

                Iout=400-( CCS[2]+CCS[3]*256)*0.1;
                parseview += QLatin1String(" Iout=");
                parseview += QString::number(Iout, 'f',1);

                Tcharge= (CCS[4]+CCS[5]*256);
                parseview += QLatin1String(" Tcharge=");
                parseview += QString::number(Tcharge, 10);

                if(CCS[7]==1)
                {
                     parseview +=" 充电允许";
                }
                else if(CCS[7]==0)
                {
                      parseview +=" 充电暂停";

                }
        }
        else
        {
         parseview="CCS,error";
        }


    }
else if (frame.frameId()==0x101aF456)//CST  problem
    {

        QByteArray CST=frame.payload();

        if(CST.size()==7)  //
        {
                //CST[3] 0 1 bits
             if(CST[3]&0x03==1)
                {

                     parseview ="  达到设定条件中止";
                }
                 // 2 3 bits
              if(CST[3]&0x0c==4)
                {

                     parseview +="  人工中止";
                }
                // 4 5 bits
             if(CST[3]&0x30==16)
               {

                    parseview +="  故障中止";
               }
               // 6 7 bits
            if(CST[3]&0xb0==64)
              {

                   parseview +="  BMS主动中止";
              }


            //CST[2]
            if(CST[2]&0x03==1)
               {

                    parseview ="  充电机过温";
               }
                // 2 3 bits
             if(CST[2]&0x0c==4)
               {

                    parseview +="  连接器故障";
               }
               // 4 5 bits
            if(CST[2]&0x30==16)
              {

                   parseview +="  充电机内部过温";
              }
              // 6 7 bits
           if(CST[2]&0xb0==64)
             {

                  parseview +="  电量不能传递";
             }


           //CST[3]
           if(CST[1]&0x03==1)
              {

                   parseview ="  充电机急停";
              }
               // 2 3 bits
            if(CST[2]&0x0c==4)
              {

                   parseview +="  其他故障";
              }

            //CST[3]
            if(CST[0]&0x03==1)
               {

                    parseview ="  电流不匹配";
               }
                // 2 3 bits
             if(CST[2]&0x0c==4)
               {

                    parseview +="  电压异常";
               }
        }
        else
        {
         parseview="CST,error";
        }

    }




//m_bms->Frame_Check(frame);




    const qint8 dataLength = frame.payload().size();

    const qint32 id = frame.frameId();

    QString view;
    if (frame.frameType() == QCanBusFrame::ErrorFrame) {
        interpretError(view, frame);
    } else {
        const char *format =
                frame.hasExtendedFrameFormat() ? "Id: %08X" : "Id:      %03X";
        view += QString::asprintf(format, static_cast<uint>(id));
        view += QLatin1String(" bytes: ");
        view += QString::number(dataLength, 10);
        if (frame.frameType() != QCanBusFrame::RemoteRequestFrame) {
            view += QLatin1String(" data: ");
            view += dataToHex(frame.payload());
        }
        view += QLatin1String(" parse: ");
        view+=parseview;
    }

    if (frame.frameType() == QCanBusFrame::RemoteRequestFrame) {
        m_ui->requestList->addItem(view);
        m_ui->requestList->scrollToBottom();
    } else if (frame.frameType() == QCanBusFrame::ErrorFrame) {
        m_ui->errorList->addItem(view);
        m_ui->errorList->scrollToBottom();
    } else {
        m_ui->receiveList->addItem(view);
        m_ui->receiveList->scrollToBottom();
    }
}

static QByteArray dataFromHex(const QString &hex)
{
    QByteArray line = hex.toLatin1();
    line.replace(' ', QByteArray());
    return QByteArray::fromHex(line);
}

void MainWindow::sendMessage() const
{
    if (!m_canDevice)
        return;

    QByteArray writings = dataFromHex(m_ui->lineEdit->displayText());

    QCanBusFrame frame;
    const int maxPayload = m_ui->fdBox->checkState() ? 64 : 8;
    int size = writings.size();
    if (size > maxPayload)
        size = maxPayload;
    writings = writings.left(size);
    frame.setPayload(writings);

    qint32 id = m_ui->idEdit->displayText().toInt(nullptr, 16);
    if (!m_ui->effBox->checkState() && id > 2047) //11 bits
        id = 2047;

    frame.setFrameId(id);
    frame.setExtendedFrameFormat(m_ui->effBox->checkState());

    if (m_ui->remoteFrame->isChecked())
        frame.setFrameType(QCanBusFrame::RemoteRequestFrame);
    else if (m_ui->errorFrame->isChecked())
        frame.setFrameType(QCanBusFrame::ErrorFrame);
    else
        frame.setFrameType(QCanBusFrame::DataFrame);

    m_canDevice->writeFrame(frame);
}

void MainWindow::interpretError(QString &view, const QCanBusFrame &frame)
{
    if (!m_canDevice)
        return;

    view = m_canDevice->interpretErrorFrame(frame);
}
void MainWindow::displaybmswindow()
{
    if(!m_bms->Is_opened())
    {
        m_bms->show();
        m_bms->rerverse_isopened();
    }
    else
    {
        m_bms->close();
       m_bms->rerverse_isopened();
    }


}

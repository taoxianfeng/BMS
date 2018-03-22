#include "bms.h"
#include "ui_bms.h"

BMS::BMS(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BMS)
{
    ui->setupUi(this);
}

BMS::~BMS()
{
    delete ui;
}

 bool BMS::Frame_Check(QCanBusFrame frame)
{
//1. recognition  frame name    and check frame data
    QByteArray data=frame.payload();
    switch(frame.frameId())
    {
    //frame data length <=8
    case 0x1801f456:
    {

        if(data[0]==0x00)
        {
          FrameName="CRM00"; // send BRM_TPCM_RTS   //BRM (41byte)
              qDebug() << "CRM00" ;
        }

        else if(data[0]==0xAA)
        {
             FrameName="CRMAA"; // get into parameter configration stage   // send BCP_TPCM_RTS  (13byte)
              qDebug() << "CRMAA" ;
        }


        else
        {
            //exception handing
            qDebug() << "CRM exception handing " ;

        }
    }
        break;

    //frame data length >8
    case 0x1cecf456:   //TPCM_RTS
                    {
                        QString BRM_TPCM_CTS="11 06 01 ff ff 00 02 00";
                        QString BRM_TPCM_EM="13 29 00 06 ff 00 02 00";

                        QString BCP_TPCM_CTS="11 02 01 ff ff 00 06 00";
                        QString BCP_TPCM_EM="13 0d 00 02 ff 00 06 00";

                       // QByteArray data=frame.payload();
                        // data.toStdString()
                        QByteArray QBAdata=frame.payload();

                        QString Realdata=QBAdata;

                        if(Realdata==BRM_TPCM_CTS)    //QByteArray  tranfer QString  have a problem???
                        {
                             FrameName="BRM_TPCM_CTS";  //start sending BRM_TPCM_DT
                        }
                        else if(Realdata==BRM_TPCM_EM)
                        {
                             FrameName="BRM_TPCM_EM";    //end flag of sendind BRM_TPCM_DT  and check next frame CRMAA
                        }
                        else if(Realdata==BCP_TPCM_CTS)
                        {
                             FrameName="BCP_TPCM_CTS";   // start send BCP_TPCM_DT  and check next frame BCP_TPCM_EM
                        }
                        else if(Realdata==BCP_TPCM_EM)
                        {
                            FrameName="BCP_TPCM_EM";   // start send BCP_TPCM_DT  and check next frame CTS(7 byte)
                        }
                        else
                        {
                            // exception handing
                            qDebug() << "err00 exception handing: "<<Realdata ;
                        }


                        //check format


                    }
        break;

    case 0x1807f456:
    {
        FrameName="CTS";

        //check CTS data

    }                                //just check next frame CML
        break;

    case 0x1808f456:
    {

        FrameName="CML";
        //check CML data
    }                                //1) send  BRO00   and 2) check K5\K6 closed or not    3)send BRO00   4)check CRO00
        break;

    case 0x100af456:
    {
        QByteArray BROdata=frame.payload();
        // QString BROdata=frame.payload().toStdString();
        if(BROdata[0]=0x00)
        FrameName="BRO00";        //
        else if(BROdata[0]=0xAA)
        FrameName="BROAA";

        else
        {
            //exception handing
        }

    }
        break;
    default:
        break;

    }
    return true;

}

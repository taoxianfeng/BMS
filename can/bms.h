#ifndef BMS_H
#define BMS_H

#include <QWidget>


#include <QCanBusFrame>
#include <QCanBus>
#include <QCloseEvent>
#include <QTimer>
#include <QtCore/qbytearray.h>
#include <QtCore/qvariant.h>
#include <QtCore/qdebug.h>
namespace Ui {
class BMS;
}

class BMS : public QWidget
{
    Q_OBJECT

public:
    explicit BMS(QWidget *parent = 0);
    ~BMS();
//private:
 // virtual  QCanBusFrame Frame_Response(QCanBusFrame &frame);
  virtual  bool Frame_Check(QCanBusFrame frame);

private:
    Ui::BMS *ui;
    float Current_demand;
    float Voltage_demand;
    bool Charging_mode;
    QString FrameName;

};

#endif // BMS_H

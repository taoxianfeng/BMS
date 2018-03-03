#ifndef BMS_H
#define BMS_H

#include <QWidget>

namespace Ui {
class BMS;
}

class BMS : public QWidget
{
    Q_OBJECT

public:
    explicit BMS(QWidget *parent = 0);
    ~BMS();

private:
    Ui::BMS *ui;
};

#endif // BMS_H

#ifndef BMSWINDOW_H
#define BMSWINDOW_H

#include <QWidget>

namespace Ui {
class bmswindow;
}

class bmswindow : public QWidget
{
    Q_OBJECT

public:
    explicit bmswindow(QWidget *parent = 0);
    ~bmswindow();
    bool Is_opened();
    void rerverse_isopened();
private:
    Ui::bmswindow *ui;
    bool is_opened;
};

#endif // BMSWINDOW_H

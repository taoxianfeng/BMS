// 2017.3.22 txf

#include "bmswindow.h"
#include "ui_bmswindow.h"

bmswindow::bmswindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::bmswindow)
{
    ui->setupUi(this);
    is_opened=false;
}

bmswindow::~bmswindow()
{
    delete ui;
}
 bool bmswindow::Is_opened()
 {


     return is_opened;
 }
void bmswindow::rerverse_isopened()
{

      is_opened=!is_opened;
}

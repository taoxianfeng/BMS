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

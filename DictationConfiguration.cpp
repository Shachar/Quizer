#include "DictationConfiguration.h"
#include "ui_DictationConfiguration.h"

DictationConfiguration::DictationConfiguration(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DictationConfiguration)
{
    ui->setupUi(this);
}

DictationConfiguration::~DictationConfiguration()
{
    delete ui;
}

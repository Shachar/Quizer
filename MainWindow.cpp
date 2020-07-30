#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "AlgebraWidget.h"
#include "DictationWidget.h"

#define ACTIVE_TAB_CONF "activeTab"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    auto activeTab = settings.value( ACTIVE_TAB_CONF, 0 );
    ui->tabWidget->setCurrentIndex( activeTab.toInt() );
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::tabChanged( int newTab ) {
    settings.setValue( ACTIVE_TAB_CONF, newTab );
}

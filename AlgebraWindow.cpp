#include "AlgebraWindow.h"
#include "ui_AlgebraWindow.h"

#include <cstdlib>

AlgebraWindow::AlgebraWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AlgebraWindow)
{
    ui->setupUi(this);

    std::srand( std::time(0) );
    newExercise();

}

AlgebraWindow::~AlgebraWindow()
{
    delete ui;
}

void AlgebraWindow::weHaveAnswer()
{
    if( checkAnswer() )
        newExercise();
}

void AlgebraWindow::newExercise() {
    a = std::rand() % 10;
    b = std::rand() % 10;

    a++;
    b++;

    char buffer[50];
    sprintf(buffer, "%d", a);
    ui->number1->setText( buffer );
    sprintf(buffer, "%d", b);
    ui->number2->setText( buffer );

    resetAnswerState();
}

bool AlgebraWindow::checkAnswer() {
    QByteArray ba = ui->answer->text().toLocal8Bit();
    int answer = atoi( ba.data() );

    if( answer == a+b )
        return true;

    QPalette *palette = new QPalette();
    palette->setColor(QPalette::Base,Qt::red);
    ui->answer->setPalette(*palette);

    ui->answer->selectAll();

    return false;
}

void AlgebraWindow::resetAnswerState() {
    ui->answer->setText("");

    QPalette *palette = new QPalette();
    palette->setColor(QPalette::Base,Qt::white);
    ui->answer->setPalette(*palette);
}

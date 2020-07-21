#include "AlgebraWindow.h"
#include "ui_AlgebraWindow.h"

#include <cstdlib>

AlgebraWindow::AlgebraWindow(QSettings &settings, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AlgebraWindow),
    settings(settings)
{
    settings.beginGroup("Algebra");
    exercises = settings.value("exercises", Additions).toUInt();

    ui->setupUi(this);

    refreshMenu();

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
    a = std::rand() % 11;
    b = std::rand() % 11;

    switch( chooseOp() ) {
    case Additions:
        answer = a+b;
        ui->operation->setText("+");
        break;
    case Subtractions:
        answer = a+b;
        ui->operation->setText("-");
        std::swap( a, answer );
        break;
    }

    char buffer[50];
    sprintf(buffer, "%d", a);
    ui->number1->setText( buffer );
    sprintf(buffer, "%d", b);
    ui->number2->setText( buffer );

    resetAnswerState();
}

bool AlgebraWindow::checkAnswer() {
    QByteArray ba = ui->answer->text().toLocal8Bit();
    char *endMarker;
    long answer = strtol( ba.data(), &endMarker, 10 );

    if( ba.size()>0 && endMarker==ba.cend() && answer == this->answer )
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

void AlgebraWindow::settingsChangedAdd( bool newState ) {
    if( newState ) {
        exercises |= Additions;
    } else {
        exercises &= ~Additions;
    }

    refreshMenu();
}

void AlgebraWindow::settingsChangedSub( bool newState ) {
    if( newState ) {
        exercises |= Subtractions;
    } else {
        exercises &= ~Subtractions;
    }

    refreshMenu();
}

void AlgebraWindow::refreshMenu() {
    if( exercises==0 )
        exercises = Additions;

    ui->settingsAddition->setChecked( exercises&Additions );
    ui->settingsSubstraction->setChecked( exercises&Subtractions );

    settings.setValue( "exercises", exercises );

    numExerciseTypes=0;
    unsigned exercises = this->exercises;
    while( exercises!=0 ) {
        if( (exercises&1) != 0 ) {
            numExerciseTypes++;
        }

        exercises >>= 1;
    }

    newExercise();
}

AlgebraWindow::Exercises AlgebraWindow::chooseOp() const {
    unsigned opOrdinal = std::rand() % numExerciseTypes;

    unsigned mask = 1;

    goto nextExercise;
    while( opOrdinal!=0 ) {
        opOrdinal--;
        mask<<=1;

    nextExercise:
        while( (exercises&mask)==0 )
            mask<<=1;
    }

    return Exercises(mask);
}

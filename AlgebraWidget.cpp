#include "AlgebraWidget.h"
#include "ui_AlgebraWidget.h"

#include <cstdlib>
#include <iostream>

AlgebraWidget::AlgebraWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AlgebraWidget)
{
    ui->setupUi(this);
    setFocusProxy( ui->answer );

    settings.beginGroup("Algebra");
    exercises = settings.value("exercises", Additions).toUInt();
    settings.endGroup();

    refreshMenu();

    std::srand( std::time(0) );
    newExercise();

}

AlgebraWidget::~AlgebraWidget()
{
    delete ui;
}

void AlgebraWidget::weHaveAnswer()
{
    if( checkAnswer() )
        newExercise();
}

void AlgebraWidget::newExercise() {
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
    case Multiplications:
        answer = a*b;
        ui->operation->setText("×");
        break;
    case Division:
        answer = a*b;
        ui->operation->setText("÷");
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

bool AlgebraWidget::checkAnswer() {
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

void AlgebraWidget::resetAnswerState() {
    ui->answer->setText("");

    QPalette *palette = new QPalette();
    palette->setColor(QPalette::Base,Qt::white);
    ui->answer->setPalette(*palette);
}

void AlgebraWidget::settingsChangedAdd( bool newState ) {
    if( newState ) {
        exercises |= Additions;
    } else {
        exercises &= ~Additions;
    }

    refreshMenu();
}

void AlgebraWidget::settingsChangedSub( bool newState ) {
    if( newState ) {
        exercises |= Subtractions;
    } else {
        exercises &= ~Subtractions;
    }

    refreshMenu();
}

void AlgebraWidget::settingsChangedMult( bool newState ) {
    if( newState ) {
        exercises |= Multiplications;
    } else {
        exercises &= ~Multiplications;
    }

    refreshMenu();
}

void AlgebraWidget::settingsChangedDiv( bool newState ) {
    if( newState ) {
        exercises |= Division;
    } else {
        exercises &= ~Division;
    }

    refreshMenu();
}

void AlgebraWidget::refreshMenu() {
    if( this->exercises==0 )
        this->exercises = Additions;

    ui->settingsAddition->setChecked( exercises&Additions );
    ui->settingsSubtraction->setChecked( exercises&Subtractions );

    settings.setValue( "Algebra/exercises", exercises );

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

AlgebraWidget::Exercises AlgebraWidget::chooseOp() const {
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

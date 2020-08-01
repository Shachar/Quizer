#ifndef ALGEBRAWIDGET_H
#define ALGEBRAWIDGET_H

#include <QWidget>
#include <QSettings>

namespace Ui {
class AlgebraWidget;
}

class AlgebraWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AlgebraWidget(QWidget *parent = 0);
    ~AlgebraWidget();

public slots:
    void weHaveAnswer();
    void resetAnswerState();
    void newExercise();

    void settingsChangedAdd( bool newState );
    void settingsChangedSub( bool newState );
    void settingsChangedMult( bool newState );
    void settingsChangedDiv( bool newState );

private:
    Ui::AlgebraWidget *ui;
    int a, b, answer;
    enum Exercises : unsigned {
        Additions = 1,
        Subtractions = 2,
        Multiplications = 4,
        Division = 8,
    };
    unsigned exercises;
    unsigned numExerciseTypes;

    QSettings settings;

    bool checkAnswer();

    void refreshMenu();

    Exercises chooseOp() const;
};

#endif // ALGEBRAWIDGET_H

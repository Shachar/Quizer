#ifndef ALGEBRAWINDOW_H
#define ALGEBRAWINDOW_H

#include <QMainWindow>
#include <QSettings>

namespace Ui {
class AlgebraWindow;
}

class AlgebraWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AlgebraWindow(QSettings &settings, QWidget *parent = 0);
    ~AlgebraWindow();

public slots:
    void weHaveAnswer();
    void resetAnswerState();

    void settingsChangedAdd( bool newState );
    void settingsChangedSub( bool newState );

private:
    Ui::AlgebraWindow *ui;
    int a, b, answer;
    enum Exercises : unsigned {
        Additions = 1,
        Subtractions = 2,
    };
    unsigned exercises;
    unsigned numExerciseTypes;

    QSettings &settings;

    void newExercise();
    bool checkAnswer();

    void refreshMenu();

    Exercises chooseOp() const;
};

#endif // ALGEBRAWINDOW_H

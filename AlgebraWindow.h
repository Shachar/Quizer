#ifndef ALGEBRAWINDOW_H
#define ALGEBRAWINDOW_H

#include <QMainWindow>

namespace Ui {
class AlgebraWindow;
}

class AlgebraWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AlgebraWindow(QWidget *parent = 0);
    ~AlgebraWindow();

public slots:
    void weHaveAnswer();
    void resetAnswerState();

private:
    Ui::AlgebraWindow *ui;
    int a, b;

    void newExercise();
    bool checkAnswer();
};

#endif // ALGEBRAWINDOW_H

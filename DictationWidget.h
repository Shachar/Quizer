#ifndef DICTATIONWIDGET_H
#define DICTATIONWIDGET_H

#include <QWidget>
#include <QSettings>

namespace Ui {
class DictationWidget;
}

class DictationWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DictationWidget(QWidget *parent = 0);
    ~DictationWidget();

public slots:
    void newAnswer();
    void idk();
    void wordsLocationDlg();
    void dontAsk();

private:
    Ui::DictationWidget *ui;
    QSettings settings;
    struct WordPair {
        QString word;
        QString translation;

        explicit WordPair( QStringList list );
    };
    std::vector< WordPair > words;
    unsigned currentQuestion;

    void newQuestion();
    void resetAnswerState();
    void readWords();
};

#endif // DICTATIONWIDGET_H

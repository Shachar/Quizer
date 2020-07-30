#include "DictationWidget.h"
#include "ui_DictationWidget.h"

#include <QFile>
#include <QTextStream>

#include <assert.h>

DictationWidget::DictationWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DictationWidget)
{
    ui->setupUi(this);

    setFocusProxy( ui->answer );

    readWords();
    newQuestion();
}

DictationWidget::~DictationWidget()
{
    delete ui;
}

void DictationWidget::newAnswer() {
    ui->lastAnswer->setText("");
    ui->lastQuestion->setText("");

    if( ui->answer->text()==words[currentQuestion].word ) {
        // Correct answer
        newQuestion();
    } else {
        // Incorrect answer
        QPalette *palette = new QPalette();
        palette->setColor(QPalette::Base,Qt::red);
        ui->answer->setPalette(*palette);

        ui->answer->selectAll();
    }
}

void DictationWidget::idk() {
    ui->lastQuestion->setText( words[currentQuestion].translation );
    ui->lastAnswer->setText( words[currentQuestion].word );

    newQuestion();
}

DictationWidget::WordPair::WordPair( QStringList list ) {
    assert( list.size()==2 );
    word = std::move( list[0] );
    translation = std::move( list[1] );
}

void DictationWidget::newQuestion() {
    assert( words.size()>0 );
    currentQuestion = std::rand() % words.size();

    ui->question->setText( words[currentQuestion].translation );

    resetAnswerState();
}

void DictationWidget::resetAnswerState() {
    ui->answer->setText("");

    QPalette *palette = new QPalette();
    palette->setColor(QPalette::Base,Qt::white);
    ui->answer->setPalette(*palette);
    ui->answer->setFocus();
}

void DictationWidget::readWords() {
    words.clear();

    settings.beginGroup("Dictation");
    auto wordsPath = settings.value("wordsPath").toString();
    settings.endGroup();

    QFile wordsFile( wordsPath );
    if( !wordsFile.open(QIODevice::ReadOnly | QIODevice::Text) ) {
        abort();
    }

    QTextStream textFile( &wordsFile );
    while( !textFile.atEnd() ) {
        QString line = textFile.readLine();
        assert( line != nullptr );
        words.emplace_back( line.split(";") );
    }
}

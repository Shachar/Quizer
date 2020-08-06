#include "DictationWidget.h"
#include "ui_DictationWidget.h"

#include <QDir>
#include <QFile>
#include <QFileDialog>
#include <QFileInfo>
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
    if( verifyAnswer() ) {
        // Correct answer
        newQuestion();
    }
}

void DictationWidget::idk() {
    ui->lastQuestion->setText( words[currentQuestion].translation );
    ui->lastAnswer->setText( words[currentQuestion].word );

    newQuestion();
}

void DictationWidget::wordsLocationDlg() {
    settings.beginGroup("Dictation");
    auto wordsPath = settings.value("wordsPath").toString();
    settings.endGroup();

    wordsPath = QFileDialog::getOpenFileName( this, "Select dictation words file", wordsPath, "CSV Files (*.csv)" );

    if( wordsPath.size()>0 ) {
        settings.setValue("Dictation/wordsPath", wordsPath);
        readWords();
        newQuestion();

        ui->answer->setFocus();
    }
}

void DictationWidget::dontAsk() {
    if( verifyAnswer() ) {
        words.erase( words.begin()+currentQuestion );

        newQuestion();
    }
}

DictationWidget::WordPair::WordPair( QStringList list ) {
    assert( list.size()==2 );
    word = std::move( list[0] );
    translation = std::move( list[1] );
}

bool DictationWidget::verifyAnswer() {
    if( words.size()==0 )
        return false;

    ui->lastAnswer->setText("");
    ui->lastQuestion->setText("");

    if( ui->answer->text()==words[currentQuestion].word ) {
        return true;
    }

    // Incorrect answer
    QPalette *palette = new QPalette();
    palette->setColor(QPalette::Base,Qt::red);
    ui->answer->setPalette(*palette);

    ui->answer->selectAll();

    return false;
}

void DictationWidget::newQuestion() {
    if( words.size()==0 )
        return;

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

    if( wordsPath.size()==0 ) {
        wordsLocationDlg();
        return;
    }

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

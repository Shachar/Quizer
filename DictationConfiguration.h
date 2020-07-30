#ifndef DICTATIONCONFIGURATION_H
#define DICTATIONCONFIGURATION_H

#include <QDialog>

namespace Ui {
class DictationConfiguration;
}

class DictationConfiguration : public QDialog
{
    Q_OBJECT

public:
    explicit DictationConfiguration(QWidget *parent = 0);
    ~DictationConfiguration();

private:
    Ui::DictationConfiguration *ui;
};

#endif // DICTATIONCONFIGURATION_H

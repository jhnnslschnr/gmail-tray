#ifndef CONFIGDIALOG_H
#define CONFIGDIALOG_H

#include <QDialog>

namespace Ui {
class ConfigDialog;
}

class ConfigDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ConfigDialog(QWidget *parent = 0);
    ~ConfigDialog();

    void load();
    void save();

public slots:
    void accept();

private:
    Ui::ConfigDialog *ui;

};

#endif // CONFIGDIALOG_H

#include "configdialog.h"
#include "ui_configdialog.h"
#include <QSettings>

ConfigDialog::ConfigDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfigDialog)
{
    ui->setupUi(this);
    load();
}

ConfigDialog::~ConfigDialog()
{
    delete ui;
}

void ConfigDialog::load() {
    QSettings settings;
    ui->edit_username->setText(settings.value("username").toString());
    ui->edit_password->setText(settings.value("password").toString());
    ui->spinbox_interval->setValue(settings.value("interval", 60000).toInt());
}

void ConfigDialog::save() {
    QSettings settings;
    settings.setValue("username", ui->edit_username->text());
    settings.setValue("password", ui->edit_password->text());
    settings.setValue("interval", ui->spinbox_interval->value());
}

void ConfigDialog::accept()
{
    save();
    QDialog::accept();
}

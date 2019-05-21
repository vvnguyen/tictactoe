#include "configurationdialog.h"
#include "ui_configurationdialog.h"
#include <QPushButton>

ConfigurationDialog::ConfigurationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfigurationDialog)
{
    ui->setupUi(this);
    updateOKButtonState();
}

ConfigurationDialog::~ConfigurationDialog()
{
    delete ui;
}

void ConfigurationDialog::updateOKButtonState() {
    bool pl1NameEmpty = ui->player1Name->text().isEmpty();
    bool pl2NameEmpty = ui->player2Name->text().isEmpty();
    QPushButton *okButton = ui->buttonBox->button(QDialogButtonBox::Ok);
    okButton->setDisabled(pl1NameEmpty||pl2NameEmpty);
}

void ConfigurationDialog::setPlayer1Name(const QString &p1name) {
    ui->player1Name->setText(p1name);
}

void ConfigurationDialog::setPlayer2Name(const QString &p2name) {
    ui->player2Name->setText(p2name);
}

QString ConfigurationDialog::player1Name() const{
    return ui->player1Name->text();
}

QString ConfigurationDialog::player2Name() const{
    return ui->player2Name->text();
}

#include "formadd.h"
#include "ui_formadd.h"

FormAdd::FormAdd(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FormAdd)
{
    ui->setupUi(this);


}

FormAdd::~FormAdd()
{
    delete ui;
}

void FormAdd::on_pbadd_released()
{
    QMessageBox msgBox;

    int ret = msgBox.information(this, "Informations", "Вы действительно хотите добавить?", QMessageBox::Ok | QMessageBox::Cancel);
    if (ret == QMessageBox::Ok){
        emit guid(ui->ledit_fio->text(), ui->ledit_addr->text(), ui->ledit_numphone->text(), px);
        this->setAttribute(Qt::WA_DeleteOnClose);
        this->close();
    }

}

void FormAdd::on_pb_load_photo_released()
{

    QGraphicsScene *sc = new QGraphicsScene();

    QString filename =   QFileDialog::getOpenFileName(this, tr("Open File"),"/home",tr("Images (*.png *.xpm *.jpg)"));
    px.load(filename);

    sc->addPixmap(px);

    ui->gview_photo->setScene(sc);



}

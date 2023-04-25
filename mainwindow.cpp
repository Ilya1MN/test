#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QStringList lst;
    lst << "По фамилии" << "По адресам" << "По номеру телефона";
    ui->comboBox->addItems(lst);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pbOpenFile_released()
{

    QString filename = QFileDialog::getOpenFileName(this, tr("CSV (*.csv)"));
        QFile file(filename);
    if ( !file.open(QFile::ReadOnly | QFile::Text) ) {
           qDebug() << "File not exists";
       } else {
           QTextStream in(&file);

          QList<QStringList> standardItemsList;
           while (!in.atEnd())
           {

               QString lineRaw = in.readLine();

               QStringList str = lineRaw.split(";");
               standardItemsList.append(str);

           }

           file.close();

           int countRows = standardItemsList.size();
           int countCols = 3;

            ui->tableWidget->setRowCount(countRows);
            ui->tableWidget->setColumnCount(countCols);

           for ( int row = 0; row < countRows; row++ ){
               for ( int column = 0; column < countCols; column++ ){

                    ui->tableWidget->setItem(row, column,  new QTableWidgetItem(standardItemsList[row][column]));
                }
           }



       }
}

void MainWindow::on_pbAdd_released()
{
    FormAdd *dialog = new FormAdd();
    dialog->show();
    connect(dialog, SIGNAL(guid(QString,QString,QString,QPixmap)), this, SLOT(guidslot(QString,QString,QString,QPixmap)));
}
void MainWindow::guidslot(QString fio, QString adr, QString numphone, QPixmap px){
  int row =  ui->tableWidget->rowCount();
  int col = ui->tableWidget->columnCount();

  ui->tableWidget->insertRow(ui->tableWidget->rowCount());
  ui->tableWidget->setItem(row, 0,new QTableWidgetItem(fio));
  ui->tableWidget->setItem(row , 1,new QTableWidgetItem(adr));
  ui->tableWidget->setItem(row, 2,new QTableWidgetItem(numphone));

 QTableWidgetItem* item = new QTableWidgetItem( );

  item->setData( Qt::DecorationRole, px );

   ui->tableWidget->horizontalHeader()->resizeSection(0, 200);
   ui->tableWidget->verticalHeader()->resizeSection(0, 200);

  ui->tableWidget->setItem( row, 3, item );


 }
QList<QStringList> MainWindow::Sorting(QList<QStringList> list){
    int row = ui->tableWidget->rowCount();

    sorts sortt;
    switch (ui->comboBox->currentIndex()) {
        case 0:
            qDebug() << "По фамилии";


            sortt.bubbleSort(&list, row);

            break;
        case 1:
            qDebug() << "По адресам";
            for (int i = 0; i < row; i++){
                QString t1 = list[i][0];
                QString t2 = list[i][1];
                list[i][0] = t2;
                list[i][1] = t1;

            }

           sortt.bubbleSort(&list, row);

           for (int i = 0; i < row; i++){
               QString t1 = list[i][0];
               QString t2 = list[i][1];
               list[i][0] = t2;
               list[i][1] = t1;

           }
            break;
    case 2:
        qDebug() << "По номерам";
        for (int i = 0; i < row; i++){
            QString t1 = list[i][0];
            QString t2 = list[i][2];
            list[i][0] = t2;
            list[i][2] = t1;
            qDebug() << list[i];
        }

       sortt.bubbleSort(&list, row);

       for (int i = 0; i < row; i++){
           QString t1 = list[i][0];
           QString t2 = list[i][2];
           list[i][0] = t2;
           list[i][2] = t1;

       }
        break;

    }

    return list;



}
void MainWindow::on_pbSort_released()
{
    int row = ui->tableWidget->rowCount();
    int column = ui->tableWidget->columnCount();
     QList<QStringList> list;

    for (int i = 0; i < row; i++){
          QStringList listittem;

       for(int j = 0; j < column; j++){
           listittem.append(ui->tableWidget->item(i,j)->text());

       }
       list.append(listittem);


    }
    list = Sorting(list);

 for (int i = 0; i < row; i++){

    for(int j = 0; j < column; j++){
            ui->tableWidget->setItem(i, j,new QTableWidgetItem(list[i][j]));
          }
      }


}


void MainWindow::on_pbDelete_released()
{
    QModelIndexList selectedRows = ui->tableWidget->selectionModel()->selectedRows();
     while (!selectedRows.empty()) {

         ui->tableWidget->removeRow(selectedRows[0].row());
         selectedRows = ui->tableWidget->selectionModel()->selectedRows();
     }
}

void MainWindow::on_pbFind_released()
{
    if (ui->lEditfind->text() != "")
    {
        for (int i = 0; i < ui->tableWidget->rowCount(); i++)
        {
            if (ui->lEditfind->text() == ui->tableWidget->item(i, 0)->text())
            {
              qDebug() << ui->lEditfind->text() <<  "   " << ui->tableWidget->item(i, 0)->text();
            }
        }
    }
}

void MainWindow::on_lEditfind_textChanged(const QString &arg1)
{

    if (ui->lEditfind->text() != nullptr)
    {
        for (int i = 0; i < ui->tableWidget->rowCount(); i++)
        {
            ui->tableWidget->item(i, 0)->setBackgroundColor(QColor(255,255,255));

            if (ui->lEditfind->text() == ui->tableWidget->item(i, 0)->text() )
            {

                    ui->tableWidget->item(i, 0)->setBackgroundColor(QColor(50,50,250));


            }

        }
    }
}

void MainWindow::on_pbsave_released()
{

       QString filepath=QFileDialog::getSaveFileName(this,tr("Save"),".",tr(" (*.csv)"));
       if(!filepath.isEmpty()){
           QFile f(filepath);
           if( f.open( QIODevice::WriteOnly ) )
           {
           QTextStream ts(&f);

           QAbstractItemModel *model = ui->tableWidget->model();
           for(int r=0; r< model->rowCount(); r++)
           {
              for(int c = 0; c< model->columnCount(); c++)
              {
                 ts << model->index(r,c).data().toString() << ';';
              }
              ts << '\n';
           }
           f.close();
           }

           qDebug() << "\ n успешный экспорт !!!";
       }

}

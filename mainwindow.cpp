#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    comboload();

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
           int countCols = 4;

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
  //  connect(dialog, SIGNAL(guid(QString,QString,QString,QPixmap)), this, SLOT(guidslot(QString,QString,QString,QPixmap)));
    connect(dialog, SIGNAL(guid(QString,QString,QString,QByteArray)), this, SLOT(guidslot(QString,QString,QString,QByteArray)));
}


//void MainWindow::guidslot(QString fio, QString adr, QString numphone, QPixmap px){
void MainWindow::guidslot(QString fio, QString adr, QString numphone, QByteArray imagebyarr){
  int row =  ui->tableWidget->rowCount();
  int col = ui->tableWidget->columnCount();

  ui->tableWidget->insertRow(ui->tableWidget->rowCount());
  ui->tableWidget->setItem(row, 0,new QTableWidgetItem(fio));
  ui->tableWidget->setItem(row , 1,new QTableWidgetItem(adr));
  ui->tableWidget->setItem(row, 2,new QTableWidgetItem(numphone));

  ui->tableWidget->setItem(row, 3,new QTableWidgetItem(QString(imagebyarr.toBase64())));


 }


void MainWindow::comboload(){
    QStringList lst;
    lst << "Пузырьковая сортировка"
        << "Сортировка выбором"
        << "Сортировка вставками"
        << "Сортировка Шелла"
        << "Сортировка кучей";
    ui->cb_var_sort->addItems(lst);
    QStringList lsst;
    lsst << "По 1" << " По 2" << " По 3" << "По всем";
    ui->cb_wh_col_by_sort->addItems(lsst);
}
int MainWindow::combobox2info(){

    switch (ui->cb_wh_col_by_sort->currentIndex()) {
    case 0:
        return 0;
        break;
    case 1:
        return 1;
        break;
    case 2:
        return 2;
        break;
    case 3:
       return 3;
        break;
    default:
        break;
    }
}
QStringList  MainWindow::combobox1info(QStringList list){
 int row = ui->tableWidget->rowCount();
     sorttext sorttxt;
    switch (ui->cb_var_sort->currentIndex()) {
    case 0:
        list = sorttxt.bubbleSort(list,row);
       return list;
        break;
    case 1:
       list = sorttxt.selectionSort(list, row);
       return list;
        break;
    case 2:
        list = sorttxt.insertionSort(list, row);
        return list;
        break;

    case 3:
        list = sorttxt.shellSort(list, row);
        return list;
        break;
    case 4:
        list = sorttxt.heapSort(list, row);
        return list;
        break;
    default:
        break;
    }
}
QList<QStringList>  MainWindow::combobox1infostring(QList<QStringList> list){
 int row = ui->tableWidget->rowCount();
        sorts sorttxt;
    switch (ui->cb_var_sort->currentIndex()) {
    case 0:
        list = sorttxt.bubbleSort(list,row);
       return list;
        break;
    case 1:
       list = sorttxt.selectionSort(list, row);
       return list;
        break;
    case 2:
        list = sorttxt.insertionSort(list, row);
        return list;
        break;

    case 3:
        list = sorttxt.shellSort(list, row);
        return list;
        break;
    case 4:
        list = sorttxt.heapSort(list, row);
        return list;
        break;
    default:
        break;
    }
}
QList<QStringList> MainWindow::Sorting(QList<QStringList> list){

    int row = ui->tableWidget->rowCount();
    int column = ui->tableWidget->columnCount();
   // int comb1 = combobox1info();
    int comb2 = combobox2info();


     QStringList listittem;
    if (comb2 == 0 || comb2 == 1 || comb2 == 2)
    {

        for (int i = 0; i < row; i++){

            listittem.append(list[i][comb2]);
        }

        listittem = combobox1info(listittem);

        for (int i = 0; i < row; i++){

            list[i][comb2] = listittem[i];
        }
    }else {
       list = combobox1infostring(list);
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


void MainWindow::on_tableWidget_pressed(const QModelIndex &index)
{
    int row= ui->tableWidget->currentRow();
     QByteArray by = QByteArray::fromBase64(ui->tableWidget->item(row,3)->text().toUtf8());
     QImage image = QImage::fromData(by);
     ui->label_3->setPixmap(QPixmap::fromImage(image));
}

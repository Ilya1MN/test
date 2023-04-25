#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);



}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pbOpenFile_released()
{

    QString filename = QFileDialog::getOpenFileName(this, tr("Excel (*.xlsx)"));
   QAxObject* excel = new QAxObject("Excel.Application", 0);
       QAxObject* workbooks = excel->querySubObject("Workbooks");
       QAxObject* workbook = workbooks->querySubObject("Open(const QString&)", filename);
       QAxObject* sheets = workbook->querySubObject("Worksheets");
       QAxObject* sheet = sheets->querySubObject("Item(int)", 1);
       //sheets->property("Count").toInt();
       QAxObject* usedRange = sheet->querySubObject("UsedRange");
       QAxObject* rows = usedRange->querySubObject("Rows");
       int countRows = rows->property("Count").toInt();
       QAxObject* usedRangep = sheet->querySubObject("UsedRangep");
       QAxObject* columns = usedRange->querySubObject("Columns");
       int countCols = columns->property("Count").toInt();
       ui->tableWidget->setRowCount(countRows);
       ui->tableWidget->setColumnCount(countCols);
       for ( int column = 0; column < 4; column++ ){
       for ( int row = 0; row < countRows; row++ ){
           QAxObject* cell = sheet->querySubObject("Cells(int,int)", row + 1, column + 1 );
           QVariant value = cell->property("Value");
           QTableWidgetItem* item = new QTableWidgetItem(value.toString());
            ui->tableWidget->setItem(row, column, item);
       }
   }
   workbook->dynamicCall("Close()");
   excel->dynamicCall("Quit()");

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


void MainWindow::on_pbSort_released()
{
    int row = ui->tableWidget->rowCount();

     QList<QStringList> list;

     for (int i = 0; i < row; i++){
           QStringList listittem;

        for(int j = 0; j < 4; j++){
            listittem.append(ui->tableWidget->item(i,j)->text());

        }
        list.append(listittem);


     }
    sorts sortt;
    sortt.bubbleSort(&list, row);


 for (int i = 0; i < row; i++){

    for(int j = 0; j < 4; j++){
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
            if (ui->lEditfind->text() == ui->tableWidget->item(i, 1)->text())
            {
              qDebug() << ui->lEditfind->text() <<  "   " << ui->tableWidget->item(i, 1)->text();
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
            ui->tableWidget->item(i, 1)->setBackgroundColor(QColor(255,255,255));

            if (ui->lEditfind->text() == ui->tableWidget->item(i, 1)->text() )
            {

                    ui->tableWidget->item(i, 1)->setBackgroundColor(QColor(50,50,250));

                  //qDebug() << ui->lEditfind->text() <<  "   " << ui->tableWidget->item(i, 1)->text();
            }

        }
    }
}

void MainWindow::on_pbsave_released()
{
    // Получить путь сохранения
       QString filepath=QFileDialog::getSaveFileName(this,tr("Save"),".",tr(" (*.xlsx)"));
       if(!filepath.isEmpty()){
           QAxObject *excel = new QAxObject(this);
           // подключить управление Excel
           excel->setControl("Excel.Application");
           // нет окна отображения
           excel->dynamicCall("SetVisible (bool Visible)","false");
           // Информация о предупреждении не отображается. Если True отключена, это будет показано подсказкой, аналогичной «файлу, который был изменен, независимо от того, сохраняется ли он»
           excel->setProperty("DisplayAlerts", false);
           // Получить коллекцию рабочих книг
           QAxObject *workbooks = excel->querySubObject("WorkBooks");
           // Создать новую рабочую книгу
           workbooks->dynamicCall("Add");
           // Получить текущую рабочую книгу
           QAxObject *workbook = excel->querySubObject("ActiveWorkBook");
           // получить коллекцию рабочих листов
           QAxObject *worksheets = workbook->querySubObject("Sheets");
           // Получить коллекцию рабочего листа 1, то есть лист1
           QAxObject *worksheet = worksheets->querySubObject("Item(int)",1);

           // Установить данные таблицы
           for(int i = 1;i<ui->tableWidget->rowCount()+1;i++)
           {
               for(int j = 1;j<ui->tableWidget->columnCount()+1;j++)
               {
                   QAxObject *Range = worksheet->querySubObject("Cells(int,int)", i, j);
                   Range->dynamicCall("SetValue(const QString &)",ui->tableWidget->item(i-1,j-1)->data(Qt::DisplayRole).toString());
               }
           }
           workbook->dynamicCall("SaveAs(const QString&)",QDir::toNativeSeparators(filepath));// Сохранить в FilePath
           workbook->dynamicCall("Close()");// закрыть рабочую книгу
           excel->dynamicCall("Quit()");// выключить Excel
           delete excel;
           excel=NULL;
           qDebug() << "\ n успешный экспорт !!!";
       }

}

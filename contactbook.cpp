#include "contactbook.h"
#include "ui_contactbook.h"

#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>


QString mFileName = "./output.txt";

void Write(QString fileName, QString str)
{
    QFile mFile(fileName); //mfile檔案 (起始檔案名稱)
    if (!mFile.open(QFile::WriteOnly | QFile::Text)) //只寫 並且是文字檔
    {
        qDebug()<<"File not open!";
        return;
    }

    QTextStream out(&mFile);   //out: 文字串流物件 --> mFile:檔案物件
    //out 只處理文字編碼 用指標把格式化文字寫入檔案物件
    out<<str; //文字輸出
    mFile.flush(); //清空緩衝區存到檔案中
    mFile.close(); //關閉檔案
}

QString Read(const QString &fileName)
{
    QFile mFile(fileName);
    if (!mFile.open(QFile::ReadOnly | QFile::Text))
    {
        qDebug() << "File not found!";
        return QString();
    }

    QTextStream in(&mFile);
    return in.readAll();
}

ContactBook::ContactBook(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ContactBook)
{
    ui->setupUi(this); //透過有人機介面的ContactBook(*ui)來安裝自己(this)的人機介面
    //開始有人機介面
    QStringList ColTotle;
    ui -> tableW->setColumnCount(4); //設定TableWidget 有多少個欄位
    ColTotle<<tr("學號")<<tr("班級")<<tr("姓名")<<tr("電話");
    ui -> tableW -> setHorizontalHeaderLabels(ColTotle); //設定欄位


}

ContactBook::~ContactBook()
{
    delete ui;
}

void ContactBook::on_insertButton_clicked()
{
    QTableWidgetItem *inputCol1, *inputCol2, *inputCol3, *inputCol4;

    inputCol1 = new QTableWidgetItem(QString(ui->lineEdit->text()));
    inputCol2 = new QTableWidgetItem(QString(ui->lineEdit_2->text()));
    inputCol3 = new QTableWidgetItem(QString(ui->lineEdit_3->text()));
    inputCol4 = new QTableWidgetItem(QString(ui->lineEdit_4->text()));
    editingLock = true;
    //添加在哪一個新列 row_index 從0開始
    int cur_row = ui-> tableW -> rowCount();
    ui -> tableW -> insertRow(cur_row);

    qDebug() << cur_row << "\n";
    ui -> tableW -> setItem(cur_row, 0, inputCol1);
    ui -> tableW -> setItem(cur_row, 1, inputCol2);
    ui -> tableW -> setItem(cur_row, 2, inputCol3);
    ui -> tableW -> setItem(cur_row, 3, inputCol4);

    isModified = true;
    editingLock = false;
}

void ContactBook::on_exportButton_clicked()
{
    saveFile();
}

void ContactBook::saveFile()
{
    QString saveFile = "";
    int rowCnt = ui -> tableW -> rowCount();
    int colCnt = ui -> tableW -> columnCount();
    //檔案對話視窗
    mFileName = QFileDialog::getSaveFileName(this, "匯出存檔", ".");

    //Cancel
    if (mFileName.isEmpty()) {
        qDebug() << "Save canceled.";
        return;
    }

    for (int i = 0; i < rowCnt; i++)
    {
        for (int j = 0; j < colCnt; j++)
        {
            saveFile += ui -> tableW -> item(i, j) -> text();
            if (j != colCnt - 1) saveFile += ",";
        }
        saveFile += "\n";
    }
    Write(mFileName, saveFile);
    isModified = false;
}

void ContactBook::on_exitButton_clicked()
{
    //存檔功能檢查
    if (!isModified) {
        close();
        return;
    }

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(
        this,
        "尚未儲存",
        "資料尚未儲存，是否要儲存？",
        QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel
        );

    if (reply == QMessageBox::Yes) {

        saveFile();
        //file save cancel
        if (mFileName.isEmpty() || isModified == true) {
            return;
        }
        close();
    }
    else if (reply == QMessageBox::No) {
        close();
    }
    else {
        // Cancel
        return;
    }

}

void ContactBook::on_importButton_clicked()
{
    mFileName = QFileDialog::getOpenFileName(this, "匯入檔案", ".");
    if (mFileName.isEmpty()) return;

    QString data = Read(mFileName);

    ui->tableW->setRowCount(0); // 清空舊資料

    editingLock = true;

    QStringList lines = data.split("\n", Qt::SkipEmptyParts);

    for (int i = 0; i < lines.size(); i++)
    {
        QString line = lines[i].trimmed();

        if (line.isEmpty()) continue;  // 空行

        QStringList parts = line.split(",");

        ui->tableW->insertRow(i);

        //write echo col
        for (int j = 0; j < parts.size(); j++)
        {
            QString value = (j < parts.size()) ? parts[j] : "";
            ui->tableW->setItem(i, j, new QTableWidgetItem(value));
        }
    }

    isModified = false;
    editingLock = false;

}


void ContactBook::on_tableW_itemChanged(QTableWidgetItem *item)
{
    if (editingLock) return;
    isModified = true;
}


#include "contactbook.h"
#include "ui_contactbook.h"

#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QShortcut>
#include <QKeySequence>
#include <QTimer>


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
    
    // 啟用排序功能
    ui -> tableW -> setSortingEnabled(true);
    
    // 設定表格欄位寬度自動調整
    ui -> tableW -> horizontalHeader()->setStretchLastSection(true);
    
    // 設定行選取模式
    ui -> tableW -> setSelectionBehavior(QAbstractItemView::SelectRows);
    ui -> tableW -> setSelectionMode(QAbstractItemView::SingleSelection);
    
    // 設定表格為可編輯
    ui -> tableW -> setEditTriggers(QAbstractItemView::DoubleClicked);
    
    // 設定提示文字
    ui -> lineEdit -> setPlaceholderText("請輸入學號");
    ui -> lineEdit_2 -> setPlaceholderText("請輸入班級");
    ui -> lineEdit_3 -> setPlaceholderText("請輸入姓名");
    ui -> lineEdit_4 -> setPlaceholderText("請輸入電話");
    
    // 設定按鈕提示
    ui -> insertButton -> setToolTip("將輸入的資料新增到表格中 (快捷鍵: Ctrl+N)");
    ui -> pushButton -> setToolTip("從CSV或TXT檔案匯入資料 (快捷鍵: Ctrl+I)");
    ui -> exportButton -> setToolTip("將表格資料匯出為CSV或TXT檔案 (快捷鍵: Ctrl+E)");
    ui -> deleteButton -> setToolTip("刪除選中的資料列 (快捷鍵: Delete)");
    ui -> exitButton -> setToolTip("結束程式 (快捷鍵: Ctrl+Q)");
    
    // 設定鍵盤快捷鍵
    QShortcut *insertShortcut = new QShortcut(QKeySequence(Qt::CTRL | Qt::Key_N), this);
    connect(insertShortcut, &QShortcut::activated, ui->insertButton, &QPushButton::click);
    
    QShortcut *importShortcut = new QShortcut(QKeySequence(Qt::CTRL | Qt::Key_I), this);
    connect(importShortcut, &QShortcut::activated, ui->pushButton, &QPushButton::click);
    
    QShortcut *exportShortcut = new QShortcut(QKeySequence(Qt::CTRL | Qt::Key_E), this);
    connect(exportShortcut, &QShortcut::activated, ui->exportButton, &QPushButton::click);
    
    QShortcut *deleteShortcut = new QShortcut(QKeySequence::Delete, this);
    connect(deleteShortcut, &QShortcut::activated, ui->deleteButton, &QPushButton::click);
    
    QShortcut *exitShortcut = new QShortcut(QKeySequence(Qt::CTRL | Qt::Key_Q), this);
    connect(exitShortcut, &QShortcut::activated, ui->exitButton, &QPushButton::click);
    
    // 設定Enter鍵在lineEdit中按下時觸發新增
    connect(ui->lineEdit, &QLineEdit::returnPressed, ui->insertButton, &QPushButton::click);
    connect(ui->lineEdit_2, &QLineEdit::returnPressed, ui->insertButton, &QPushButton::click);
    connect(ui->lineEdit_3, &QLineEdit::returnPressed, ui->insertButton, &QPushButton::click);
    connect(ui->lineEdit_4, &QLineEdit::returnPressed, ui->insertButton, &QPushButton::click);
}

ContactBook::~ContactBook()
{
    delete ui;
}

void ContactBook::on_insertButton_clicked()
{
    // 驗證必填欄位
    QString studentId = ui->lineEdit->text().trimmed();
    QString className = ui->lineEdit_2->text().trimmed();
    QString name = ui->lineEdit_3->text().trimmed();
    QString phone = ui->lineEdit_4->text().trimmed();
    
    if (studentId.isEmpty() || name.isEmpty())
    {
        QMessageBox::warning(this, "警告", "學號和姓名為必填欄位！");
        return;
    }
    
    QTableWidgetItem *inputCol1, *inputCol2, *inputCol3, *inputCol4;

    inputCol1 = new QTableWidgetItem(studentId);
    inputCol2 = new QTableWidgetItem(className);
    inputCol3 = new QTableWidgetItem(name);
    inputCol4 = new QTableWidgetItem(phone);
    
    // 設定文字顏色為黑色
    inputCol1->setForeground(QBrush(QColor(0, 0, 0)));
    inputCol2->setForeground(QBrush(QColor(0, 0, 0)));
    inputCol3->setForeground(QBrush(QColor(0, 0, 0)));
    inputCol4->setForeground(QBrush(QColor(0, 0, 0)));

    //添加在哪一個新列 row_index 從0開始
    int cur_row = ui-> tableW -> rowCount();
    ui -> tableW -> insertRow(cur_row);

    qDebug() << cur_row << "\n";
    ui -> tableW -> setItem(cur_row, 0, inputCol1);
    ui -> tableW -> setItem(cur_row, 1, inputCol2);
    ui -> tableW -> setItem(cur_row, 2, inputCol3);
    ui -> tableW -> setItem(cur_row, 3, inputCol4);
    
    // 清空輸入欄位
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();
    
    // 將焦點設回第一個輸入欄位
    ui->lineEdit->setFocus();
    
    updateStatus("✓ 資料已新增成功！");
}

void ContactBook::on_exportButton_clicked()
{
    QString saveFile = "";
    int rowCnt = ui -> tableW -> rowCount();
    int colCnt = ui -> tableW -> columnCount();
    
    if (rowCnt == 0)
    {
        QMessageBox::warning(this, "警告", "沒有資料可以匯出！");
        return;
    }
    
    //檔案對話視窗
    mFileName = QFileDialog::getSaveFileName(this, "匯出存檔", ".", "CSV 檔案 (*.csv);;文字檔案 (*.txt);;所有檔案 (*)");
    
    if (mFileName.isEmpty())
    {
        return; // 使用者取消
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
    updateStatus("✓ 資料已成功匯出！");
    QMessageBox::information(this, "成功", "資料已成功匯出！");
}

void ContactBook::on_pushButton_clicked()
{
    // 匯入功能實作
    QString importFile = QFileDialog::getOpenFileName(this, "選擇匯入檔案", ".", "CSV 檔案 (*.csv);;文字檔案 (*.txt);;所有檔案 (*)");
    
    if (importFile.isEmpty())
    {
        return; // 使用者取消
    }
    
    QFile mFile(importFile);
    if (!mFile.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::critical(this, "錯誤", "無法開啟檔案！");
        return;
    }
    
    QTextStream in(&mFile);
    int importedCount = 0;
    
    while (!in.atEnd())
    {
        QString line = in.readLine();
        QStringList fields = line.split(",");
        
        // 確保有4個欄位
        if (fields.size() >= 4)
        {
            QTableWidgetItem *col1 = new QTableWidgetItem(fields[0].trimmed());
            QTableWidgetItem *col2 = new QTableWidgetItem(fields[1].trimmed());
            QTableWidgetItem *col3 = new QTableWidgetItem(fields[2].trimmed());
            QTableWidgetItem *col4 = new QTableWidgetItem(fields[3].trimmed());
            
            // 設定文字顏色為黑色
            col1->setForeground(QBrush(QColor(0, 0, 0)));
            col2->setForeground(QBrush(QColor(0, 0, 0)));
            col3->setForeground(QBrush(QColor(0, 0, 0)));
            col4->setForeground(QBrush(QColor(0, 0, 0)));
            
            int cur_row = ui -> tableW -> rowCount();
            ui -> tableW -> insertRow(cur_row);
            ui -> tableW -> setItem(cur_row, 0, col1);
            ui -> tableW -> setItem(cur_row, 1, col2);
            ui -> tableW -> setItem(cur_row, 2, col3);
            ui -> tableW -> setItem(cur_row, 3, col4);
            
            importedCount++;
        }
    }
    
    mFile.close();
    updateStatus(QString("✓ 已成功匯入 %1 筆資料！").arg(importedCount));
    QMessageBox::information(this, "成功", QString("已匯入 %1 筆資料！").arg(importedCount));
}

void ContactBook::on_deleteButton_clicked()
{
    // 刪除選中的行
    int currentRow = ui -> tableW -> currentRow();
    
    if (currentRow < 0)
    {
        QMessageBox::warning(this, "警告", "請先選擇要刪除的資料列！");
        return;
    }
    
    // 確認刪除
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "確認刪除", 
                                  "確定要刪除選中的資料嗎？",
                                  QMessageBox::Yes | QMessageBox::No);
    
    if (reply == QMessageBox::Yes)
    {
        ui -> tableW -> removeRow(currentRow);
        updateStatus("✓ 資料已刪除成功！");
    }
}

void ContactBook::on_exitButton_clicked()
{
    // 確認是否要離開
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "確認", "確定要結束程式嗎？",
                                  QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes)
    {
        close();
    }
}

void ContactBook::updateStatus(const QString &message, int duration)
{
    ui->statusLabel->setText(message);
    ui->statusLabel->setStyleSheet("font-size: 10pt; color: #27ae60; padding: 5px; font-weight: bold;");
    
    QTimer::singleShot(duration, this, [this]() {
        ui->statusLabel->setText("就緒 ✓");
        ui->statusLabel->setStyleSheet("font-size: 10pt; color: #000000; padding: 5px;");
    });
}

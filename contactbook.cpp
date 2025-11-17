#include "contactbook.h"
#include "ui_contactbook.h"

#include <QDebug>
#include <QFile>
#include <QFileDialog>


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

    // 應用美化樣式
    QString styleSheet = R"(
        /* 主視窗樣式 */
        QDialog {
            background-color: #f5f7fa;
            font-family: "Microsoft JhengHei", "微軟正黑體", Arial, sans-serif;
        }

        /* 表格樣式 */
        QTableWidget {
            background-color: white;
            border: 2px solid #d0d7de;
            border-radius: 8px;
            gridline-color: #e1e4e8;
            selection-background-color: #0969da;
            selection-color: white;
            font-size: 14px;
        }

        QTableWidget::item {
            padding: 8px;
            border-bottom: 1px solid #e1e4e8;
        }

        QTableWidget::item:selected {
            background-color: #0969da;
            color: white;
        }

        QTableWidget::item:hover {
            background-color: #f6f8fa;
        }

        QHeaderView::section {
            background-color: #0969da;
            color: white;
            padding: 10px;
            border: none;
            font-weight: bold;
            font-size: 14px;
            text-align: center;
        }

        QHeaderView::section:hover {
            background-color: #0860ca;
        }

        /* 標籤樣式 */
        QLabel {
            color: #24292f;
            font-size: 14px;
            font-weight: 500;
            padding: 5px;
        }

        /* 輸入框樣式 */
        QLineEdit {
            background-color: white;
            border: 2px solid #d0d7de;
            border-radius: 6px;
            padding: 8px 12px;
            font-size: 14px;
            color: #24292f;
        }

        QLineEdit:focus {
            border-color: #0969da;
            outline: none;
        }

        QLineEdit:hover {
            border-color: #8c959f;
        }

        /* 按鈕樣式 */
        QPushButton {
            background-color: #0969da;
            color: white;
            border: none;
            border-radius: 6px;
            padding: 10px 20px;
            font-size: 14px;
            font-weight: 500;
            min-width: 80px;
        }

        QPushButton:hover {
            background-color: #0860ca;
        }

        QPushButton:pressed {
            background-color: #0757ba;
        }

        /* 新增按鈕 - 綠色主題 */
        QPushButton#insertButton {
            background-color: #1a7f37;
        }

        QPushButton#insertButton:hover {
            background-color: #1a7f37;
            opacity: 0.9;
        }

        QPushButton#insertButton:pressed {
            background-color: #116329;
        }

        /* 匯出按鈕 - 紫色主題 */
        QPushButton#exportButton {
            background-color: #8250df;
        }

        QPushButton#exportButton:hover {
            background-color: #7745cc;
        }

        QPushButton#exportButton:pressed {
            background-color: #6639ba;
        }

        /* 結束按鈕 - 灰色主題 */
        QPushButton#exitButton {
            background-color: #6e7781;
        }

        QPushButton#exitButton:hover {
            background-color: #57606a;
        }

        QPushButton#exitButton:pressed {
            background-color: #424a53;
        }

        /* 匯入按鈕 - 橙色主題 */
        QPushButton#pushButton {
            background-color: #fb8500;
        }

        QPushButton#pushButton:hover {
            background-color: #e07700;
        }

        QPushButton#pushButton:pressed {
            background-color: #c66900;
        }

        /* 滾動條樣式 */
        QScrollBar:vertical {
            background-color: #f6f8fa;
            width: 12px;
            border-radius: 6px;
        }

        QScrollBar::handle:vertical {
            background-color: #d0d7de;
            border-radius: 6px;
            min-height: 20px;
        }

        QScrollBar::handle:vertical:hover {
            background-color: #8c959f;
        }

        QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical {
            height: 0px;
        }

        QScrollBar:horizontal {
            background-color: #f6f8fa;
            height: 12px;
            border-radius: 6px;
        }

        QScrollBar::handle:horizontal {
            background-color: #d0d7de;
            border-radius: 6px;
            min-width: 20px;
        }

        QScrollBar::handle:horizontal:hover {
            background-color: #8c959f;
        }

        QScrollBar::add-line:horizontal, QScrollBar::sub-line:horizontal {
            width: 0px;
        }
    )";

    this->setStyleSheet(styleSheet);
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

    //添加在哪一個新列 row_index 從0開始
    int cur_row = ui-> tableW -> rowCount();
    ui -> tableW -> insertRow(cur_row);

    qDebug() << cur_row << "\n";
    ui -> tableW -> setItem(cur_row, 0, inputCol1);
    ui -> tableW -> setItem(cur_row, 1, inputCol2);
    ui -> tableW -> setItem(cur_row, 2, inputCol3);
    ui -> tableW -> setItem(cur_row, 3, inputCol4);
}

void ContactBook::on_exportButton_clicked()
{
    QString saveFile = "";
    int rowCnt = ui -> tableW -> rowCount();
    int colCnt = ui -> tableW -> columnCount();
    //檔案對話視窗
    mFileName = QFileDialog::getSaveFileName(this, "匯出存檔", ".");
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
}


void ContactBook::on_exitButton_clicked()
{
    //加入存檔功能
    close();
}

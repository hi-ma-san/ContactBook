#ifndef CONTACTBOOK_H
#define CONTACTBOOK_H

#include <QDialog>


QT_BEGIN_NAMESPACE
namespace Ui {
class ContactBook; //有人機介面的ContactBook
}
QT_END_NAMESPACE

class ContactBook : public QDialog //沒有人機介面的ContactBook
{
    Q_OBJECT

public:
    ContactBook(QWidget *parent = nullptr);
    ~ContactBook();

private slots:

    void on_insertButton_clicked();

    void on_exportButton_clicked();

    void on_pushButton_clicked();

    void on_deleteButton_clicked();

    void on_exitButton_clicked();

private:
    Ui::ContactBook *ui; //用指標指向有人機介面的ContactBook
    void updateStatus(const QString &message, int duration = 3000);
};
#endif // CONTACTBOOK_H

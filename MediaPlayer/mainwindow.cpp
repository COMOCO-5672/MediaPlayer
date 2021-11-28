#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow() { delete ui; }
void MainWindow::on_pushButton_clicked()
{
    auto text = ui->lineEdit->text().trimmed();
    if (text.isEmpty()) {
        QMessageBox::warning(this, "warning", QString::fromLocal8Bit("输入内容为空"));
        return;
    }
    qDebug("url:%s", text);
    if (!pStream_) {
        pStream_ = new stream;
        pStream_->openByUrl(text.toStdString());
    } else {
        // close
        // pStream_->closeInput();
    }
}

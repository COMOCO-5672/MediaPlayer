#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
  ui->setupUi(this);
}

MainWindow::~MainWindow() { delete ui; }
void MainWindow::on_pushButton_clicked()
{
  auto text = ui->lineEdit->text().trimmed();
  if (text.isEmpty())
    return;
  // start play rtsp
}

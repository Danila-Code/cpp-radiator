#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QString image_path = ":/images/images/radiator.bmp";
    SetPixmap(ui->lbl_image, image_path);

}

void MainWindow::SetPixmap(QLabel* label_pix, const QString path) {
    QPixmap pix(path);
    Q_ASSERT(!pix.isNull());

    label_pix->setPixmap(pix);
    FitToImage(label_pix);
    label_pix->show();
}

void MainWindow::FitToImage(QLabel *label) {
    QPixmap pix = label->pixmap();
    int width = pix.width();
    int height = pix.height();
    label->move(10,0);
    label->setFixedHeight(height);
    label->setFixedWidth(width);
}

MainWindow::~MainWindow()
{
    delete ui;
}

#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QRegularExpression>
#include <limits>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowTitle("Расчёт ребристого радиатора");
    QString image_path = ":/images/images/radiator.bmp";
    SetPixmap(ui->lbl_image, image_path);

    SetValidators();

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
    label->move(width + 40,0);
    label->setFixedHeight(height);
    label->setFixedWidth(width);
}

MainWindow::~MainWindow() {
    delete ui;
}
// Calculate radiator temperature and thermal coeffs
void MainWindow::on_pb_calculate_clicked() {
    SetRadiatorParams();
    //radiator_.GetRadiatorTemperature();
}

void MainWindow::on_le_base_length_textChanged(const QString &arg1) {
    Validate(ui->le_base_length);
}

void MainWindow::on_le_base_width_textChanged(const QString &arg1) {
    Validate(ui->le_base_width);
}

void MainWindow::on_le_base_height_textChanged(const QString &arg1) {
    Validate(ui->le_base_height);
}

void MainWindow::on_le_fin_length_textChanged(const QString &arg1) {
    Validate(ui->le_fin_length);
}

void MainWindow::on_le_fin_width_textChanged(const QString &arg1) {
    Validate(ui->le_fin_width);
}

void MainWindow::on_le_fin_height_textChanged(const QString &arg1) {
    Validate(ui->le_fin_height);
}

void MainWindow::on_le_fin_step_textChanged(const QString &arg1) {
    Validate(ui->le_fin_step);
}

void MainWindow::on_le_fin_area_width_textChanged(const QString &arg1) {
    Validate(ui->le_fin_area_width);
}

void MainWindow::on_led_conductivity_textChanged(const QString &arg1) {
    Validate(ui->led_conductivity);
}

void MainWindow::on_led_blackness_textChanged(const QString &arg1) {
    Validate(ui->led_blackness);
}

void MainWindow::on_led_t_env_textChanged(const QString &arg1) {
    //Validate(ui->led_t_env);
}

void MainWindow::on_led_power_textChanged(const QString &arg1) {
    Validate(ui->led_power);
}

// set validators for lineedits
void MainWindow::SetValidators() {
    ui->led_blackness->setValidator(new QDoubleValidator(0.0, 1.0, 10, this));
    ui->led_conductivity->setValidator(new QDoubleValidator(0.0001, __DBL_MAX__, 10, this));
    ui->led_t_env->setValidator(new QDoubleValidator(-273.0, __DBL_MAX__, 10, this));
    ui->led_power->setValidator(new QDoubleValidator(0, __DBL_MAX__, 10, this ));
    // all sizes in mm - int values
    QRegularExpression re("le_.+");
    QList<QLineEdit*> le_list =  ui->tb_radiator_params->findChildren<QLineEdit*>(re);
    for (QLineEdit* le : le_list) {
        le->setValidator(new QIntValidator(1, INT_MAX, this));
    }
}
// set params of Radiator
void MainWindow::SetRadiatorParams() {
    // base sizes
    radiator_.SetBaseThickness(ui->le_base_height->text().toDouble());
    radiator_.SetBaseLength(ui->le_base_length->text().toDouble());
    radiator_.SetBaseWidth(ui->le_base_width->text().toDouble());
    // fins sizes
    radiator_.SetFinHeight(ui->le_fin_height->text().toDouble());
    radiator_.SetFinLength(ui->le_fin_length->text().toDouble());
    radiator_.SetFinWidth(ui->le_fin_width->text().toDouble());
    radiator_.SetFinAreaWidth(ui->le_fin_area_width->text().toDouble());
    radiator_.SetFinStep(ui->le_fin_step->text().toDouble());
    // thermal params
    radiator_.SetConductivity(ui->led_conductivity->text().toDouble());
    radiator_.SetBlackness(ui->led_blackness->text().toDouble());
    radiator_.SetTEnv(ui->led_t_env->text().toDouble());
    radiator_.SetPower(ui->led_power->text().toDouble());
    // set orientation
    radiator_.SetOrientation(static_cast<Orientation>(ui->cb_orientation->currentIndex()));
}
// verify line edit text and undo if it invalid
void MainWindow::Validate(QLineEdit* const le) {
    if (!le->hasAcceptableInput()) {
        le->undo();
    }
}

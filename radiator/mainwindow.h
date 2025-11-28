#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QLineEdit>

#include "radiator.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void SetPixmap(QLabel* label_pix, const QString path);

    void FitToImage(QLabel *label);

private slots:
    void on_pb_calculate_clicked();

    void on_le_base_length_textChanged(const QString &arg1);
    void on_le_base_width_textChanged(const QString &arg1);
    void on_le_base_height_textChanged(const QString &arg1);

    void on_le_fin_length_textChanged(const QString &arg1);
    void on_le_fin_width_textChanged(const QString &arg1);
    void on_le_fin_height_textChanged(const QString &arg1);
    void on_le_fin_step_textChanged(const QString &arg1);
    void on_le_fin_area_width_textChanged(const QString &arg1);

    void on_led_conductivity_textChanged(const QString &arg1);
    void on_led_blackness_textChanged(const QString &arg1);

    void on_led_t_env_textChanged(const QString &arg1);
    void on_led_power_textChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;

    Radiator radiator_;

    void SetValidators();
    void SetRadiatorParams();
    void Validate(QLineEdit* const le);

};
#endif // MAINWINDOW_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_horizontalSlider_RPM_valueChanged(int value);

    void on_horizontalSlider_TEMP_valueChanged(int value);

    void on_horizontalSlider_Fuel_valueChanged(int value);

    void on_pushButton_Left_pressed();

    void on_pushButton_Right_pressed();

    void on_horizontalSlider_Speed_valueChanged(int value);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H

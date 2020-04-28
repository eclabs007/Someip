#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include "communication.h"
extern void send_data(s_vehicle_data_t data);
s_vehicle_data_t vdata;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //this->setStyleSheet("background-color: purple ;");
   QPixmap bkgnd("./car.jpg");
   bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
   QPalette palette;
   palette.setBrush(QPalette::Background, bkgnd);
   this->setPalette(palette);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_horizontalSlider_RPM_valueChanged(int value)
{
   qDebug() << "RPM :" << value;
   vdata.message=value;
   vdata.type=TYPE_DATA_RPM;
   send_data(vdata);

}

void MainWindow::on_horizontalSlider_TEMP_valueChanged(int value)
{
    qDebug() << "TEMP :" << value;
    vdata.message=value;
    vdata.type=TYPE_DATA_TEMP;
    send_data(vdata);
}

void MainWindow::on_horizontalSlider_Fuel_valueChanged(int value)
{
    qDebug() << "Fuel :" << value;
    vdata.message=value;
    vdata.type=TYPE_DATA_FUEL;
    send_data(vdata);
}

static int Indicator_state;

void MainWindow::on_pushButton_Left_pressed()
{
    qDebug() << "Left Pressed:" ;
    static int is_on=0;
    if (is_on==0){
    vdata.message=1;
    vdata.type=TYPE_DATA_LI;
    send_data(vdata);
    is_on=1;

    }else{
        vdata.message=0;
        vdata.type=TYPE_DATA_LI;
        send_data(vdata);
        is_on=0;
    }
}

void MainWindow::on_pushButton_Right_pressed()
{
    qDebug() << "Right Pressed:" ;
    static int is_on=0;
    if (is_on==0){
    vdata.message=1;
    vdata.type=TYPE_DATA_RI;
    send_data(vdata);
    is_on=1;

    }else{
        vdata.message=0;
        vdata.type=TYPE_DATA_RI;
        send_data(vdata);
        is_on=0;
    }
}

void MainWindow::on_horizontalSlider_Speed_valueChanged(int value)
{
    qDebug() << "Speed :" << value;
    vdata.message=value;
    vdata.type=TYPE_DATA_SPEED;
    send_data(vdata);
}

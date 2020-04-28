#include "mainwindow.h"
#include <QApplication>
#include "communication.h"
#include "pthread.h"
pthread_t tid_com;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    pthread_create(&tid_com,NULL,init_communication,NULL);

    a.exec();

    return 1;
}

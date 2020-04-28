#include "cluster.h"
#include <QLocale>
#include<QDebug>

static Cluster * clusterInstance = Q_NULLPTR;

Cluster::Cluster(QObject *parent)
    : QObject(parent), m_speed(), m_rpm(), m_fuel(), m_totalDistance()
{
    mTotalDistance = 23567 * 1000;

    connect(&distanceTimer, SIGNAL(timeout()), this, SLOT(calcTotalDistance()));

    distanceTimer.setInterval(1000);
    distanceTimer.start();
}

Cluster *Cluster::instance()
{
    if ( clusterInstance == Q_NULLPTR )
    {
        clusterInstance = new Cluster;
        clusterInstance->init();
    }

    return clusterInstance;
}

void Cluster::finalize()
{
    if ( clusterInstance != Q_NULLPTR )
    {
        delete clusterInstance;
        clusterInstance = Q_NULLPTR;
    }
}

Cluster::~Cluster()
{
//    if ( distanceTimer.isActive() )
//    {
//        distanceTimer.stop();
//    }
}

void Cluster::init()
{
    setSpeed(QVariant(0));
    setRpm(QVariant(0));
    setFuel(QVariant(0));
    setTotalDistance(QVariant("23,567 km"));
}

QVariant Cluster::speed() const
{
    return m_speed;
}
void Cluster::setSpeed(QVariant value)
{
    m_speed = value;
    qDebug() << "Setting Speed:"<<value ;
    emit speedChanged();
}

QVariant Cluster::rpm() const
{
    return m_rpm;
}
void Cluster::setRpm(QVariant value)
{
    m_rpm = value;
qDebug() << "Setting RPM:"<<value ;
    emit rpmChanged();
}

QVariant Cluster::fuel() const
{
    return m_fuel;
}
void Cluster::setFuel(const QVariant &fuel)
{
    m_fuel = fuel;
      qDebug() << "Setting fuel:"<<fuel ;
    emit fuelChanged();
}
QVariant Cluster::temp() const
{
    return m_temp;
}
void Cluster::setTemp(const QVariant &temp)
{
    m_temp = temp;
      qDebug() << "Setting Temp:"<<temp ;
    emit tempChanged();
}
QVariant Cluster::totalDistance() const
{
    return m_totalDistance;
}

void Cluster::setTotalDistance(const QVariant &totalDistance)
{
    m_totalDistance = totalDistance;
    emit totalDistanceChanged();
}

void Cluster::calcTotalDistance()
{
    int speed = m_speed.toInt();
    int move = (speed * 1000) / (60 * 60);

    mTotalDistance += move;

    QString distance = QLocale(QLocale::English).toString(mTotalDistance / 1000) + " km";

    setTotalDistance(distance);
}
QVariant Cluster::r_value() const
{
    return m_r_value;
}
void Cluster::set_r_value (const QVariant &value)
{
       m_r_value = value;
      qDebug() << "Setting r_value:"<<value ;
    emit r_valueChanged();
}
QVariant Cluster::l_value() const
{
    return m_l_value;
}
void Cluster::set_l_value (const QVariant &value)
{
       m_l_value = value;
      qDebug() << "Setting l_value:"<<value ;
    emit l_valueChanged();
}

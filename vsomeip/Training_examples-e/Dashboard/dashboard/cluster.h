

#ifndef CLUSTER_H
#define CLUSTER_H

#include <QObject>
#include <QVariant>
#include <QTimer>

class Cluster : public QObject
{
    Q_OBJECT
  /*  Q_PROPERTY(type name
               (READ getFunction [WRITE setFunction] |
                MEMBER memberName [(READ getFunction | WRITE setFunction)])
               [RESET resetFunction]
               [NOTIFY notifySignal]
               [REVISION int]
               [DESIGNABLE bool]
               [SCRIPTABLE bool]
               [STORED bool]
               [USER bool]
               [CONSTANT]
               [FINAL])*/
    Q_PROPERTY(QVariant speed READ speed NOTIFY speedChanged)

    Q_PROPERTY(QVariant rpm   READ rpm   NOTIFY rpmChanged)
    Q_PROPERTY(QVariant fuel  READ fuel  NOTIFY fuelChanged)
    Q_PROPERTY(QVariant totalDistance READ totalDistance NOTIFY totalDistanceChanged)
    Q_PROPERTY(QVariant temp READ temp NOTIFY tempChanged)
    Q_PROPERTY(QVariant r_value READ r_value NOTIFY r_valueChanged)
    Q_PROPERTY(QVariant l_value READ l_value NOTIFY l_valueChanged)

public:
    static Cluster * instance();
    static void finalize();

    ~Cluster();

    void init();

private:
    explicit Cluster(QObject *parent = 0);

public:
    // Q_PROPERTY

    QVariant m_rpm;
    QVariant m_speed;
    QVariant m_fuel;
    QVariant m_totalDistance;
    QVariant m_temp;
    QVariant m_r_value;
    QVariant m_l_value;

public:
    // Q_PROPERTY getter setter
    QVariant speed() const;
    void setSpeed(QVariant value);

    QVariant rpm() const;
    void setRpm(QVariant value);

    QVariant fuel() const;
    void setFuel(const QVariant &fuel);

    QVariant totalDistance() const;
    void setTotalDistance(const QVariant & totalDistance);
    QVariant temp()const;
    void setTemp(const QVariant & temp);

    QVariant r_value()const;
    void set_r_value(const QVariant &value);
    QVariant l_value()const;
    void set_l_value(const QVariant &value);


public slots:
    void calcTotalDistance();

signals:
    // Q_PROPERTY signal
    void speedChanged();
    void rpmChanged();
    void fuelChanged();
    void totalDistanceChanged();
    void tempChanged();
    void r_valueChanged();
     void l_valueChanged();

private:
    quint32 mTotalDistance;
    QTimer distanceTimer;
};

#endif // CLUSTER_H

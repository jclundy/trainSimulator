#include "test1.h"

#include <QDebug>

Test1::Test1()
{
    m_train = new Train();

    qDebug() << "Created train";
    qDebug() << "length: " << m_train->m_length;
    qDebug() << "speed: " << m_train->m_speed;
    qDebug() << "speed setpoint: " << m_train->m_speedSetpoint;
    qDebug() << "acceleration: " << m_train->m_acceleration;

    qDebug() << "control model is null: " << (m_train->m_controlModel == NULL);
}

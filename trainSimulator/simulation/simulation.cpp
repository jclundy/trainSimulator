#include "simulation.h"
#include "exampletracksystem.h"
#include <QDebug>

Simulation::Simulation(QObject *parent) : QObject(parent),
    m_timer(this)
{
    m_timeout = 5000; //set timeout to 5 seconds
    m_timeSinceLastMovement = 0;
    m_dt = 0.25;
    m_interval = 250;

    connectSlots();
}

void Simulation::connectSlots() {
    connect(&m_timer, &QTimer::timeout, this, &Simulation::slot_timerEvent);
}

TrackSystem* Simulation::getTrackSystem() {
    return m_trackSystem;
}

void Simulation::loadTrackSystem() {
    m_trackSystem = ExampleTrackSystem::generateExample1();
    m_controller = new SystemController(m_trackSystem);
}

void Simulation::loadTrainDestinations() {
    m_controller->setAllTrainDestinations(ExampleTrackSystem::generateExample1Destinations());
}

void Simulation::setTimeout(unsigned long timeout) {
    m_timeout = timeout;
}



void Simulation::startSimulation() {
    if(m_trackSystem == NULL || m_controller == NULL) {
        return;
    }
    m_timeSinceLastMovement = 0;
    m_timer.setInterval(m_interval);
    m_timer.start();
}

void Simulation::stopSimulation() {
    m_timeSinceLastMovement = 0;
    m_timer.stop();
    // train controller - should stop all trains
}

void Simulation::slot_timerEvent() {
    m_controller->controlTrains();
    m_trackSystem->driveTrains(m_dt);

    if(m_trackSystem->areAllTrainsStopped())

    qDebug() << "timer event";
    // m_trackSystem->driveSignals();
}

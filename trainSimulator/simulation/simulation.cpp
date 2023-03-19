#include "simulation.h"
#include "exampletracksystem.h"
#include <QDebug>
#include <QDateTime>
Simulation::Simulation(QObject *parent) : QObject(parent),
    m_timer(this)
{
    m_timeout = 5000; //set timeout to 5 seconds
    m_timeSinceLastMovement = 0;
    m_dt = 0.25;
    m_interval = 10; // timer interval 10 ms
    m_elapsedSeconds = 0;
    m_iterations = 0;

    connectSlots();

    QDateTime time = QDateTime::currentDateTime();
    QString fileName = QString("simulation_output_") + time.toString(Qt::ISODate) + QString(".txt");
    m_logger = new SimulationLogger(fileName);

}

void Simulation::connectSlots() {
    connect(&m_timer, &QTimer::timeout, this, &Simulation::slot_timerEvent);
}

TrackSystem* Simulation::getTrackSystem() {
    return m_trackSystem;
}

SystemController* Simulation::getController() {
    return m_controller;
}

float Simulation::getElapsedSeconds() {
    return m_elapsedSeconds;
}

int Simulation::getIterations() {
    return m_iterations;
}

void Simulation::loadTrackSystem() {
    m_trackSystem = ExampleTrackSystem::generateExample1();
    m_controller = new SystemController(m_trackSystem);
    m_logger->setTrackSystem(m_trackSystem);
}

void Simulation::loadTrainDestinations() {
    m_controller->setAllTrainDestinations(ExampleTrackSystem::generateExample1Destinations());
    m_logger->setTrainPaths(m_controller->getTrainPaths());
}

void Simulation::setTimeout(unsigned long timeout) {
    m_timeout = timeout;
}

void Simulation::startSimulation() {
    if(m_trackSystem == NULL || m_controller == NULL) {
        return;
    }


    m_logger->openFile();
    m_logger->logTrackSystemInfo();
    m_logger->logTrainPaths();

    m_trackSystem->unHaltAllTrains();

    m_timeSinceLastMovement = 0;
    m_elapsedSeconds = 0;
    m_iterations = 0;
    m_timer.setInterval(m_interval);
    m_timer.start();
}

void Simulation::stopSimulation() {
    m_timeSinceLastMovement = 0;
    m_timer.stop();
    m_controller->stopAllTrains();
    m_logger->closeFile();

    qDebug() << "stopped simulation";
}

void Simulation::slot_timerEvent() {
    m_controller->controlTrains();
    m_trackSystem->driveTrains(m_dt);

    m_elapsedSeconds += m_dt;
    m_iterations++;

    if(m_trackSystem->areAllTrainsStopped()) {
        m_timeSinceLastMovement+= m_timer.interval();
    } else {
        m_timeSinceLastMovement = 0;
    }

    if(m_timeSinceLastMovement > m_timeout || m_trackSystem->areAllTrainsHalted()) {
        stopSimulation();
    }

    qDebug() << "timer event";
    // m_trackSystem->driveSignals();

    m_logger->logTimeStep(m_iterations, m_elapsedSeconds);

}

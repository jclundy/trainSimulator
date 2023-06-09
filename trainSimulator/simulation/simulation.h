#ifndef SIMULATION_H
#define SIMULATION_H

#include <QObject>
#include <QTimer>

#include "track_system/tracksystem.h"
#include "track_system/systemcontroller.h"
#include "simulationlogger.h"

class Simulation : public QObject
{
    Q_OBJECT
public:
    explicit Simulation(QObject *parent = nullptr);
    void connectSlots();

    // getters
    TrackSystem* getTrackSystem();
    SystemController* getController();

    float getElapsedSeconds();
    int getIterations();
    // initialization
    void loadTrackSystem();
    void loadTrainDestinations();
    void setTimeout(unsigned long timeout); // in ms

    // running simulation
    void startSimulation();
    void stopSimulation();

signals:

public slots:
    void slot_timerEvent();

private:
    int m_timeout; //ms
    float m_dt;
    int m_interval;

    float m_elapsedSeconds;
    int m_iterations;

    TrackSystem* m_trackSystem;
    SystemController* m_controller;
    QTimer m_timer;
    SimulationLogger* m_logger;
};

#endif // SIMULATION_H

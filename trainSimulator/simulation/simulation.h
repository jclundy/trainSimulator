#ifndef SIMULATION_H
#define SIMULATION_H

#include <QObject>
#include <QTimer>

#include "track_system/tracksystem.h"
#include "track_system/systemcontroller.h"

class Simulation : public QObject
{
    Q_OBJECT
public:
    explicit Simulation(QObject *parent = nullptr);

    // getters
    TrackSystem* getTrackSystem();
    // initialization
    void loadTrackSystem();
    void loadTrainDestinations();

    void setTimeout(float timeout); // in seconds

    // running simulation
    void startSimulation();
    void stopSimulation();

signals:

public slots:

private:
    TrackSystem* m_trackSystem;
    SystemController* m_controller;
    QTimer m_timer;
};

#endif // SIMULATION_H

#include "exampletracksystem.h"

TrackSystem * ExampleTrackSystem::generateExample1() {
    TrackSystem* trackSystem = new TrackSystem();


    LinearTrack* track0 = trackSystem->addLinearTrack();
    track0->getTrackGeometry()->translateRearPosition(QPointF(0,0));

    JunctionTrack* track1 = trackSystem->addJunctionTrack();
    track1->connectRearToTrack(track0);

    LinearTrack* track2 = trackSystem->addLinearTrack();
    track2->connectRearToTrack(track1);

    LinearTrack* track3 = trackSystem->addLinearTrack();
    track3->connectRearToTrack(track2);

    // other forks
    LinearTrack* track4 = trackSystem->addLinearTrack();
    track4->connectFrontToTrack(track1);
    track4->getTrackGeometry()->setRotationAboutFront(120);


    LinearTrack* track5 = trackSystem->addLinearTrack();
    track5->connectRearToTrack(track1);
    track5->getTrackGeometry()->setRotationAboutRear(-120);

    Train* train0 = trackSystem->addTrain();
    train0->place(track0);
    Train* train1 = trackSystem->addTrain();
    train1->place(track4);

    Signal* signal_0_rear = trackSystem->addSignal();
    signal_0_rear->placeOnTrackRear(track0);

    Signal* signal_0_front = trackSystem->addSignal();
    signal_0_front->placeOnTrackFront(track0);

    Signal* signal_1_rear = trackSystem->addSignal();
    signal_1_rear->placeOnTrackRear(track1);

    Signal* signal_1_front = trackSystem->addSignal();
    signal_1_front->placeOnTrackFront(track1);

    Signal* signal_2_rear = trackSystem->addSignal();
    signal_2_rear->placeOnTrackRear(track2);

    Signal* signal_2_front = trackSystem->addSignal();
    signal_2_front->placeOnTrackFront(track2);

    Signal* signal_3_rear = trackSystem->addSignal();
    signal_3_rear->placeOnTrackRear(track3);

    Signal* signal_3_front = trackSystem->addSignal();
    signal_3_front->placeOnTrackFront(track3);

    Signal* signal_4_front = trackSystem->addSignal();
    signal_4_front->placeOnTrackFront(track4);

    Signal* signal_4_rear = trackSystem->addSignal();
    signal_4_rear->placeOnTrackRear(track4);

    Signal* signal_5_rear = trackSystem->addSignal();
    signal_5_rear->placeOnTrackRear(track5);

    Signal* signal_5_front = trackSystem->addSignal();
    signal_5_front->placeOnTrackFront(track5);

    track1->selectRearBranchById(0);
    track1->selectForwardBranchById(5);


    return trackSystem;
}

QMap<unsigned int, unsigned int> ExampleTrackSystem::generateExample1Destinations() {
    QMap<unsigned int, unsigned int> map;
    // key - train, value - destination track id
    map.insert(0, 5);
    map.insert(1, 3);
    return map;
}

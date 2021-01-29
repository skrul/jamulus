#pragma once

#include <QObject>
#include <QElapsedTimer>

#include <prometheus/counter.h>
#include <prometheus/gauge.h>
#include <prometheus/exposer.h>
#include <prometheus/registry.h>

class CMetrics : public QObject
{
    Q_OBJECT

public:
    CMetrics(prometheus::Registry& registry);

    void UpdateConnectionCount(int connectionCount);
    void IncrementMainLoopCount();
    void MainLoopStart();
    void MainLoopEnd();

//public slots:
//    void OnPingTimeResult ( int iPingTime );

protected:
    prometheus::Family<prometheus::Gauge>& connectionCountFamily;
    prometheus::Gauge& connectionCount;

    prometheus::Family<prometheus::Counter>& serverMainLoopCountFamily;
    prometheus::Counter& serverMainLoopCount;

    prometheus::Family<prometheus::Gauge>& mainLoopTimeFamily;
    prometheus::Gauge& mainLoopTime;

    QElapsedTimer elapsedTimer;
};

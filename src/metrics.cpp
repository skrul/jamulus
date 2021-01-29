#include "metrics.h"

CMetrics::CMetrics ( prometheus::Registry& registry) :
    connectionCountFamily(prometheus::BuildGauge().Name("connection_count").Register(registry)),
    connectionCount(connectionCountFamily.Add({})),
    serverMainLoopCountFamily(prometheus::BuildCounter().Name("main_loop_count").Register(registry)),
    serverMainLoopCount(serverMainLoopCountFamily.Add({})),
    mainLoopTimeFamily(prometheus::BuildGauge().Name("main_loop_time").Register(registry)),
    mainLoopTime(mainLoopTimeFamily.Add({}))
{
//    QObject::connect ( pClient, &CClient::PingTimeReceived,
//        this, &CMetrics::OnPingTimeResult );
}

void CMetrics::UpdateConnectionCount(int iConnectionCount) {
    connectionCount.Set(iConnectionCount);
}

void CMetrics::IncrementMainLoopCount() {
    serverMainLoopCount.Increment();
}

void CMetrics::MainLoopStart() {
    elapsedTimer.start();
}

void CMetrics::MainLoopEnd() {
    double t = elapsedTimer.nsecsElapsed() / 1000000000.0;
    mainLoopTime.Set(t);
}

//void CMetrics::OnPingTimeResult ( int iPingTime )
//{
//    pingTime.Set(iPingTime);
//    overallDelay.Set(pClient->EstimatedOverallDelay(iPingTime));
//}

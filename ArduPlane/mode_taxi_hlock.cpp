#include "mode.h"
#include "Plane.h"

/*
bool ModeTaxiHLock::_enter()
{
    return true;
}
*/

void ModeTaxiHLock::update()
{
    ModeFBWA::update();
    // Elevator down
    SRV_Channels::set_output_limit(SRV_Channel::k_elevator, SRV_Channel::SRV_CHANNEL_LIMIT_MAX);
}

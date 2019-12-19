#include "mode.h"
#include "Plane.h"

bool ModeDeadstop::_enter()
{
    plane.arming.disarm();
    // Disables stick input
    plane.auto_navigation_mode = true;
    plane.auto_throttle_mode = true;
    plane.throttle_allows_nudging = false;
    plane.gcs().send_text(MAV_SEVERITY_WARNING, "Dropped to deadstop mode");
    return true;
}

void ModeDeadstop::update()
{
    // Elevator down
    SRV_Channels::set_output_limit(SRV_Channel::k_elevator, SRV_Channel::SRV_CHANNEL_LIMIT_MIN);

    // Throttle down
    if (plane.have_reverse_thrust()) {
        // configured for reverse thrust, use TRIM
        SRV_Channels::set_output_limit(SRV_Channel::k_throttle, SRV_Channel::SRV_CHANNEL_LIMIT_TRIM);
        SRV_Channels::set_output_limit(SRV_Channel::k_throttleLeft, SRV_Channel::SRV_CHANNEL_LIMIT_TRIM);
        SRV_Channels::set_output_limit(SRV_Channel::k_throttleRight, SRV_Channel::SRV_CHANNEL_LIMIT_TRIM);
    } else {
        // use MIN
        SRV_Channels::set_output_limit(SRV_Channel::k_throttle, SRV_Channel::SRV_CHANNEL_LIMIT_MIN);
        SRV_Channels::set_output_limit(SRV_Channel::k_throttleLeft, SRV_Channel::SRV_CHANNEL_LIMIT_MIN);
        SRV_Channels::set_output_limit(SRV_Channel::k_throttleRight, SRV_Channel::SRV_CHANNEL_LIMIT_MIN);
    }

    // Brakes on full
    SRV_Channels::set_output_limit(SRV_Channel::k_rcin6, SRV_Channel::Limit::MAX);

    plane.servos_output();

    plane.arming.disarm();
}

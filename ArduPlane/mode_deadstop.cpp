#include "mode.h"
#include "Plane.h"

bool ModeDeadstop::_enter()
{
    plane.arming.disarm();
    return true;
}

void ModeDeadstop::update()
{
    plane.g2.servo_channels.disable_passthrough(true);

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

    SRV_Channels::set_output_limit(SRV_Channel::k_manual, SRV_Channel::SRV_CHANNEL_LIMIT_TRIM);
    SRV_Channels::set_output_limit(SRV_Channel::k_none, SRV_Channel::SRV_CHANNEL_LIMIT_TRIM);

    plane.arming.disarm();
    // B-600 braking signal; 0 indexed (so 10 = channel 11)
    SRV_Channels::set_output_pwm_chan(10, 2000);
    plane.servos_output();
}


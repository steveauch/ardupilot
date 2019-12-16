#include "mode.h"
#include "Plane.h"

bool ModeTaxiWP::_enter(){
    plane.throttle_allows_nudging = false;
    plane.auto_throttle_mode = false;
    plane.auto_navigation_mode = false;
    plane.auto_state.vtol_mode = false;
    plane.mission.start_or_resume();
    return true;
}

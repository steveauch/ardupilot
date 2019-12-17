#include "mode.h"
#include "Plane.h"

bool ModeTaxiWP::_enter(){
    plane.throttle_allows_nudging = false;
    plane.auto_throttle_mode = false;
    plane.auto_navigation_mode = false;
    plane.auto_state.vtol_mode = false;

    plane.next_WP_loc = plane.prev_WP_loc = plane.current_loc;
    plane.mission.start_or_resume();
    return true;
}

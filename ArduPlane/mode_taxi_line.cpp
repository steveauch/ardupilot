#include "mode.h"
#include "Plane.h"

bool ModeTaxiLine::_enter(){
    plane.throttle_allows_nudging = false;
    plane.auto_throttle_mode = false;
    plane.auto_navigation_mode = false;
    plane.auto_state.vtol_mode = false;
    //plane.auto_state.crosstrack = true;

    //plane.next_WP_loc = plane.prev_WP_loc = plane.current_loc;
    plane.mission.start_or_resume();
    //plane.auto_state.next_wp_crosstrack = true;
    return true;
}

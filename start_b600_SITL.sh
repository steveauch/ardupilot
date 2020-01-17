#!/bin/bash

MISSION_PLANNER_IP=192.168.0.75:14550 
cd "${BASH_SOURCE%/*}/" || exit
pwd
./Tools/autotest/sim_vehicle.py -v ArduPlane --aircraft ./ArduPlane/B-600 -f \
jsbsim:B-600 -L AUGC $@ -m --out=udp:$MISSION_PLANNER_IP 

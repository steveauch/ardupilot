#!/bin/bash
cd "${BASH_SOURCE%/*}/" || exit
pwd
./Tools/autotest/sim_vehicle.py -v ArduPlane --aircraft ./ArduPlane/B-600 -f jsbsim:B-600 -L AUGC $@

#!/usr/bin/python3

""" Briefly set a force on the B-600 model using the JSBSim telnet interface """

from telnetlib import Telnet
import atexit
import time
import tty
import termios
import sys
import select

HOST = "localhost"
PORT = 1137

SET_STR = b"set external_reactions/kick/magnitude "

TERM_SETTINGS = termios.tcgetattr(sys.stdin)


def main():
    """Main"""

    argc = len(sys.argv)
    if argc > 1:
        impulse = sys.argv[1]
    else:
        impulse = 100
    if argc > 2:
        duration = sys.argv[2]
    else:
        duration = 1
    force = impulse / duration

    tty.setcbreak(sys.stdin.fileno())
    atexit.register(reset_terminal_settings)

    try:
        with Telnet(HOST, PORT) as telnet:
            print("Connected to simulation. Press any key to kick UAV")
            while True:
                if key_pressed():
                    print(SET_STR.decode() + str(force))
                    telnet.write(SET_STR + str(force).encode() + "\n".encode())
                    time.sleep(duration)
                    telnet.write(SET_STR + b"0" + "\n".encode())
                    print(SET_STR.decode() + "0")
                    print(telnet.read_some().decode())
                print(telnet.read_very_eager().decode().strip(), end="")
    except ConnectionRefusedError:
        print(
            "Could not connect to simulation. Ensure JSBSim is running and try again."
        )
        sys.exit(1)


def has_input():
    "Returns true if input is waiting in stdin"
    return select.select([sys.stdin], [], [], 0) == ([sys.stdin], [], [])


def reset_terminal_settings():
    """Reset terminal settings"""
    termios.tcsetattr(sys.stdin, termios.TCSADRAIN, TERM_SETTINGS)


def key_pressed():
    "Nonblocking input; returns true if a key has been entered since last call"
    result = False
    while has_input():
        result = True
        sys.stdin.read(1)
    return result


if __name__ == "__main__":
    main()

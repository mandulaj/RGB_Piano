import subprocess
import re, serial

MIDI_CHAN = '20'
SERIAL = '/dev/ttyUSB0'

proc = subprocess.Popen(['aseqdump','-p', MIDI_CHAN],stdout=subprocess.PIPE)

ser = serial.Serial(SERIAL, 2000000)

for line in iter(proc.stdout.readline,''):
    cmd = re.split('\W+',line.decode('utf-8'))
    if cmd[3] == "Note":
        note = int(cmd[7]) - 21
        if cmd[4] == "on":
            velocity = int(cmd[9])
            print("Note {} is on. Velocity: {}".format(note, velocity))
            note ^= 0x80
        else:
            print("Note {} is off".format(note))
        ser.write(bytes([note]))
        ser.flush()

    elif cmd[3] == "Control":
        if cmd[9] == '127':
            print("Pedal Down")
            ser.write(bytes([0xFF]))
        else:
            print("Pedal Up")
            ser.write(bytes([0xFE]))

import sys, time
import numpy
import depth_eye
import cv2

filename = sys.argv[1]
frame_count = int(sys.argv[2])
frame_rate = 150
frames = []
captured = 0


def frame_cb(phase, amplitude):
    global frames, captured
    frames.append((phase, amplitude))
    captured += 1

devices = depth_eye.scan()
print("Found %d devices" % len(devices))

if (len(devices) == 0):
    print("No device found, exiting")
    sys.exit(1)

selected = devices[0]

# Start capture
c = depth_eye.capture(selected, frame_cb, frame_rate)

while(captured < frame_count):
    pass

numpy.save(filename, frames)
print("Done!")

c.stop()


# Write all data to a file


sys.exit(0)

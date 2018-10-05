import sys, time
import numpy
import depth_eye
import cv2

ff = None

def frame_cb(phase, amplitude):
    global ff
    ff = (phase, amplitude)

devices = depth_eye.scan()
print("Found %d devices" % len(devices))

if (len(devices) == 0):
    print("No device found, exiting")
    sys.exit(1)

selected = devices[0]

c = depth_eye.capture(selected, frame_cb)

while True:

    if ff is not None:
        phase, ampl = ff #numpy.random.random((80, 60))
        phase_img = cv2.merge([phase/1000.0, phase/1000.0, phase/1000.0])
        cv2.imshow("phase", phase_img)

        ampl_img = cv2.merge([ampl/1000.0, ampl/1000.0, ampl/1000.0])
        cv2.imshow("amplitude", ampl_img)

        ff = None
        cv2.waitKey(1)

time.sleep(10)

import sys, time
import numpy
import depth_eye
import cv2
import signal

ff = None
running = True

class CameraStop:
    def __init__(self, cam_object):
        self.cam_object = cam_object

    def __call__(self, sig, frame):
        #self.cam_object.stop()
        global running
        running = False


def frame_cb(phase, amplitude):
    global ff
    ff = (phase, amplitude)

devices = depth_eye.scan()
print("Found %d devices" % len(devices))

if (len(devices) == 0):
    print("No device found, exiting")
    sys.exit(1)

selected = devices[0]

# Start capture
c = depth_eye.capture(selected, frame_cb, 100)

# Register break handler
signal.signal(signal.SIGINT, CameraStop(c))

ampl_gain = 200.0
phase_gain = 1000.0

while running:

    if ff is not None:
        phase, ampl = ff #numpy.random.random((80, 60))
        phase_img = cv2.merge([phase/phase_gain, phase/phase_gain, phase/phase_gain])
        cv2.imshow("phase", phase_img)


        ampl_img = cv2.merge([ampl/ampl_gain, ampl/ampl_gain, ampl/ampl_gain])
        cv2.imshow("amplitude", ampl_img)

        ff = None
        cv2.waitKey(1)

c.stop()
sys.exit(0)
import sys, time
import numpy
import matplotlib.pyplot as plt
import depth_eye
import cv2

ff = None

def frame_cb(phase):
    print("F")
    global ff
    ff = phase
    #plt.imshow(numpy.random.random((80, 60)))
    #plt.show(0)
    #print phase
    pass
    #cv2.imshow(numpy.random.random((60, 80)))

devices = depth_eye.scan()
print("Found %d devices" % len(devices))

if (len(devices) == 0):
    print("No device found, exiting")
    sys.exit(1)

selected = devices[0]

c = depth_eye.capture(selected, frame_cb)

while True:

    if ff is not None:
        data = ff #numpy.random.random((80, 60))
        print data
        img = cv2.merge([data/4000.0, data/4000.0, data/4000.0])
        cv2.imshow("phase", img)
        ff = None
        cv2.waitKey(1)
        #plt.imshow(nump))y.random.random((80, 60)))
        #im.set_array(numpy.random.random((80, 60)))
        
        #ff = None
        #plt.show(1)

time.sleep(10)

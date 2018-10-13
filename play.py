import sys
import cv2
import numpy


filename = sys.argv[1]
frames = numpy.load(filename)
count = len(frames)

print("Found %d frames" % count)

ampl_gain = 40.0
phase_gain = 1000.0

font = cv2.FONT_HERSHEY_SIMPLEX


for fn in range(0, count):
    phase, ampl = frames[fn]
    phase_img = cv2.merge([phase/phase_gain, phase/phase_gain, phase/phase_gain])
    cv2.putText(phase_img, str(fn) ,(5,20), font, 1,(0,0,0), 1, cv2.LINE_AA)
    cv2.imshow("phase", phase_img)

    ampl_img = cv2.merge([ampl/ampl_gain, ampl/ampl_gain, ampl/ampl_gain])
    cv2.imshow("amplitude", ampl_img)

    cv2.waitKey(50)

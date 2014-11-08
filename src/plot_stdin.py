#!/usr/bin/env python

import matplotlib.pyplot as plt
import sys

def main():
    frameskip = 5
    plt.ion()

    framecount = 0
    N = 0
    data = []
    fig = plt.figure()
    sp = fig.add_subplot(111)
    sp.set_ylim(-1, 1)
    sp.set_ylim(-1, 1)
    line1 = None
    line2 = None
    
    while True:
        data = sys.stdin.readline()
        if data == '':
            break
        framecount += 1
        if framecount % frameskip != 0:
            continue
        data = data.split(" ")
        data = map(float, data)
        sp.set_title(str(framecount))
        if line1 is None:
            # If plotting absolute value:
            #line, = sp.plot(range(len(data)), data)

            # If plotting real and imaginary separately:
            line1, = sp.plot(range(len(data) / 2), data[:len(data) / 2])
            line2, = sp.plot(range(len(data) / 2), data[len(data) / 2:])
        else:
            # If plotting absolute value:
            #line.set_xdata(range(len(data)))
            #line.set_ydata(data)

            # If plotting real and imaginary separately:
            line1.set_xdata(range(len(data) / 2))
            line1.set_ydata(data[:len(data) / 2])
            line2.set_xdata(range(len(data) / 2))
            line2.set_ydata(data[len(data) / 2:])

        #plt.savefig("./frames1/"+str(framecount)+".png")
        plt.draw()

if __name__ == "__main__":
    sys.exit(main())

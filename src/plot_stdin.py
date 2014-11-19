#!/usr/bin/env python

import matplotlib.pyplot as plt
import sys

def main():
    if len(sys.argv) > 1:
        frameskip = int(sys.argv[1])
    else:
        frameskip = 1

    plt.ion()

    fig = plt.figure()
    #sp = fig.add_subplot(111)
    #sp.set_ylim(0, 1)
    #sp.set_ylim(0, 1)
    sp1 = fig.add_subplot(211)
    sp1.set_ylim(-1, 1)
    sp1.set_ylim(-1, 1)
    sp2 = fig.add_subplot(212)
    sp2.set_ylim(-1, 1)
    sp2.set_ylim(-1, 1)
    #line = None
    line1 = None
    line2 = None
    
    framecount = 0
    data = []
    while True:
        data = sys.stdin.readline()
        if data == '':
            break
        framecount += 1
        if framecount % frameskip != 0:
            continue
        data = data.split(" ")
        data = map(float, data)
        sp1.set_title("%05d" % framecount)
        #if line is None:
        if line1 is None:
            # If plotting absolute value:
            #line, = sp.plot(range(len(data)), data)

            # If plotting real and imaginary separately:
            line1, = sp1.plot(range(len(data) / 2), data[:len(data) / 2], 'b-')
            line2, = sp2.plot(range(len(data) / 2), data[len(data) / 2:], 'r-')
        else:
            # If plotting absolute value:
            #line.set_xdata(range(len(data)))
            #line.set_ydata(data)

            # If plotting real and imaginary separately:
            line1.set_xdata(range(len(data) / 2))
            line1.set_ydata(data[:len(data) / 2])
            line2.set_xdata(range(len(data) / 2))
            line2.set_ydata(data[len(data) / 2:])

        #plt.savefig("/home/paultan/sims/piab/1/%04d.png" % framecount)
        #print framecount
        plt.draw()

if __name__ == "__main__":
    sys.exit(main())

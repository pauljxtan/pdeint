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
    sp.set_ylim(0, 1)
    #sp.set_ylim(-1, 1)
    line = None
    
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
        if line is None:
            line, = sp.plot(range(len(data)), data)
        else:
            line.set_xdata(range(len(data)))
            line.set_ydata(data)
        #plt.savefig("./frames1/"+str(framecount)+".png")
        plt.draw()

if __name__ == "__main__":
    sys.exit(main())

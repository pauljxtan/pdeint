# pdeint #

Integrating partial differential equations in C. While PDE integration code is harder to generalize than for ordinary differential equatoins (see __odeint__ repo) the routines are still fairly versatile. Also, some (if not all) of the most interesting physical phenomena (e.g. fluid dynamics, quantum) cannot be described by ODEs alone, so the motivation is clear.

Often it is useful to cast the problem into an alternate form, which makes the whole process even more tricky to generalize.

## Particle in a box ##

Background: http://en.wikipedia.org/wiki/Particle_in_a_box

The program __particle_box__ integrates a quantum-mechanical "particle in a box" using a Crank-Nicolson finite difference scheme.

### Quick start ###

We can plot this in real-time by piping the stdout to a Python script (requires matplotlib). Using the following parameters:
* Box width       : 1.0e-9
* Grid steps      : 1001
* Time step       : 1.0e-18
* Number of steps : 10000
* sigma           : 1.0e-10
* kappa           : 5.0e10
and a frameskip of 3 (adjust this for your own machine) for the animation, we can use
```bash
$ ./particle_box 1.0e-9 1001 1.0e-18 10000 1.0e-10 5.0e10 | ./plot_stdin.py 3
```

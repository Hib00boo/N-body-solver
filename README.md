# N body problem solver
This code allows the user to plot and solve N body problems. The system is defined in [AstroSim.cpp](AstroSim/AstroSim.cpp) and an example problem (will eventually be) in [Main.cpp](AstroSim/Main.cpp).
## N body problem
An N body problem is defined as the problem of predicting movement in a group of N amount of celestial bodies in a system. All solving methods are based off "The Fundamentals Of Astrodynamics" by R. R. Bate, D. D. Muller and J. E. White (which can either be [bought here](https://www.indigo.ca/en-ca/fundamentals-of-astrodynamics-second-edition/9780486497044.html) or is available in pdf format online)
As of writing this readme (19/01/2024), the following methods have been implemented using the material from chapter 1.3 :
* Compute the gravitational force between 2 objects in space in vector form.
* Compute the gravitational force between 2 objects in space as a number.
* Plot objects in a system.
* Show the gravitational force vector (fg) on the plotted graph.

The following text will be a brief explanation of the classes or interfaces found in the code.
### System
This class represents the system in which we find the celestial bodies.
### Object
This interface represents the bodies we might find in an N body problem. So far, only Planet and Satellite type objects have been implemented.
### Planet
This implements object to represent a planet in a system.
### Satellite
This implements object to represent a satellite in a system. Expected to be much smaller and less heavy than Planet type objects.

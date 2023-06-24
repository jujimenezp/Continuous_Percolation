#!/usr/bin/python3
#
from struct import unpack
import numpy as np
import matplotlib.pyplot as plt

circles = np.loadtxt('results/mci_circles.dat', unpack=True)
points = np.loadtxt('results/mci_points.dat', unpack=True)

fig, ax = plt.subplots()

ax.set_xlabel('x')
ax.set_ylabel('y')
ax.set_xlim((0,50))
ax.set_ylim((0,50))

t = np.linspace(0, 2*np.pi, 50)
# Plot circles
for idx in range(len(circles[0])):
    x = circles[0,idx]
    y = circles[1,idx]
    
    u = x + 4*np.cos(t)
    v = y + 4*np.sin(t)

    ax.plot(u, v, 'k-')

# Plot points
ax.scatter(points[0], points[1], s=3, c='red')
plt.gca().set_aspect('equal')
plt.savefig('results/integral.pdf',format='pdf',bbox_inches='tight')

plt.show()

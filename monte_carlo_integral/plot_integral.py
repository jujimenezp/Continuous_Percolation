from struct import unpack
import numpy as np
import matplotlib.pyplot as plt

circles = np.loadtxt('circles_coords.dat', unpack=True)
points = np.loadtxt('monte-carlo_points.dat', unpack=True)

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
ax.scatter(points[0], points[1], s=5, c='red')

plt.savefig('integral.jpg')

plt.show()
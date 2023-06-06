#!/usr/bin/python3

import pandas as pd
from matplotlib import pyplot as plt
from matplotlib.ticker import MultipleLocator

data = pd.read_csv("results.dat",delimiter="\t")

data['center']=list(zip(data['x'],data['y']))

circle=[]
fig, ax = plt.subplots()
ax.xaxis.set_major_locator(MultipleLocator(5))
ax.yaxis.set_major_locator(MultipleLocator(5))
ax.grid(which='major', linestyle='-')
ax.set_xlim((0,50))
ax.set_ylim((0,50))
for i in range(len(data['center'])):
    circle.append(plt.Circle(data.at[i, 'center'],3,color='blue',fill=False))
    ax.add_patch(circle[i])
    plt.text(data.at[i,'x'], data.at[i,'y'], str(data.at[i,'cluster']), ha='center', va='center')
ax.set_aspect('equal')
plt.savefig('data.pdf', format='pdf', bbox_inches='tight')

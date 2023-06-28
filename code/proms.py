#!/usr/bin/python3

import numpy as np
import pandas as pd
from scipy.stats import linregress
import matplotlib.pyplot as plt

Ls = [45, 60, 75, 90, 120, 135]
avgs = []
stds = []

for L in Ls:
    data = pd.read_csv(f'results/areas_{L}.dat',delimiter='\t')
    avgs.append(np.log(np.average(data,axis=0)[1]))
    stds.append(-np.log(np.std(data,axis=0,ddof=1)[1]))

res = linregress(np.log(Ls), stds)
x = np.linspace(3.8,4.9,500)
y = res.intercept + x*res.slope
print(f'slope = {res.slope} +/- {res.stderr}')
print(f'R2 = {res.rvalue}')

fig, ax = plt.subplots()
ax.set_xlabel(r'log(L)')
ax.set_ylabel(r'-log($\Delta L$)')
ax.scatter(np.log(Ls),stds)
ax.plot(x,y)
plt.show()

#!/usr/bin/python3

import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

data = pd.read_csv('results/areas_135.dat',delimiter='\t')
x = data.iloc[:,1]
bins = 30

fig,ax = plt.subplots()
ax.set_title(r'Área ocupada en $t_{percolante}$ para $L=50$')
ax.hist(x, bins)
plt.show()
#plt.savefig('results/hist_50.pdf',format='pdf',bbox_inches='tight')

import numpy as np
import matplotlib.pyplot as plt

data = np.genfromtxt('out', delimiter=",")

plt.imshow(data, interpolation='nearest', cmap='viridis')
plt.savefig('out.pdf')

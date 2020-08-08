import numpy as np
import matplotlib.pyplot as plt

data = np.genfromtxt('out2', delimiter=",")

plt.imshow(data, interpolation='nearest', cmap='viridis')
plt.savefig('out2.pdf')

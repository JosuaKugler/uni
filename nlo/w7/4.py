import numpy as np
from generic_trust_region import generic_trust_region
from example_functions import rosenbrock
import matplotlib.pyplot as plt
from visualization_functions import plot_2d_iterates_contours

a = 1
b = 100
rosenbrock_f = lambda x: rosenbrock(a, b, x)[0]
rosenbrock_prime = lambda x: rosenbrock(a, b, x)[1]
rosenbrock_two_prime = lambda x: rosenbrock(a, b, x)[2]

#x0_list = [[5, 5], [0, 0], [5, 0], [0, 5]]
x0_list = [[1, 2], [2, 1], [2.5, 2], [0, 4]]

histories = []

for x0 in x0_list:
    _, history = generic_trust_region(
        x0,
        rosenbrock_f,
        rosenbrock_prime,
        rosenbrock_two_prime,
        np.eye(2),
        Delta_0=1,
        eta_1=1e-2,
        eta_2=0.6,
        gamma_1=0.5,
        gamma_2=2,
    )
    histories.append(history)


plot_2d_iterates_contours(
    rosenbrock_f, histories, labels=[f"x0={x0}" for x0 in x0_list], xlims=[-1, 3], ylims=[0, 5]
)
plt.savefig("iterates_contours_rosenbrock")
plt.show()

for history in histories:
    deltas = history["Delta"]
    plt.plot(range(len(deltas)), deltas)
plt.savefig("trust_region_size_rosenbrock")
plt.show()



for history in histories:
    areds = history["ared"]
    plt.plot(range(len(areds)), areds)
    plt.yscale('log')
plt.savefig("reduction_rosenbrock")
plt.show()
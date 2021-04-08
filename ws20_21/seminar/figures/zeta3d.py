import mpmath
import numpy
import colorsys
import matplotlib.pyplot as plt
import tikzplotlib

# 2-d array of points
real_points = 200
imag_points = 200
points = []

pypoints = numpy.zeros((real_points, imag_points), dtype='complex')

# viewport on complex plane
rmin = -10
rmax = 10
imin = -10
imax = 10

with open("plotdata.dat") as f:
    # calculate zeta(s)
    for rp in range(real_points):
        f.write("\n")
        for ip in range(imag_points):
            try:
                real = rmin + ((rmax - rmin) * rp/real_points)
                imag = imin + ((imax - imin) * ip/imag_points)
                value = mpmath.zeta(complex(real,imag))
                pypoints[ip,rp] = value
                f.write(f"{real} {imag} {numpy.abs(value, dtype='float64')}\n")
            except ValueError:
                # ignore pole
                pass
            pass
        pass


fig2 = plt.figure(figsize = (15,15))
plt.contour(realpoints, 900, linewidths=0.5, origin='lower', extent=[rmin, rmax, imin, imax])
tikzplotlib.save("full_real_value_contour.tex")

plt.show()
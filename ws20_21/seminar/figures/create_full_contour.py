import mpmath
import numpy
import colorsys
import matplotlib.pyplot as plt
import tikzplotlib

# 2-d array of points
real_points = 200
imag_points = 200
points = numpy.zeros((real_points, imag_points), dtype='complex')


# viewport on complex plane
rmin = -10
rmax = 10
imin = -10
imax = 10

# calculate zeta(s)

for rp in range(real_points):
    for ip in range(imag_points):
        try:
            real = rmin + ((rmax - rmin) * rp/real_points)
            imag = imin + ((imax - imin) * ip/imag_points)
            points[ip,rp] = mpmath.zeta(complex(real,imag))
        except ValueError:
            # ignore pole
            pass
        pass
    pass

# vectorise abs and log
abspoints  = numpy.log(numpy.abs( points), dtype='float64')
realpoints = numpy.log(numpy.real(points), dtype='float64')
imagpoints = numpy.log(numpy.imag(points), dtype='float64')

#fig1 = plt.figure(figsize = (15,15))
#plt.contour(abspoints, 100, linewidths=0.5, origin='lower', extent=[rmin, rmax, imin, imax])

#plt.show()
#tikzplotlib.save("full_absolute_value_contour.tex")


fig2 = plt.figure(figsize = (15,15))
plt.contour(realpoints, 900, linewidths=0.5, origin='lower', extent=[rmin, rmax, imin, imax])
tikzplotlib.save("full_real_value_contour.tex")

plt.show()
#fig2.savefig("figures/real_value_contour_plot.pdf")


#fig3 = plt.figure(figsize = (15,15))
#plt.contour(imagpoints, 900, linewidths=0.5, origin='lower', extent=[rmin, rmax, imin, imax])
#tikzplotlib.save("full_imag_value_contour.tex")
#plt.show()
#fig3.savefig("figures/imag_value_contour_plot.pdf")


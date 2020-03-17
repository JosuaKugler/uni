#
# Gnuplot-Skript für einige Abbildungen, die in der Vorlesung PTP1
# gezeigt wurden.
#
# Aufruf mit:
#
# gnuplot --persist -c abbPTP1.gp {fig_1 ... fig_5}
# gnuplot -c abbPTP1.gp {fig_1 ... fig_5} pdf
#

if (ARG2 eq "pdf") {
  set terminal pdfcairo enhanced colour dashed \
    font "Liberation Serif,12" linewidth 2
  set out ARG1.".pdf"
}

#
# Taylor-Näherung
#

if (ARG1 eq "fig_1" || ARG1 eq "fig_2") {
  set title "Taylor-Näherung, f(x) = (1+x)^{-1/2}"
  f (x) = 1.0/sqrt (1.0+x)
  f0 = 1.0
  f1 = -0.5
  f2 = 3.0/8.0
  f3 = -5.0/16.0
}
if (ARG1 eq "fig_1") {
  unset log xy
  set grid
  set key top right
  set xlabel "x"
  set ylabel "f(x) und Näherungen"
  plot [0:0.5][] \
    f (x) ls 1, \
    f0+f1*x ls 12 t "linear", \
    f0+f1*x+f2*x*x ls 13 t "quadratisch", \
    f0+f1*x+f2*x*x+f3*x**3 ls 14 t "kubisch"
}
if (ARG1 eq "fig_2") {
  unset log xy
  set grid
  set key top left
  set xlabel "x"
  set ylabel "relative Abweichung"
  plot [0:0.5][-0.05:0.05] \
    1.0-(f0+f1*x)/f (x) ls 12 t "linear", \
    1.0-(f0+f1*x+f2*x*x)/f (x) ls 13 t "quadratisch", \
    1.0-(f0+f1*x+f2*x*x+f3*x**3)/f (x) ls 14 t "kubisch"
}

#
# Richtungsfelder
#

if (ARG1 eq "fig_3") {
  set title "Richtungsfeld, y' = -y"
  f (x, y) = -y
  s = 0.3
  set xlabel "t/{/Symbol l}"
  set ylabel "f (t, N) = -N"
  set xrange [0:5]
  set yrange [-2:2]
  set samples 30
  set isosamples 30
}
if (ARG1 eq "fig_4") {
  set title "Richtungsfeld, y' = -1-y"
  f (x, y) = -1.0-y
  s = 0.3
  set xlabel "t/(v_E/g)"
  set ylabel "f (t, v) = -1.0-v/v_E"
  set xrange [0:5]
  set yrange [-2:2]
  set samples 30
  set isosamples 30
}
if (ARG1 eq "fig_5") {
  set title "Richtungsfeld, y' = -y/x+x^2y^2"
  f (x, y) = -y/x+(x*y)**2
  s = 0.15
  set xlabel "x"
  set ylabel "f (x, y) = -y/x+(xy)^2"
  set xrange [0:3]
  set yrange [-1:3]
  set samples 50
  set isosamples 50
}
if (ARG1 eq "fig_3" || ARG1 eq "fig_4" || ARG1 eq "fig_5") {
  n  (x, y) = sqrt (1.0+f (x, y)**2)
  nx (x, y) = 1.0/n (x, y)
  ny (x, y) = f (x, y)/n (x, y)
  plot "++" \
    using 1:2:(s*nx ($1, $2)):(s*ny ($1, $2)) with vectors linestyle 1 notitle
}

if (ARG2 eq "pdf") {
  set out
  set terminal qt
}

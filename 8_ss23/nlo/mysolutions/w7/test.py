from numpy import array
import matplotlib.pyplot as plt

a = [array([2.40460915, 0.85513601]), array([1.80998096, 0.97406986]), array([2.14505475, 0.96109123]), 
array([2.12467111, 0.93991277])]

# *i unpacks i into a tuple (i[0], i[1]), which is interpreted as (x,y) by plt.scatter
for i in a:
    plt.scatter(*i)

plt.show()
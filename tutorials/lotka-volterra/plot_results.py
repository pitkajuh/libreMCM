# -*- coding: utf-8 -*-
import numpy as np
import matplotlib.pyplot as plt

time=np.arange(0, 301, 1)
x=np.loadtxt("r.txt")
y=np.loadtxt("f.txt")
plt.plot(time, x, label="r, libreMCM")
plt.plot(time, y, label="f, libreMCM")
plt.legend()
plt.show()

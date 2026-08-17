# -*- coding: utf-8 -*-
import numpy as np
import matplotlib.pyplot as plt

time=np.arange(0, 300, 1)
x=np.loadtxt("0.txt")
y=np.loadtxt("1.txt")
plt.plot(time, x, label="0, libreMCM")
plt.plot(time, y, label="1, libreMCM")
plt.legend()
plt.show()

# Jupiter Notebook
import numpy
import pandas
a = pandas.read_csv('dataset.txt', sep=' ', header=None)
y = a[0]
del a[0]
import sklearn
from sklearn.neural_network import MLPRegressor
clf = MLPRegressor(hidden_layer_sizes = 40, activation = 'logistic', alpha = 0.001)
clf.fit(a, y)
t = clf.coefs
r = []
for x in t[0]:
    for e in x:
        r.append(e)
for x in t[1]:
    for e in x:
        r.append(e)_
numpy.savetxt('coefficients.txt', r, newline = ' ')
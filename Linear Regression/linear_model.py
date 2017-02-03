# Jupiter Notebook
import numpy
import pandas
a = pandas.read_csv('dataset.txt', sep=' ', header=None)
y = a[0]
del a[0]
import sklearn
from sklearn import linear_model
clf = sklearn.linear_model.LinearRegression(fit_intercept=False)
clf.fit(a, y)
t = clf.coef_
numpy.savetxt('coefficients.txt', t, newline = ' ')
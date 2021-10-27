import matplotlib.pyplot as plt
import numpy as np


def exp_spread(mu, t):
	return 1 - np.exp(-mu * t)

def exp_density(mu, t):
	return mu * np.exp(-mu * t)
	
def hyperexp_density(mu1, mu2, mu3, t):
	return 0.5 * mu1 * (np.exp(-mu1 * t)) + 0.353 * mu2 * (np.exp(-mu2 * t)) + 0.147 * mu3 * (np.exp(-mu3 * t))

def erlang(r, mu, t):
	return r * mu * (np.exp(r * -mu * t)) * (((r * mu * t) ** (r - 1)) / (np.math.factorial(r - 1)))

def paint(t, xrange: float, yrange: float, axes_names, func_name, first_arg, second_arg=None, third_arg=None):

	plt.figure()
	axes = plt.gca()

	if not second_arg:
		for i in range(len(first_arg)):
			plt.plot(t, func_name(first_arg[i], t))
	else:
		if not third_arg:
			for i in range(len(first_arg)):
				plt.plot(t, func_name(first_arg[i], second_arg[i], t))
		else:
			for i in range(len(first_arg)):
				plt.plot(t, func_name(first_arg[i], second_arg[i], third_arg[i], t))

	axes.set_ylim([0, yrange])
	axes.set_xlim([0, xrange])

	plt.legend(axes_names, loc = 1)
	plt.show()


if __name__ == '__main__':
	''' Для отрисовки каждого графика требуется раскомментировать нужную строку и изменить 2 и 3 параметр на 
		свои(отвечают за оси координат)

	'''

	x = np.arange(0.0, 0.35, 0.001)

	mu1 = 51.0
	mu2 = mu1 * 2
	mu3 = mu1 * 3

	mu4 = 1 / ((0.5 / mu1) + (0.353 / mu2) + (0.147 / mu3))
	mu51 = (2 * mu1) / 3
	mu52 = mu51 / 3
	mu53 = mu51 / 5

	# График 1
	#paint(x, 0.15, 1.05, ('mu1', 'mu2', 'mu3'), exp_spread, (mu1, mu2, mu3))

	# График 2
	#paint(x, 0.12, 105, ('alfa', 'beta'), exp_density, (mu1, mu2, mu3)) 

	# График 3
	#paint(x, 0.12, 105, ('alfa', 'beta'), hyperexp_density, (mu1, mu3), second_arg=(mu2, mu2), third_arg=(mu3, mu1)) 

	# График 4
	#paint(x, 0.12, 73, ('mu4'), exp_density, (mu4)) 
	
	# График 5
	paint(x, 0.33, 28, ('mu51', 'mu52', 'mu53'), erlang, (3, 9, 15), second_arg=(mu51, mu52, mu53)) 


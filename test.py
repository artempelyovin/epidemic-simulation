from typing import Tuple, List

import numpy as np

from scipy.interpolate import interp1d
import matplotlib.pyplot as plt


def _provide_data(path_to_statistics: str) -> Tuple[List[int], List[int], List[int], List[int]]:
    with open(path_to_statistics, 'r', encoding='utf8') as file:
        lines = file.read().split('\n')[:-1]

    y_susceptible = [int(line.split(' ')[0]) for line in lines] 
    y_infected = [int(line.split(' ')[1]) for line in lines]
    y_recovered = [int(line.split(' ')[2]) for line in lines]
    x = [n for n in range(len(y_susceptible))]

    return x, y_susceptible, y_infected, y_recovered
    


def _main() -> None:
    x, y_susceptible, y_infected, y_recovered = _provide_data('statistics.txt')
    
    # Interpolation
    # x_new = np.linspace(0, len(x)-1, 500)
    # f1 = interp1d(x, y_susceptible, kind = 'cubic')
    # f2 = interp1d(x, y_infected, kind = 'cubic')
    # f3 = interp1d(x, y_recovered, kind = 'cubic')

    plt.title(f"The epidemic ended in {len(x)} days...")
    # plt.plot(x_new, f1(x_new), 'g')
    # plt.plot(x_new, f2(x_new), 'r')
    # plt.plot(x_new, f3(x_new), 'b')
    plt.plot(x, y_susceptible, 'g')
    plt.plot(x, y_infected, 'r')
    plt.plot(x, y_recovered, 'b')
    plt.legend(['susceptible', 'infected', 'recovered'], loc = 'best')
    plt.savefig('test.png')


if __name__ == '__main__':
    _main()

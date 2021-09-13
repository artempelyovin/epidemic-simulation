from typing import Tuple, List

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
    
    plt.title(f"The epidemic ended in {len(x)} days...")
    plt.plot(x, y_susceptible, 'g')
    plt.plot(x, y_infected, 'r')
    plt.plot(x, y_recovered, 'b')
    plt.legend(['susceptible', 'infected', 'recovered'], loc = 'best')
    plt.savefig('statistics.png')


if __name__ == '__main__':
    _main()

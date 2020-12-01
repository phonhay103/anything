import numpy as np 
import matplotlib.pyplot as plt

n = 10
m = 100
N_GENERATIONS = 400

CROSS_RATE = 0.9
MUTATION_RATE = 0.05
BOUND = 100

def sphere_function(x):
    return np.sum(x*x, axis=1)

def compute_fitness(pred):
    return 1/(1+pred)

def select(pop, fitness):
    idx = np.random.choice(np.arange(m), size=m, replace=True, p=fitness/fitness.sum())
    return pop[idx]

def crossover(s1, s2):
    crossover_prob = np.random.rand((n))
    crossover_mask = crossover_prob < CROSS_RATE

    s1[crossover_mask], s2[crossover_mask]  = s2[crossover_mask], s1[crossover_mask].copy()

    return (s1, s2)

def mutate(child):
    mutate_vector = (np.random.random(size=n)-0.5)*BOUND

    mutate_prob = np.random.rand((n))
    mutate_mask = mutate_prob < MUTATION_RATE

    child[mutate_mask] = mutate_vector[mutate_mask]
    return child

pop = (np.random.random(size=(m, n)) - 0.5)*BOUND

losses = []

for g in range(N_GENERATIONS):
    cost_value = sphere_function(pop)

    fitness = compute_fitness(cost_value)
    if g%1 == 0:
        losses.append(np.min(cost_value))
    
    pop = select(pop, fitness)
    parent_pop = pop.copy()

    for i in range(m//2-2):
        k1 = np.random.randint(0, m, size=1)
        k2 = np.random.randint(0, m, size=1)

        s1 = parent_pop[k1].copy()[0]
        s2 = parent_pop[k2].copy()[0]

        s1, s2 = crossover(s1, s2)

        s1 = mutate(s1)
        s2 = mutate(s2)

        pop[i*2][:] = s1
        pop[i*2+1][:] = s2
    
    two_best = fitness.argsort()[-2:]
    pop[m-2][:] = parent_pop[two_best[0]].copy()[0]
    pop[m-1][:] = parent_pop[two_best[1]].copy()[0]

import matplotlib.pyplot as plt
plt.plot(losses[:100])
plt.show()
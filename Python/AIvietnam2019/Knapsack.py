import random

m = 1000                # Kích thước quần thể
n = 12                  # Số lượng vật
n_generation = 1000     # number of generations
max_weight = 70         # khối lượng tối đa cái túi có thể đựng được

# Vẽ biểu đồ quá trình tối ưu
fitnesses = []

# Dữ liệu cho trước
weights = [1, 3, 5, 7, 10, 12, 15, 23, 32, 33, 35, 37]
prices = [1, 3, 6, 7, 12, 15, 25, 32, 44, 45, 47, 50]

def generate_random_value():
    return random.randint(0, 1) # 1 2 3 4 ...

def compute_fitness(individual):
    fitness = sum(c*x for c, x in zip(individual, prices))
    if sum(c*x for c, x in zip(individual, weights)) > max_weight:
        fitness = 0
    return fitness

def create_individual():
    return [generate_random_value() for _ in range(n)]

def crossover(individual1, individual2, crossover_rate=0.9):
    individual1_new = individual1.copy()
    individual2_new = individual2.copy()

    for i in range(n):
        if random.random() < crossover_rate:
            individual1_new[i] = individual2[i]
            individual2_new[i] = individual1[i]
    return individual1_new, individual2_new

def mutate(individual, mutation_rate=0.05):
    individual_m = individual.copy()

    for i in range(n):
        if random.random() < mutation_rate:
            individual_m[i] = generate_random_value()
    return individual_m

def selection(sorted_old_population):
    index1 = random.randint(0, m-1)
    while True:
        index2 = random.randint(0, m-1)
        if index2 != index1:
            break

    individual_s = sorted_old_population[index1]
    if index2 > index1:
        individual_s = sorted_old_population[index2]
    return individual_s

def create_new_population(old_population, elitism=2, gen=1):
    sorted_population = sorted(old_population, key=compute_fitness)

    if gen%1 == 0:
        fitnesses.append(compute_fitness(sorted_population[m-1]))
    
    new_population = []
    while len(new_population) < m-elitism:
        # selection
        individual_s1 = selection(sorted_population)
        individual_s2 = selection(sorted_population)

        # crossover
        individual_c1, individual_c2 = crossover(individual_s1, individual_s2)

        # mutate
        individual_m1 = mutate(individual_c1)
        individual_m2 = mutate(individual_c2)

        new_population.append(individual_m1)
        new_population.append(individual_m2)
    
    for i in sorted_population[m-elitism:]:
        new_population.append(i.copy())
    
    return new_population
    

population = [create_individual() for _ in range(m)]
for i in range(n_generation):
    population = create_new_population(population, 2, i)

sorted_population = sorted(population, key = compute_fitness)
print(sorted_population[-1])
print(sum(c*x for c, x in zip(sorted_population[-1], weights)))
print(compute_fitness(sorted_population[-1]))
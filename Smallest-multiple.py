import numpy as np
from collections import defaultdict
import math

def prime_factors(n):
    factors = []
    
    while n % 2 == 0:
        factors.append(2)
        n = n // 2
    
    for i in range(3, int(n**0.5) + 1, 2):
        while n % i == 0:
            factors.append(i)
            n = n // i
    
    if n > 2:
        factors.append(n)
    
    return factors

def factor_occurrences(factors):
    occurrences = defaultdict(int)
    for factor in factors:
        occurrences[factor] += 1
    return occurrences

def lcm(numbers):
    result = 1
    for factor, count in numbers.items():
            result *= pow(factor, count)
    return result

def least_common_multiple(n):

    list_occurrences = []
    for number in range(2, n + 1):
        list_occurrence = factor_occurrences(prime_factors(number))
        list_occurrences.append(list_occurrence)

    max_counts = defaultdict(int)
    # Calculate maximum occurrences of each factor
    for d in list_occurrences:
        for factor, count in d.items():
            if count > max_counts[factor]:
                max_counts[factor] = count

    print("Factors with maximum occurrences:", dict(max_counts))
    
    result_lcm = lcm(max_counts)
    return result_lcm

result = least_common_multiple(10)
print(result)
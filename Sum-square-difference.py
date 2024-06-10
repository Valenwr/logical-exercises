import numpy as np
from collections import defaultdict
import math

def sum_squares(n):
    sum = 0
    for number in range(1, n + 1):
        number = pow(number, 2)
        sum += number
    return sum

def square_sum(n):
    sum = 0
    for number in range(1, n + 1):
        sum += number
    sum = pow(sum, 2)
    return sum

result_sum_squares = sum_squares(10)
result_square_sum = square_sum(10)
result_difference = result_square_sum - result_sum_squares

print(f'The difference between {result_square_sum} and {result_sum_squares} is', result_square_sum - result_sum_squares)
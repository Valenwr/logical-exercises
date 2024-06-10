def fibonacci(n):
    a, b = 1, 2
    for _ in range(n):
        yield a
        a, b = b, a + b

result = list(fibonacci(10))
even_sum = sum([par for par in result if par % 2 == 0])
print(even_sum)



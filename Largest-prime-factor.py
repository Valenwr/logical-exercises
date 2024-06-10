import math

def primes_detector(number):
    prime_factors = []
    # Check for the number of 2s that divide number
    while number % 2 == 0:
        prime_factors.append(2)
        number = number // 2

    # Number must be odd at this point, so a skip of 2 is used (i.e., 3, 5, 7, etc.)
    for i in range(3, int(math.sqrt(number)) + 1, 2):
        # While i divides number, append i and divide number
        while number % i == 0:
            prime_factors.append(i)
            number = number // i

    # If number is a prime number greater than 2
    if number > 2:
        prime_factors.append(number)

    return prime_factors

# Example usage
result = primes_detector(13195)
print(result[-1:])


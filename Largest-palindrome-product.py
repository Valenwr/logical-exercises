import math

def largest_palindrome_product(n):
    start = pow(10, n - 1)
    end = pow(10, n) - 1
    largest_palindrome = 0

    for first_factor in range(end, start - 1, -1):
        for second_factor in range(first_factor, start - 1, -1):
            result = first_factor * second_factor
            if palindrome(result) and result > largest_palindrome:
                largest_palindrome = result

    return largest_palindrome

def palindrome(num):
    num = str(num)
    limit = len(num)
    
    for i in range(0, limit // 2):
        if num[i] != num[limit - 1 - i]:
            return False
    
    return True

print(largest_palindrome_product(3)) 

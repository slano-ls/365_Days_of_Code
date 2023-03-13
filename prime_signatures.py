import math 

factors = []
def prime_factors(n):
    i = 2
    while i * i <= n:
        if n % i:
            i += 1
        else:
            n //= i
            factors.append(n)
            factors.append(i)
            factors.append(" ")
            factors.append(" ")
            factors.append(" ")
    return factors
n=2    

for n in range(2, 100):
    prime_factors(n)

print(factors)


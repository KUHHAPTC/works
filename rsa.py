from collections import namedtuple
import random
import time
from typing import List

class PublicKey(namedtuple('PublicKey', 'n e')):
    
    __slots__ = ()

    def decrypt(self, x):
        ''' Decoding message x. 3rd arg - division by modulus. '''
        
        return pow(x, self.e, self.n)

    def encrypt(self, x):
        ''' Encoding message x. 3rd arg - division by modulus. '''

        return pow(x, self.e, self.n)


class PrivateKey(namedtuple('PrivateKey', 'n d')):

    __slots__ = ()

    def decrypt(self, x):
        ''' Decoding message x. 3rd arg - division by modulus. '''
        
        return pow(x, self.d, self.n)

    def encrypt(self, x):
        ''' Encoding message x. 3rd arg - division by modulus. '''

        return pow(x, self.d, self.n)
 
def is_Prime(n):
    ''' Miller-Rabin primality test.
 
    A return value of False means n is certainly not prime. A return value of
    True means n is very likely a prime.

    '''

    if n == 0 or n == 1 or n == 4 or n == 6 or n == 8 or n == 9:
        return False
 
    if n == 2 or n == 3 or n == 5 or n == 7:
        return True

    s = 0
    d = n - 1

    while d % 2 == 0:
        d >>= 1
        s += 1
    assert(2 ** s * d == n - 1)
 
    def is_trial_composite(a):
        ''' Checks whether the number a is composite. '''

        x = pow(a, d, n)
        if x == 1 or x == (n - 1):
            return False

        for i in range(s):
            if pow(a, 2 ** i * d, n) == n - 1:
                return False

        return True  
 
    for _ in range(8): # number of trials 
        
        a = random.randrange(2, n - 1)

        if is_trial_composite(a):
            return False
 
    return True  

def are_relatively_prime(a, b):
    ''' Checking for mutually prime numbers, numbers are mutually prime if they have no common divisor other than 1. '''

    for n in range(2, min(a, b) + 1):
        if a % n == b % n == 0:
            return False

    return True

def bezout(a, b):
    ''' Implementation of the extended Euclidean algorithm, returns x, y and gcd(a, b) for the Bezout equation: ax + by = gcd(a, b). '''

    x, xx, y, yy = 1, 0, 0, 1

    while b:
        q = a // b
        a, b = b, a % b
        x, xx = xx, x - xx * q
        y, yy = yy, y - yy * q

    return (x, y, a)

def get_q(length, p):
    ''' We choose such a q so that it is simple and q * p < (2 ^ length). '''

    q_min = (1 << (length - 1)) // p + 1
    q_max = ((1 << length) - 1) // p

    print(f'min={q_min}, max={q_max}')

    q = 4

    while (is_Prime(q) == False) and (q != p):
        q = random.randint(q_min, q_max)
    
    return q

def get_e(eiler):
    ''' We choose random e (has to be less than eiler) that is relatively prime with the result of eiler`s functon'''

    while True:
        e = random.randint(7, 2154)
        if is_Prime(e) == True:
            if are_relatively_prime(e, eiler):
                break

    return e

def make_key_pair(length, primes: List[int]):
    ''' Return a pair of keys (public and private)'''

    p = random.choice(primes)
    primes.remove(p)

    q = get_q(length, p)

    print(f'p={p}, q={q}')

    eiler = (p - 1) * (q - 1)
    n = p * q

    e = get_e(eiler)

    # The extended Euler algorithm can return a negative value, here it, in this case, is transformed into a positive one
    gcd = bezout(e, eiler)
    d = gcd[0] if gcd[0] > 0 else gcd[0] + eiler
    
    return PublicKey(n, e), PrivateKey(n, d)

def time_decorator(func):

    def wrapper(length):
        time_ = time.monotonic()
        x = func(length)
        print(f'It took: {time.monotonic() - time_}')
        return x

    return wrapper

def get_list_of_primes(length):
    ''' Returns 10 primes from such a range that they will be > 2 ^ ([length // 2] - 1) and < than 2 ^ ([length // 2] + 1). '''

    start = 1 << (length // 2 - 1)
    stop = 1 << (length // 2 + 1)
    print(f'start={start}, stop={stop}')

    primes = []
    x = random.randint(start, stop)
    while len(primes) != 10:
        x = random.randint(start, stop)
        if is_Prime(x) == True:
            if x not in primes:
                primes.append(x)

    return primes

def create_keys(name_of_user, length):
    ''' Creating a public and secret key for the specified user. '''

    primes = get_list_of_primes(length)
    public, private = make_key_pair(length, primes)
    print(f'{name_of_user}`s {public}')
    print(f'{name_of_user}`s {private}\n')
    
    return public, private


@time_decorator
def initiate(length):

    message = int(input('Input a value to encrypt: '))

    public_key_receiver, private_key_receiver = create_keys('Receiver', length)

    public_key_sender, private_key_sender = create_keys('Sender', length)

    # Шифровка подписи закрытым ключом отправителя
    signature = private_key_sender.encrypt(message)

    encrypted_message = public_key_receiver.encrypt(message)

    encrypted_signature = public_key_receiver.encrypt(signature)

    decrypted_message = private_key_receiver.decrypt(encrypted_message)

    decrypted_signature = private_key_receiver.decrypt(encrypted_signature)

    prototype = public_key_sender.decrypt(decrypted_signature)

    print(f'{signature} signature that we get with private sender`s key\n')
    print(f'{encrypted_signature} encrypted signature with public receiver`s key')
    print(f'{decrypted_signature} decrypted signature with public receiver`s key\n')

    print(f'{encrypted_message} encrypted message with public receiver`s key')
    print(f'{decrypted_message} decrypted message with private receiver`s key')
    print(f'{prototype} decrypted message with public sender`s key')
    
    return decrypted_message == prototype

if __name__ == '__main__':
    ''' The RSA encryption algorithm, which allows you to obtain a public and private key for a user-selected number of bits, a
        speed of up to 10 seconds for numbers from 1 to 2^ 1024, using the Miller-Rabin test, the Euclid algorithm and the random 
        module. Session key encryption algorithm from

        '''

    length = 100
    result = initiate(length)

    answer = 'Success' if result else 'Fail'
    print(answer)

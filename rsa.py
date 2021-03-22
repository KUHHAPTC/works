import random
from collections import namedtuple

# именованный кортеж, обращение через точку
class PublicKey(namedtuple('PublicKey', 'n e')):
    __slots__ = ()

    def encrypt(self, x):
        #  Кодирование сообщения x
        # Третий аргумент - аргумент, на который требуется произвести деление по модулю
        return pow(x, self.e, self.n)

    def decrypt(self, x):

        #  Декодирование сообщения x
        # Третий аргумент - аргумент, на который требуется произвести деление по модулю
        return pow(x, self.e, self.n)


class PrivateKey(namedtuple('PrivateKey', 'n d')):

    __slots__ = ()

    def decrypt(self, x):

        #  Декодирование сообщения x
        # Третий аргумент - аргумент, на который требуется произвести деление по модулю
        return pow(x, self.d, self.n)

    def encrypt(self, x):
        #  Кодирование сообщения x
        # Третий аргумент - аргумент, на который требуется произвести деление по модулю
        return pow(x, self.d, self.n)
 
def is_Prime(n):
    """
    Miller-Rabin primality test.
 
    A return value of False means n is certainly not prime. A return value of
    True means n is very likely a prime.
    """
    # Тест Миллера-Рабина, возврашает False, если n точно не простое, возвращает True, если вероятнее всего простое.
    if n != int(n):
        return False
    n = int(n)
    #Miller-Rabin test for prime
    if n == 0 or n == 1 or n == 4 or n == 6 or n == 8 or n == 9:
        return False
 
    if n == 2 or n == 3 or n == 5 or n == 7:
        return True
    s = 0
    d = n-1
    while d % 2 == 0:
        d >>= 1
        s += 1
    assert(2 ** s * d == n - 1)
 
    def trial_composite(a):
        if pow(a, d, n) == 1:
            return False
        for i in range(s):
            if pow(a, 2 ** i * d, n) == n - 1:
                return False
        return True  
 
    for i in range(8):#number of trials 
        a = random.randrange(2, n)
        if trial_composite(a):
            return False
 
    return True  

def are_relatively_prime(a, b):

    # Проверка на взаимнопростые числа, числа являются взаимнопростыми, если у них нет общего делителя, кроме 1
    for n in range(2, min(a, b) + 1):
        if a % n == b % n == 0:
            return False
    return True

def bezout(a, b):

    # Реализация расширенного алгоритма Евклида, возвращает x, y и НОД(a, b) для уравнения Безу: ax + by = gcd(a, b)
    x, xx, y, yy = 1, 0, 0, 1
    while b:
        q = a // b
        a, b = b, a % b
        x, xx = xx, x - xx*q
        y, yy = yy, y - yy*q
    return (x, y, a)

import time
start_time = time.time()

def make_key_pair(length):

    n_min = 1 << (length - 1)
    n_max = (1 << length) - 1
    start = 1 << (length // 2 - 1)
    stop = 1 << (length // 2 + 1)


    primes = []
    x = random.randint(start, stop)
    while len(primes) != 10:
        x = random.randint(start, stop)
        if is_Prime(x) == True:
            if x not in primes:
                primes.append(x)




    p = random.choice(primes)
    primes.remove(p)
    n_min1 = n_min // p + 1
    n_max1 = n_max // p
    q = 4
    while (is_Prime(q) == False) and (q != p):
        q = random.randint(n_min1, n_max1)


    # Выбираем e, меньше чем ((p - 1) * (q - 1) - функция Эйлера)
    # И чтобы e не имело общих множителей с ((p - 1) * (q - 1) - функция Эйлера)
    # Слишком малые значения e ослабят безопасность шифрования RSA, поэтому начинаем с 7
    eiler = (p - 1) * (q - 1)
    n = p * q
    while True:
        e = random.randint(3, 1001)
        if is_Prime(e) == True:
            if are_relatively_prime(e, eiler):
                break
    #Расширенный алгоритм Эйлера может вернуть отрицательное значение, здесь оно, в таком случае, преображается в положительное
    w = bezout(e, eiler)
    if(w[0] < 0):
        d = w[0] + eiler
    else:
        d = w[0]

    return PublicKey(n, e), PrivateKey(n, d)

length = 100
print('Input a value to encrypt: ', end = '')
message = int(input())
message = message % (length - 2)
message = random.randint(2 ** message, 2 ** (length - 1))
#Создание секретного и открытого ключей получателя
publicRes, privateRes = make_key_pair(length)
print('Receiver`s ' + str(publicRes))
print('Receiver`s ' + str(privateRes))
#Создание секретного и открытого ключей отправителя
publicSend, privateSend = make_key_pair(length)
print('Sender`s ' + str(publicSend))
print('Sender`s ' + str(privateSend))
# Шифровка пробного сообщения закрытым ключом отправителя
autification = privateSend.encrypt(message)
# Расшифровка пробного сообщения открытым ключом отправителя
result = publicSend.decrypt(autification)
print(str(autification) + " encrypted by prog Check")
print(str(result) + " decrypted by prog Check")

#x = random.randint(2 ** (length - 1), 2 ** length)
y = publicRes.encrypt(message)

print(str(y) + " encrypted by prog")
print(str(privateRes.decrypt(y)) + " decrypted by prog")
assert privateRes.decrypt(y) == result
print("--- %s seconds ---" % (time.time() - start_time))
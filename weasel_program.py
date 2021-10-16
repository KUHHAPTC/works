import random as rand
import string as strg
from time import sleep

def new_string(count, string):

    if int(count) == int(len(dummy)):
        to_back = string[:(count - 1)] + rand.choice(all_characters)
    elif(int(count) == 1):
        to_back = rand.choice(all_characters) + string[count:]
    else:
        to_back = string[:(count - 1)] + rand.choice(all_characters) + string[(count):]

    return to_back

def new_list(safe_list):
    another_list = []

    for seq in safe_list:
        count = 0
        temp = 0

        for symb in seq:
            temp += 1 
            chance = rand.randint(1, 101)
            if(chance <= (e * 100)):
                count += 1
                seq = new_string(temp, seq)
        another_list.append(seq)

    return another_list

def count_list(safe_list):
    count = []
    another_list = []

    for seq in safe_list:
        temp = 0
        for i in range(len(dummy)):
            if(seq[i] == dummy[i]):
                temp += 1
        count.append(temp)

    func_max = count.index(max(count))

    print(f"Amount of right symbols is: {count[func_max]}/{len(dummy)}")

    for i in count:
        if i == count[func_max]:
            print(f"MY DUMMY IS: {dummy}")
            for _ in range(100):
                another_list.append(safe_list[int(func_max)])
            break

    return another_list

def get_string():

    new_line = strg.ascii_letters + ' '

    for i in result:
        if i not in new_line:
            new_line = new_line + i
    
    return new_line

if __name__ == '__main__':
    ''' Реализация алгоритма weasel program, описанная в https://en.wikipedia.org/wiki/Weasel_program. '''

    dummy = "METHINKS IT IS LIKE A WEASEL"
    result = input(f"Enter your sequences of {len(dummy)} characters: ")
    # result = "irwvcSDamrtvxacxvbqadfSXfplN"

    e = 0.05

    safe_list = []

    all_characters = get_string()

    for i in range(0, 100):
        safe_list.append(result)

    itter = 0
    while result != dummy:

        itter += 1
        safe_list = new_list(safe_list)
        safe_list = count_list(safe_list)

        result = safe_list[0]
        print(f"Itteration number {itter} has {result}")
        sleep(0.5)

    print(f"WE GOT SUCCSSESS ON THE PHRASE |{dummy}| on {itter} itteration")

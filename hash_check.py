import sys
import os
import hashlib

def hash_func(file: str, algorithm: str) -> str: 
    '''Функция будет возвращать хэш файла в соответствии с указанным алгоритмом хэширования (md5, sha1, sha256)'''
    algs = {'md5': hashlib.md5(), 'sha1': hashlib.sha1(), 'sha256': hashlib.sha256()}
    with open(file, "rb") as f:
        while True: # для больших файлов
            data = f.read(4096)
            if not data:
                break
            algs[algorithm].update(data)
    return algs[algorithm].hexdigest()

if __name__ == '__main__':
    feats = {} # Здесь будет словарь, ключами будут названия файлов, значениями списки из 2-ух элементов - алгоритм и контрольная сумма

    folders = sys.argv[1:]

    if os.path.exists(folders[0]):
        with open(folders[0], "r") as f:
            elements = [folder for folder in f.read().split('\n') if folder] 
            '''
                Оставляем в списке только непустые строки из файла, сначала считываем весь файл и делаем список, отделяя по символу
                разделения строки(\n), а потом выбираем только нужные строки.
            '''
            for element in elements:
                temp = element.split(' ') # Добавляем все данные в список
                feats[temp[0]] = temp[1:] # По названию файла добавляем в список его параметры

        real_files = feats.keys()

        if os.path.isdir(folders[1]):
            files = os.listdir(folders[1])
            results = {}
            for file in files:
                if file in real_files: # Чтобы хеширование происходило только для тех файлов, которые есть в файле(исходном)
                    results[file] = hash_func((folders[1] + "\\" + file), feats[file][0])

            for file in real_files:
                if feats.get(file)[1] == results.get(file):
                    print(f"{file} OK")
                elif results.get(file) == None:
                    print(f"{file} NOT FOUND")
                else:
                    print(f"{file} FAILED")
            
        else:
            print("Folder doesnt exist")
   
    else:
        print("File doesnt exist")
        
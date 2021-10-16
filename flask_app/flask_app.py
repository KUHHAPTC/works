import csv
import datetime
from flask import abort, Flask, jsonify, make_response, request
import pytz


app = Flask(__name__)

def get_database():
    ''' Функция получения условной базы данных.'''

    with open('RU.txt', mode='r', encoding='utf-8') as file:

        fieldnames = ['geonameid', 'name', 'asciiname', 'alternatenames', 'latitude', 'longtitude', 'feature class',
                     'feature code', 'country code', 'cc2', 'admin1 code', 'admin2 code', 'admin3 code', 'admin4 code', 
                     'population', 'elevation', 'dem', 'timezone', 'modification date']
                     
        reader = list(csv.DictReader(file, fieldnames=fieldnames, delimiter='\t'))

        for town in reader:
            town['geonameid'] = int(town.get('geonameid'))
            town['alternatenames'] = town['alternatenames'].split(',')
            town['latitude'] = float(town.get('latitude'))
            town['longtitude'] = float(town.get('longtitude'))
            town['population'] = int(town.get('population'))

        return reader

def get_utc_by_timezone(town_timezone):
    ''' Возвращает значение UTC по значению временной зоны. '''

    return int(datetime.datetime.now(pytz.timezone(town_timezone)).strftime('%z')[:-2])

@app.errorhandler(404)
def not_found(error):
    ''' Более наглядный вывод ошибки. '''

    return make_response(jsonify({'error': 'Not found'}), 404)

@app.route('/id/<int:geonameid>', methods=['GET'])
def get_town_by_id(geonameid):
    ''' Функция получает id города и возвращает информацию о нем.

        Если такой id существует, то переменной geoname присвоится соответствующий город. 
        В случае, если не существует, будет выброшено сообщение.

    '''

    geoname = [temp for temp in database if temp.get('geonameid') == geonameid]
    if not len(geoname):
        abort(404)

    return jsonify({f'Information about town': geoname[0]})

@app.route('/list', methods=['GET'])
def several_towns():
    ''' Функция получает страницу и количество городов на странице, и возвращает информацию о городах на указанной странице.

        Высчитывается начальный номер и конечный номер города из всех городов. Генератором списка получаем 
        соответстующие города из списка.

    '''

    page = request.args.get('page', default=1, type=int)
    amount = request.args.get('amount', default=1, type=int)

    start_index = (page - 1) * amount
    last_index = start_index + amount
    
    towns = [town for index, town in enumerate(database, start=1) if index >= start_index and index <= last_index]

    if not len(towns):
        abort(404)

    return jsonify({f'Города с {page} страницы': towns})

def max_by_population(town_name, database):
    ''' Возвращает город с максимальным населением со всей информацией о нем, среди всех городов с таким же названием. '''

    alternative_towns = [town for town in database if town_name in town.get('alternatenames')]
    result_town = max(alternative_towns, key=lambda k: k.get('population'))

    return result_town

@app.route('/towns', methods=['GET'])
def get_two_towns():
    ''' Функция получает название 2-ух городов, возвращает информацию о каждом, а также дополнительную информацию.

        В переменные first_town_info и second_town_info города с максимальным населением по названию городов.

        Далее, в случае непустого параметра 'timezone' у каждого города, создается словарь с ключами временных зон,
        куда мы получаем значения с помощью функции get_utc_by_timezone, далее проверяется разница между ними и соответствующий 
        результат записывается в переменную time_info.

    '''

    first_town = request.args.get('first', type=str)
    second_town = request.args.get('second', type=str)

    first_town_info = max_by_population(second_town, database)
    second_town_info = max_by_population(first_town, database)

    if not (first_town_info and second_town_info):
        abort(404)

    timezones = {
            first_town_info.get('timezone'): get_utc_by_timezone(first_town_info.get('timezone')),
            second_town_info.get('timezone'): get_utc_by_timezone(second_town_info.get('timezone'))
            }

    if not first_town_info.get('timezone') or not second_town_info.get('timezone'):
        time_info = 'Not enough information'
    else:
        difference = abs(timezones[first_town_info.get('timezone')] - timezones[second_town_info.get('timezone')])
        if not difference:
            time_info = 'Match'
        else:
            time_info = f'Differ by {difference}h.'
    
    return jsonify({
                    f'Information about {second_town}': second_town_info, 
                    f'Information about {first_town}': first_town_info,
                    'timezones': timezones,
                    'Additional information': {
                                    'To the north' : first_town if first_town_info.get('latitude') > second_town_info.get('latitude')
                                    else second_town,
                                    'Timezones': time_info
                                    }
                })

if __name__ == '__main__':

    database = get_database()
    app.config['JSON_AS_ASCII'] = False
    app.run(host='127.0.0.1', port=8000, debug=True)    

import aiohttp
import asyncio
import datetime
import random
import time

from fake_useragent import UserAgent


URL_MAIN = "https://remanga.org/panel/add-titles/"

ua = UserAgent()
headers = {
    "Accept": "text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,*/*;q=0.8",
    # "Accept-Encoding": "gzip, deflate, br",
    "Accept-Language": "ru-RU,ru;q=0.8,en-US;q=0.5,en;q=0.3",
    "Connection": "keep-alive",
    "Referer": "https://remanga.org/",
    "Origin": "https://remanga.org/",
    "Sec-Fetch-Dest": "empty",
    "Sec-Fetch-Mode": "cors",
    "Sec-Fetch-Site": "same-site",
    "TE": "trailers",
    "User-Agent": f"{ua.random}"
}


async def send_post(i, kwargs):
    # отказался от json.load, потому что там автоматическое преобразование, например: null -> None
    with open('jsons/cookies.json', 'r') as f:
        cookies = f.read()

    with open('txt_files/tokens.txt', 'r') as f:
        tokens = f.read().split('\n')[:-1]

    token = random.choice(tokens)

    t = time.monotonic()
    async with aiohttp.ClientSession() as session:
        session.headers.update({'Cookie': f'user={cookies}'})
        data = aiohttp.FormData()
        data.add_fields(("csrfmiddlewaretoken", token),
                        ("en_name", kwargs["title_en"]),
                        ("rus_name", kwargs["title_ru"]),
                        ("another_name", kwargs["title"]),
                        ("type", "1"),
                        ("categories", "5"),
                        ("categories", "6"),
                        ("genres", "2"),
                        ("publishers", "5242"),
                        ("status", "4"),
                        ("age_limit", "0"),
                        ("issue_year", "2022"),
                        ("original_link", kwargs["url"]))

        data.add_field("cover",
                       open("12414.png", 'rb'),
                       filename='12414.png',
                       content_type='multipart/form-data')
        proxy_free = 'http://110.165.23.162:80'
        proxy_check = 'http://23.239.20.205:80'
        # proxy = 'http://206.253.164.146:80'
        # proxy_3 = 'http://107.151.182.247:80' # jaloba na ssl
        # proxy_2 = 'http://Seldeydarasama00:Z3l6OwW@5.180.154.89:45785'
        proxy_1 = 'http://Seldeydarasama00:Z3l6OwW@191.101.148.75:45785'
        # proxy_4 = 'http://yWCAVM2j:1LZThx9T@212.193.142.234:54893' # jaloba na ssl
        # proxy_5 = 'http://5.42.177.53:3128' # https vidimo
        async with session.post(URL_MAIN, headers=headers, data=data) as resp:

            print(f'send post {time.monotonic() - t} ({kwargs["title_ru"]})')
            # print(await resp.text())

            if resp.status == 200:

                with open('txt_files/successes.txt', 'a') as file:
                    file.write(f'{kwargs["title"]}/{kwargs["title_en"]}/{kwargs["title_ru"]}/{datetime.datetime.now()}\n')



def run_post(*args, amount=0):
    loop = asyncio.get_event_loop()
    coroutines = [send_post(i + 1 + amount, args[i - 1]) for i in range(len(args))]
    result = loop.run_until_complete(asyncio.gather(*coroutines))
    return len(result)


if __name__ == '__main__':
    run_post(*[{
        "title": "알아채기 쉬운 완전판",
        "title_en": "easy to notce",
        "title_ru": "Понятная полная версия 1",
        "url": "http://seoji.nl.go.kr/landingPage?isbn=9791139902150"
    }, {
        "title": "알아채기 쉬운 완전판",
        "title_en": "myth of the nil",
        "title_ru": "Понятная полная версия 2",
        "url": "http://seoji.nl.go.kr/landingPage?isbn=9791139902150"
    }, {
        "title": "알아채기 쉬운 완전판",
        "title_en": "the law of sharin",
        "title_ru": "Понятная полная версия 3",
        "url": "http://seoji.nl.go.kr/landingPage?isbn=9791139902150"
    }])

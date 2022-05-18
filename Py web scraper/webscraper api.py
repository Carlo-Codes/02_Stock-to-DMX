from timeit import repeat
import requests #requests http
import json
import time

starttime = time.time()
final_data = { "data" : [{"Price": 1, "High": 4539.66, "Low": 4451.5}, {"Price": 2, "High": 4539.66, "Low": 4451.5}]}


def write_data(data):
    file = open("G:\\Work\\Coding\\c++\\Practice\\Web scraper to shader\\bin\\data\\data.json","w")
    if len(final_data["data"]) >= 5:
        del final_data["data"] [0]
        final_data["data"].append(data)
    else:
        final_data["data"].append(data)
    json.dump(final_data, file, indent = 6)
    file.close
    
def getdata(symbol):
    header = {"x-API-KEY": "w9KCovFjCZ1N1sUhhb2h092YgvE2gL6t214BwJbM"}
    url = "https://yfapi.net/v6/finance/quote"
    query = {"symbols" : symbol, "region" : "US", "lang" : "en"}

    r = requests.request("GET", url, headers = header, params = query).text
    data = json.loads(r)
    price = data['quoteResponse']['result'][0]["regularMarketPrice"]
    high = data['quoteResponse']['result'][0]["regularMarketDayHigh"]
    low = data['quoteResponse']['result'][0]["regularMarketDayLow"]
    stock_data = {"Price" : price, "High" : high, "Low" : low}
    return stock_data


def get_multiple_dataV2(symbol, delay = 2):
    i=0
    while True:
        if i < 20: # delete this to run continious
            data = getdata(symbol)
            print (data)
            write_data(data)
        time.sleep(60)
        i += 1
    

#get_multiple_data(10, 2, "^GSPC")
get_multiple_dataV2("ETH-USD")



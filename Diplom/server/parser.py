import pandas as pd

def kill_NaN(arr):
    for i in range(len(arr)):
        if pd.isna(arr[i]):
            arr[i] = arr[i - 1]

def parserDutchStyleLife():
    try:
        dutchStyleLife = pd.read_excel(r'./dutchStyleLife.xlsx', sheet_name='Лист1')
        breakpoint = -1
        result = {}
        kill_NaN(dutchStyleLife['Значения'])
        for i in range(len(dutchStyleLife['Жанры натюрмортов'])):
            if not(pd.isna(dutchStyleLife['Жанры натюрмортов'][i])):
                key = dutchStyleLife['Жанры натюрмортов'][i]
                if breakpoint != -1:
                    result[dutchStyleLife['Жанры натюрмортов'][breakpoint]] = dict(zip(dutchStyleLife['Сегменты'][breakpoint:i].to_list(), dutchStyleLife['Значения'][breakpoint:i].to_list()))
                breakpoint = i
        else:
            result[key] = dict(zip(dutchStyleLife['Сегменты'][breakpoint:i + 1].to_list(), dutchStyleLife['Значения'][breakpoint:i + 1].to_list()))
        return result
    except: 
        return 'Parser Error'

if __name__ == "__main__":
    print(parserDutchStyleLife())
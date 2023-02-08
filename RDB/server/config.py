#Backend server connection
SHost = '0.0.0.0'
SPort = '5002'

#SQL server connection
DBHost = '127.0.0.1'
user = 'postgres'
password = 'Danstrigin2!'
DBName = 'hotels'
DBPort = 5432

def pars_to_json(columns, queru):
    res = []
    for i in range(len(queru)):
        res += [dict(zip(columns, queru[i]))]
    return dict(zip(range(len(queru)), res))
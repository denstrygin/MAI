from flask import Flask, request
from parser import parserDutchStyleLife
import pymongo

app = Flask(__name__)

def db_connection():
    try:
        client = pymongo.MongoClient('mongodb://127.0.0.1:27017')
        db = client.dutchStyleLife
    except pymongo.errors.ServerSelectionTimeoutError:
        return "Connection to Database Error"
    return db.symbol 

def parse_response(coll, id):
    if id == '-1':
        id = {}
    else:
        id = {'_id': int(id)}
    response = {}
    for i in coll.find(id):
        del i['_id']
        keys = i.keys()
        for key in keys:
            skeys = list(i[key].keys())
            response.update({key: skeys})
    print(response)
    return response

@app.route('/')
def hello():
    return 'Welcome to the DutchStileLife server!'

@app.route('/refresh_db')
def refresh_db():
    try: 
        exelList = parserDutchStyleLife()
        if exelList == 'Parser Error':
            return 'Parser Error'
        keys, count = exelList.keys(), 0
        coll = db_connection()
        if coll == "Connection to Database Error":
            return coll
        coll.delete_many({})
        for key in keys:
            coll.insert_one({'_id': count, key: exelList[key]})
            count += 1
    except:
        return 'Error'
    return 'Success'

@app.route('/list_of_segments')
def list_of_segments():
    id = request.args.get('id')
    coll = db_connection()
    if coll == "Connection to Database Error":
        return coll
    return parse_response(coll, id)

@app.route('/list_of_symbols')
def list_of_symbols():
    return 'getListOfSymbols()'

if __name__ == '__main__':
    app.run(debug=True, port = 5000)
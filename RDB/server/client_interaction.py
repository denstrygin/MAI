from connection import PostgresConnection
from config import user, password, DBName, DBHost, DBPort, pars_to_json
from flask import jsonify, request
import datetime

class Client_interaction:
    def __init__(self, DBHost, user, password, DBName, DBPort):
        self.postgre_connection = PostgresConnection(
            user = user,
            password = password,
            dbname = DBName,
            dbhost = DBHost,
            dbport = DBPort
        )

    def get_list_hotel(self):
        list_hotel = self.postgre_connection.execute_query(
            '''
            Select id_hotel, name from hotel;
            '''
        ).fetchall()
        columns = (
            'id_hotel',
            'name'
        )
        #print(list_hotel)
        return jsonify(pars_to_json(columns, list_hotel)), 201

    def get_client_info_hotel(self):
        request_body = dict(request.json)
        id_hotel = request_body["id_hotel"]
        info_hotel = self.postgre_connection.execute_query(
            f'''
            Select * from hotel where id_hotel = {id_hotel};
            '''
        ).fetchall()
        columns = (
            'id_hotel',
            'name',
            'count_of_building',
            'profit_per_month',
            'profit_per_year',
            'alltime_profit',
            'tax_on_area',
            'adress',
            'phone',
            'roomines',
            'image'
        )
        return jsonify(pars_to_json(columns, info_hotel)), 201

    def get_list_room(self, id_hotel = 1):
        list_room = self.postgre_connection.execute_query(
            f'''
            Select * from room where id_h = {id_hotel}
            '''
        ).fetchall()
        columns = (
            'id_room',
            'room_number',
            'floor',
            'capacity',
            'price',
            'id_h',
            'image'
        )
        #print(list_room)
        return jsonify(pars_to_json(columns, list_room)), 201

    def filter(self, id_hotel = 1, min_cost = None, max_cost = None, capacity = None, min_date = None, max_date = None):
        queru = f'Select * from room where id_h = {id_hotel}'
        columns = (
            'id_room',
            'room_number',
            'floor',
            'capacity',
            'price',
            'id_h',
            'image'
        )
        if min_cost:
            queru += f' and price >= \'{min_cost}\''
        if max_cost:
            queru += f' and price <= \'{max_cost}\''
        if capacity:
            queru += f' and capacity = {capacity}'
        if min_date:
            now = datetime.datetime.now()
            curDate = now.date()
            queru += f''
        if max_date:
            queru += f''
        list_room = self.postgre_connection.execute_query(queru).fetchall()
        #print(list_room)
        return jsonify(pars_to_json(columns, list_room)), 201

    def add_new_stay(self):
        request_body = dict(request.json)
        id_guest = request_body["id_guest"]
        id_room = request_body["id_room"]
        id_staff = request_body["id_staff"]
        id_h = request_body["id_h"]
        check_in = request_body["check_in"]
        check_out = request_body["check_out"]

        queru = f'''
        Insert into stay (id_guest, id_room, id_staff, id_h, check_in, check_out) 
        values ({id_guest}, {id_room}, {id_staff}, {id_h}, \'{check_in}\', \'{check_out}\')
        '''
        client_orders = self.postgre_connection.execute_query(queru).fetchall()
        
        return 'vse norm', 201

    def get_client_orders(self, id_guest = 1):
        queru = f'Select * from stay where id_guest = {id_guest}'
        columns = (
            'id_guest', 
            'id_room', 
            'id_staff', 
            'id_h', 
            'check_in', 
            'check_out'
        )
        client_orders = self.postgre_connection.execute_query(queru).fetchall()
        #print(client_orders)
        return jsonify(pars_to_json(columns, client_orders)), 201

    def get_min_max_price_room(self):
        list_min_max = self.postgre_connection.execute_query(
            f'''
            Select MIN(price) as min, MAX(price) as max from room;
            '''
        ).fetchall()
        columns = (
            'min',
            'max'
        )
        #print(list_min_max)
        return jsonify(pars_to_json(columns, list_min_max)), 201

    def get_min_max_capacity_room(self):
        list_min_max = self.postgre_connection.execute_query(
            f'''
            Select MIN(capacity) as min, MAX(capacity) as max from room;
            '''
        ).fetchall()
        columns = (
            'min',
            'max'
        )
        #print(list_min_max)
        return jsonify(pars_to_json(columns, list_min_max)), 201

client_interaction = Client_interaction(DBHost, user, password, DBName, DBPort)

if __name__ == '__main__':
    client_interaction.get_list_hotel()
    #client_interaction.get_info_hotel()
    #client_interaction.get_list_room()
    #client_interaction.add_new_stay(id_guest = 1, id_room = 1, id_staff = 7, id_h = 1, check_in = '2024-12-09', check_out = '2024-12-12')
    #client_interaction.get_client_orders()

    #now = datetime.datetime.now()
    #print(now.date())
    #client_interaction.filter()
    #client_interaction.get_min_max_capacity_room()
    pass
from connection import PostgresConnection
from config import user, password, DBName, DBHost, DBPort, pars_to_json
from flask import jsonify, request
import datetime

class Admin_interaction:
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
        return jsonify(pars_to_json(columns, list_hotel)), 201

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

    def get_info_hotel(self, id_hotel = 1):
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

    def get_info_room(self, id_hotel = 1):
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

    def get_info_guest(self):
        list_guest = self.postgre_connection.execute_query(
            f'''
            Select * from guest;
            '''
        ).fetchall()
        columns = (
            'id_guest',
            'f_name',
            'l_name',
            'passport',
            'person_with',
            'phone',
            'email',
            'password'
        )
        #print(list_guest)
        return jsonify(pars_to_json(columns, list_guest)), 201
    
    def get_info_staff(self):
        list_staff = self.postgre_connection.execute_query(
            f'''
            Select * from staff;
            '''
        ).fetchall()
        columns = (
            'id_staff',
            'f_name', 
            'l_name', 
            'id_post', 
            'password',
            'email', 
            'id_h', 
            'phone'
        )
        #print(list_staff)
        return jsonify(pars_to_json(columns, list_staff)), 201

    def get_info_shift(self):
        list_shift = self.postgre_connection.execute_query(
            f'''
            Select * from shift;
            '''
        ).fetchall()
        columns = (
            'id_shift',
            'id_room', 
            'id_staff', 
            'date', 
            'id_h'
        )
        #print(list_shift)
        return jsonify(pars_to_json(columns, list_shift)), 201

    def get_info_stay(self):
        list_stay = self.postgre_connection.execute_query(
            f'''
            Select * from stay;
            '''
        ).fetchall()
        columns = (
            'id_stay',
            'id_shift',
            'id_room', 
            'id_staff', 
            'date', 
            'id_h'
        )
        #print(list_stay)
        return jsonify(pars_to_json(columns, list_stay)), 201

    def get_info_post(self):
        info_post = self.postgre_connection.execute_query(
            f'''
            Select * from post;
            '''
        ).fetchall()
        columns = (
            'id_post',
            'post',
            'salary_min',
            'shift_id'
        )
        #print(info_post)
        return jsonify(pars_to_json(columns, info_post)), 201

    def update_info_hotel(self):
        request_body = dict(request.json)
        id_hotel = request_body["id_hotel"]
        name = request_body["name"]
        count_of_building = request_body["count_of_building"]
        profit_per_month = request_body["profit_per_month"]
        profit_per_year = request_body["profit_per_year"]
        alltime_profit = request_body["alltime_profit"]
        tax_on_area = request_body["tax_on_area"]
        adress = request_body["adress"]
        phone = request_body["phone"]
        roomines = request_body["roomines"]
        image = request_body["image"]

        list_hotel = self.postgre_connection.execute_query(
            f'''
            Update hotel
            Set name = {name}, count_of_building = {count_of_building}, profit_per_month = {profit_per_month},
            profit_per_year = {profit_per_year}, alltime_profit = {alltime_profit}, tax_on_area = {tax_on_area},
            adress = \'{adress}\', phone = {phone}, roomines = {roomines}, image = {image}
            where id_hotel = {id_hotel};
            '''
        ).fetchall()
        #print(list_hotel)
        return 'Okay!', 201

    def update_info_room(self):
        request_body = dict(request.json)
        id_room = request_body["id_room"]
        id_h = request_body["id_h"]
        room_number = request_body["room_number"]
        floor = request_body["floor"]
        capacity = request_body["capacity"]
        price = request_body["price"]
        image = request_body["image"]

        list_room = self.postgre_connection.execute_query(
            f'''
            Update room
            Set room_number = {room_number}, floor = {floor}, capacity = {capacity},
            price = {price}, id_h = {id_h}, image = {image}
            where id_room = {id_room};
            '''
        ).fetchall()
        #print(list_room)
        return 'Okay!', 201

    def update_info_guest(self):
        request_body = dict(request.json)
        id_guest = request_body["id_guest"]
        f_name = request_body["f_name"]
        l_name = request_body["l_name"]
        passport = request_body["passport"]
        person_with = request_body["person_with"]
        phone = request_body["phone"]
        email = request_body["email"]
        password = request_body["password"]

        list_guest = self.postgre_connection.execute_query(
            f'''
            Update guest
            Set f_name = {f_name}, l_name = {l_name}, passport = {passport},
            person_with = {person_with}, phone = {phone}, email = {email}, password = {password}
            where id_guest = {id_guest};
            '''
        ).fetchall()
        #print(list_guest)
        return 'Okay!', 201
    
    def update_info_staff(self):
        request_body = dict(request.json)
        id_staff = request_body["id_staff"]
        f_name = request_body["f_name"]
        l_name = request_body["l_name"]
        id_post = request_body["id_post"]
        password = request_body["password"]
        email = request_body["email"]
        id_h = request_body["id_h"]
        phone = request_body["phone"]

        list_staff = self.postgre_connection.execute_query(
            f'''
            Update staff
            Set f_name = {f_name}, l_name = {l_name}, id_post = {id_post}, password = {password},
            email = {email}, id_h = {id_h}, phone = {phone}
            where id_staff = {id_staff};
            '''
        ).fetchall()
        #print(list_staff)
        return 'Okay!', 201

    def update_info_shift(self):
        request_body = dict(request.json)
        id_shift = request_body["id_shift"]
        id_room = request_body["id_room"]
        id_staff = request_body["id_staff"]
        date = request_body["date"]
        id_h = request_body["id_h"]

        list_shift = self.postgre_connection.execute_query(
            f'''
            Update shift
            Set id_room = {id_room}, id_staff = {id_staff}, date = \'{date}\', id_h = {id_h}
            where id_shift = {id_shift};
            '''
        ).fetchall()
        #print(list_shift)
        return 'Okay!', 201

    def update_info_stay(self):
        request_body = dict(request.json)
        id_stay = request_body["id_stay"]
        id_guest = request_body["id_guest"]
        id_room = request_body["id_room"]
        id_staff = request_body["id_staff"]
        id_h = request_body["id_h"]
        check_in = request_body["check_in"]
        check_out = request_body["check_out"]

        list_stay = self.postgre_connection.execute_query(
            f'''
            Update stay
            Set id_guest = {id_guest}, id_room = {id_room}, id_staff = {id_staff}, id_h = {id_h},
            check_in = \'{check_in}\', check_out = \'{check_out}\'
            where id_stay = {id_stay};
            '''
        ).fetchall()
        #print(list_stay)
        return 'Okay!', 201

    def update_info_post(self):
        request_body = dict(request.json)
        id_post = request_body["id_post"]
        post = request_body["post"]
        salary_min = request_body["salary_min"]
        shift_id = request_body["shift_id"]

        info_post = self.postgre_connection.execute_query(
            f'''
            Update post
            Set post = {post}, salary_min = {salary_min}, shift_if = {shift_id}
            where id_post = {id_post};
            '''
        ).fetchall()
        #print(info_post)
        return 'Okay!', 201

    def insert_info_hotel(self):
        request_body = dict(request.json)
        name = request_body["name"]
        count_of_building = request_body["count_of_building"]
        profit_per_month = request_body["profit_per_month"]
        profit_per_year = request_body["profit_per_year"]
        alltime_profit = request_body["alltime_profit"]
        tax_on_area = request_body["tax_on_area"]
        adress = request_body["adress"]
        phone = request_body["phone"]
        roomines = request_body["roomines"]
        image = request_body["image"]
        code = self.postgre_connection.execute_query(
            f'''
            INSERT INTO hotel
            (name, count_of_building, profit_per_month, profit_per_year,
            alltime_profit, tax_on_area, adress, phone, roomines, image)
            VALUES
            (\'{name}\', {count_of_building}, {profit_per_month}, {profit_per_year},
            {alltime_profit}, {tax_on_area}, \'{adress}\', \'{phone}\', {roomines}, \'{image}\');
            '''
        ).fetchall()
        #print(code)
        return 'Okey!', 201

    def insert_info_room(self):
        request_body = dict(request.json)
        room_number = request_body["room_number"]
        floor = request_body["floor"]
        capacity = request_body["capacity"]
        price= request_body["price"]
        id_h = request_body["id_h"]
        image = request_body["image"]

        list_room = self.postgre_connection.execute_query(
            f'''
            INSERT INTO room
            (room_number, floor, capacity, price, id_h, image)
            VALUES
            ({room_number}, {floor}, {capacity}, {price}, {id_h}, \'{image}\');
            '''
        ).fetchall()
        #print(list_room)
        return 'Okey!', 201

    def insert_info_guest(self):
        request_body = dict(request.json)
        f_name = request_body["f_name"]
        l_name = request_body["l_name"]
        passport = request_body["passport"]
        person_with = request_body["person_with"]
        phone = request_body["phone"]
        email = request_body["email"]
        password = request_body["password"]

        list_guest = self.postgre_connection.execute_query(
            f'''
            INSERT INTO guest
            (f_name, l_name, passport, person_with, phone, email, password)
            VALUES
            (\'{f_name}\', \'{l_name}\', {passport}, {person_with}, \'{phone}\', \'{email}\', {password});
            '''
        ).fetchall()
        #print(list_guest)
        return 'Okey!', 201
    
    def insert_info_staff(self):
        request_body = dict(request.json)
        f_name = request_body["f_name"]
        l_name = request_body["l_name"]
        id_post = request_body["id_post"]
        password = request_body["password"]
        email = request_body["email"]
        id_h = request_body["id_h"]
        phone = request_body["phone"]

        list_staff = self.postgre_connection.execute_query(
            f'''
            INSERT INTO staff
            (f_name, l_name, id_post, password, email, id_h, phone)
            VALUES
            ('{f_name}', '{l_name}', {id_post}, '{password}', '{email}', {id_h}, {phone});
            '''
        ).fetchall()
        #print(list_staff)
        return 'Okey!', 201

    def insert_info_shift(self):
        request_body = dict(request.json)
        id_room = request_body["id_room"]
        id_staff = request_body["id_staff"]
        date = request_body["date"]
        id_h = request_body["id_h"]

        list_shift = self.postgre_connection.execute_query(
            f'''
            INSERT INTO shift
            (id_room, id_staff, date, id_h)
            VALUES
            ({id_room}, {id_staff}, '{date}', {id_h});
            '''
        ).fetchall()
        #print(list_shift)
        return 'Okay!', 201

    def insert_info_post(self):
        request_body = dict(request.json)
        post = request_body["post"]
        salary_min = request_body["salary_min"]
        shift_id = request_body["shift_id"]

        list_stay = self.postgre_connection.execute_query(
            f'''
            INSERT INTO post
            (post, salary_min, shift_id)
            VALUES
            ('{post}', {salary_min}, {shift_id});
            '''
        ).fetchall()
        #print(list_stay)
        return 'Okay!', 201

    def insert_info_stay(self):
        request_body = dict(request.json)
        id_guest = request_body["id_guest"]
        id_room = request_body["id_room"]
        id_staff = request_body["id_staff"]
        id_h = request_body["id_h"]
        check_in = request_body["check_in"]
        check_out = request_body["check_out"]

        list_stay = self.postgre_connection.execute_query(
            f'''
            INSERT INTO stay
            (id_guest, id_room, id_staff, id_h, check_in, check_out)
            VALUES
            ({id_guest}, {id_room}, {id_staff}, {id_h}, '{check_in}', '{check_out}')
            '''
        ).fetchall()
        #print(list_stay)
        return 'Okey!', 201

    def delete_info_hotel(self):
        request_body = dict(request.json)
        id_hotel = request_body["id_hotel"]

        list_hotel = self.postgre_connection.execute_query(
            f'''
            Delete from hotel where id_hotel = {id_hotel};
            '''
        ).fetchall()
        #print(list_hotel)
        return 'Okay!', 201

    def delete_info_room(self):
        request_body = dict(request.json)
        id_room = request_body["id_room"]

        list_room = self.postgre_connection.execute_query(
            f'''
            Delete from room where id_room = {id_room}
            '''
        ).fetchall()
        #print(list_room)
        return 'Okay!', 201

    def delete_info_guest(self):
        request_body = dict(request.json)
        id_guest = request_body["id_guest"]

        list_guest = self.postgre_connection.execute_query(
            f'''
            Delete from guest where id_guest = {id_guest};
            '''
        ).fetchall()
        #print(list_guest)
        return 'Okay!', 201
    
    def delete_info_staff(self):
        request_body = dict(request.json)
        id_staff = request_body["id_staff"]

        list_staff = self.postgre_connection.execute_query(
            f'''
            Delete from staff where id_staff = {id_staff};
            '''
        ).fetchall()
        #print(list_staff)
        return 'Okay!', 201

    def delete_info_shift(self):
        request_body = dict(request.json)
        id_shift = request_body["id_shift"]

        list_shift = self.postgre_connection.execute_query(
            f'''
            Delete from shift where id_shift = {id_shift};
            '''
        ).fetchall()
        #print(list_shift)
        return 'Okay!', 201

    def delete_info_stay(self):
        request_body = dict(request.json)
        id_stay = request_body["id_stay"]

        list_stay = self.postgre_connection.execute_query(
            f'''
            Delete from stay where id_stay = {id_stay};
            '''
        ).fetchall()
        #print(list_stay)
        return 'Okay!', 201

    def delete_info_post(self):
        request_body = dict(request.json)
        id_post = request_body["id_post"]

        list_post = self.postgre_connection.execute_query(
            f'''
            Delete from post where id_post = {id_post};
            '''
        ).fetchall()
        #print(list_post)
        return 'Okay!', 201

admin_interaction = Admin_interaction(DBHost, user, password, DBName, DBPort)

if __name__ == '__main__':
    #admin_interaction.get_list_hotel()
    admin_interaction.get_info_hotel()
    #admin_interaction.get_info_room()
    #admin_interaction.get_info_guest()
    #admin_interaction.get_info_staff()
    #admin_interaction.get_info_shift()
    #admin_interaction.get_info_stay()
    #admin_interaction.update_info_hotel()
    #admin_interaction.update_info_room()
    #admin_interaction.update_info_guest()
    #admin_interaction.update_info_staff()
    #admin_interaction.update_info_shift()
    #admin_interaction.update_info_stay()
    #admin_interaction.insert_info_hotel()
    #admin_interaction.insert_info_room()
    #admin_interaction.insert_info_guest()
    #admin_interaction.insert_info_staff()
    #admin_interaction.insert_info_shift()
    #admin_interaction.insert_info_stay()
    #admin_interaction.delete_info_hotel()
    #admin_interaction.delete_info_room()
    #admin_interaction.delete_info_guest()
    #admin_interaction.delete_info_staff()
    #admin_interaction.delete_info_shift()
    #admin_interaction.delete_info_stay()
    pass
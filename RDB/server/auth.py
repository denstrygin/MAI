from connection import PostgresConnection
from config import user, password, DBName, DBHost, DBPort, pars_to_json
from flask import jsonify
import datetime

class Auth():
    def __init__(self, DBHost, user, password, DBName, DBPort):
        self.postgre_connection = PostgresConnection(
            user = user,
            password = password,
            dbname = DBName,
            dbhost = DBHost,
            dbport = DBPort
        )

    def insert_info_guest(self, f_name, l_name, passport, persons_with, phone, email, password):
        list_guest = self.postgre_connection.execute_query(
            f'''
            INSERT INTO guest
            (f_name, l_name, passport, persons_with, phone, email, password)
            VALUES
            (\'{f_name}\', \'{l_name}\', {passport}, \'{persons_with}\', \'{phone}\', \'{email}\', \'{password}\');
            '''
        ).fetchall()
        #print(list_guest)
        return 'Okey!', 201

    def control_guest(self, email, password):
        control = self.postgre_connection.execute_query(
            f'''
            Select id_guest from guest
            where email = \'{email}\' and password = \'{password}\';
            '''
        ).fetchall()
        #print(control)
        return jsonify(pars_to_json(('id_guest'), control)), 201
    
    def control_staff(self, email, password):
        control = self.postgre_connection.execute_query(
            f'''
            Select id_staff from staff
            where email = \'{email}\' and password = \'{password}\' and id_post <> 1;
            '''
        ).fetchall()
        #print(control)
        return jsonify(pars_to_json(('id_staff'), control)), 201

    def control_admin(self, email, password):
        control = self.postgre_connection.execute_query(
            f'''
            Select id_staff from staff
            where email = \'{email}\' and password = '{password}' and id_post = 1;
            '''
        ).fetchall()
        #print(control)
        return jsonify(pars_to_json(('id_staff'), control)), 201

auth = Auth(DBHost, user, password, DBName, DBPort)

if __name__ == '__main__':
    print(auth.insert_info_guest(f_name = 'Василий', l_name = 'Плешков', passport = '45161201493', persons_with = '2', phone = '+79296598963', email = 'vasyaplesh@gmail.com', password = '123456'))
    #auth.control_guest('nuraztook@gmail.com', 4)
    #auth.control_staff('olegbarin@gmail.com', 123456)
    #auth.control_admin('babaykin@gmail.com', 123456)
    pass
import threading
import requests
from config import SHost, SPort
from flask import Flask, request, render_template

from client_interaction import client_interaction
from admin_interaction import admin_interaction
from auth import auth

class Server:
    def __init__(self, host, port):
        self.host = host
        self.port = port
        self.app = Flask(__name__)
        self.app.add_url_rule('/shutdown', view_func = self.shutdown)
        self.app.add_url_rule('/', view_func = self.get_home)
        self.app.add_url_rule('/home', view_func = self.get_home)
        self.app.add_url_rule('/list_hotel', view_func = client_interaction.get_list_hotel)
        self.app.add_url_rule('/info_hotel', view_func = client_interaction.get_client_info_hotel, methods = ['POST'])
        self.app.add_url_rule('/list_room', view_func = client_interaction.get_list_room, methods = ['POST'])
        self.app.add_url_rule('/client_orders', view_func = client_interaction.get_client_orders) 
        #self.app.add_url_rule('/alist_hotel', view_func = admin_interaction.get_list_hotel)
        #self.app.add_url_rule('/alist_room', view_func = admin_interaction.get_list_room)
        self.app.add_url_rule('/ainfo_hotel', view_func = admin_interaction.get_info_hotel)
        self.app.add_url_rule('/ainfo_room', view_func = admin_interaction.get_info_room)
        self.app.add_url_rule('/ainfo_guest', view_func = admin_interaction.get_info_guest)
        self.app.add_url_rule('/ainfo_staff', view_func = admin_interaction.get_info_staff)
        self.app.add_url_rule('/ainfo_shift', view_func = admin_interaction.get_info_shift)
        self.app.add_url_rule('/ainfo_stay', view_func = admin_interaction.get_info_stay)
        self.app.add_url_rule('/ainfo_post', view_func = admin_interaction.get_info_post)
        # все что ниже нужно прописать как правильно обращаться типа 'POST' но я не особо шарю
        self.app.add_url_rule('/auinfo_hotel', view_func = admin_interaction.update_info_hotel, methods = ['PUT'])
        self.app.add_url_rule('/auinfo_room', view_func = admin_interaction.update_info_room, methods = ['PUT'])
        self.app.add_url_rule('/auinfo_guest', view_func = admin_interaction.update_info_guest, methods = ['PUT'])
        self.app.add_url_rule('/auinfo_staff', view_func = admin_interaction.update_info_staff, methods = ['PUT'])
        self.app.add_url_rule('/auinfo_shift', view_func = admin_interaction.update_info_shift, methods = ['PUT'])
        self.app.add_url_rule('/auinfo_stay', view_func = admin_interaction.update_info_stay, methods = ['PUT'])
        self.app.add_url_rule('/auinfo_post', view_func = admin_interaction.update_info_post, methods = ['PUT'])
        self.app.add_url_rule('/aiinfo_hotel', view_func = admin_interaction.insert_info_hotel, methods = ['POST'])
        self.app.add_url_rule('/aiinfo_room', view_func = admin_interaction.insert_info_room, methods = ['POST'])
        self.app.add_url_rule('/aiinfo_guest', view_func = admin_interaction.insert_info_guest, methods = ['POST'])
        self.app.add_url_rule('/aiinfo_staff', view_func = admin_interaction.insert_info_staff, methods = ['POST'])
        self.app.add_url_rule('/aiinfo_shift', view_func = admin_interaction.insert_info_shift, methods = ['POST'])
        self.app.add_url_rule('/aiinfo_post', view_func = admin_interaction.insert_info_post, methods = ['POST'])
        self.app.add_url_rule('/aiinfo_stay', view_func = admin_interaction.insert_info_stay, methods = ['POST'])
        self.app.add_url_rule('/adinfo_hotel', view_func = admin_interaction.delete_info_hotel)
        self.app.add_url_rule('/adinfo_room', view_func = admin_interaction.delete_info_room)
        self.app.add_url_rule('/adinfo_guest', view_func = admin_interaction.delete_info_guest)
        self.app.add_url_rule('/adinfo_staff', view_func = admin_interaction.delete_info_staff)
        self.app.add_url_rule('/adinfo_shift', view_func = admin_interaction.delete_info_shift)
        self.app.add_url_rule('/adinfo_stay', view_func = admin_interaction.delete_info_stay)
        self.app.add_url_rule('/adinfo_post', view_func = admin_interaction.delete_info_post)
        self.app.add_url_rule('/auinfo_guest', view_func = auth.control_guest)
        self.app.add_url_rule('/auinfo_staff', view_func = auth.control_staff)
        self.app.add_url_rule('/auinfo_admin', view_func = auth.control_admin)

    def get_home(self):
        return render_template('client.html')

    def run_server(self):
        self.server = threading.Thread(target = self.app.run, kwargs = {'host': self.host, 'port': self.port})
        self.server.start()
        return self.server

    def shutdown(self):
        terminate_func = request.environ.get('werkzeug.server.shutdown')
        if terminate_func:
            terminate_func()

    def shutdown_server(self):
        request.get(f'http://{self.host}:{self.port}/shutdown')

if __name__ == '__main__':
    server = Server(SHost, SPort)
    server.run_server()
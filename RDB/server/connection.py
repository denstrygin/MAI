from sqlalchemy.orm import sessionmaker
from sqlalchemy import create_engine

from config import user, password, DBName, DBHost, DBPort

class PostgresConnection:
    def __init__(self, dbhost, user, password, dbname, dbport):
        self.user = user
        self.password = password
        self.dbname = dbname
        self.dbhost = dbhost
        self.dbport = dbport
        self.connection = self.get_connection()
        
        session = sessionmaker(
            bind = self.connection.engine,
            autocommit=True,
            autoflush=True,
            enable_baked_queries=False,
            expire_on_commit=True
        )

        self.session = session()
    
    def get_connection(self):
        engine = create_engine(
            f'postgresql+psycopg2://{self.user}:{self.password}@{self.dbhost}:{self.dbport}/{self.dbname}',
            encoding = 'utf8'
        )
        return engine.connect()

    def execute_query(self, query):
        res = self.connection.execute(query)
        return res
    
if __name__ == '__main__':
    postgre = PostgresConnection(
        user = user,
        password = password,
        dbname = DBName,
        dbhost = DBHost,
        dbport = DBPort
    )
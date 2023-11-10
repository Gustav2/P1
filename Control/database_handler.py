import sqlite3
import time


class DatabaseHandler:
    def __init__(self, db_name):
        self.db_name = db_name
        self.con = sqlite3.connect(self.db_name, check_same_thread=False)
        self.cursor = self.con.cursor()

    def create_db(self):
        self.cursor.execute('''CREATE TABLE IF NOT EXISTS sensor_data
            (uid text, topic text, value text, timestamp text)''')
        self.con.commit()

    def insert_data(self, uid, topic, value, timestamp):
        self.cursor.execute("INSERT INTO sensor_data VALUES (?, ?, ?, ?)", (uid, topic, value, timestamp))
        self.con.commit()

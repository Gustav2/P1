import sqlite3


class DatabaseHandler:
    def __init__(self, db_name):
        self.db_name = db_name
        self.con = sqlite3.connect(self.db_name, check_same_thread=False)
        self.cursor = self.con.cursor()

    def create_db(self):
        self.cursor.execute('''CREATE TABLE IF NOT EXISTS sensor_data
            (uid text, topic text, value text, timestamp text)''')
        self.cursor.execute('''CREATE TABLE IF NOT EXISTS sensors_subscribed (topic text UNIQUE, type text)''')
        self.con.commit()

    def insert_data(self, uid, topic, value, timestamp):
        self.cursor.execute(
            "INSERT INTO sensor_data VALUES (?, ?, ?, ?)", (uid, topic, value, timestamp))
        self.con.commit()

    def add_sensor(self, topic, type):
        self.cursor.execute(
            "INSERT INTO sensors_subscribed VALUES (?, ?)", (topic, type))
        self.con.commit()

    def get_all_sensors(self):
        self.cursor.execute("SELECT * FROM sensors_subscribed")
        return self.cursor.fetchall()


if __name__ == '__main__':
    db = DatabaseHandler("main.db")
    print(db.get_all_sensors())

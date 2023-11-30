import sqlite3


class DatabaseHandler:
    def __init__(self, db_name):
        self.db_name = db_name
        self.con = sqlite3.connect(self.db_name, check_same_thread=False)
        self.cursor = self.con.cursor()

    def create_db(self):
        self.cursor.execute('''CREATE TABLE IF NOT EXISTS sensor_data 
            (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                uid text, 
                topic text, 
                value text, 
                timestamp datetime
            )
        ''')
        self.cursor.execute('''CREATE TABLE IF NOT EXISTS sensors_subscribed 
            (
                uid text UNIQUE PRIMARY KEY, 
                topic text UNIQUE, 
                type text,
                FOREIGN KEY (uid) REFERENCES sensor_data (uid)
            )
        ''')
        self.con.commit()

    def insert_data(self, uid, topic, value, timestamp):
        self.cursor.execute(
            f"INSERT INTO sensor_data (uid, topic, value, timestamp) VALUES (?, ?, ?, ?)", (uid, topic, value, timestamp))
        self.con.commit()

    def add_sensor(self, uid, topic, sensor_type):
        self.cursor.execute(
            "INSERT INTO sensors_subscribed (uid, topic, type) VALUES (?, ?, ?)", (uid, topic, sensor_type))
        self.con.commit()

    def remove_sensor(self, topic):
        print("Removing sensor", topic)
        self.cursor.execute(
            "DELETE FROM sensors_subscribed WHERE topic=?", (topic,))
        self.con.commit()

    def get_all_sensors(self) -> list[tuple]:
        self.cursor.execute("SELECT * FROM sensors_subscribed")
        return self.cursor.fetchall()


if __name__ == '__main__':
    db = DatabaseHandler("main.db")
    print(db.get_all_sensors())

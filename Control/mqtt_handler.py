import json
import datetime
import sqlite3

import paho.mqtt.client as mqtt
from database_handler import DatabaseHandler


class MQTTHandler:
    def __init__(self):
        self.client = mqtt.Client(client_id="Home")
        self.credentials = None
        self.base_topic = "sensor/"
        self.broker = None
        self.port = None

        self._load_config()
        self.db_handler = DatabaseHandler("main.db")
        self.db_handler.create_db()

    def connect(self):
        self.client.username_pw_set(
            self.credentials["username"], self.credentials["password"])
        self.client.on_message = self._on_message

        self.client.connect(self.broker, self.port)
        self.client.message_callback_add(
            self.base_topic + "#", self._sensor_receive)
        self.client.loop_start()
        self._add_db_sensors()

    def disconnect(self):
        self.client.loop_stop()
        self.client.disconnect()

    def sensor_subscribe(self, topic, qos=2):
        try:
            self.db_handler.add_sensor(topic, self.base_topic + topic, "mode 1")
            self.client.subscribe(self.base_topic + topic, qos)
            return "Successfully subscribed to " + topic
        except sqlite3.IntegrityError:
            return "Sensor already exists - not added"

    def subscribe(self, topic, qos=2):
        self.client.subscribe(topic, qos)

    def unsubscribe(self, topic):
        self.client.unsubscribe(topic)

    def _add_db_sensors(self):
        sensors = self.db_handler.get_all_sensors()
        for sensor in sensors:
            self.client.subscribe(sensor[1], 2)

    def _sensor_receive(self, client, userdata, message):
        if message.retain == 1:
            return
        self.db_handler.insert_data(
            message.topic.split("/")[1], message.topic, message.payload.decode("utf-8"), datetime.datetime.now())

    def _on_message(self, client, userdata, message):
        print("fallback", message.topic, message.payload)

    def _load_config(self):
        with open("config.json") as f:
            data = json.load(f)
            self.credentials = {"username": data["username"], "password": data["password"]}
            self.broker = data["broker"]
            self.port = data["port"]

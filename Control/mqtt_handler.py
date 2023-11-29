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

        self._load_credentials()
        self.db_handler = DatabaseHandler("main.db")
        self.db_handler.create_db()

    def connect(self):
        self.client.username_pw_set(
            self.credentials["username"], self.credentials["password"])
        print("Connecting to broker", self.broker, "on port", self.port)
        print("Client ID:", self.client._client_id)
        print("Credentials:", self.credentials)
        self.client.on_message = self._on_message

        self.client.connect(self.broker, self.port)
        self.client.message_callback_add(
            self.base_topic+"#", self._sensor_receive)
        self.client.loop_start()

    def disconnect(self):
        self.client.loop_stop()
        self.client.disconnect()

    def sensor_subscribe(self, topic, qos=2):
        try:
            self.db_handler.add_sensor(self.base_topic + topic, "topic")
            self.client.subscribe(self.base_topic + topic, qos)
        except sqlite3.IntegrityError:
            print("Sensor already exists")
            return




    def subscribe(self, topic, qos=2):
        self.client.subscribe(topic, qos)

    def _sensor_receive(self, client, userdata, message):
        if message.retain == 1:
            return
        self.db_handler.insert_data(
            message.topic.split("/")[1], message.topic, message.payload.decode("utf-8"), datetime.datetime.now())
        print("Received message: " + str(message.payload.decode("utf-8")) +
              " on topic " + str(message.topic) + " with QoS " + str(message.qos))

    def _on_message(self, client, userdata, message):
        print("fallback", message.topic, message.payload)

    def _load_credentials(self):
        with open("config.json") as f:
            data = json.load(f)
            self.credentials = {"username": data["username"], "password": data["password"]}
            self.broker = data["broker"]
            self.port = data["port"]


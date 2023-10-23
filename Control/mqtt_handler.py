import json
import paho.mqtt.client as mqtt


class MQTTHandler:
    def __init__(self, broker, port):
        self.client = mqtt.Client()
        self.credentials = None
        self.base_topic = None
        self.broker = broker
        self.port = port

        self._load_credentials()

    def connect(self):
        self.client.username_pw_set(self.credentials["username"], self.credentials["password"])
        self.client.on_message = self._on_message

        self.client.connect(self.broker, self.port)
        self.client.loop_start()

    def disconnect(self):
        self.client.loop_stop()
        self.client.disconnect()

    def subscribe(self, topic):
        self.client.subscribe(topic)

    def _on_message(self, client, userdata, message):
        print("message received ", str(message.payload.decode("utf-8")))
        print("message topic=", message.topic)
        print("message qos=", message.qos)
        print("message retain flag=", message.retain)

    def _load_credentials(self):
        with open("credentials.json") as f:
            self.credentials = json.load(f)

import json
import paho.mqtt.client as mqtt


class MQTTHandler:
    def __init__(self, broker, port):
        self.client = mqtt.Client()
        self.credentials = None
        self.base_topic = "sensor/"
        self.broker = broker
        self.port = port

        self._load_credentials()

    def connect(self):
        self.client.username_pw_set(self.credentials["username"], self.credentials["password"])
        self.client.on_message = self._on_message

        self.client.connect(self.broker, self.port)
        self.client.message_callback_add(self.base_topic+"#", self._sensor_receive)
        self.client.loop_start()

    def disconnect(self):
        self.client.loop_stop()
        self.client.disconnect()

    def sensor_subscribe(self, topic, qos=2):
        self.client.subscribe(self.base_topic + topic, qos)

    def subscribe(self, topic, qos=2):
        self.client.subscribe(topic, qos)

    def _sensor_receive(self, client, topic, message):
        print("Received message: " + str(message.payload.decode("utf-8")) + " on topic " + str(message.topic) + "with QoS " + str(message.qos))

    def _on_message(self, client, userdata, message):
        print("fallback", message.topic, message.payload)

    def _load_credentials(self):
        with open("credentials.json") as f:
            self.credentials = json.load(f)

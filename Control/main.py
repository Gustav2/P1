from mqtt_handler import MQTTHandler


def main():
    handler = MQTTHandler("localhost", 2000)
    handler.connect()
    handler.sensor_subscribe("test")
    handler.subscribe("test2")
    handler.subscribe("sensor")
    while True:
        pass


if __name__ == "__main__":
    main()

from mqtt_handler import MQTTHandler


def main():
    handler = MQTTHandler("localhost", 2000)
    handler.connect()
    handler.subscribe("test")
    while True:
        pass


if __name__ == "__main__":
    main()

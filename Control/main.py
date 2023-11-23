from time import sleep

from mqtt_handler import MQTTHandler


def main():
    handler = MQTTHandler("192.168.1.149", 1883)
    handler.connect()
    handler.sensor_subscribe("temp")
    handler.sensor_subscribe("button")
    handler.sensor_subscribe("humidity")
    handler.sensor_subscribe("flowRate")
    handler.sensor_subscribe("flowTotal")
    while True:
        sleep(1)
        pass


if __name__ == "__main__":
    main()

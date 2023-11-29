from flask import Flask

from mqtt_handler import MQTTHandler

app = Flask(__name__)
handler = MQTTHandler()
handler.connect()


def main():
    handler.sensor_subscribe("temp")
    handler.sensor_subscribe("button")
    handler.sensor_subscribe("humidity")
    handler.sensor_subscribe("flowRate")
    handler.sensor_subscribe("flowTotal")
    handler.sensor_subscribe("alive")


@app.route("/")
def hello():
    return "Hello World!"


if __name__ == "__main__":
    main()
    app.run(host="0.0.0.0", port=8080)

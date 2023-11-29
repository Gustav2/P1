from flask import Flask, render_template, request

from mqtt_handler import MQTTHandler

app = Flask(__name__)
handler = MQTTHandler()
handler.connect()


"""def main():
    handler.sensor_subscribe("temp")
    handler.sensor_subscribe("button")
    handler.sensor_subscribe("humidity")
    handler.sensor_subscribe("flowRate")
    handler.sensor_subscribe("flowTotal")
    handler.sensor_subscribe("alive")"""


@app.route("/")
def index():
    return render_template("index.html")


@app.route("/sensor", methods=["GET", "POST"])
def sensor():
    if request.method == "POST":
        handler.sensor_subscribe(request.form["topic"])
        return render_template("sensor_add.html")

    return render_template("sensor_add.html")


if __name__ == "__main__":
    main()
    app.run(host="0.0.0.0", port=8080)

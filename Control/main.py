from flask import Flask, render_template, request, redirect
import requests

from mqtt_handler import MQTTHandler

app = Flask(__name__)
handler = MQTTHandler()
handler.connect()


@app.route("/", methods=["GET", "POST"])
def sensor():
    msg = ""
    if request.method == "POST":
        if request.form["topic"] == "":
            msg = "Topic cannot be empty"
        else:
            msg = handler.sensor_subscribe(request.form["topic"])

    return render_template("sensor_add.html", msg=msg, sensors=handler.db_handler.get_all_sensors())


@app.route("/sensor/<path:text>", methods=["GET"])
def sensor_data(text):
    data = handler.db_handler.get_data(text)
    return render_template("sensor_data.html", data=data, uid=text)


@app.route("/sensor/<path:text>/delete", methods=["POST"])
def unsubscribe(text):
    print(text)
    handler.unsubscribe(handler.base_topic + text)
    handler.db_handler.remove_sensor(handler.base_topic + text)

    return redirect("/")


@app.route("/upload", methods=["GET", "POST"])
def upload():
    if request.method == "POST":
        host = request.form.get("host")
        port = request.form.get("port")
        with open('main.db', 'rb') as f:
            r = requests.post(f'{host}:{port}', files={'main.db': f})
    return render_template("upload.html")


if __name__ == "__main__":
    # main()
    app.run(host="0.0.0.0", port=8080)

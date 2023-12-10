from flask import Flask, request

app = Flask(__name__)


@app.route("/", methods=["POST"])
def index():
    uploaded_file = request.files['main.db']
    uploaded_file.save(uploaded_file.filename)
    return {}


if __name__ == "__main__":
    # main()
    app.run(host="0.0.0.0", port=5000)

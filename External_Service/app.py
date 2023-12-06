from flask import Flask, render_template, request, redirect

app = Flask(__name__)


@app.route("/", methods=["GET", "POST"])
def index():
    if request.method == "POST":
        uploaded_file = request.files['main.db']
        uploaded_file.save(uploaded_file.filename)
        return {}
    return render_template("index.html")


if __name__ == "__main__":
    # main()
    app.run(host="0.0.0.0", port=5000)

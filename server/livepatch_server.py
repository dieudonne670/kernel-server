from flask import Flask, render_template, request, jsonify
import os

app = Flask(__name__)

UPLOAD_FOLDER = "patches"
os.makedirs(UPLOAD_FOLDER, exist_ok=True)

@app.route("/")
def index():
    return render_template("upload.html")

@app.route("/upload", methods=["POST"])
def upload_patch():
    if "patch" not in request.files:
        return jsonify({"error": "No file uploaded"}), 400

    file = request.files["patch"]
    filepath = os.path.join(UPLOAD_FOLDER, file.filename)
    file.save(filepath)

    return jsonify({"message": "Patch uploaded", "file": file.filename})

if __name__ == "__main__":
    app.run(host="0.0.0.0", port=10000)

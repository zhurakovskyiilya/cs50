import cs50
import csv

from flask import Flask, jsonify, redirect, render_template, request

# Configure application
app = Flask(__name__)

# Reload templates when they are changed
app.config["TEMPLATES_AUTO_RELOAD"] = True


@app.after_request
def after_request(response):
    """Disable caching"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/", methods=["GET"])
def get_index():
    return redirect("/form")


@app.route("/form", methods=["GET"])
def get_form():
    return render_template("form.html")


@app.route("/form", methods=["POST"])
def post_form():
    if not request.form.get("name"):
        return render_template("error.html",  message="You must state your name.")

    elif not request.form.get("Last name"):
        return render_template("error.html",  message="You must state your Last name.")

    elif not request.form.get("gender"):
        return render_template("error.html", message="Please choose a gender")

    elif not request.form.get("Username"):
        return render_template("error.html", message="Please choose a username")

    elif not request.form.get("Zip"):
        return render_template("error.html", message="Please choose a zip")
    elif not request.form.get("kids"):
        return render_template("error.html", message="Please choose a kids")

    with open("survey.csv", "a") as file:
        writer = csv.writer(file)
        writer.writerow((request.form.get("name"), request.form.get("Last name"), request.form.get("gender"), request.form.get("Username"), request.form.get("Zip"),
        request.form.get("kids")
        ))
    return redirect("/sheet")



@app.route("/sheet", methods=["GET"])
def get_sheet():
    with open("survey.csv", "r") as file:
        reader = csv.reader(file)
        users = list(reader)
    return render_template("sheet.html", users = users)


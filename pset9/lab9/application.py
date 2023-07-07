import os, re

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session

valid_day = [31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31]

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

app.secret_key = "jamesdasaladadefrutas"

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///birthdays.db")

@app.route("/", methods=["GET", "POST"])
def index():
    if request.method == "POST":
        rows = db.execute("SELECT name, month, day FROM birthdays")

        name = request.form.get("name").strip()
        month = request.form.get("month")
        day = request.form.get("day")

        if re.search(r'[^A-Za-z\s]', name) or name == "":
            message = "ERRO: preencha todos os campos"
            return render_template("index.html", rows=rows, message=message)

        if month == "" or day == "":
            message = "ERRO: preencha todos os campos"
            return render_template("index.html", rows=rows, message=message)
        
        month = int(month)
        day = int(day)

        if month < 1 or month > 12:
            message = "ERRO: mês inválido"
            return render_template("index.html", rows=rows, message=message)

        if day < 1 or day > valid_day[month - 1]:
            message = "ERRO: dia inválido"
            return render_template("index.html", rows=rows, message=message)

        db.execute("INSERT INTO birthdays(name, day, month) VALUES(?, ?, ?)", name, day, month)
        return redirect("/")

    else:
        # TODO: Display the entries in the database on index.html
        rows = db.execute("SELECT name, month, day FROM birthdays")
        return render_template("index.html", rows=rows)
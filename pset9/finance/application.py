import os
from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session # type: ignore
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash
from datetime import datetime
from helpers import apology, login_required, lookup, usd # type: ignore

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True


# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required # Decorator -> usuário deve estar logado para entrar na aplicação
def index():
    """Show portfolio of stocks"""
    inventory = db.execute("SELECT * FROM inventory WHERE user_id = ?", session["user_id"])

    total = 0
    values = []
    for i in range(len(inventory)):
        value = lookup(inventory[i]["quote"])
        value["shares"] = inventory[i]["shares"]
        value["total"] = round(inventory[i]["shares"] * value["price"], 2)
        values.append(value)
        total += value["total"]

    cash = db.execute("SELECT * FROM users WHERE id = ?", session["user_id"])
    cash = round(cash[0]["cash"], 2)
    total += cash
    total = round(total, 2)

    return render_template("index.html", values=values, cash=cash, total=total)


@app.route("/register", methods=["GET", "POST"])
def register():
    """Criar usuário e logar"""
    if request.method == "POST":
        username = request.form.get("username")
        password = request.form.get("password")
        retyped_password = request.form.get("password_retyped")

        if len(db.execute("SELECT username FROM users WHERE username = ?", username)) != 0:
            # flash("Username is already being used")
            return apology("username is already being used", 403)
        elif username == '':
            flash("Invalid username")
            return redirect("/register")
            # return apology("invalid username", 403)
        elif password == '':
            # flash("Invalid username")
            return apology("invalid password", 403)
        elif len(password) < 8: # type: ignore
            # flash("Invalid username")
            return apology("password must be at least 8 characters long and include at least one numeric", 403)
        elif len(password) > 30: # type: ignore
            # flash("Invalid username")
            return apology("password must be a maximum of 30 characters", 403)
        elif retyped_password == '':
            # flash("Invalid username")
            return apology("retype the password", 403)
        elif password != retyped_password:
            # flash("Passwords do not match")
            return apology("passwords do not match", 403)
        else:
            password = generate_password_hash(password) # type: ignore
            db.execute("INSERT INTO users(username, hash) VALUES(?, ?)", username, password)
            rows = db.execute("SELECT * FROM users WHERE username = ?", username)
            session["user_id"] = rows[0]["id"]

        return redirect("/")

    return render_template("register.html")


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""
    session.clear()

    if request.method == "POST":

        if not request.form.get("username"):
            return apology("must provide username", 403)

        elif not request.form.get("password"):
            return apology("must provide password", 403)

        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")): # type: ignore
            return apology("invalid username and/or password", 403)

        session["user_id"] = rows[0]["id"]

        return redirect("/")

    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""
    session.clear()
    return redirect("/")

@app.route("/forgot")
def forgot():
    """aaaa"""
    return apology("desenvolvendo sa pora")

@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        quote = lookup(request.form.get("quote_search"))

        if quote == None:
            return apology("quote not found", 403)
        
        return render_template("quote.html", quote=quote)

    return render_template("quote.html")


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        quote = lookup(request.form.get("quote"))
        shares = request.form.get("shares")

        if quote == None:
            return apology("quote not found", 403)

        if shares == "":
            return apology("invalid shares", 403)
        
        shares = int(shares) # type: ignore 
        if shares <= 0:
            return apology("invalid shares", 403)

        total_price = shares * quote["price"]
        total_price = round(total_price, 2)

        user_cash = db.execute("SELECT * FROM users WHERE id = ?", session["user_id"])
        user_cash = user_cash[0]["cash"]
        if user_cash < total_price:
            return apology("you don't have money for that", 403)
        user_cash = user_cash - total_price

        timestamp = datetime.now()
        timestamp = f"{timestamp.date()} {timestamp.hour}:{timestamp.minute}:{timestamp.second}"
        
        db.execute("UPDATE users SET cash = ? WHERE id = ?", user_cash, session["user_id"])
        db.execute("INSERT INTO history (user_id, quote, shares, unit_price, total_price, timestamp) VALUES (?, ?, ?, ?, ?, ?)", session["user_id"], quote["symbol"], shares, quote["price"], total_price, timestamp)
        
        if len(db.execute("SELECT * FROM inventory WHERE user_id = ? AND quote = ?", session["user_id"], quote["symbol"])) == 0:
            db.execute("INSERT INTO inventory (user_id, quote, shares) VALUES (?, ?, ?)", session["user_id"], quote["symbol"], shares)
        else:
            db.execute("UPDATE inventory SET shares = shares + ? WHERE user_id = ? AND quote = ?", shares, session["user_id"], quote["symbol"])

        return redirect("/")
    
    return render_template("buy.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    inventory = db.execute("SELECT * FROM inventory WHERE user_id = ?", session["user_id"])

    if request.method == "POST":
        quote = request.form.get("quote")
        shares = request.form.get("shares")
        found_quote = False

        for i in range(len(inventory)):
            if inventory[i]["quote"] == quote:
                inventory = inventory[i]
                found_quote = True
                break

        if found_quote == False:
            return apology("invalid quote symbol")
        if shares == "":
            return apology("invalid shares")                 
        if int(shares) > inventory["shares"] or int(shares) <= 0: # type: ignore
            return apology("invalid shares")
        shares = int(shares) # type: ignore

        price = lookup(inventory["quote"])
        total_price = shares * price["price"]
        total_price = round(total_price, 2)

        if price == None:
            return apology("quote not found", 403)

        timestamp = datetime.now()
        timestamp = f"{timestamp.date()} {timestamp.hour}:{timestamp.minute}:{timestamp.second}"
        shares = shares * -1

        db.execute("UPDATE users SET cash = cash + ? WHERE id = ?", total_price, session["user_id"])
        db.execute("INSERT INTO history (user_id, quote, shares, unit_price, total_price, timestamp) VALUES (?, ?, ?, ?, ?, ?)", session["user_id"], inventory["quote"], shares, price["price"], total_price, timestamp)
        
        if inventory["shares"] + shares == 0:
            db.execute("DELETE FROM inventory WHERE user_id = ? AND quote = ?", session["user_id"], inventory["quote"])
        else:
            db.execute("UPDATE inventory SET shares = shares + ? WHERE user_id = ? AND quote = ?", shares, session["user_id"], inventory["quote"])

        return redirect("/")

    return render_template("sell.html", inventory=inventory)


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    rows = db.execute("SELECT * FROM history WHERE user_id = ?", session["user_id"])
    return render_template("history.html", rows=rows)



def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)

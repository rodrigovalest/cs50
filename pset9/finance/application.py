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
    return apology("TODO")


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        quote = lookup(request.form.get("quote"))
        if quote == None:
            return apology("quote not found", 403)
        
        quantity = request.form.get("quantity")
        print(quantity)
        if int(quantity) <= 0 or quantity == "": # type: ignore
            return apology("invalid quantity", 403)    
        quantity = int(quantity) # type: ignore

        total_price = quantity * quote["price"]

        user_cash = db.execute("SELECT * FROM users WHERE id = ?", session["user_id"])
        if user_cash[0]["cash"] < total_price:
            return apology("you don't have money for that", 403)
        user_cash[0]["cash"] = user_cash[0]["cash"] - total_price

        timestamp = datetime.now()
        timestamp = f"{timestamp.date()} {timestamp.hour}:{timestamp.minute}:{timestamp.second}"
        
        db.execute("UPDATE users SET cash = ? WHERE id = ?", user_cash[0]["cash"], session["user_id"])
        db.execute("INSERT INTO history (user_id, quote, quantity, unit_price, total_price, timestamp) VALUES (?, ?, ?, ?, ?, ?)", session["user_id"], quote["symbol"], quantity, quote["price"], total_price, timestamp)
        
        if len(db.execute("SELECT * FROM inventory WHERE user_id = ? AND quote = ?", session["user_id"], quote["symbol"])) == 0:
            db.execute("INSERT INTO inventory (user_id, quote, quantity) VALUES (?, ?, ?)", session["user_id"], quote["symbol"], quantity)
        else:
            db.execute("UPDATE inventory SET quantity = quantity + ? WHERE user_id = ? AND quote = ?", quantity, session["user_id"], quote["symbol"])

        return redirect("/")
    
    return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    rows = db.execute("SELECT * FROM history WHERE user_id = ?", session["user_id"])
    return render_template("history.html", rows=rows)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")): # type: ignore
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""
    session.clear()
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        quote_result = lookup(request.form.get("quote_search"))

        if quote_result == None:
            return apology("quote not found", 403)
        
        return render_template("quote.html", quote_result=quote_result)

    return render_template("quote.html")


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
            # flash("Invalid username")
            return apology("invalid username", 403)
        elif password == '':
            # flash("Invalid username")
            return apology("invalid password", 403)
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


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    return apology("TODO")


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)

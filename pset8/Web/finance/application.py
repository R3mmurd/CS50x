import os
from datetime import datetime

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

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
@login_required
def index():
    """Show portfolio of stocks"""
    user = db.execute("SELECT * FROM users WHERE id = :id", id=session['user_id'])[0]
    purchases = db.execute(
        "SELECT stock_symbol, shares FROM stocks WHERE user_id = :user_id",
        user_id=user["id"]
    )

    rows = []

    for purchase in purchases:
        stock = lookup(purchase["stock_symbol"])
        rows.append({
            "symbol": stock["symbol"],
            "name": stock["name"],
            "shares": purchase["shares"],
            "price": usd(stock["price"]),
            "total": usd(stock["price"] * purchase["shares"])
        })
    return render_template("index.html", rows=rows, cash=usd(user["cash"]))


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == 'POST':
        # Ensure symbol was submitted
        if not request.form.get("symbol"):
            return apology("must provide stock's symbol")
        
        # Ensure shares was submitted
        if not request.form.get("shares"):
            return apology("must provide number of shares")

        # Ensure that shares is a positive integer
        try:
            shares = int(request.form["shares"])

            if shares <= 0:
                raise ValueError

        except ValueError:
            return apology("Number of shares must an integer value greater than zero")

        # Ensure that stock exists
        stock = lookup(request.form["symbol"])
        if stock is None:
            return apology("Stock not found", 404)

        # Search user
        user = db.execute("SELECT * FROM users WHERE id = :id", id=session['user_id'])[0]
        
        # Total price to pay
        total_price = shares * stock["price"]

        # Ensure that user can afford with that numbers of shares
        if total_price > user["cash"]:
            return apology("You cannot afford that number of shares of stock")

        # Search stock
        stocks = db.execute("SELECT * FROM stocks WHERE stock_symbol = :symbol", symbol=stock["symbol"])      

        if not stocks:
            # Add the stock
            stock_id = db.execute(
                "INSERT INTO stocks (stock_symbol, user_id, shares) VALUES (:symbol, :user_id, :shares)",
                symbol=stock["symbol"], user_id=user["id"], shares=shares
            )
        else:
            # Update the stock
            stock_id = stocks[0]["id"]
            db.execute(
                "UPDATE stocks SET shares = :shares WHERE id = :stock_id",
                shares=stocks[0]["shares"] + shares, stock_id=stock_id
            )
        # Create the new transaction
        db.execute(
            "INSERT INTO transactions (stock_id, shares, price, datetime, type) VALUES (:stock_id, :shares, :price, :now, :type)",
            stock_id=stock_id, shares=shares, price=stock["price"], now=datetime.now().isoformat(' '), type='purchase'
        )
        # Update user cash
        db.execute("UPDATE users set cash=:remaining WHERE id = :user_id", remaining=user["cash"] - total_price, user_id=user["id"])
        return redirect("/")
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    query = """
        SELECT stocks.stock_symbol AS symbol, transactions.datetime AS datetime,
        transactions.shares AS shares, transactions.price AS price, transactions.type AS type
        FROM transactions
        INNER JOIN stocks ON transactions.stock_id = stocks.id
        WHERE stocks.user_id = :user_id
    """
    transactions = db.execute(query, user_id=session["user_id"])

    rows = []

    for transaction in transactions:
        stock = lookup(transaction["symbol"])
        rows.append({
            "transaction": transaction["type"],
            "datetime": datetime.fromisoformat(transaction["datetime"]).strftime("%b %d, %Y %I:%M:%S"),
            "symbol": transaction["symbol"],
            "name": stock["name"],
            "shares": transaction["shares"],
            "price": usd(transaction["price"]),
            "total": usd(transaction["shares"] * transaction["price"])
        })

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
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
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

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    if request.method == 'POST':
        # Ensure symbol was submitted
        if not request.form.get("symbol"):
            return apology("must provide stock's symbol")
        
        stock = lookup(request.form["symbol"])

        if stock is None:
            return apology("Stock not found", 404)

        stock["price"] = usd(stock["price"])
        return render_template("quoted.html", stock=stock)
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == 'POST':
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username")

        # Ensure password was submitted
        if not request.form.get("password"):
            return apology("must provide password")

        # Ensure confirmation was submitted
        if not request.form.get("confirmation"):
            return apology("must provide password confirmation")

        # Ensure that password and confirmation are equal
        if request.form["password"] != request.form["confirmation"]:
            return apology("Password and password confirmation do not match")

        # Insert the user and redirect to login
        db.execute(
            "INSERT INTO users (username, hash) VALUES (:username, :hash)",
            username=request.form["username"],
            hash=generate_password_hash(request.form["password"])
        )
        return redirect("/")

    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == 'POST':
        # Ensure symbol was submitted
        if not request.form.get("symbol"):
            return apology("must provide stock's symbol")
        
        # Ensure shares was submitted
        if not request.form.get("shares"):
            return apology("must provide number of shares")

        # Ensure that shares is a positive integer
        try:
            shares = int(request.form["shares"])

            if shares <= 0:
                raise ValueError

        except ValueError:
            return apology("Number of shares must an integer value greater than zero")
        
        # Ensure that stock exists
        stock = lookup(request.form["symbol"])
        if stock is None:
            return apology("Stock not found", 404)

        # Search user
        user = db.execute("SELECT * FROM users WHERE id = :id", id=session['user_id'])[0]

        # Ensure that user owns shares of the stock
        stocks = db.execute(
            "SELECT * FROM stocks WHERE stock_symbol = :symbol AND user_id = :user_id",
            symbol=stock["symbol"], user_id=user["id"]
        )
        if not stocks:
            return apology("You do not have shares of that stock")

        # Ensure that user have enough shares
        if shares > stocks[0]["shares"]:
            return apology("You do not have enough shares to sell")
        
        # Total price
        total_price = shares * stock["price"]

        # Update the stock
        db.execute(
            "UPDATE stocks SET shares = :shares WHERE id = :stock_id",
            shares=stocks[0]["shares"] - shares, stock_id=stocks[0]["id"]
        )

        # Create the new transaction
        db.execute(
            "INSERT INTO transactions (stock_id, shares, price, datetime, type) VALUES (:stock_id, :shares, :price, :now, :type)",
            stock_id=stocks[0]["id"], shares=shares, price=stock["price"], now=datetime.now().isoformat(' '), type='sale'
        )
        # Update user cash
        db.execute("UPDATE users set cash=:new_value WHERE id = :user_id", new_value=user["cash"] + total_price, user_id=user["id"])
        return redirect("/")
    else:
        return render_template("sell.html")


@app.route("/add_cash", methods=['GET', 'POST'])
@login_required
def add_cash():
    if  request.method == 'POST':
        # Ensure shares was submitted
        if not request.form.get("cash"):
            return apology("must provide cash")

        # Ensure that cash is a positive float
        try:
            cash = float(request.form["cash"])

            if cash <= 0:
                raise ValueError

        except ValueError:
            return apology("Cash must a real value greater than zero")

        # Search user
        user = db.execute("SELECT * FROM users WHERE id = :id", id=session['user_id'])[0]
        # Update the user cash
        db.execute("UPDATE users set cash=:new_value WHERE id = :user_id", new_value=user["cash"] + cash, user_id=user["id"])
        
        return redirect("/")
    else:
        return render_template("add_cash.html")


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)

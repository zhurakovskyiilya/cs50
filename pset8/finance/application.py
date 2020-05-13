import os

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


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    #if request.method == "GET":
        #Выбрать знак акции,и кол-во акции которые пренадлежат id
        #stocks_shares = db.execute("SELECT symbol, shares FROM total WHERE id=:id ORDER BY symbol",
                                    #id=session["user_id"])
    #return render_template("index.html")
    #return redirect(url_for("index.html"))
    return apology("TODO")



@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":

        if not request.form.get("symbol"):
            return apology("Missing symbol")

        elif not request.form.get("shares"):
            return apology("Missing shares")
        # Проверка поля внутри формы, число или нет.
        elif not request.form.get("shares").isdigit():
            return apology("Please chose integer")
        # проверка числа на позитивность.
        elif int(request.form.get("shares")) < 1:
            return apology("number of stocks is less zero", 400)

        # проверка цены по символу
        symbol = request.form.get("symbol")
        quote = lookup(symbol)
        # Проверка на валидность символа
        if quote == None :
            return apology("The stock does not exist", 400)
        # Сохраняем цену данного символа в переменную
        price = quote["price"]
        # Вибираем кеш пользователя из базы данных.
        cash = db.execute("SELECT cash FROM users WHERE id=:id", id=session["user_id"])
        # цену символа умножаем на число пользователя, если оно больше чем бюджет,вернуть apology
        if float(price) * int(request.form.get("shares")) > float(cash[0]["cash"]):
                return apology("You don't have enough cash", 400)
        #
        else:
            #  обновляем кеш
            rows3 = db.execute("UPDATE users SET cash =:update_cash WHERE id=:id", update_cash = float(cash[0]["cash"]) - (float(price)*int(request.form.get("shares"))), id=session["user_id"])
            # Вибираем в портфеле все символы, для проверки на наличие shares (кол-во) акций
            rows2 = db.execute("SELECT * FROM portfolio WHERE id=:id AND symbol=:symbol",id=session["user_id"], symbol=symbol )
            # Если нету shares в определенном символе,тогда добавить.
            if len(rows2) == 0:
                db.execute("INSERT INTO partfolio ( id, symbol, shares) VALUES (:id, :symbol, :shares)",id=session["user_id"] )
            else:
            #Если есть уже кол-во акций,тогда обновить старое кол-во на новое кол-во.
                db.execute("UPDATE partfolio SET shares= shares + :shares",shares = shares)


    else:

        return render_template("buy.html")


@app.route("/check", methods=["GET"])
def check():
    """Return true if username available, else false, in JSON format"""
    return jsonify("TODO")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    return apology("TODO")


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
    """Get stock quote."""
    if request.method == "POST":

        if not request.form.get("symbol"):
            return apology("please provide symbol",400)

        symbol = request.form.get("symbol").upper()

        quote = lookup(symbol)

        if quote == None:
            return apology("Invalid symbol")

        return render_template("quoted.html", name=quote["name"], symbol=symbol, price=quote["price"])

    else:
        # если метод Get
        return render_template("quote.html")



@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    session.clear()
    # если метод POST
    if request.method == "POST":
        # запрос имени
        username = request.form.get("username")
        if not username:
            return apology("please provide username",400)
         # Запрос пароля
        password = request.form.get("password")
        if not password:
                return apology("must provide password", 400)
        # запрос подтверждения пароля
        confirmation = request.form.get("confirmation")
        # Если пароль потверждение не сопадает с паролем,извинение.
        if password != confirmation:
               return apology("Password doesn't match")

        # защита пароля, хеширование пароля на екране.
        hashpass = generate_password_hash(password)

        #Проверка имени на оригинальность в базе данных.
        result = db.execute("SELECT username FROM users WHERE username=:username",
                            username=request.form.get("username"))
        # Если имея совпадает тогда 400
        if result:
            return apology("Username already exists")

        #Добавление пароля и имени, защита пароля
        rows = db.execute("INSERT INTO users (username, hash) VALUES (:username, :hash)", username=request.form.get("username"),hash = hashpass)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        #if len(rows) != 1 or not pwd_context.verify(request.form.get("password"), rows[0]["hash"]):
            #return apology("invalid username and/or password", 403)

        # Открыть cash ползователя из базы данных, найти его по id
        #cash = db.execute("SELECT cash FROM users WHERE id=:id", id=session["user_id"])

        #запомнить пользователя, при входе.
        session["user_id"] = rows[0]["id"]


     #Redirect user to home page
        #return render_template("index.html", cash=cash[0]["cash"], budget=cash[0]["cash"])
        return redirect("/")
    else:
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

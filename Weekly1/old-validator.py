# PASSWORD VALIDATOR TEMPLATE: REPLACE THIS LINE WITH YOUR FILE HEADER
import string
from random import randint, shuffle


def validate(password):
    inv1 = 0
    inv2 = 0
    sec1 = 0
    sec2 = 0
    sec3 = 0
    sec4 = 0
    sec5 = 0
    i = 0
    j = 0
    specChar = string.punctuation
    password = input(password)
    if len(password) < 8:
        inv1 = 1
    for x in password:
        if x == '-' or x == '_' or x == ' ':
            inv2 = 1
    if len(password) >= 8:
        sec1 = 1
    for y in password:
        if (y.isupper()) == 1:
            sec2 = 1
    for z in password:
        if (z.islower()) == 1:
            sec3 = 1
    for v in password:
        if (v.isdigit()) == 1:
            sec4 = 1
    for w in password:
        if w == specChar[i]:
            sec5 = 1
            i = i + 1
    if inv1 == 1 or inv2 == 1:
        print('invalid')
    elif sec1 == sec2 == sec3 == sec4 == sec5 and inv1 == inv2 == 0:
        print('secure')
    else:
        print('insecure')

    pass


def generate(n):
    Char1 = 0
    Char2 = 0
    Char3 = 0
    Char4 = 0
    j = 0
    specChar = list(string.punctuation)
    upChar = string.ascii_uppercase
    lowChar = string.ascii_lowercase
    digChar = list(string.digits)
    del specChar[12]
    del specChar[25]
    Password = ('')
    n = int(input(n))
    while int(n) < 8:
        print('Try again')
        n = int(input('Enter a integer greater than 7: '))
    while j < n:
        randUpper = randint(0, 25)
        randLower = randint(0, 25)
        randSpecChar = randint(0, 29)
        randDigit = randint(0, 9)
        Char1 = digChar[randDigit]
        Password = Password + str(Char1)
        j = j + 1
        if j == n:
                break
        Char2 = specChar[randSpecChar]
        Password = Password + str(Char2)
        j = j + 1
        if j == n:
                break
        Char3 = upChar[randUpper]
        Password = Password + str(Char3)
        j = j + 1
        if j == n:
                break
        Char4 = lowChar[randLower]
        Password = Password + str(Char4)
        j = j + 1
        if j == n:
                break
    Pass = list(Password)
    shuffle(Pass)
    Password = ''.join(Pass)
    # https://stackoverflow.com/questions/2668312/shuffle-string-in-python
    # the three lines of code above were taken from Mike Byers' answer.  Thank
    #  you to Mike for helping me finish this weekly assignment
    print('Your new, secure password is: ' + Password)
    pass


if __name__ == "__main__":
    # Any code indented under this line will only be run
    # when the program is called directly from the terminal
    # using "python3 validator.py". This can be useful for
    # testing your implementations by calling them here.

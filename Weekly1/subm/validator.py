# Name: Ryan Brooks
# ID: 1530605
# Course: CKPUT 274 fall 2018
# assignment: Weekly exercise 1: password validator
# two section in this code were taken from stack overflow.
# credit was given when those lines of code appear.
import string
from random import randint, shuffle


def validate(password):
    # takes in a password of user determined length and character style
    # determines if it is secure, insecure, or invalid based on a series
    # of tests and then outputs secure, insecure, or invalid based on the
    # result of those tests.

    # pre creating variables
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
    # the first 2 statements are to test if a password is invalid
    # using if statements and for loops
    if len(password) < 8:
        inv1 = 1
    for x in password:
        if x == '-' or x == '_' or x == ' ':
            inv2 = 1
    # the next 5 if, while, and for statements are tests to determine
    # if a password is secure
    if len(password) >= 8:
        sec1 = 1
    for y in password:
        if (y.isupper()) == 1:
            sec2 = 1
    for z in password:
        if (z.islower()) == 1:
            sec3 = 1
    while j < len(password):
        j = j + 1
        for v in password:
                if (v.isdigit()) == 1:
                        sec4 = 1
    if any(w in password for w in specChar):
        # https://stackoverflow.com/questions/9884958/
        # check-special-character-in-string
        # THanks to eumiro for the 1 line of code above to fix my issue with
        # the special character checking.
        sec5 = 1
    # using logical statements and the previous test variables
    # to determine if invalid, secure, or insecure should be printed
    if inv1 == 1 or inv2 == 1:
        Result = 'Invalid'
        return Result
    elif sec1 == sec2 == sec3 == sec4 == sec5 == 1 and inv1 == inv2 == 0:
        Result = 'Secure'
        return Result
    else:
        Result = 'Insecure'
        return Result

    pass


def generate(n):
    # takes in an integer values that the user can determine and then creates
    # a randomly generated, secure password of said length and outputs it.
    # if the user enters a value less than 8 the function outputs Try again
    # and prompts the user to enter a value greater than or equal to 8.

    # pre creating variables
    Char1 = 0
    Char2 = 0
    Char3 = 0
    Char4 = 0
    j = 0
    specChar = list(string.punctuation)
    upChar = string.ascii_uppercase
    lowChar = string.ascii_lowercase
    digChar = list(string.digits)
    # deleting the _ and - from the string.punctuation list
    del specChar[12]
    del specChar[25]
    Password = ('')
    # prompt for input
    # if the user inputs a value of less then 8 the user is prompted again
    # to enter a value
    if n < 8:
        return 'Try again'
    # creating the password with completely random picks
    # using randint and lists as well as string appending
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
    # shuffling the values in the generated password
    # to make the password even more random
    Pass = list(Password)
    shuffle(Pass)
    Password = ''.join(Pass)
    # https://stackoverflow.com/questions/2668312/shuffle-string-in-python
    # the three lines of code above were taken from Mike Byers' answer.  Thank
    #  you to Mike for helping me finish this weekly assignment
    newPass = 'Your new, secure password is: ' + Password
    return newPass
    pass


if __name__ == "__main__":
    pass
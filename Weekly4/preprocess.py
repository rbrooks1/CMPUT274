'''
Name: Ryan Brooks
ID: 1530605
Course: CKPUT 274 fall 2018
assignment: Weekly exercise 4: Word preprocessing
'''

import sys
import string


def modeDetermine():
    # this function takes arguments from the command line
    # in the terminal and returns the second list element
    # (index 1) which is the mode that is to be used
    # if too many or too few arguments are passed this function
    # prints an error meessage and then exits the program
    mode = []
    # the three lines below are hard-coded to shorten the elif statement
    # as if I did not do so it would be too long and cause a style error
    # which if I triedto fix the style error would produce a syntax error
    a = 'keep-stops'
    b = 'keep-digits'
    c = 'keep-symbols'
    for t in sys.argv:
        mode.append("{}".format(t))
    if len(mode) == 1:
        useMode = 'noMode'
        return(useMode)
    elif mode[1] == b or mode[1] == a or mode[1] == c:
        useMode = mode[1]
        print(useMode)
        return (useMode)
    else:
        print(str(mode[1]) + ' is not a valid mode.')
        print('Please use one of the following as your mode:')
        print('keep-digits, keep-stops, or keep-symbols')
        sys.exit(1)


def takeInput():
    # Function takes input and return a list of said input
    words = input().split()
    return(words)


def makeLower(words):
    # makes all list elements from the input lowercase
    # https://stackoverflow.com/questions/1801668/convert-a-python-list-with-
    # strings-all-to-lowercase-or-uppercase
    # thanks to YOU and paxdiablo for the list comprehension below.
    wordsLower = [word.lower() for word in words]
    return(wordsLower)


# https://stackoverflow.com/questions/4371231/removing-punctuation-from-python-list-items
# the list comprehensions were taken from Mark Byers answer on this page.
# thanks to Mark Byers for the code.
def remPunc(wordsLower):
    # removes all special characters from each list item and removes all
    # empty list elements.
    words = wordsLower
    wordsPunc = [''.join(c for c in s if c not in string.punctuation) for s
                 in words]
    wordsPunc = [s for s in wordsPunc if s]
    return(wordsPunc)


def remDigits(wordsPunc):
    # takes in the list with punctuation removed and removes
    # all digits except if the list element only contains digits
    wordsDig = []
    for i in wordsPunc:
        if i.isdigit() is True:
            wordsDig.append(i)
        elif i.isdigit() is False:
            i = ''.join(j for j in i if not j.isdigit())
            wordsDig.append(i)
    return(wordsDig)


def remStopWords(wordsDig):
    # reads a seperate file that contains all stop words
    # into a list and then checks the list with the 
    # updated input list (after removing punctuation and digits)
    # and proceeds to remove all of the stop words
    processedWords = []
    file = open('stop-words', 'r')
    sentence = file.read()
    file.close()
    stripList = [s.strip() for s in sentence]
    for i in wordsDig:
        if i in sentence:
            pass
        elif i not in sentence:
            processedWords.append(i)
    processedWords = ' '.join(processedWords)
    return(processedWords)


def modeRun(words, useMode):
    # takes in the mode passed in the command line
    # as well as the original input list and based
    # on the mode used runs all other processing
    # functions except for the one the mode asks
    # the program not to run
    if useMode == 'keep-stops':
        a = makeLower(words)
        b = remPunc(a)
        c = remDigits(b)
        processedWords = ' '.join(c)
        return(processedWords)
    elif useMode == 'keep-digits':
        a = makeLower(words)
        b = remPunc(a)
        c = remStopWords(b)
        processedWords = ' '.join(c)
        return(processedWords)
    elif useMode == 'keep-symbols':
        a = makeLower(words)
        b = remDigits(a)
        c = remStopWords(b)
        processedWords = ' '.join(c)
        return(cprocessedWords)


if __name__ == "__main__":
    # Any code indented under this line will only be run
    # when the program is called directly from the terminal
    # using "python3 preprocess.py". This is directly relevant
    # to this exercise, so you should call your code from here.
    Mode = modeDetermine()
    TakeInput = takeInput()
    if Mode == 'noMode':
        lowCaseChar = makeLower(TakeInput)
        puncRem = remPunc(lowCaseChar)
        digRem = remDigits(puncRem)
        finalProcess = remStopWords(digRem)
        print(finalProcess)
    else:
        modeProcess = modeRun(TakeInput, Mode)
        print(modeProcess)

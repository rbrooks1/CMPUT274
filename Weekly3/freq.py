'''
Name: Ryan Brooks
ID: 1530605
Course: CKPUT 274 fall 2018
assignment: Weekly exercise 3: Word Frequency
'''

import sys
from collections import Counter


def filenameDetermine():
    # this function takes arguments from the command line
    # in the terminal and returns the second list element
    # (index 1) which is the file name that is to be opened
    # if too many or too few arguments are passed this function
    # prints an error meessage and then exists the program
    filename = []
    for t in sys.argv:
        filename.append("{}".format(t))
    if len(filename) > 2:
        print('Too many command line arguments')
        print('proper usage: python3 freq.py <input_file_name>')
        print('input_file_name is the name of the file being read')
        sys.exit(1)
    elif len(filename) < 2:
        print('Too few command line arguments')
        print('proper usage: python3 freq.py <input_file_name>')
        print('input_file_name is the name of the file being read')
        sys.exit(1)
    else:
        nameFile = filename[1]
        return (nameFile)


def openFile(nameFile):
    # this function opens the file of a given name from the
    # previous function
    try:
        x = open(nameFile, 'r')
        return(x)
    except IOError:
        print('File open failed: %s' % (nameFile))
        sys.exit(-1)


def readFile(file):
    # this function reads the file opened in the
    # in the previous function and then appends
    # each line to a list
    try:
        sentence = file.readlines()
        file.close()
        stripList = [s.strip() for s in sentence]
        return(stripList)
    except:
        print('File read failed')
        sys.exit(-1)


def listSplit(fileWordList):
    # takes the list created from the read function
    # and then splits it so that each word is its own
    # element in a list
    wordList = []
    newList = ' '.join(fileWordList)
    newList = newList.split()
    for word in newList:
        wordList.append(word)
    return(wordList)


# https://stackoverflow.com/questions/2600191/how-to-count-the-occurrences-of-a-list-item
# thanks to user52028778 and user724266 for the Counter code idea as well as
# the from collections import Counter code
def dictCount(sList):
    # creates a dictionary that counts the frequency of each
    # list element from the list reated in the above function
    # and appends the word as the key and the number of times
    # it occurs as the value
    uDict = Counter(sList)
    uDict = dict(uDict)
    return(uDict)


def sortDict(uDict):
    # Sorts the dictionary created above and appends only the dictionary
    # values to a list sorted in lexicographic order
    # https://www.geeksforgeeks.org/python-sort-python-dictionaries-by-key-or-value/
    # idea for this code came from the above website
    sortedCount = []
    keyList = sorted(uDict)
    for i in sorted(uDict):
        sortedCount.append(uDict[i])
    return(sortedCount)


def createFreq(sortedDict):
    # creates a list of the frequency of each word using the list
    # created above
    i = 0
    k = 0
    freqInt = []
    freqCount = []
    while i < len(sortedDict):
        freqInt.append(sortedDict[i]/len(sortedDict))
        i += 1
    while k < len(freqInt):
        freqCount.append(round(freqInt[k], 3))
        k += 1
    return(freqCount)


def sortedKey(uDict):
    # creates a list of the dictionary keys in lexicographic order
    # only reason for this function is to not return two
    # different values in one function
    keyList = sorted(uDict)
    return(keyList)


def outTable(sortedCount, freqcount, keyList, filename):
    # take all the properly sorted lists and the original filename
    # and write to a new filename, that is the same as the original, but
    # with the .out extension, a table containing each word, it's count,
    # and it's frequency
    try:
        fileOut = open(filename + '.out', 'w')
        j = 0
        while j < len(sortedCount):
            fileOut.write(keyList[j] + ' ' + str(sortedCount[j]) + ' ' +
                          str(freqcount[j]) + '\n')
            j += 1
        fileOut.close()
    except IOError:
        print('file open failed', IOError)
        sys.exit(-1)


if __name__ == "__main__":
    nameFile = filenameDetermine()
    fileopen = openFile(nameFile)
    fileread = readFile(fileopen)
    splitl = listSplit(fileread)
    countdict = dictCount(splitl)
    sortdict = sortDict(countdict)
    frequency = createFreq(sortdict)
    sortkey = sortedKey(countdict)
    outTable(sortdict, frequency, sortkey, nameFile)

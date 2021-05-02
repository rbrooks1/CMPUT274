# Name: Ryan Brooks
# ID: 1530605
# Course: CKPUT 274 fall 2018
# assignment: Weekly exercise 2: Unfair Dice
import random


def biased_rolls(prob_list, s, n):
    # takes in a list of roll probabilities, a seed
    # value and the number of rolls.
    # performs operations to determine which number
    # of a die with len(prob_list) sides rolls
    # based on the probabilities of each number and
    # the seed given.
    # returns a list of each number rolled in the
    # or they were rolled.
    """ Simulate n rolls of a biased m-sided die and return
    a list containing the results.

    Arguments:
        prob_list: a list of the probabilities of rolling the
                   number on each side of the m-sided die. The list
                   will always have the length m (m >= 2), where m is
                   the number of sides numbered 1 to m. Therefore,
                   for example, the probability stored at index 0 in
                   the list is the probability of rolling a 1 on
                   the m-sided die.
        s: the seed to use when initializing the PRNG
        n: the number of rolls to return

    Return:
        rollsList: a list (of length n) containing each of the n rolls of the
               biased die, in the order they were generated.
    """
    # start by precreating a  variable and determining the seed
    # used for the die.
    rollsList = []
    random.seed(s)
    # this loop runs through n rolls and appends a number value to rollsList
    # the variable rolls that was to be returned was changed to rollsList
    # this loop determines which number was rolled by subtracting each value
    # in the prob_list from the randomly generated number until the roll
    # value is <= to 0 and then appends a value of i + 1 to the rollsList.
    for x in range(n):
        roll = random.random()
        i = 0
        while i < len(prob_list):
            roll -= prob_list[i]
            if roll <= 0:
                rolls = i + 1
                rollsList.append(rolls)
                break
            i += 1
    return rollsList
    # return the resulting rolls


def draw_histogram(m, rollsList, width):
    # takes in the sides of a die, the width for a graph, and
    # the list of rolls from the previous function and outputs
    # a histogram(graph) of determined width with asterisks
    # showing the positive rolls and dots(.) showing
    # that a roll didn't occur.
    """ Draws a frequency histogram of the rolls of an m-sided die
    mapped to a fixed width.
    Arguments:
        m (int): the number of sides on the die
        rollsList (list): the list of rolls generated by the biased die
        width (int): the fixed width of the histogram, in characters
                     (this is the length of the longest bar in the
                     histogram, to maximize space in the chart)

    Returns:
        None (but prints the histogram to standard output)
    """
    # pre creating variables, mostly for loops.
    # loop1 was made instead of just l as the style checker thought l was
    # an ambiguous variable.
    j = 0
    k = 0
    loop1 = 0
    p = 0
    z = '*'
    q = '.'
    countList = []
    asterisks = []
    scaleList = []
    # while loop to create the count of each number in rollsList
    while j < len(rollsList):
        y = rollsList.count(j + 1)
        countList.append(y)
        j = j + 1
    # finding the greatest value in the countList to determine how many
    # lines in the histogram are made and to help create scaling.
    maximum = max(countList)
    # this while loop creates the scaleList for scaling to be possible.
    while p < len(countList):
        scale = (countList[p]/maximum)*width
        scaleList.append(scale)
        p = p + 1
    # This while loop creates the asterisks list which determines
    # how many asterisks should be created for each number rolled.
    while k < len(scaleList):
        if scaleList[k] >= width:
            amount = z * width
            asterisks.append(amount)
        else:
            amount = z * int(scaleList[k])
            asterisks.append(amount)
        k = k + 1
    # start printing the histogram
    print('Frequency Histogram: ' + str(m) + '-sided Die')
    # this while loop creates the lines for the amount of rolls for
    # each side of the m sided die and prints them accordingly.
    while loop1 < m:
        w = loop1 + 1
        t = q * (width - len(asterisks[loop1]))
        if len(t) >= width:
            t = ''
        print(str(w) + ': ' + asterisks[loop1] + str(t))
        loop1 = loop1 + 1

    # this function should print to standard output
    # you should not return anything!


if __name__ == "__main__":
    pass
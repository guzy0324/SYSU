# 6.00 Problem Set 3
# 
# Hangman game
#

# -----------------------------------
# Helper code
# You don't need to understand this helper code,
# but you will have to know how to use the functions
# (so be sure to read the docstrings!)

import random
import string

WORDLIST_FILENAME = "words.txt"

def loadWords():
    """
    Returns a list of valid words. Words are strings of lowercase letters.
    
    Depending on the size of the word list, this function may
    take a while to finish.
    """
    print "Loading word list from file..."
    # inFile: file
    inFile = open(WORDLIST_FILENAME, 'r', 0)
    # line: string
    line = inFile.readline()
    # wordlist: list of strings
    wordlist = string.split(line)
    print "  ", len(wordlist), "words loaded."
    return wordlist

def chooseWord(wordlist):
    """
    wordlist (list): list of words (strings)

    Returns a word from wordlist at random
    """
    x=random.choice(wordlist)
    return random.choice(wordlist)

# end of helper code
# -----------------------------------

# Load the list of words into the variable wordlist
# so that it can be accessed from anywhere in the program
wordlist = loadWords()

def isWordGuessed(sW, lG):
    '''
    secretWord: string, the word the user is guessing
    lettersGuessed: list, what letters have been guessed so far
    returns: boolean, True if all the letters of secretWord are in lettersGuessed;
      False otherwise
    '''
    # FILL IN YOUR CODE HERE...
    for i in sW:
        if i not in lG:
            return False
    return True

def getGuessedWord(sW, lG):
    '''
    secretWord: string, the word the user is guessing
    lettersGuessed: list, what letters have been guessed so far
    returns: string, comprised of letters and underscores that represents
      what letters in secretWord have been guessed so far.
    '''
    # FILL IN YOUR CODE HERE...
    rs=''
    for i in sW:
        if i in lG:
            rs+=i
        else:
            rs+='_ '
    return rs

def getAvailableLetters(lG):
    '''
    lettersGuessed: list, what letters have been guessed so far
    returns: string, comprised of letters that represents what letters have not
      yet been guessed.
    '''
    # FILL IN YOUR CODE HERE...
    import string
    vc=string.ascii_lowercase
    for i in lG:
        vc=vc.replace(i,'')
    return vc

    

def hangman(sW):
    '''
    secretWord: string, the secret word to guess.

    Starts up an interactive game of Hangman.

    * At the start of the game, let the user know how many 
      letters the secretWord contains.

    * Ask the user to supply one guess (i.e. letter) per round.

    * The user should receive feedback immediately after each guess 
      about whether their guess appears in the computers word.

    * After each round, you should also display to the user the 
      partially guessed word so far, as well as letters that the 
      user has not yet guessed.

    Follows the other limitations detailed in the problem write-up.
    '''
    # FILL IN YOUR CODE HERE...
    print('Welcome to the game, Hangman!')
    print('I am thinking of a word that is '+str(len(sW))+' letters long.')
    print('-------------')
    print('You have 8 guesses left.')
    print('Available letters: abcdefghijklmnopqrstuvwxyz')
    lG=[raw_input('Please guess a letter: ').lower()]
    if isWordGuessed(sW, lG) is True:
        print('Good guess: '+str(getGuessedWord(sW, lG)))
        print('-------------')
        return('Congratulations, you won!')
    if lG[-1] in sW:
        print('Good guess: '+str(getGuessedWord(sW, lG)))
    else:
        print('Oops! That letter is not in my word:'+' _'*len(sW))
    print('------------')
    i=7
    while i>0:
        print('You have '+str(i)+' guesses left.')
        print('Available letters: '+str(getAvailableLetters(lG)))
        x=raw_input('Please guess a letter: ').lower()
        if x in lG:
            print("Oops! You've already guessed that letter: "+str(getGuessedWord(sW,lG)))
        else:
            lG.append(x)
            if isWordGuessed(sW, lG) is True:
                print('Good guess: '+str(getGuessedWord(sW, lG)))
                print('-------------')
                return('Congratulations, you won!')
            if x in sW:
                print('Good guess: '+str(getGuessedWord(sW, lG)))
            else:
                print('Oops! That letter is not in my word: '+str(getGuessedWord(sW,lG)))
            i-=1
        print('------------')

    return('Sorry, you ran out of guesses. The word was else. The word was '+sW)

# When you've completed your hangman function, uncomment these two lines
# and run this file to test! (hint: you might want to pick your own
# secretWord while you're testing)

secretWord = chooseWord(wordlist).lower()
print(hangman(secretWord))
while True:
    if raw_input('')!='':
        break

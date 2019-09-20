# Ryan Lee
# Title: HelloWorld.py

from datetime import datetime

calen = datetime.now()
sentence = "spaghetti"
upcase = "TUNDRA"
sword = 'Hello New Town'

print("Hello World!")
print("I like to eat bread and fruit.")
print("The %s slayed the %s %s." % ("Knight", "fearsome", "dragon"))
print("There are " + str(2) + " coconuts.")
print('There\'s a village in the distance!')

print(sentence)
print(len(sentence))
print(sentence.upper())
print(upcase.lower())
print(repr(sword))

print(calen)

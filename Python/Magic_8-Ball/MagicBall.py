# Ryan Lee
# Title: MagicBall.py

import sys
import random

ans = True

while ans:

	ask = input("Ask the Magic 8-Ball a question or press enter to quit: ")

	dice = random.randint(1, 20)

	if ask == "":
		sys.exit()
	elif dice == 1:
		print("It is certain.")
	elif dice == 2:
		print("It is decidedly so.")
	elif dice == 3:
		print("Without a doubt.")
	elif dice == 4:
		print("Yes - definitely.")
	elif dice == 5:
		print("You may rely on it.")
	elif dice == 6:
		print("As I see it, yes.")
	elif dice == 7:
		print("Most likely.")
	elif dice == 8:
		print("Outlook good.")
	elif dice == 9:
		print("Yes.")
	elif dice == 10:
		print("Signs point to yes.")
	elif dice == 11:
		print("Reply hazy, try again.")
	elif dice == 12:
		print("Ask again later.")
	elif dice == 13:
		print("Better not tell you now.")
	elif dice == 14:
		print("Cannot predict now.")
	elif dice == 15:
		print("Concentrate and ask again.")
	elif dice == 16:
		print("Don't count on it.")
	elif dice == 17:
		print("My reply is no.")
	elif dice == 18:
		print("My sources say no.")
	elif dice == 19:
		print("Outlook not so good.")
	elif dice == 20:
		print("Very doubtful.")

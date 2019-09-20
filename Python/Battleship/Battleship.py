# Ryan Lee
# Title: Battleship.py

"""
Ideas to place the ships: have the user enter the indexes of the ships, while telling user
which ship it is and the amt. of spaces it occupies. Have to check boundaries then.
Store coordinates in which data structure?
To check the ship conditions: booleans? variables to store indexes and then check said indexes?
"""

from random import randint
import sys

board = []

def board_create(board):
  for x in range(0, 10):
    board.append(["O"] * 10)

def print_board(board):
  for row in board:
    print(" ".join(row))

def random_row(board):
  return randint(0, len(board) - 1)

def random_col(board):
  return randint(0, len(board[0]) - 1)

def place_ships():

def chicken_dinner():
  print("You have destroyed all enemy ships. You win!")

def game_over():
  print("All your ships have been sunk. Game Over!")
  sys.exit()

print_board(board)


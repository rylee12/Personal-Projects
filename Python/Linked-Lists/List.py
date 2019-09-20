# Ryan Lee
# Title: List.py
# Description: This file contains the class definition of a List ADT. It contains the
# necessary constructors and functions needed to create, manipulate, maintain, and delete
# a List ADT.

class List:
	class Node:
		def __init__(self, data, next = None, prev = None):
			self.data = data
			self.next = next
			self.prev = prev
	
	def __init__(self):
		self.front = None
		self.back = None
		self.cursor = None
		self.length = 0
		self.index = -1
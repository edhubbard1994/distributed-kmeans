import random
import os

MIN = 1
MAX = 200
DATA_SIZE = 10000000

with open("data.txt", "a+") as file:
	for i in range(DATA_SIZE):
		num = random.randint(MIN, MAX)
		file.write(str(num))
		file.write("\n")
	

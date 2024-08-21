from random import randint

try:
	width = int(input("Enter the width of the map: "))
	height = int(input("Enter the height of the map: "))
	walls = int(input("Enter the ratio /100 of walls: "))
	collectibles = int(input("Enter the number of collectibles: "))
	monsters = int(input("Enter the number of monsters: "))
	rd_player = int(input("Do you want to place the player randomly? (1 for yes, 0 for no): "))
	rd_exit = int(input("Do you want to place the exit randomly? (1 for yes, 0 for no): "))
	auto_save = int(input("Do you want to save the map to a file? (1 for yes, 0 for no): "))
except ValueError:
	print("Please enter a valid number.")
	exit()



if width < 1 or height < 1:
	print("Please enter a valid number.")
	exit()

if width > 50 or height > 50:
	print("The map is too big.")
	exit()

if walls < 0 or walls > 100:
	print("Please enter a valid number for walls.")
	exit()

if collectibles < 0:
	print("Please enter a valid number for collectibles.")
	exit()

if monsters > 5:
	print("Too many monsters.")
	exit()

if rd_player != 0 and rd_player != 1:
	print("Please enter a valid number for spawning the player.")
	exit()

if rd_exit != 0 and rd_exit != 1:
	print("Please enter a valid number for spawning the exit.")
	exit()

if auto_save != 0 and auto_save != 1:
	print("Please enter a valid number for saving the map.")
	exit()

class Map:
	GROUND = "0"
	WALL = "1"
	COLLECTIBLE = "C"
	EXIT = "E"
	PLAYER = "P"
	MONSTER = "M"

	def __init__(self, width, height):
		self.width = width
		self.height = height
		self.map = [[Map.GROUND for x in range(width)] for y in range(height)]
		#border
		for x in range(width):
			self.map[0][x] = Map.WALL
			self.map[height-1][x] = Map.WALL
		for y in range(height):
			self.map[y][0] = Map.WALL
			self.map[y][width-1] = Map.WALL
	
	def set(self, x, y, value):
		self.map[y][x] = value

	def get(self, x, y):
		return self.map[y][x]
	
	def print(self):
		for y in range(self.height):
			for x in range(self.width):
				print(self.map[y][x], end="")
			print()

	def place_ratio(self, value, ratio):
		for y in range(1, self.height-1):
			for x in range(1, self.width-1):
				if randint(0, 100) < ratio and self.get(x, y) == Map.GROUND:
					self.set(x, y, value)
	def place_random(self, value, number):
		for i in range(number):
			x = randint(1, self.width-2)
			y = randint(1, self.height-2)
			while self.get(x, y) != Map.GROUND:
				x = randint(1, self.width-2)
				y = randint(1, self.height-2)
			self.set(x, y, value)

m = Map(width, height)
m.place_ratio(Map.WALL, walls)
m.place_random(Map.COLLECTIBLE, collectibles)
m.place_random(Map.MONSTER, monsters)
if rd_player:
	m.place_random(Map.PLAYER, 1)
else:
	try:
		x = int(input("Enter the x coordinate of the player: "))
		y = int(input("Enter the y coordinate of the player: "))
	except ValueError:
		print("Please enter a valid number.")
		exit()
	m.set(x, y, Map.PLAYER)
if rd_exit:
	m.place_random(Map.EXIT, 1)
else:
	try:
		x = int(input("Enter the x coordinate of the exit: "))
		y = int(input("Enter the y coordinate of the exit: "))
	except ValueError:
		print("Please enter a valid number.")
		exit()
	m.set(x, y, Map.EXIT)

if auto_save:
	with open("maps/g_map.ber", "w") as f:
		for y in range(m.height):
			for x in range(m.width):
				f.write(m.get(x, y))
			f.write("\n")
else:
	m.print()

import math
def multiply(x, y): 
	if (x < 10  and y < 10):
		return x * y

	#	sizeX = 0; sizeY = 0
	sizeX = len(str(x)); sizeY = len(str(y))
	sizeMax = max(sizeX, sizeY)
	sizeHalf = math.ceil(sizeMax/2)

	a = math.floor(x / pow(10, sizeHalf))
	b = x % pow(10, sizeHalf)
	c = math.floor(y / pow(10, sizeHalf))
	d = y % pow(10, sizeHalf)	
	'''
	
	counter = 0
	temp = x
	b = 0
	while counter < size/2:
		b += temp % 10 * pow(10, counter) 
		temp = temp/10
		counter += 1
	a = temp
	counter = 0
	temp = y
	d = 0
	while counter < size/2:
		d += temp % 10 * pow(10, counter) 
		temp = temp/10
		counter += 1
	c = temp
	print("Hey", x, y)
	print(a, b, c, d)
	'''
	partOne = multiply(a, c)
	partTwo = multiply(b, d)
	partThree = multiply((a + b), (c + d)) - partOne - partTwo
	return int( pow(10, 2*sizeHalf) * partOne + pow(10, sizeHalf) * partThree + partTwo)
	
	

def main():
	x = int(input("Enter the first number:"))
	y = int(input("Enter the second number:"))
	result = multiply(x,y)
	print result

if __name__ == "__main__":
	 main()

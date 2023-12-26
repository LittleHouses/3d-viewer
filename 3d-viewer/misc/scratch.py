def toNDC(val) :
	left = -400
	right = 400

	return (2 * val) / (right - left) - (right + left) / (right - left)


print(toNDC(20))
from random import randint


maxPage = 679
maxoffset = 10
maxLastOffset = 1

f = open('out.txt', 'w')

for x in range(50000000):
	pageNum = randint(0,maxPage)
	
	if pageNum == maxPage:
		offset = randint(0,maxLastOffset)
	else:
		offset = randint(0,maxoffset)

	f.write(str(pageNum)+","+str(offset)+"\n")


f.close()
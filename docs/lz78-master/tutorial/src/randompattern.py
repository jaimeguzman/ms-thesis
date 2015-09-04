import random
import sys

if len(sys.argv) != 3:
	print "Uso: python " + 	sys.argv[0] + " <texto> <salida>"
	sys.exit(0)

f = open(sys.argv[1],"r")
texto = f.read()
largo = len(texto)
aux = 0
g = open(sys.argv[2],"a")
while aux < 10000:
	rand = random.randint(0,largo-4)
	patron = texto[rand:rand+4] + "\n"
	g.write(patron)
	aux += 1

f.close()
g.close()

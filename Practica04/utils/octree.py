class Color(object):
	def __init__(self, red=0, green=0, blue=0):
		self.red = red
		self.green = green
		self.blue = blue

class NodoOctree(object):

	def __init__(self, nivel,padre):	
		#El nodo debe almacenar un color en RGB
		self.color = Color(0,0,0)
		# un contador (parasaber cuantos pixeles tienen ese color) 
		self.cont_pixel = 0
		#un flag para saber si es nodo hoja.
		self.hoja = false
		self.hijos=[0 for _ in range(8)]
	
	def es_hoja():
		#saber si es nodo hoja(no tiene hijos)
		return self.cont_pixel > 0;

	#Lea los pixeles de una imagen
        #Obtenga una suma de la cantidad de píxeles para el nodo y sus hijos
	def get_cantPixeles(self):
		suma = self.contador_pixel
		for i in range(8):
			nodo = self.hijos[i]
			if nodo:
				suma = suma + nodo.cont_pixel
		return 
#Construya el Octree segun el algoritmo explicado en clases.
class Octree(object):
        MAX_DEPTH = 8
	def __init__(self, arg):
		self.niveles={i: [] for i in range(OctreeQuantizer.MAX_DEPTH)}
		self.root = NodoOctree(0,self)

		
		

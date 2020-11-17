import math
import csv
import cv2
import numpy as np
from os import walk, getcwd, path
from matplotlib import pyplot as plt

class Nodo:
    def __init__(self, point, axis, label):
        self.point = point
        self.left = None
        self.right = None
        self.axis = axis
        self.label = label


def build_kdtree(points, dimension, depth=0):
    if len(points) == 0:
        return None

    axis = depth % dimension
    points.sort(key=lambda var: var[0][axis])

    medio = len(points) // 2
    arbol = Nodo(points[medio][0], axis, points[medio][1])
    arbol.left = build_kdtree(points[:medio], dimension, depth+1)
    arbol.right = build_kdtree(points[medio+1:], dimension, depth + 1)
    return arbol


def distance_entre_puntos(point1,point2):
    distance = 0
    #print(type(point1[0]))
    for i in range(len(point1)):
        if type(point1[i]) != tuple:
            distance += pow(point1[i]-point2[i], 2)
        else:
            for j in range(len(point1[i])):
                distance += pow(point1[i][j]-point2[i][j], 2)
    return math.sqrt(distance)


def punto_cercano(point,p1,p2):
    if not p1:
        return p2
    if not p2:
        return p1
    if distance_entre_puntos(point, p1.point) > distance_entre_puntos(point,p2.point):
        return p2
    return p1


def closest_point(node,point):
    if not node:
        return None

    nb = None
    ob = None
    axis = node.axis
    if node.point[axis] > point[axis]:
        nb = node.left
        ob = node.right
    else:
        nb = node.right
        ob = node.left

    best = punto_cercano(point, closest_point(nb, point), node)

    if distance_entre_puntos(best.point, point) > math.fabs(point[axis] - node.point[axis]):
        best = punto_cercano(point,closest_point(ob,point), node)

    return best


def anhdir_elemento(lista,elemento):
    lista.append(elemento)
    lista.sort()


def resta_especial(p1, p2):
    if type(p1) == tuple:
        diff = 0
        for i in range(len(p1)):
            diff += math.fabs(p1[i] - p2[i])
        return math.fabs(diff)
    else:
        return math.fabs(p1 - p2)


def closest_k_point(point_2, node ,lista,cant_puntos):
    if not node:
        return None
    anhdir_elemento(lista, [distance_entre_puntos(point_2, node.point), [node.point, node.label]])
    nb = None
    ob = None
    if node.point[node.axis] > point_2[node.axis]:
        nb = node.left
        ob = node.right
    else:
        nb = node.right
        ob = node.left
    closest_k_point(point_2, nb, lista, cant_puntos)
    diferencia = resta_especial(point_2[node.axis],node.point[node.axis])
    distancia_maxima = lista[len(lista) - 1][0]
    if len(lista) < cant_puntos or diferencia < distancia_maxima:
        closest_k_point(point_2, ob, lista, cant_puntos)


def closest_n_points(node, point_2, cant_puntos):
    p_cercanos = []
    closest_k_point(point_2, node, p_cercanos, cant_puntos)
    p_cercanos.sort()
    answer = p_cercanos[:cant_puntos]
    return answer


def recorrido_arbol(node):
    if not node:
        return


def clasificacion(node, point_2, cant_puntos, estados):
    value = closest_n_points(node, point_2, cant_puntos)
    contador_tipo_a = 0
    contador_tipo_b = 0

    for i in range(len(value)):
        """
        print("-----------------------")
        print(value[i][1][1])
        print("------------------------")
        """
        if value[i][1][1] == estados[0]:
            contador_tipo_a += 1
        else:
            contador_tipo_b += 1

    if contador_tipo_a > contador_tipo_b:
        return estados[0]
    return estados[1]


def utilizando_archivo():
    valores = []
    estados = ['Dead', 'Survived']
    with open('train.csv', newline='') as File:
        reader = csv.reader(File)
        for row in reader:
            if row[2] == 'Pclass':
                continue
            values = []
            for i in range(1, 8):
                if i == 3:
                    continue
                if i == 4:
                    if row[i] == 'male':
                        values.append(1)
                    else:
                        values.append(0)
                    continue
                if row[i] == '':
                    values.append(0)
                    continue
                values.append(row[i])

            extra = list(map(float, values[1:]))
            if values[0] == '0':
                valores.append([extra, 'Dead'])
            elif values[0] == '1':
                valores.append([extra, 'Survived'])

    # acabo lectura de data
    dimension = len(valores[0][0])
    arbol = build_kdtree(valores[:], dimension)

    point_consulta = [3, 1, 34.5, 0, 0]
    print(clasificacion(arbol,point_consulta, int(math.sqrt(len(valores))) + 1, estados))
    point_consulta = [1, 0, 23, 1, 0]
    print(clasificacion(arbol, point_consulta, int(math.sqrt(len(valores))) + 1, estados))

def grafica_histograma(imagen):
    img = cv2.imread(imagen)
    #hsv = cv2.cvtColor(img, cv2.COLOR_BGR2HSV)
    color = ('b', 'g', 'r')
    valores = []
    for i, col in enumerate(color):
        histr = cv2.calcHist([img], [i], None, [12], [0, 256])
        valores.append(list(map(int, histr)))
    answer = []
    for i in range(len(valores[0])):
        answer.append((valores[0][i], valores[1][i], valores[2][i]))
    cv2.destroyAllWindows()
    return answer


def esimagen(extension):
    if extension == '.png':
        return True
    if extension == '.jpg':
        return True
    if extension == '.jpeg':
        return True
    return False


def calcular_histograma(ruta, valores, label):
    dir, subdirs, archivos = next(walk(ruta))
    for archivo in archivos:
        nombre, extension = path.splitext(archivo)
        #print(archivo)
        if esimagen(extension):
            valores.append((grafica_histograma(ruta + archivo), label))


def utilizando_imagenes():
    valores = []
    estados = ['Leon', 'Gorila']
    cwd = getcwd()
    data_leones = '/entrenamiento/leones/'
    data_gorila = '/entrenamiento/gorila/'
    calcular_histograma(cwd + data_leones, valores, "Leon")
    kk = len(valores)
    calcular_histograma(cwd + data_gorila, valores, "Gorila")
    """
    for i in range(kk, len(valores)):
        print(valores[i])
    """
    # acabo lectura de data
    dimension = len(valores[0][0])
    arbol = build_kdtree(valores[:], dimension)
    point_consulta = grafica_histograma(cwd + "/entrenamiento/lion10.png")
    print(clasificacion(arbol,point_consulta, 3, estados))
    point_consulta = grafica_histograma(cwd + "/entrenamiento/20.jpeg")
    print(clasificacion(arbol, point_consulta, 3, estados))


utilizando_archivo()
pp = []
utilizando_imagenes()
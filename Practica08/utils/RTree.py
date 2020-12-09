import os
import pygame
from pygame.locals import *

class Point:
    def __init__(self, x, y, user_data=""):
        self.x = x
        self.y = y
        self.userData = user_data

    def esigual(self, b):
        if b.x == self.x and b.y == self.y:
            return True
        return False

    def __str__(self):
        return str(self.x) + " " + str(self.y)


class Rectangle:
    def __init__(self, x, y, w, h):
        self.x = x
        self.y = y
        self.w = w
        self.h = h

    def contains(self, point):
        if self.x + self.w >= point.x >= self.x - self.w and self.y + self.h >= point.y >= self.y - self.h:
            return True
        return False

    def intersects(self, range):
        if range.x - range.w < self.x + self.w or range.y + range.h > self.y - self.h or range.y - range.h < self.y + self.h or range.x + range.w > self.x - self.w:
            return True
        return False

    def calcular_perimetro(self):
        return 4.0 * self.w + 4.0 * self.h

    def reorganizar_rectangulo(self, b):
        largo = 2.0 * self.w
        distancia_largo = 0
        if b.x < self.x - self.w:
            distancia_largo = b.x - (self.x - self.w)
            largo += ((self.x - self.w) - b.x)

        elif b.x > self.x + self.w:
            distancia_largo = b.x - (self.x + self.w)
            largo += (b.x - self.x + self.w)

        ancho = 2.0 * self.h
        distancia_ancho = 0
        if b.y < self.y - self.h:
            distancia_ancho = b.y - (self.y - self.h)
            ancho += ((self.y - self.h) - b.y)
        elif b.y > self.y + self.h:
            distancia_ancho = b.y - (self.y - self.h)
            ancho += (b.y - self.y + self.h)

        return Rectangle(self.x + (distancia_largo / 2), self.y + (distancia_ancho / 2), largo / 2, ancho / 2)

    def esigual(self, a):
        if a.x == self.x and a.y == self.y and a.w == self.w and a.h == self.h:
            return True
        return False

    def pasar_info(self, b):
        b.x = self.x
        b.y = self.y
        b.w = self.w
        b.h = self.h

    def contains_rectangle(self, a):
        if a.x - a.w < self.x - self.w:
            return False
        if a.x + a.w > self.x + self.w:
            return False
        if a.y - a.h < self.y - self.h:
            return False
        if a.y + a.h > self.y + self.h:
            return False
        return True


    def __str__(self):
        return str(self.x) + " " + str(self.y)

class Nodo:
    def __init__(self, B, parent=None):
        self.B = B
        self.child_nodes = []
        self.points = []
        self.padre = parent

    def is_overflow(self):
        if len(self.points) > self.B:
            return True
        return False

    def isroot(self):
        if self.padre:
            return False
        return True

    def isleaf(self):
        if len(self.child_nodes) == 0:
            return True
        return False

    def choose_subtree(self, b):
        a = None
        pos = 0
        c = Rectangle(0, 0, 0, 0)
        perimetro = 1e10
        for i in range(len(self.points)):
            if self.points[i].contains(b):
                pos = i
                return self.child_nodes[i], c, pos
            else:
                value = self.points[i].reorganizar_rectangulo(b)
                new_perimetro = value.calcular_perimetro()
                if new_perimetro < perimetro:
                    pos = i
                    value.pasar_info(c)
                    perimetro = new_perimetro
                    a = self.child_nodes[i]
        return a, c, pos


def sortX(val):
    return val.x


def sortY(val):
    return val.y


def ordenar_rect_x(a):
    return a.x - a.w


def ordenar_rect_y(a):
    return a.y - a.h



class Cola:
    def __init__(self):
        self.items = []

    def estaVacia(self):
        return self.items == []

    def push(self, item):
        self.items.append(item)

    def avanzar(self):
        return self.items.pop(0)

    def tamano(self):
        return len(self.items)

    def front(self):
        return self.items[0]

class Rtree:
    def __init__(self, B):
        self.capacidad = B
        self.root = Nodo(B)

    def get_root(self):
        return self.root

    def range_query(self, a):
        c = []
        self.range_query_2(self.root, a, c)
        return c

    def range_query_2(self, b, a, c):
        if b.isleaf():
            for i in b.points:
                if a.contains(i):
                    c.append(i)
        else:
            for i in range(len(b.points)):
                if a.intersect(b.points[i]):
                    self.range_query_2(b.child_nodes[i], a, c)


    def generar_graphviz(self):
        texto1 = open("arbol.dot", "w")
        texto1.close()

        texto = open("arbol.dot", "w")
        texto.write('digraph g {\n')
        texto.write("node [shape = record,height=.1];\n")
        values = Cola()
        padres = Cola()
        cantidad = Cola()
        values.push(self.root)
        nombre = "e"
        estado = 0
        node = 0
        helper = 0
        while not values.estaVacia():
            avan = not padres.estaVacia()
            aux = values.front()
            values.avanzar()
            if aux.isleaf():
                texto.write("node"+str(node)+"[label = "+'"')
                node+=1
                for i in range(len(aux.points)):
                    texto.write("<f"+str(i)+"> |("+str(int(aux.points[i].x))+","+str(int(aux.points[i].y))+")|")

                texto.write('"')
                texto.write("];\n")

                if avan:
                    if helper == cantidad.front():
                        padres.avanzar()
                        cantidad.avanzar()
                        helper = 0

                    texto.write('"')
                    texto.write("node" + str(padres.front()))
                    texto.write('"')
                    texto.write(":f" + str(helper) + "-> ")
                    texto.write('"')
                    texto.write("node" +str(node-1))
                    texto.write('"')
                    texto.write("\n")
                    helper+=1
            else:
                texto.write("node"+str(node)+"[label = ")
                node+=1
                texto.write('"')
                for i in range(len(aux.points)):
                    texto.write("<f"+str(i)+"> |"+nombre+str(estado)+"|")
                    estado += 1
                    values.push(aux.child_nodes[i])

                texto.write('"')
                texto.write("];\n")
                if avan:
                    if helper == cantidad.front():
                        padres.avanzar()
                        cantidad.avanzar()
                        helper = 0

                    texto.write('"')
                    texto.write("node" + str(padres.front()))
                    texto.write('"')
                    texto.write(":f"+ str(helper) + "-> ")
                    texto.write('"')
                    texto.write("node" + str(node-1))
                    texto.write('"')
                    texto.write("\n")
                    helper+=1
                padres.push(node-1)
                cantidad.push(len(aux.points))

        texto.write("}\n")
        texto.close()

    def insert(self, p):
        return self.insert2(self.root, p)

    def insert2(self, u, p):
        if u.isleaf():
            u.points.append(p)
            if u.is_overflow():
                self.handle_overflow(u)
        else:
            v, solucion, pos = u.choose_subtree(p)
            v.padre = u
            self.insert2(v, p)
            if not u.points[pos].contains(p):
                solucion.pasar_info((v.padre).points[pos])

    def obtener_rec_points(self, a, estado):
        answer = Rectangle(0, 0, 0, 0)
        if estado:
            answer.w = (a[len(a) - 1].x - a[0].x) / float(2.0)
            answer.x = a[len(a) - 1].x - answer.w
            a.sort(key=sortY)
            answer.h = (a[len(a) - 1].y - a[0].y) / float(2.0)
            answer.y = a[len(a) - 1].y - answer.h

        else:

            answer.h = (a[len(a) - 1].y - a[0].y) / float(2.0)
            answer.y = a[len(a) - 1].y - answer.h
            a.sort(key=sortX)
            answer.w = (a[len(a) - 1].x - a[0].x) / float(2.0)
            answer.x = a[len(a)- 1].x - answer.w
        return answer

    def obtener_rec_rect(self, a):
        answer = Rectangle(0, 0, 0, 0)
        x_min = y_min = 1e9
        x_max = y_max = 0
        for i in range(len(a)):
            if a[i].x - a[i].w < x_min:
                x_min = a[i].x - a[i].w

            if a[i].x + a[i].w > x_max:
                x_max = a[i].x + a[i].w

            if a[i].y + a[i].h > y_max:
                y_max = a[i].y + a[i].h

            if a[i].y - a[i].h < y_min:
                y_min = a[i].y - a[i].h

        answer.w = (x_max - x_min) / float(2.0)
        answer.x = (x_max - answer.w)
        answer.h = (y_max - y_min) / float(2.0)
        answer.y = (y_max - answer.h)
        return answer

    def evaluar_node(self, a, data1, data2, ans1, ans2):
        valor_min = int(0.4 * self.capacidad)
        perimetro_minimo = 1e10 if ans1.calcular_perimetro() + ans2.calcular_perimetro() == 0 else ans1.calcular_perimetro() + ans2.calcular_perimetro()
        for i in range(valor_min, len(a) - valor_min):
            a1 = a[:i]
            a2 = a[i:]
            prueba = self.obtener_rec_rect(a1)
            prueba1 = self.obtener_rec_rect(a2)

            p_prueba = prueba.calcular_perimetro()
            p_prueba1 = prueba1.calcular_perimetro()
            if p_prueba + p_prueba1 < perimetro_minimo:
                perimetro_minimo = p_prueba + p_prueba1
                prueba.pasar_info(ans1)
                prueba1.pasar_info(ans2)
                del data1[:]
                del data2[:]
                for valor in a1:
                    data1.append(valor)
                for valor in a2:
                    data2.append(valor)

    def evaluar_leaf(self, valores, data1, data2, rectangulo1, rectangulo2, estado):
        valor_min = int(0.4 * self.capacidad)
        perimetro_minimo = 1e10 if rectangulo1.calcular_perimetro() + rectangulo2.calcular_perimetro() == 0 else rectangulo1.calcular_perimetro() + rectangulo2.calcular_perimetro()

        for i in range(valor_min, len(valores) - valor_min):
            a1 = valores[:i]
            a2 = valores[i:]
            prueba = self.obtener_rec_points(a1[:], estado)
            prueba1 = self.obtener_rec_points(a2[:], estado)
            p_prueba = prueba.calcular_perimetro()
            p_prueba1 = prueba1.calcular_perimetro()
            if p_prueba + p_prueba1 < perimetro_minimo:
                perimetro_minimo = p_prueba + p_prueba1
                prueba.pasar_info(rectangulo1)
                prueba1.pasar_info(rectangulo2)
                del data1[:]
                del data2[:]
                for valor in a1:
                    data1.append(valor)
                for valor in a2:
                    data2.append(valor)


    def split_leaf(self, a, best1, best2, ans1, ans2):
        a.sort(key=sortX)
        self.evaluar_leaf(a[:], best1.points, best2.points, ans1, ans2, True)
        a.sort(key=sortY)
        self.evaluar_leaf(a[:], best1.points, best2.points, ans1, ans2, False)

    def split_nodos(self, a, best1, best2, a1, a2):
        a.sort(key=ordenar_rect_x)
        self.evaluar_node(a[:], best1.points, best2.points, a1, a2)
        a.reverse()
        self.evaluar_node(a[:], best1.points, best2.points, a1, a2)
        a.sort(key=ordenar_rect_y)
        self.evaluar_node(a[:], best1.points, best2.points, a1, a2)
        a.reverse()
        self.evaluar_node(a[:], best1.points, best2.points, a1, a2)

    def updateMBR(self, actual, father, first, Second, a1, a2):
        pos = 0
        if actual.isleaf():
            for i in range(len(father.points)):
                if (father.points[i]).contains(actual.points[0]):
                    estado = True
                    for j in range(1,len(actual.points)-1):
                        if not (father.points[i]).contains(actual.points[j]):
                            estado = False
                            break

                    if estado:
                        pos = i

            father.points.insert(pos, a2)
            father.points.insert(pos, a1)
            aux = father.child_nodes[pos]
            father.child_nodes.insert(pos, Second)
            father.child_nodes.insert(pos, first)
            Second.padre = father
            first.padre = father
            father.points.pop(pos+2)
            father.child_nodes.pop(pos+2)

        else:

            for i in range(len(father.points)):
                if (father.points[i]).contains_rectangle(actual.points[0]):
                    estado = True
                    for j in range(1, len(actual.points)):
                        if not (father.points[i]).contains_rectangle(actual.points[j]):
                            estado = False
                            break

                    if estado:
                        pos = i

            father.points.insert(pos, a2)
            father.points.insert(pos, a1)
            aux = father.child_nodes[pos]
            father.child_nodes.insert(pos, Second)
            father.child_nodes.insert(pos, first)
            Second.padre = father
            first.padre = father
            for i in range(len(first.points)):
                for j in range(len(aux.points)):
                    if first.points[i].esigual(aux.points[j]):
                        first.child_nodes[i] = aux.child_nodes[j]
                        aux.child_nodes[j] = None
                        break

            for i in range(len(Second.points)):
                for j in range(len(aux.points)):
                    if Second.points[i].esigual(aux.points[j]):
                        Second.child_nodes[i] = aux.child_nodes[j]
                        aux.child_nodes[j] = None
                        break

            father.points.pop(pos + 2)
            father.child_nodes.pop(pos + 2)

    def handle_overflow(self, u):
        best1 = Nodo(self.capacidad)
        best2 = Nodo(self.capacidad)
        ans = Rectangle(0, 0, 0, 0)
        ans1 = Rectangle(0, 0, 0, 0)

        if u.isleaf():
            self.split_leaf(u.points[:], best1, best2, ans, ans1)
        else:
            self.split_nodos(u.points[:], best1, best2, ans, ans1)

        if u.isroot():
            #print(best1.points)
            #print(best2.points)
            #print(ans.x)
            #print(ans1.x)
            new_root = Nodo(self.capacidad)
            new_root.points.append(ans)
            new_root.points.append(ans1)
            new_root.child_nodes.append(best1)
            best1.padre = new_root
            new_root.child_nodes.append(best2)
            best2.padre = new_root
            if len(u.child_nodes) != 0:
                for i in range(len(best1.points)):
                    for j in range(len(u.points)):
                        if best1.points[i].esigual(u.points[j]):
                            best1.child_nodes.insert(i, u.child_nodes[j])
                            break

                for i in range(len(best2.points)):
                    for j in range(len(u.points)):
                        if best2.points[i].esigual(u.points[j]):
                            best2.child_nodes.insert(i, u.child_nodes[j])
                            break

            self.root = new_root

        else:
            padre_u = u.padre
            self.updateMBR(u, padre_u, best1, best2, ans, ans1)
            if padre_u.is_overflow():
                self.handle_overflow(padre_u)


def testing(a):
    b = [4, 8]
    del a[:]
    for k in b:
        a.append(k)


def get_rectangulos(RTREE, v):
    del v[:]
    values = Cola()
    values.push(RTREE.get_root())
    while not values.estaVacia():
        aux = values.front()
        values.avanzar()
        if not aux.isleaf():
            for i in range(len(aux.points)):
                v.append(aux.points[i])
                values.push(aux.child_nodes[i])


WIDTH = 640
HEIGHT = 480

def main():
    B = 3
    extra = Rtree(B)
    screen = pygame.display.set_mode((WIDTH, HEIGHT))
    pygame.display.set_caption("Pruebas Pygame")

    background = pygame.Surface(screen.get_size())
    background = background.convert()
    background.fill((250, 250, 250))
    screen.blit(background, (0, 0))
    pygame.display.flip()
    v_puntos = []
    estado = True
    rectangulos = []
    while estado:
        for eventos in pygame.event.get():
            if eventos.type == QUIT:
                estado = False
                break
        if not estado:
            continue
        if pygame.mouse.get_pressed()[0]:
            coords = pygame.mouse.get_pos()
            color = (0, 0, 0)
            radius = 5
            anhadir = Point(coords[0], coords[1])
            checking = True

            for val in v_puntos:
                if val.esigual(anhadir):
                    checking = False
                    break

            if checking:
                # dibuja el círculo
                extra.insert(anhadir)
                get_rectangulos(extra, rectangulos)
                v_puntos.append(anhadir)
                screen.blit(background, (0, 0))
                for point in v_puntos:
                    pygame.draw.circle(screen, color, (point.x, point.y), radius, 0)

                color_rec = (255, 0, 0)
                width_rec = 1

                for rect in rectangulos:
                    pygame.draw.rect(screen, color_rec, (rect.x - rect.w, rect.y + rect.h, rect.w * 2.0, rect.h * 2.0), width_rec)

                pygame.display.flip()

        if pygame.mouse.get_pressed()[2]:
            screen.blit(background, (0, 0))
            pygame.display.flip()

    pygame.quit()
    print("Paso")
    extra.generar_graphviz()
    os.system('dot arbol.dot -o arbol.png -Tpng -Gcharset=utf8')
    return 0


if __name__ == '__main__':
    pygame.init()
    main()
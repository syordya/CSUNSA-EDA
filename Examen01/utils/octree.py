import vtk

puntos=[]#Arrays de Puntos
actors=[]#Puntos mapeados

def rect(x,y,z,w,h,p,color):
    cube=vtk.vtkCubeSource()
    cube.SetXLength(w)
    cube.SetYLength(h)
    cube.SetZLength(p)
    cube.SetCenter(x,y,z)

    cubeMapper=vtk.vtkPolyDataMapper()
    cubeMapper.SetInputConnection(cube.GetOutputPort())

    cubeActor=vtk.vtkActor()
    cubeActor.GetProperty().SetColor(color[0],color[2],color[1])
    cubeActor.GetProperty().SetOpacity(0.5)
    cubeActor.SetMapper(cubeMapper)
    actors.append(cubeActor)

def punto(x,y,z,color):
    cube=vtk.vtkSphereSource()
    cube.SetRadius(6.0)
    cube.SetCenter(x,y,z)
    cubeMapper=vtk.vtkPolyDataMapper()
    cubeMapper.SetInputConnection(cube.GetOutputPort())
    cubeActor=vtk.vtkActor()
    cubeActor.GetProperty().SetColor(color[0],color[0],color[2])
    cubeActor.SetMapper(cubeMapper)
    puntos.append(cubeActor)

def Pantalla():
    ren = vtk.vtkRenderer()
    for act in puntos:
        ren.AddActor(act)

    for act in actors:
        ren.AddActor(act)

    renWin = vtk.vtkRenderWindow()
    renWin.AddRenderer(ren)
    renWin.SetSize(600, 600)
    iren = vtk.vtkRenderWindowInteractor()
    iren.SetRenderWindow(renWin)
    ren.SetBackground(0,0,0)
    renWin.Render()
    iren.Start()

class Point:
    def __init__(self, x, y, z):
        self.x = x
        self.y = y
        self.z = z

class Rectangulo:
    def __init__(self, x, y, z, w, h, p):
        self.x = x
        self.y = y
        self.z = z
        self.w = w
        self.h = h
        self.p = p

    def cotiene(self, point):
        return point.x >= self.x - self.w and point.x <= self.x + self.w and point.y >= self.y - self.h and point.y <= self.y + self.h and point.z >= self.z - self.p and point.z <= self.z + self.p

    def intersect(self, rango):
        return not (rango.x-rango.w>self.x+self.w or rango.x+rango.w<self.x-self.w or rango.y-rango.h>self.y+self.h or rango.y+rango.h<self.y-self.h or rango.z-rango.p >self.z+self.p or rango.z+rango.p<self.z-self.p)


class Octree:
    def __init__(self, perimetro, n,color=[0,0,1]):
        self.perimetro = perimetro
        self.capacidad = n
        self.points = []
        self.divided = False
        self.color=color

    def Subdividir(self):
        x = self.perimetro.x
        y = self.perimetro.y
        z = self.perimetro.z
        w = self.perimetro.w/2
        h = self.perimetro.h/2
        p = self.perimetro.p/2

        noup = Rectangulo(x-w,y+h,z+p,w,h,p);
        neup = Rectangulo(x+w,y+h,z+p,w,h,p);
        soup = Rectangulo(x-w,y-h,z+p,w,h,p);
        seup = Rectangulo(x+w,y-h,z+p,w,h,p);

        nodw = Rectangulo(x-w,y+h,z-p,w,h,p);
        nedw = Rectangulo(x+w,y+h,z-p,w,h,p);
        sodw = Rectangulo(x-w,y-h,z-p,w,h,p);
        sedw = Rectangulo(x+w,y-h,z-p,w,h,p);

        self.sonNOup = Octree(noup,self.capacidad,[noup.x/254,noup.y/250,self.perimetro.p-noup.z/236])
        self.sonNEup = Octree(neup,self.capacidad,[neup.x/254,neup.y/250,self.perimetro.p-neup.z/236])
        self.sonSOup = Octree(soup,self.capacidad,[soup.x/254,soup.y/250,self.perimetro.p-soup.z/236])
        self.sonSEup = Octree(seup,self.capacidad,[seup.x/254,seup.y/250,self.perimetro.p-seup.z/236])

        self.sonNOdw = Octree(nodw,self.capacidad,[nodw.x/254,nodw.y/250,self.perimetro.p-nodw.z/236])
        self.sonNEdw = Octree(nedw,self.capacidad,[nedw.x/254,nedw.y/250,self.perimetro.p-nedw.z/236])
        self.sonSOdw = Octree(sodw,self.capacidad,[sodw.x/254,sodw.y/250,self.perimetro.p-sodw.z/236])
        self.sonSEdw = Octree(sedw,self.capacidad,[sedw.x/254,sedw.y/250,self.perimetro.p-sedw.z/236])

        self.divided = True



    def Insertar(self, point):
        if not self.perimetro.cotiene(point):
            return
        if len(self.points) < self.capacidad:
            self.points.append(point)
        else:
            if self.divided==False:
                self.Subdividir()
            self.sonNOup.Insertar(point)
            self.sonNEup.Insertar(point)
            self.sonSOup.Insertar(point)
            self.sonSEup.Insertar(point)
            self.sonNOdw.Insertar(point)
            self.sonNEdw.Insertar(point)
            self.sonSOdw.Insertar(point)
            self.sonSEdw.Insertar(point)



    def query(self,rango,found):
        if(not self.perimetro.intersect(rango)):
            return
        for p in self.points:
            if(rango.cotiene(p)):
                found.append(p)
        if(self.divided == True):
            self.sonNOup.query(rango,found)
            self.sonNEup.query(rango,found)
            self.sonSOup.query(rango,found)
            self.sonSEup.query(rango,found)
            self.sonNOdw.query(rango,found)
            self.sonNEdw.query(rango,found)
            self.sonSOdw.query(rango,found)
            self.sonSEdw.query(rango,found)

    def Mostrar(self):
        rect(self.perimetro.x,self.perimetro.y,self.perimetro.z,self.perimetro.w*2,self.perimetro.h*2,self.perimetro.p*2,self.color)
        if(self.divided):
            self.sonNOup.Mostrar()
            self.sonNEup.Mostrar()
            self.sonSOup.Mostrar()
            self.sonSEup.Mostrar()
            self.sonNOdw.Mostrar()
            self.sonNEdw.Mostrar()
            self.sonSOdw.Mostrar()
            self.sonSEdw.Mostrar()
        for p in self.points:
            punto(p.x,p.y,p.z,self.color)

from random import*


def main():
    perimetro = Rectangulo (200,200,200,200,200,200)
    ot= Octree(perimetro,8)
    for i in range(0,77):
        val1 = randrange(400)
        val2 = randrange(400)
        val3 = randrange(400)
        p = Point(val1,val2,val3)
        ot.Insertar(p)
    ot.Mostrar()
    rango = Rectangulo(randrange(200),randrange(200),randrange(200),randrange(100),randrange(100),randrange(100))
    rect(rango.x,rango.y,rango.z,rango.w*3,rango.h*3,rango.p*3,[255,0,0])

    rango_punto= []
    ot.query(rango,rango_punto)
    for it in rango_punto:
        punto(it.x,it.y,it.z,[255,0,0])
    print(rango_punto)


Pantalla()
main()

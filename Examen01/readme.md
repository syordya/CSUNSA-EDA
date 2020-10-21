## Octree
> :warning: **Not all functions works well**: As we are learning `js` modules, some functions like region query are not working. Please pull the *stable* branch to view this project rolling out!

Un octree es una estructura en "árbol" de datos en la cual cada nodo interno tiene exactamente 8 "hijos". Las estructuras octree se usan mayormente para partir un espacio tridimensional, dividiéndolo recursivamente en ocho octantes. Las estructuras octree son las análogas tridimensionales de los quadtree bidimensionales..

### Resultado
![Octree animation](/Examen01/imgs/octree.gif)
El siguiente Octree contiene las siguientes funciones :
- *Insertion* : Función que inserta puntos en el octree.
- *Query* : Consulta puntos en el octree.
- *Squery* : Muestra la region de consulta en el octree.
- *CleanQuery* : Limpia las consultas ya realizadas.
- *Points* : Muestra la cantidad de puntos encontrados.

### Lenguajes y librerías
- JavaScript
- Three.js


### Instalación y ejecución
```
npm install
npm run build
```

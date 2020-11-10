k = 2; // dimensions
vecinos = 3; // Buscar vecinos más cercanos

class Node {
  constructor(point, axis) {
    this.point = point;
    this.left = null;
    this.right = null;
    this.axis = axis;
  }
}

function getHeight(node) {

  if (!node) {
    return -1;
  }
  if (node.left == null && node.right == null) {
    return 0;
  }
  var left_child;
  var right_child
  left_child = getHeight(node.left) + 1;
  right_child = getHeight(node.right) + 1;

  return Math.max(left_child, right_child);
}

// https://es.wikipedia.org/wiki/%C3%81rbol_kd
// points = [[1,2],[4,5]]
function buildKdTree(points, depth = 0) {

  var median;
  var root;

  // Construye el KD-Tree y retorna el nodo raiz
  if (points.length == 0) {
    return null;
  }
  else {
    // Select axis based on depth so that axis cycles through all valid values
    var axis = depth % k; // par 0 (x), impar 1 (y)

    points = points.sort(
      function (a, b) {
        if (a[axis] < b[axis]) return -1;
        if (a[axis] > b[axis]) return 1;
        return 0;
      });

    //console.log("array : ", points);
    // Sort point list and choose median as pivot element
    if (points.length == 1) {
      median = 0;
    }
    else {
      median = Math.floor(points.length / 2); // los arrays impares con CEIL no daba en la mediana por eso FLOOR
      // console.log("meddd : ",median);
    }

    // Create node and construct subtrees
    root = new Node(points[median], axis);
    // console.log( " Nodo root : ", root.point);
    root.left = buildKdTree(points.slice(0, median), depth + 1);
    root.right = buildKdTree(points.slice(median + 1,), depth + 1);

    return root;

  }
}

function generateDot(node) {
  if (!node || getHeight(node) == 0) {
    return '';
  }

  let str = '';
  if (node.left) {
    str += '"' + node.point[0] + ',' + node.point[1] + '"';
    str += " -> ";
    str += '"' + node.left.point[0] + ',' + node.left.point[1] + '"';
    str += ';\n';
    str += generateDot(node.left);
  }
  if (node.right) {
    str += '"' + node.point[0] + ',' + node.point[1] + '"';
    str += " -> ";
    str += '"' + node.right.point[0] + ',' + node.right.point[1] + '"';
    str += ';\n';
    str += generateDot(node.right);
  }
  return str;
}

function distanceSquared(pointA, pointB) {
  var distance = 0;
  for (var i = 0; i < k; i++) {
    distance += Math.pow((pointA[i]-pointB[i]), 2)
  }
  return Math.sqrt(distance);
}

function closest_point_brute_force(points, point){
  var distance = Number.MAX_VALUE;
  var point_c = null;
  for (var i = 0; i< points.length; i++){
      var auxiliar = distanceSquared(points[i], point);
      if (auxiliar < distance){
          distance = auxiliar;
          point_c = points[i];
      }
  }
  return point_c;
}

//Best = min(distance(query, current_node), best).
function naive_closest_point (node , point , depth = 0, best = null ){

  if (!node) {
    return best;
  }

  var ladoIZQ = node.left;
  var ladoDER = node.right;


  //la distancia menor comprobamos de los nodos visitado
  if(best == null || distanceSquared(node.point ,point) < distanceSquared(best,point)){
    best = node.point;
  }

  //Coprobamos los si el punto es menor y va a la iz y si es mayor a la derecha
  if (point[depth % k] < node.point[depth % k]) {
    return naive_closest_point(ladoIZQ, point, depth +1 , best)
  }
  else{
    return naive_closest_point(ladoDER, point, depth +1 , best)
  }

}

function masCercano(puntoConsulta, p1, p2) {
  if (!p1) {
    return p2;
  }
  if (!p2) {
    return p1;
  }
  return (distanceSquared(puntoConsulta, p1) < distanceSquared(puntoConsulta, p2))? p1 : p2;
}

function closestPoint(node, puntoConsulta, depth = 0, best = null) {
  if (!node) {
    return null;
  }

  // Escogiendo árbol de la izquierda o derecha
  var subTree1 = node.left;
  var subTree2 = node.right;
  if (puntoConsulta[depth%k] >= node.point[depth%k]) {
    subTree1 = node.right;
    subTree2 = node.left;
  }

  // Mejor distancia entre el padre y el subTree1.
  best = masCercano(puntoConsulta, closestPoint(subTree1, puntoConsulta, depth + 1), node.point);

  // Viendo sí la distancia del punto de consulta al sector es menor que la distancia del mejor punto
  if (Math.abs(puntoConsulta[depth%k] - node.point[depth%k]) < distanceSquared(puntoConsulta, best)) {
    // Comparar mejor distancia con subTree2.
    best = masCercano(puntoConsulta, closestPoint(subTree2, puntoConsulta, depth + 1), node.point);
  }

  return best;
}

function knn(node, puntoConsulta, kpoints, depth = 0) {
  if (!node) {
    return null;
  }

  var temp;
  var subTree1 = node.left;
  var subTree2 = node.right;

  if (puntoConsulta[depth%k] >= node.point[depth%k]) {
    subTree1 = node.right;
    subTree2 = node.left;
  }

  // Mejor distancia entre el padre y el subTree1.
  masCercano(puntoConsulta, knn(subTree1, puntoConsulta, kpoints, depth +1), node.point);

  // Variable para ordenar por distancias
  const sortByDistance = (a, b) => a[2] - b[2];

  if (kpoints.length < vecinos) {
    temp = node.point;
    temp.push(Math.round(distanceSquared(puntoConsulta, temp)*100)/100);
    kpoints.push(temp);
    kpoints.sort(sortByDistance);
  } else {
    temp = node.point;
    temp.push(Math.round(distanceSquared(puntoConsulta, temp)*100)/100);
    if (temp[2] < kpoints[kpoints.length - 1][2]) {
      kpoints.pop();
      kpoints.push(temp);
      kpoints.sort(sortByDistance);
    }
  }

  if(kpoints.length < vecinos || kpoints[0][2] >= Math.abs(puntoConsulta[depth % k] - node.point[depth%k])) {
    masCercano(puntoConsulta, knn(subTree2, puntoConsulta, kpoints, depth +1), node.point);
  }
}

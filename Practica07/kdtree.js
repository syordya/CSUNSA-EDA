k = 2; // Espacio vectorial

class Node {
  constructor(point, axis) {
    this.point = point;
    this.left = null;
    this.right = null;
    this.axis = axis;
  }
}

class Rectangle {
  // Coloca rectangulo con centro x, y
  constructor(x, y, w, h) {
    this.x = x;
    this.y = y;
    this.w = w;
    this.h = h;
  }
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

function distanceSquared(pointA, pointB) {
  var distance = 0;
  for (var i = 0; i < k; i++) {
    distance += Math.pow((pointA[i]-pointB[i]), 2)
  }
  return Math.sqrt(distance);
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

function rangeQueryCircle(node, puntoConsulta, kpoints, radio, depth = 0) {
  if (!node) return null;

  var subTree1 = node.left;
  var subTree2 = node.right;

  if (puntoConsulta[depth%k] >= node.point[depth%k]) {
    subTree1 = node.right;
    subTree2 = node.left;
  }

  masCercano(point, rangeQueryCircle(subTree1, puntoConsulta, kpoints, radio, depth + 1), node.point);

  if (distanceSquared(puntoConsulta, node.point) < radio) {
    node.point.push(distanceSquared(puntoConsulta, node.point));
    kpoints.push(node.point);
  }

  if (radio >= Math.abs(puntoConsulta[depth%k] - node.point[depth%k])) {
    masCercano(puntoConsulta, rangeQueryCircle(subTree2, puntoConsulta, kpoints, radio, depth + 1), node.point);
  }
}

function rangeQueryRect(node, puntoConsulta, kpoints, rectangle, depth = 0) {
  if (!node) return null;

  var subTree1 = node.left;
  var subTree2 = node.right;

  if (puntoConsulta[depth%k] >= node.point[depth%k]) {
    subTree1 = node.right;
    subTree2 = node.left;
  }

  masCercano(puntoConsulta, rangeQueryRect(subTree1, puntoConsulta, kpoints, rectangle, depth + 1), node.point);
  if (node.point[0] > (rectangle.x - rectangle.w) &&
      node.point[0] < (rectangle.x + rectangle.w) &&
      node.point[1] > (rectangle.y - rectangle.h) &&
      node.point[1] < (rectangle.y + rectangle.h)) {
    kpoints.push(node.point)
  }

  let distanceSector = Math.abs(puntoConsulta[depth%k] - node.point[depth%k]);
  if (distanceSector <= rectangle.x + rectangle.w ||
      distanceSector <= rectangle.x - rectangle.w ||
      distanceSector <= rectangle.y + rectangle.h ||
      distanceSector <= rectangle.y - rectangle.h) {
        masCercano(puntoConsulta, rangeQueryRect(subTree2, puntoConsulta, kpoints, rectangle, depth + 1), node.point);
  }
}

function show() {
  var width = 700;
  var height = 500;

  for (var x = 0; x < width; x += width / 10) {
    for (var y = 0; y < height; y += height / 5) {
      stroke(125, 125, 125);
      strokeWeight(1);
      line(x, 0, x, height);
      line(0, y, width, y);
    }
  }

  data.forEach((point) => {
    fill(255, 255, 255);
    circle(point[0], height - point[1], 7);
    textSize(8);
    text(point[0] + ',' + point[1], point[0] + 5, height - point[1]);
  });
}

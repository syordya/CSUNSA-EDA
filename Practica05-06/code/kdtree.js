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

function masCercano(puntoConsulta, p1, p2) {
  if (!p1) {
    return p2;
  }
  if (!p2) {
    return p1;
  }
  return (distanceSquared(puntoConsulta, p1) < distanceSquared(puntoConsulta, p2))? p1 : p2;
}

function closestPoint(node, point, depth = 0, best = null) {
  if (!node) {
    return null;
  }

  var subTree1 = node.left;
  var subTree2 = node.right;

  if (point[depth%k] >= node.point[depth%k]) {
    subTree1 = node.right;
    subTree2 = node.left;
  }

  best = masCercano(point, closestPoint(subTree1, point, depth + 1), node.point);

  if (distanceSquared(point, best) > Math.abs(point[depth%k] - node.point[depth%k])) {
    best = masCercano(point, closestPoint(subTree2, point, depth + 1), node.point);
  }

  return best;
}

function knn(node, point, kpoints, depth = 0) {
  if (!node) {
    return null;
  }

  var temp;
  var subTree1 = node.left;
  var subTree2 = node.right;

  if (point[depth%k] >= node.point[depth%k]) {
    subTree1 = node.right;
    subTree2 = node.left;
  }

  masCercano(point, knn(subTree1, point, kpoints, depth +1), node.point);

  const sortByX = (a, b) => a[2] - b[2];
  if (kpoints.length < vecinos) {
    temp = node.point;
    temp.push(Math.round(distanceSquared(point, temp)*100)/100);
    kpoints.push(temp);
    kpoints.sort(sortByX);
  } else {
    temp = node.point;
    temp.push(Math.round(distanceSquared(point, temp)*100)/100);
    if (temp[2] < kpoints[kpoints.length - 1][2]) {
      kpoints.pop();
      kpoints.push(temp);
      kpoints.sort(sortByX);
    }
  }

  if(kpoints.length < vecinos || kpoints[0][2] >= Math.abs(point[depth % k] - node.point[depth%k])) {
    masCercano(point, knn(subTree2, point, kpoints, depth +1), node.point);
  }
}

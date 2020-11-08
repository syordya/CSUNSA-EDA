k = 2;

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

    console.log("array : ", points);
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
    str += '"' + node.point + '"';
    str += "->";
    str += '"' + node.left.point + '"';
    str += ';\n';
    str += generateDot(node.left);
  }
  if (node.right) {
    str += '"' + node.point + '"';
    str += "->";
    str += '"' + node.right.point + '"';
    str += ';\n';
    str += generateDot(node.right);
  }
  return str;
}

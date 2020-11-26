const csv = require('csv-parser');
const fs = require('fs');

let k = 6; // dimensiones
let vecinos = 15; // vecinos más cercanos

class Node {
  constructor(point, axis) {
    this.point = point;
    this.left = null;
    this.right = null;
    this.axis = axis;
  }
}

function buildKdTree(points, depth = 0) {
  var median;
  var root;

  if (points.length == 0) {
    return null;
  }

  var axis = depth % k;
  points = points.sort(
    function (a, b) {
      if (a[axis] < b[axis]) return -1;
      if (a[axis] > b[axis]) return 1;
      return 0;
    });
    if (points.length == 1) {
      median = 0;
    }
    else {
      median = Math.floor(points.length / 2);
    }
    root = new Node(points[median], axis);
    root.left = buildKdTree(points.slice(0, median), depth + 1);
    root.right = buildKdTree(points.slice(median + 1,), depth + 1);
    return root;
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

  // Ordenar por distancias
  const sortByDistance = (a, b) => a[k+1] - b[k+1];

  if (kpoints.length < vecinos) {
    temp = node.point;
    temp.push(distanceSquared(puntoConsulta, temp));
    kpoints.push(temp);
    kpoints.sort(sortByDistance);
  } else {
    temp = node.point;
    temp.push(distanceSquared(puntoConsulta, temp));
    if (temp[k+1] < kpoints[kpoints.length - 1][k+1]) {
      kpoints.pop();
      kpoints.push(temp);
      kpoints.sort(sortByDistance);
    }
  }

  if(kpoints.length < vecinos || kpoints[0][k+1] >= Math.abs(puntoConsulta[depth % k] - node.point[depth%k])) {
    masCercano(puntoConsulta, knn(subTree2, puntoConsulta, kpoints, depth +1), node.point);
  }
}

var data = [];
var queryPoints = [];

// Parse tests.csv
fs.createReadStream('moche_vs_yuan-tests.csv', { star:10 })
.on('error', () => {
  // handle error
})
.pipe(csv())
.on('data', (row) => {
  var a = parseFloat(`${row["meanB"]}`);
  var b = parseFloat(`${row["meanG"]}`);
  var c = parseFloat(`${row["meanR"]}`);
  var d = parseFloat(`${row["stdevB"]}`);
  var e = parseFloat(`${row["stdevG"]}`);
  var f = parseFloat(`${row["stdevR"]}`);
  var g = `${row["class"]}`;
  queryPoints.push([a,b,c,d,e,f,g]);
})
.on('end', () => {})
.on('close', function(){})

// Parse dogs_vs_cats
fs.createReadStream('moche_vs_yuan.csv', { star:10 })
.on('error', () => {
  // handle error
})
.pipe(csv())
.on('data', (row) => {
  var a = parseFloat(`${row["meanB"]}`);
  var b = parseFloat(`${row["meanG"]}`);
  var c = parseFloat(`${row["meanR"]}`);
  var d = parseFloat(`${row["stdevB"]}`);
  var e = parseFloat(`${row["stdevG"]}`);
  var f = parseFloat(`${row["stdevR"]}`);
  var g = `${row["class"]}`;
  data.push( [a,b,c,d,e,f,g] );
})
.on('end', () => {
  let root = buildKdTree(data);
  let correct = 0;

  queryPoints.forEach((puntoConsulta) => {
    let kvecinos = []
    let cats = 0;
    let dogs = 0;
    let result = '';
    knn(root, puntoConsulta, kvecinos);
    for(let i = 0 ; i < kvecinos.length; i++) {
      if(kvecinos[i][k] == 'moche') {
        cats++;
      } else {
        dogs++;
      }
    }
    console.log(cats, dogs)
    if (cats > dogs) {
      result = "moche"
    } else {
      result = "yuan"
    }
    console.log(result);

    if (puntoConsulta[k] == result) {
      correct++;
    }
  });

  let accuracy = Math.round((correct/queryPoints.length)*1000)/1000;

  console.log(`Accuracy = ${accuracy}$.`)
})
.on('close', function(){} )

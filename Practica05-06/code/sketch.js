function setup() {
  var width = 250;
  var height = 200;

  var canvas = createCanvas(width, height);
  canvas.parent('parentCanvas');

  background(0);
  for (var x = 0; x < width; x += width / 10) {
    for (var y = 0; y < height; y += height / 5) {
      stroke(125, 125, 125);
      strokeWeight(1);
      line(x, 0, x, height);
      line(0, y, width, y);
    }
  }

  /*
  var data = [];
  for (let i = 0; i < 6; i++) {
    var x = Math.floor(Math.random() * height);
    var y = Math.floor(Math.random() * height);
    data.push([x, y]);

    fill(255, 255, 255);
    circle(x, height - y, 7);
    text(x + ',' + y, x + 5, height - y);
    textSize(8);
  }
  */

  //var data = [[21,84],[90,102],[5,150],[84,138],[161,29],[181,45],[6,114],[148,85],[106,189],[158,120]]
  var data = [[100,100],[40,70],[90,40],[70,130],[175,100],[150,30],[140,110]];
  var point = [140, 90];

  var x =  point[0];
  var y =  point[1];
  fill(81, 209, 246);
  circle(x, height - y, 7);
  textSize(8);
  text(x + ',' + y, x + 5, height - y);

  data.forEach((point) => {
    fill(255, 255, 255);
    circle(point[0], height - point[1], 7);
    textSize(8);
    text(point[0] + ',' + point[1], point[0] + 5, height - point[1]);
  });


  var root = buildKdTree(data);
  console.log(root);
  var graphDot = "digraph G {\n" + generateDot(root) + '}';
  console.log(graphDot);
  var brute = closest_point_brute_force(data, point); //[140,110]
  var naive = naive_closest_point(root, point); // [175,100]
  var best = closestPoint(root, point); //[140,110]
  //Probando el naive
  //var best = naive_closest_point(root,point);
  console.log(brute);
  console.log(naive);
  console.log(best);

  var x =  best[0];
  var y =  best[1];

  fill(57, 255, 20);
  circle(x, height - y, 7);
  textSize(8);
  text(x + ',' + y, x + 5, height - y);

  kvecinos = []
  knn(root, point, kvecinos);
  console.log(kvecinos)

  var image = Viz(graphDot, {format: 'svg'});
  var graph = document.getElementById('graphHolder');

  graph.innerHTML = image;		// SVG
}

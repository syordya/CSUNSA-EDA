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

  // Generar n puntos aleatorios
  let n = 10
  var data = [];
  for (let i = 0; i < n; i++) {
    var x = Math.floor(Math.random() * height);
    var y = Math.floor(Math.random() * height);

    data.push([x, y]);
    fill(255, 255, 255);
    circle(x, height - y, 7);
    text(x + ',' + y, x + 5, height - y);
    textSize(8);
  }

  //var data = [[21,84],[90,102],[5,150],[84,138],[161,29],[181,45],[6,114],[148,85],[106,189],[158,120]]
  //var data = [[100,100],[40,70],[90,40],[70,130],[175,100],[150,30],[140,110]];
  var puntoConsulta = [140, 90];

  var root = buildKdTree(data);
  console.log(root);
  var graphDot = "digraph G {\n" + generateDot(root) + '}';
  console.log(graphDot);
  var brute = closest_point_brute_force(data, puntoConsulta); //[140,110]
  var naive = naive_closest_point(root, puntoConsulta); // [175,100]
  var best = closestPoint(root, puntoConsulta); //[140,110]
  console.log(brute);
  console.log(naive);
  console.log(best);
  kvecinos = []
  knn(root, puntoConsulta, kvecinos);
  console.log(kvecinos)

  // PuntoConsulta
  fill(81, 209, 246);
  circle(puntoConsulta[0], height - puntoConsulta[1], 7);
  textSize(8);
  text(puntoConsulta[0] + ',' + puntoConsulta[1], puntoConsulta[0] + 5, height - puntoConsulta[1]);

  /*
  // Puntos
  data.forEach((point) => {
    fill(255, 255, 255);
    circle(point[0], height - point[1], 7);
    textSize(8);
    text(point[0] + ',' + point[1], point[0] + 5, height - point[1]);
  });
  */

  /*
  // Mejor próximo
  fill(57, 255, 20);
  circle(best[0], height - best[1], 7);
  textSize(8);
  text(best[0] + ',' + best[1], best[0] + 5, height - best[1]);
  */

  // k vecinos más cercanos
  kvecinos.forEach((vecino) => {
    fill(57, 255, 20);
    circle(vecino[0], height - vecino[1], 7);
    textSize(8);
    text(vecino[0] + ',' + vecino[1], vecino[0] + 5, height - vecino[1]);
  });

  var image = Viz(graphDot, {format: 'svg'});
  var graph = document.getElementById('graphHolder');
  graph.innerHTML = image;		// SVG
}

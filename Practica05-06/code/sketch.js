function setup() {
  var width = 250;
  var height = 200;
  createCanvas(width, height);

  background(0);
  for (var x = 0; x < width; x += width / 10) {
    for (var y = 0; y < height; y += height / 5) {
      stroke(125, 125, 125);
      strokeWeight(1);
      line(x, 0, x, height);
      line(0, y, width, y);
    }
  }

  var data = [];
  for (let i = 0; i < 6; i++) {
    var x = Math.floor(Math.random() * height);
    var y = Math.floor(Math.random() * height);
    data.push([x, y]);

    fill(255, 255, 255);
    circle(x, height - y, 7);
    textSize(8);
    text(x + ',' + y, x + 5, height - y);
  }
  //var data = [[21,84],[90,102],[5,150],[84,138],[161,29],[181,45],[6,114],[148,85],[106,189],[158,120]]


  var root = buildKdTree(data);
  console.log(root);
  var graphDot = "digraph G {\n" + generateDot(root) + '}';
  console.log(graphDot);
}

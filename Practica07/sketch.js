let data = []
let root;

function setup() {
  var width = 700;
  var height = 500;

  createCanvas(width, height);

  // Generar n puntos aleatorios
  let n = 300
  for (let i = 0; i < n; i++) {
    var x = Math.floor(Math.random() * height);
    var y = Math.floor(Math.random() * height);
    data.push([x, y]);
  }

  root = buildKdTree(data);
}

function draw() {
  background(0);
  show();
  stroke(0,255,0);
  noFill();

  let x = mouseX;
  let y = mouseY;
  radio = 100;
  //circle(x, y, radio*2);
  rectMode(CENTER);
	let range = new Rectangle(x, y, 50, 50)
	rect(range.x, range.y, range.w*2, range.h*2);

  let kvecinos = [];
  puntoConsulta = [range.x, range.y];

  rangeQueryCircle(root, puntoConsulta, kvecinos, radio);
  //rangeQueryRect(root, puntoConsulta, kvecinos, range);

  console.log(kvecinos);

  for(let i = 0; i < kvecinos.length;i++){
    let c = color(255, 204, 0);
    fill(c);
    circle(kvecinos[i][0], height - kvecinos[i][1], 7);
    textSize(8);
    text(kvecinos[i][0] + ',' + kvecinos[i][1], kvecinos[i][0]+5, height - kvecinos[i][1]);
  }
}

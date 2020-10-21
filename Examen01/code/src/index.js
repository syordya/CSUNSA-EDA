import * as THREE from 'three';
import { createOctree, octree, scene, rand, q } from './sketch.js';
import { Point, Cubo } from './octree.js';

window.crear = function() {
  var m = 100;
  var n = 8
  createOctree(m, n);
}


window.insertar = function() {
  var px = document.getElementById("X").value;
  var py = document.getElementById("Y").value;
  var pz = document.getElementById("Z").value;
  let point = new Point(px, py, pz);
  octree.insert(point);
}

window.query = function() {
  dquery();
  var cx = document.getElementById("CX").value;
  var cy = document.getElementById("CY").value;
  var cz = document.getElementById("CZ").value;
  var cw = document.getElementById("CW").value;
  var ch = document.getElementById("CH").value;
  var cd = document.getElementById("CD").value;
  let cubo = new Cubo(cx, cy, cz, cw, ch, cd);
  let found = [];
  octree.query(cubo, found);
  document.getElementById("demo").innerHTML = "Puntos : " + found.length;
}

window.squery = function() {
  dquery();
  var cx = document.getElementById("CX").value;
  var cy = document.getElementById("CY").value;
  var cz = document.getElementById("CZ").value;
  var cw = document.getElementById("CW").value;
  var ch = document.getElementById("CH").value;
  var cd = document.getElementById("CD").value;
  var geometry = new THREE.BoxGeometry(cw * 2, ch * 2, cd * 2);
  var material = new THREE.MeshBasicMaterial({ color: 0x000000, opacity: 0.8, transparent: false, });
  material.color.set(this.color);
  var cube = new THREE.Mesh(geometry, material);
  cube.position.set(cx, cy, cz);
  //q = cube;
  scene.add(q);
}


window.dquery = function() {
  var cx = document.getElementById("CX").value;
  var cy = document.getElementById("CY").value;
  var cz = document.getElementById("CZ").value;
  var cw = document.getElementById("CW").value;
  var ch = document.getElementById("CH").value;
  var cd = document.getElementById("CD").value;
  let cubo = new Cubo(cx, cy, cz, cw, ch, cd);
  octree.cleanQuery(cubo);
  scene.remove(q);
  document.getElementById("demo").innerHTML = "Puntos : 0";
  //q = null;
}

window.nrand = function() {
  var nr = document.getElementById("N2").value;
  rand(nr, 100);
}

window.clean = function() {
  scene = new THREE.Scene();
  scene.background = new THREE.Color(0xffffff);
  light = new THREE.DirectionalLight(0xffffff, 0.9);
  light.position.set(-100, 100, 0);
  camera.add(light);
  scene.add(camera);
  scene.add(axisHelper);

}

import * as THREE from 'three';
import { OrbitControls } from 'three/examples/jsm/controls/OrbitControls.js';
import { Point, Cubo, OcTree } from './octree.js';

var scene = new THREE.Scene();
var camera = new THREE.PerspectiveCamera(75, window.innerWidth / window.innerHeight, 0.1, 1000);
var renderer = new THREE.WebGLRenderer();
var controls = new OrbitControls(camera, renderer.domElement);
renderer.setSize(window.innerWidth, window.innerHeight);
scene.background = new THREE.Color(0xffffff);
document.body.appendChild(renderer.domElement);

camera.position.y = -20;
camera.position.x = -100;
camera.position.z = -100;
var light = new THREE.DirectionalLight(0xffffff, 0.8);
light.position.set(-100, 100, 0);
camera.add(light);
scene.add(camera);

var axisHelper = new THREE.AxisHelper(1.25);
scene.add(axisHelper);

var octree;
var q;

function createOctree(m, n) {
    let cubo = new Cubo(m / 2, m / 2, m / 2, m / 2, m / 2, m / 2);
    octree = new OcTree(cubo, n);
}


function rand(n, m) {
    for (let i = 0; i < n; i++) {
        let x = Math.random() * m;
        let y = Math.random() * m;
        let z = Math.random() * m;
        let point = new Point(x, y, z);
        octree.insert(point);
    }
}


controls.update();

var animate = function () {
    requestAnimationFrame(animate);
    controls.update();
    renderer.render(scene, camera);
};

animate();

export { createOctree, octree, scene, rand, q };

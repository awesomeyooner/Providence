import * as THREE from '../libs/three.min.js';
//  import * as THREE from 'https://cdnjs.cloudflare.com/ajax/libs/three.js/r128/three.module.min.js';
import { OrbitControls } from '../libs/orbit.min.js';

const container = document.getElementById('canvas-container');

//initializing
const scene = new THREE.Scene();
const camera = new THREE.PerspectiveCamera(75, container.clientWidth / container.clientHeight, 0.1, 1000);
const renderer = new THREE.WebGLRenderer();
renderer.setSize(container.clientWidth, container.clientHeight);
container.appendChild(renderer.domElement);

camera.position.z = 5;

//camera controls
const controls = new OrbitControls( camera, renderer.domElement );
// controls.minDistance = 20;
// controls.maxDistance = 50;
// controls.maxPolarAngle = Math.PI / 2;

//axis
scene.add( new THREE.AxesHelper( 20 ) );

//box
const geometry = new THREE.BoxGeometry();
const material = new THREE.MeshBasicMaterial({ color: 0x00ff00 });
const cube = new THREE.Mesh(geometry, material);
scene.add(cube);

//point
// const pointGeometry = new THREE.BufferGeometry();
// pointGeometry.setAttribute('position', new THREE.BufferAttribute(new Float32Array([0, 0, 0]), 3));
// const pointMaterial = new THREE.PointsMaterial({size: 0.1, color: 0xff0000});
// const point = new THREE.Points(pointGeometry, pointMaterial);
// scene.add(point)

function animate() {
    requestAnimationFrame(animate);

    cube.position.x = 1;
    cube.rotation.x += 0.01;
    cube.rotation.y += 0.01;

    renderer.render(scene, camera);
}

animate();

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
const geometry = new THREE.BoxGeometry(1, 1, 0.2);
const material = new THREE.MeshBasicMaterial({ color: 0x00ff00 });
const cube = new THREE.Mesh(geometry, material);
scene.add(cube);

//point
// const pointGeometry = new THREE.BufferGeometry();
// pointGeometry.setAttribute('position', new THREE.BufferAttribute(new Float32Array([0, 0, 0]), 3));
// const pointMaterial = new THREE.PointsMaterial({size: 0.1, color: 0xff0000});
// const point = new THREE.Points(pointGeometry, pointMaterial);
// scene.add(point)

var x, y, z = 0;

function animate() {
    requestAnimationFrame(animate);

    cube.position.x = x;
    cube.position.y = y;
    cube.position.z = z;

    //cube.rotation.y += 0.01;

    renderer.render(scene, camera);
}

animate();

//=============================================

function updateNumber() {
    fetch("/number")
        .then(response => response.text())
        .then(data => {
            document.getElementById("number").innerText = data;
        });
}

function updateImage() {
    fetch("/image")
        .then(response => response.blob())
        .then(blob => {
            const imgElement = document.getElementById("videoStream");
            imgElement.src = URL.createObjectURL(blob);
        });
}

function updatePose(){
    fetch('/pose')  // Send a GET request to /json
        .then(response => response.json())  // Parse the JSON response
        .then(data => {
            // Access elements of the JSON object
            x = data.x;
            y = data.y;
            z = data.z;
        })
        .catch(error => console.error('Error fetching JSON:', error));  // Error handling
}

function update(){
    updateNumber();
    updateImage();
    updatePose();
}   



setInterval(update, 20); // Update every second

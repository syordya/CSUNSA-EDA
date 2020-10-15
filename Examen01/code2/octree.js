
var alpha = 0.2;
class Point {
    //Posicion x , y , z
    constructor (x, y, z ){
        this.x = x;
        this.y = y;
        this.z = z ;
        //Creamos la esfera
        this.geometry = new THREE.SphereGeometry( 2, 10, 10 );
        this.material = new THREE.MeshPhongMaterial();
        this.sphere = new THREE.Mesh( this.geometry, this.material );
        this.sphere.position.set(x,y,z);
        scene.add( this.sphere );
    }
}

class Cubo{
    constructor (x, y,z, w, h,d){
        this.x = x; 
        this.y = y;
        this.z = z;
        this.w = w; //ancho
        this.h = h; //altura
        this.d = d;//profundidad
    }
    // verifica si este objeto contiene un objeto Punto
    contains ( point ){
        if(point.x >= this.x - this.w && 
           point.x <= this.x + this.w &&
           point.y >= this.y - this.h &&
           point.y <= this.y + this.h &&
           point.z >= this.z - this.d && 
           point.z <= this.z + this.d )
                return true;
        return false;
    }

    // verifica si este objeto se intersecta con otro objeto Cubo
    intersects(range){
        if(range.x - range.w > this.x + this.w ||
           range.x + range.w < this.x - this.w ||
           range.y - range.h > this.y + this.h ||
           range.y + range.h < this.y - this.h ||
           range.z - range.d > this.z + this.d ||
           range.z + range.d < this.z - this.d )
            return false;
        return true;
    }
}

class OcTree {
    constructor (cubo,n){
        this.cubo = cubo ; // cubo
        this.capacity = n; // capacidad maxima de cada cuadrante
        this.points = []; // vector , almacena los puntos a almacenar
        this.divided = false ;
        //Math.random() retorna un punto flotante, un número pseudo-aleatorio dentro del rango [0, 1). 
        // Separe los valores RGB entre 0 y 1
        this.color = new THREE.Color( Math.random()*1,Math.random()*1,Math.random()*1);
        //CUBO
        this.geometry = new THREE.BoxGeometry(cubo.w*2,cubo.h*2,cubo.d*2);
        this.material = new THREE.MeshBasicMaterial( { color: 0x00ff00, opacity: alpha , transparent: true, } );
        this.material.color.set(this.color);
        this.cube = new THREE.Mesh( this.geometry, this.material );
        this.cube.position.set(cubo.x,cubo.y,cubo.z);
        scene.add(this.cube);
    }

    insert(point){
        //Si el punto no esta en los limites (cubo)del octree Return
        if (!this.cubo.contains(point)) {
            return;
        }
        //Si ( this . points . length ) < ( this . capacity )
        if (this.points.length < this.capacity) {
            //Insertamos en el vector this . points
            this.points.push(point);
            //Color a la esfera
            point.material.color.set(this.color);
          
        }
        else{
            //Dividimos si aun no ha sido dividido
            if (!this.divided){
                this.subdivide();
            }
            //Insertamos recursivamente en los 4 hijos
            this.northeastf.insert(point); 
            this.northwestf.insert(point);
            this.southeastf.insert(point); 
            this.southwestf.insert(point);
            this.northeastb.insert(point); 
            this.northwestb.insert(point);
            this.southeastb.insert(point); 
            this.southwestb.insert(point);
        }
    }

    //divide el octree en 8 octrees
    subdivide(){
        let x = this.cubo.x;
        let y = this.cubo.y;
        let z = this.cubo.z;
        let w = this.cubo.w / 2;
        let h = this.cubo.h / 2;
        let d = this.cubo.d / 2;

        // Crear 8 hijos
        let nef = new Cubo(x + w, y - h,z - d, w, h, d);
        let nwf = new Cubo(x - w, y - h,z - d, w, h, d);
        let sef = new Cubo(x + w, y + h,z - d, w, h, d);
        let swf = new Cubo(x - w, y + h,z - d, w, h, d);

        let neb = new Cubo(x + w, y - h,z + d, w, h, d);
        let nwb = new Cubo(x - w, y - h,z + d, w, h, d);
        let seb = new Cubo(x + w, y + h,z + d, w, h, d);
        let swb = new Cubo(x - w, y + h,z + d, w, h, d);

        //Asignar los OcTree creados a cada hijo
        this.northeastf = new OcTree(nef, this.capacity);
        this.northwestf = new OcTree(nwf, this.capacity);
        this.southeastf = new OcTree(sef, this.capacity);
        this.southwestf = new OcTree(swf, this.capacity);

        this.northeastb = new OcTree(neb, this.capacity);
        this.northwestb = new OcTree(nwb, this.capacity);
        this.southeastb = new OcTree(seb, this.capacity);
        this.southwestb = new OcTree(swb, this.capacity);

        alpha = alpha + 0.1;
        //Hacer : this . divided <- true
        this.divided = true;

    }

    
    query(range,found){
        if(!found){
            found=[];
        }
        //no se intercepta con los limites del cuadrante
        if(!range.intersects(this.cubo)){
            return found;
        }
        //Ciclo por cada punto del queadtree
        for(let p of this.points){
            //Verificamos si esta dentro del rango
            if(range.contains(p)){
                //1 1 1 blanco / Cambia este color 
                p.material.color.set(new THREE.Color(1,1,1));
                //Lo insertamos en el vector found
                found.push(p);
                //count++;
            }
        }
        //Si ha sido dividido
        if(this.divided){
            //Llamamos recursivamente a cada hijo
            this.northwestf.query(range,found);
            this.northeastf.query(range,found);
            this.southwestf.query(range,found);
            this.southeastf.query(range,found);
            this.northwestb.query(range,found);
            this.northeastb.query(range,found);
            this.southwestb.query(range,found);
            this.southeastb.query(range,found);
        }
        return found;
    }

    cleanQuery(range){
        if(!range.intersects(this.cubo)){
            return;
        }
        else{
            for(let p of this.points){
                if(range.contains(p)){
                    //Vuelve a su color
                    p.material.color.set(this.color);
                }
            }
            if(this.divided){
                this.northwestf.cleanQuery(range);
                this.northeastf.cleanQuery(range);
                this.southwestf.cleanQuery(range);
                this.southeastf.cleanQuery(range);
                this.northwestb.cleanQuery(range);
                this.northeastb.cleanQuery(range);
                this.southwestb.cleanQuery(range);
                this.southeastb.cleanQuery(range);
            }
        }
    }


}

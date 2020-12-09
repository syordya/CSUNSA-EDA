#include <iostream>
#include <math.h>
#include <vector>

using namespace std;

class Point {
    public:
        int x;
        int y;
        // constructor
        point(int _x, int _y){
            x = _x;
            y = _y;
        }
}

class MBR {
    public: 
        int n; // capacidad
        int largo, ancho;
        float perimetro;

        // constructor
        mbr(int _n){
            n = _n;
        }

        // calcular area
        void obtener_perimetro(point izq,point der){
            _y = izq.y - der.y;
            _x = izq.x - der.x;
            largo = abs(_y);
            ancho = abs(_x);

            area = largo * ancho * 2;
        }

        // obtener perimetro de mbr
        float perimetro(){
            return  perimetro;
        }

        void update(vector<point> u){
            // falta
        }
}

class Node {
    public:
        vector <Point> puntos;
        bool isLeaf;
        vector <MBR> nodos; // falta implementar
        Node () {
            isLeaf = true;
        }
}

class RTree {
    public : 
        int n; // capacidad
        Node* root;
        
        RTree(int _n){
            root = new Node();
            n = _n;
        }

        // INSERT
        void insert(Node* u, Point p){
            if ( u->isLeaf == true){
                u->points.push_back(p);
                if( n < u->points.size()){ // u tiene B + 1 puntos
                    handle_overflow(u); 
                }
            }
            else{
                Node *v = new Node();
                v = choose_subtree(u, p); // falta implementar
                insert(v, p);
            }
        }

        // HANDLE-OVERFLOW
        void handle_overflow(Node *u){

            // hacemos split a u
            if(u->isLeaf == true)
                splitL(u); // split para hojas
            else
                split(u); // split para nodos no hojas

            if ( u == this.root) {
                // Creamos nuevo nodo raiz con 
                // u y u' como sus hijos
                Node* nueva_raiz = new Node();
                nueva_raiz = u;
                nueva_raiz->isLeaf = false;
                root->nodos = u;

            }
            else {
                Node* nuevo_nodo = new Node(); // creamos nuevo nodo
                nuevo_nodo->nodos = u; // nuevo_nodo <- el padre de u 
                update(nuevo_nodo->nodos); // actualizar MBR(u) en el nuevo nodo
                if(n < nuevo_nodo->nodos.size()){ // overflows
                    handle_overflow(nuevo_nodo);
                }
            }
        }

        void choose_subtree(Node* u, Point p){
            // falta
        }
}

int main(){

    return 0;
}

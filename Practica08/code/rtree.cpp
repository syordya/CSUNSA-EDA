#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>
#define Point pair<int,int>
#define x first
#define y second
using namespace std;

class Node;

// Retorna el maximo perimetro
int maxPerimetro(vector<Point> points){
    // inicializando el minimo y maximo en el eje X del primer Point
    // y en el eje Y del primer Point
    int max_x=points[0].x;
    int min_x=max_x;
    int max_y=points[0].y;
    int min_y=max_y;

    for(int i=1; i<points.size(); i++){

        if(points[i].x > max_x)
            max_x=points[i].x;

        if(points[i].x < min_x)
            min_x=points[i].x;

        if(points[i].y > max_y)
            max_y=points[i].y;

        if(points[i].y < min_y)
            min_y=points[i].y;
    }

    // retorna el perimetro
    return 2*((max_x-min_x)+(max_y-min_y)); 
}

// Verifica si los puntos estan ordenados de forma creciente
// segun el eje X
bool sortbyx(Point a,Point b){
    return (a.x < b.x);
}

// Verifica si los puntos estan ordenados de forma creciente
// segun el eje Y
bool sortbyy(Point a, Point b){
    return (a.y < b.y);
}

// Generando vertices del MBR
vector<Point> generar_vertices(vector<Point> points){
    int max_x=points[0].x;
    int min_x=points[0].x;
    int max_y=points[0].y;
    int min_y=points[0].y;

    for(int i=0; i<points.size(); i++){

        if(points[i].x > max_x)
            max_x=points[i].x;

        if(points[i].x < min_x) 
            min_x=points[i].x;

        if(points[i].y > max_y)
            max_y=points[i].y;

        if(points[i].y < min_y)
            min_y=points[i].y;
    }
    Point v1(min_x,min_y); // vertice 1
    Point v2(min_x,max_y); // vertice 2
    Point v3(max_x,min_y); // vertice 3
    Point v4(max_x,max_y); // vertice 4

    // retorna el vector de los vertices del MBR
    return (vector<Point> {v1,v2,v3,v4});
}

class MBR{
    public:
        vector<Point> vertices; 
        Node* child;
    public:
        MBR(vector<Point> points,Node* child){
            // generamos los vertices
            this->vertices=generar_vertices(points);
            this->child=child;
        }

        // funcion que verifica si un punto esta dentro del MBR
        bool contiene(Point p){
            // Si esta dentro del rango de los vertices del MBR retorna True
            // sino False
            if(vertices[0].x <= p.x && vertices[0].y <= p.y &&
            vertices[3].x >= p.x && vertices[3].y >= p.y)
                return true;
            else
                return false;
        }

        int agregando_punto(Point p){
            int newx,newy,x,y;
            newx=min(abs(vertices[0].x - p.x),abs(vertices[3].x - p.x));
            newy=min(abs(vertices[0].y - p.y),abs(vertices[3].y - p.y));
            return newx+newy;
        }
        
        // Esta funcion verifica si dos MBR se intersectan
        bool interseca(MBR mbr){
            // Recorre los vertices del 'mbr' si uno esta contenido
            // en el MBR retorna True, sino False
            for(int i=0; i < mbr.vertices.size(); i++){
                if(contiene(mbr.vertices[i]))
                    return true;
            }
            return false;
        }
};

// Ordena los MBR con respecto al eje X por el lado izquierdo
bool sortbyleftx(MBR a,MBR b){
    return (a.vertices[0].x < b.vertices[0].x);
}
// Ordena los MBR con respecto al eje y por el lado izquierdo
bool sortbylefty(MBR a,MBR b){
    return (a.vertices[0].y < b.vertices[0].y);
}

// Ordena los MBR con respecto al eje X por el lado derecho
bool sortbyrightx(MBR a,MBR b){
    return (a.vertices[4].x < b.vertices[4].x);
}

// Ordena los MBR con respecto al eje Y por el lado derecho
bool sortbyrighty(MBR a,MBR b){
    return (a.vertices[4].y < b.vertices[4].y);
}

int maxPerimetro(vector<MBR> mbr){
    int maxx=mbr[0].vertices[0].x;
    int minx=maxx;
    int maxy=mbr[0].vertices[0].y;
    int miny=maxy;
    for(int i=0; i<mbr.size(); i++){
        if(mbr[i].vertices[3].x > maxx)
            maxx=mbr[i].vertices[3].x;
        if(mbr[i].vertices[0].x < minx)
            minx=mbr[i].vertices[0].x;
        if(mbr[i].vertices[3].y > maxy)
            maxy=mbr[i].vertices[3].y;
        if(mbr[i].vertices[0].y < miny)
            miny=mbr[i].vertices[0].y;
    }
    return 2*((maxx-minx)+(maxy-miny));
}

class Node{
public:
    vector<Point> points;
    vector<MBR> mbrs;
    bool is_leaf;
    int deep;
    Node* parent;
    MBR* MBRparent;
    //debemos guardar la direccion del bmr parent
    //para luego poder actualizarlo cuando hagamos un split
    //en el overñaklsjdfñl
public:
    Node(int deep){
        this->is_leaf=true;
        this->deep=deep;
    }
};

class Rtree{
public:
    Node* root;
    int capacidad;
public:
    Rtree(int capacidad){
        this->root=new Node(0);
        this->capacidad=capacidad;
    }
    Node* chooseSubtree(Node* node,Point p){
        int minPerimetro=node->mbrs[0].agregando_punto(p);
        Node* result=node->mbrs[0].child;
        for(int i=0; i<node->mbrs.size(); i++){
            if(node->mbrs[i].contiene(p))
                return node->mbrs[i].child;
            else{
                int temp=node->mbrs[i].agregando_punto(p);
                if(temp < minPerimetro){
                    minPerimetro=temp;
                    result=node->mbrs[i].child;
                }
            }
        }
        return result;
    }
    
    void actualizarMBR(Node* node){
        if(node == this->root)
            return;
        if(node->is_leaf){
            for(int i=0; i<node->parent->mbrs.size(); i++){
                if((node->parent->mbrs[i].child) == node){
                    node->parent->mbrs[i].vertices=generar_vertices(node->points);
                    break;
                }
            }
            actualizarMBR(node->parent);
        }else{
            for(int i=0; i<node->parent->mbrs.size(); i++){
                if((node->parent->mbrs[i].child) == node){
                    vector<Point> p;
                    for(int j=0; j<node->mbrs.size(); j++)
                        copy(node->mbrs[j].vertices.begin(),node->mbrs[j].vertices.end(),back_inserter(p));
                    node->parent->mbrs[i].vertices==generar_vertices(p);
                    break;
                }
            }
            actualizarMBR(node->parent);
        }
    }
    Node* splitMBR(Node*& node){
        int m = node->mbrs.size();
        int limit = ceil(0.4*capacidad);
        int bestPerimetro = 999999999;
        vector<MBR> bestMBR1,bestMBR2;
        for(int axis=0; axis<2; axis++){
            for(int direc=0; direc<2; direc++){
                if(axis==0 && direc==0)
                    sort(node->mbrs.begin(),node->mbrs.end(),sortbyleftx);
                if(axis==0 && direc==1)
                    sort(node->mbrs.begin(),node->mbrs.end(),sortbyrightx);
                if(axis==1 && direc==0)
                    sort(node->mbrs.begin(),node->mbrs.end(),sortbylefty);
                if(axis==1 && direc==1)
                    sort(node->mbrs.begin(),node->mbrs.end(),sortbyrighty);
                for(int i=limit; i<=(m-limit); i++){
                    vector<MBR> S1,S2;
                    for(int j=0; j<node->mbrs.size(); j++){
                        if(j<i) S1.push_back(node->mbrs[j]);
                        else    S2.push_back(node->mbrs[j]);
                    }
                    int temPerimetro=maxPerimetro(S1) + maxPerimetro(S2);
                    if(bestPerimetro > temPerimetro){
                        bestPerimetro = temPerimetro;
                        bestMBR1 = S1;
                        bestMBR2 = S2;
                    }
                }
            }
        }
        Node* newNode=new Node(node->deep);
        newNode->is_leaf=false;
        newNode->mbrs = bestMBR2;
        node->mbrs = bestMBR1;
        return newNode;
    }
    Node* split(Node*& node){
        if(!node->is_leaf)
            return splitMBR(node);
        int m=node->points.size();
        int limit=ceil(0.4*capacidad);
        int bestPerimetro=maxPerimetro(node->points)*5;
        vector<Point> bestMBR1,bestMBR2;
        for(int axis=0; axis<2; axis++){
            if(axis == 0)
                sort(node->points.begin(),node->points.end(),sortbyx);
            else
                sort(node->points.begin(),node->points.end(),sortbyy);
            for(int i=limit; i<=(m-limit); i++){
                vector<Point> S1,S2;
                for(int j=0; j<node->points.size(); j++){
                    if(j<i) S1.push_back(node->points[j]);
                    else    S2.push_back(node->points[j]);
                }
                int temPerimetro=maxPerimetro(S1) + maxPerimetro(S2);
                if(bestPerimetro > temPerimetro){
                    bestPerimetro = temPerimetro;
                    bestMBR1 = S1;
                    bestMBR2 = S2;
                }
            }
        }
        Node* newNode = new Node(node->deep);
        newNode->points = bestMBR2;
        node->points = bestMBR1;
        return newNode;
    }
    void actualizarDeep(Node* node,int deep){
        node->deep=deep;
        if(node->is_leaf)   return;
        for(int i=0; i<node->mbrs.size(); i++){
            actualizarDeep(node->mbrs[i].child,deep+1);
        }
    }
    void overflow(Node* node){
        Node* node2 = split(node);
        if(node == this->root){
            Node* newRoot = new Node(0);
            newRoot->is_leaf=false;
            node->parent=newRoot;
            node2->parent=newRoot;
            vector<Point> vec1,vec2;
            if(node->is_leaf){
                vec1=node->points;
                vec2=node2->points;
            }else{
                for(int i=0; i<node->mbrs.size(); i++)
                    copy(node->mbrs[i].vertices.begin(), node->mbrs[i].vertices.end(), back_inserter(vec1));
                for(int i=0; i<node2->mbrs.size(); i++)
                    copy(node2->mbrs[i].vertices.begin(), node2->mbrs[i].vertices.end(), back_inserter(vec2));
            }
            MBR mbr1(vec1,node);
            MBR mbr2(vec2,node2);
            newRoot->mbrs.push_back(mbr1);
            newRoot->mbrs.push_back(mbr2);
            actualizarDeep(newRoot,0);
            this->root=newRoot;
        }else{
            Node* padre=node->parent;
            vector<Point> vert1,vert2;
            if(node->is_leaf){
                vert1=node->points;
                vert2 = node2->points;
            }
            else{
                for(int i=0; i<node->mbrs.size(); i++)
                    copy(node->mbrs[i].vertices.begin(), node->mbrs[i].vertices.end(), back_inserter(vert1));
                for(int i=0; i<node2->mbrs.size(); i++){
                    copy(node2->mbrs[i].vertices.begin(), node2->mbrs[i].vertices.end(), back_inserter(vert2));
                }
            }
            MBR mbr1(vert1,node);
            MBR mbr2(vert2,node2);
            padre->mbrs.push_back(mbr2);
            int pos = padre->mbrs.size()-1;
            node2->parent = node->parent;
            if(padre->mbrs.size() > this->capacidad){
                overflow(padre);
            }
            actualizarMBR(node);
        }
    }
    void insert(Node* node,Point p){
        if(node->is_leaf){
            node->points.push_back(p);
            if(node->points.size() > this->capacidad){
                overflow(node);
            }
            actualizarMBR(node);
        }else{
            Node* newNode=chooseSubtree(node,p);
            insert(newNode,p);
        }
    }
    void insert(Point p){
        return insert(this->root,p);
    }
    void print(Node* node){
        if(node->is_leaf){
            cout<<"nivel hoja "<<node->deep<<": ";
            for(int i=0; i<node->points.size(); i++)
                cout<<"("<<node->points[i].x<<","<<node->points[i].y<<") ";
            cout<<endl;
        }else{
            //cout<<"nivel "<<node->deep<<endl;
            for(int i=0; i<node->mbrs.size(); i++){
                cout<<"MBR: ";
                for(int j=0; j<1; j++)
                    cout<<"("<<node->mbrs[i].vertices[j].x<<","<<node->mbrs[i].vertices[j].y<<") "<<endl;
                print(node->mbrs[i].child);
            }
        }
    }

    void print(){
        print(this->root);
    }


};
int main(){
    Rtree tree(3);
    tree.insert(Point(1,5));
    tree.insert(Point(4,1));
    tree.insert(Point(3,14));
    tree.insert(Point(4,10));
    tree.insert(Point(5,7));
    tree.insert(Point(8,13));
    tree.insert(Point(9,9));
    tree.insert(Point(11,11));
    tree.insert(Point(13,12));
    tree.insert(Point(10,6));
    tree.insert(Point(15,8));
    tree.insert(Point(14,4));
    tree.insert(Point(13,2));
    tree.print();

    return 0;
}
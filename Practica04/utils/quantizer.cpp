#include <bits/stdc++.h>
#include "CImg.h"
using namespace std;
using namespace cimg_library;

string int_to_bin(int n){
    bitset<8> bin_x(n);
    return bin_x.to_string();
}

int bin_to_int(int n){
    string bin_string = to_string(n);
    int number = stoi(bin_string, 0, 2);
	return number;
}


class Node{
    public:
        int RED,GREEN,BLUE,contador,nivel;
        Node *pSon[8];
    public:
        Node(int r=0,int g=0, int b=0){
            RED = r;
            GREEN = g;
            BLUE = b;
            contador = 1;
            nivel = 0;
            pSon[0]=pSon[1]=pSon[2]=pSon[3]=pSon[4]=pSon[5]=pSon[6]=pSon[7]=NULL;
        }
};
class Octree{
    public:
        Node *root;
        int Num_color;
        vector<Node *> pallete;
        map<int,vector<Node *>> nivel_node;
    public:
        Octree(){
            root = new Node (0,0,0);
            Num_color =0 ;
        };

        void insert(Node *&temp,vector<int> positions,int r,int g, int b){
            Node * aux  = root;
            while(!positions.empty()){
                int i = positions.front();
                if (!aux->pSon[i]){
                    aux->pSon[i] = new Node (r,g,b);
                    Num_color+=1;
                }
                else{
                    aux->pSon[i]->RED+=r;
                    aux->pSon[i]->GREEN+=g;
                    aux->pSon[i]->BLUE+=b;
                    aux->pSon[i]->contador+=1;
                }
                positions.erase(positions.begin());
                aux = aux->pSon[i];
            }
        }

        void inserttt(Node *&temp,vector<int> &positions,int r,int g, int b){
            if(positions.empty()) return;
            int elemt= positions.front();
            if(temp->pSon[elemt]==0){
                temp->pSon[elemt] = new Node (r,g,b);this->Num_color+=1;
            }
            else{
                temp->pSon[elemt]->RED+=r;
                temp->pSon[elemt]->GREEN+=g;
                temp->pSon[elemt]->BLUE+=b;
                temp->pSon[elemt]->contador+=1;
            }

            positions.erase(positions.begin());
            return insert(temp->pSon[elemt],positions,r,g,b);
        }

        void promedio_color(Node *&temp){
            if(!temp){
                return;
            }
            else{
                for (int i=0;i<8;i++){
                    Node *aux = temp->pSon[i];
                    if(aux){
                        temp->RED       +=aux->RED;
                        temp->GREEN     +=aux->GREEN;
                        temp->BLUE      +=aux->BLUE;
                        temp->contador  +=aux->contador;
                        Num_color-=1;
                    }
                    temp->pSon[i]=0;
                }
            }
        }

        vector<int> index(int r,int g,int b){
            string R = int_to_bin(r);
            string G = int_to_bin(g);
            string B = int_to_bin(b);
            vector<int> salida;
            for(int i=0;i<8;i++){
                string elemeto_aux;
                elemeto_aux.push_back(R[i]); elemeto_aux.push_back(G[i]); elemeto_aux.push_back(B[i]);
                salida.push_back(bin_to_int(stoi(elemeto_aux)));
            }
            insert(root,salida,r,g,b);
            return salida;
        }
        void print(Node *tmp){
            if (tmp == NULL) return;
	        queue<Node *> q;
	        q.push(tmp);
	        while (q.empty() == false){
		        int nodeCount = q.size();
		        while (nodeCount > 0){
			        Node *node = q.front();
			        cout<<"("<<node->RED<<") ";
			        q.pop();
			        if (node->pSon[0]!=NULL)q.push(node->pSon[0]);
			        if (node->pSon[1]!=NULL)q.push(node->pSon[1]);
			        if (node->pSon[2]!=NULL)q.push(node->pSon[2]);
			        if (node->pSon[3]!=NULL)q.push(node->pSon[3]);
			        if (node->pSon[4]!=NULL)q.push(node->pSon[4]);
			        if (node->pSon[5]!=NULL)q.push(node->pSon[5]);
			        if (node->pSon[6]!=NULL)q.push(node->pSon[6]);
			        if (node->pSon[7]!=NULL)q.push(node->pSon[7]);
			        nodeCount--;
		        }
		        cout << endl;
	        }
        }

        void Quantizer_Color(int numero, Node *&tmp){
	        if (tmp == NULL) return;
	        queue<Node *> q;
	        stack<Node *> arr;
	        q.push(tmp);
	        int nvl=0;
	        map<int,vector<Node *>> nivel_nodes;
	        while (q.empty() == false){
		        int nodeCount = q.size();
		        while (nodeCount > 0){
			        Node *node = q.front();
			        node -> nivel = nvl;
			        nivel_nodes[nvl].push_back(node);
			        q.pop();
                    arr.push(node);
			        if (node->pSon[0]!=NULL)q.push(node->pSon[0]);
			        if (node->pSon[1]!=NULL)q.push(node->pSon[1]);
			        if (node->pSon[2]!=NULL)q.push(node->pSon[2]);
			        if (node->pSon[3]!=NULL)q.push(node->pSon[3]);
			        if (node->pSon[4]!=NULL)q.push(node->pSon[4]);
			        if (node->pSon[5]!=NULL)q.push(node->pSon[5]);
			        if (node->pSon[6]!=NULL)q.push(node->pSon[6]);
			        if (node->pSon[7]!=NULL)q.push(node->pSon[7]);
			        nodeCount--;
		        }
		        nvl+=1;
	        }

	        for(int i=7;i!=0;i--){
	            cout<<i<<"\t"<<nivel_nodes[i].size()<<endl;
	            for(auto temp:nivel_nodes[i]){
                    int hojas = nivel_nodes[3].size()+nivel_nodes[4].size();
	                if(Num_color<=numero){cout<<nivel_nodes[1].size()<<" "<<nivel_nodes[2].size()<<endl;break;}
                    for (int i=0;i<8;i++){
                        Node *aux = temp->pSon[i];
                        if(aux){
                            temp->RED       +=aux->RED;
                            temp->GREEN     +=aux->GREEN;
                            temp->BLUE      +=aux->BLUE;
                            temp->contador  +=aux->contador;
                            Num_color       -=1;
                        }
                        temp->pSon[i]   =NULL;
                    }
                    nivel_nodes[i].pop_back();
                }
	        }
        }

        void generate_Pallete(Node *tmp){
            if(!tmp)
                return;
            else
                for(int i=0;i<8;i++){
                    if(tmp->pSon[i]){
                        pallete.push_back(tmp->pSon[i]);
                        generate_Pallete(tmp->pSon[i]);
                    }
                }
        }

        void Create_palette(int numero,vector<Node *>arr){
            numero = sqrt(numero);
            CImg<int> theImage(numero,numero,1,3,1);
            int valor = 0;
            int data = numero;
            while(!arr.empty()){
                for (int i=valor; i<data; i++){if(arr.empty()) break;
                    for (int j=valor; j<data; j++){
                        if(arr.empty()) break;
                        theImage(i,j,0,0) = arr.front()->RED/arr.front()->contador;
                        theImage(i,j,0,1) = arr.front()->GREEN/arr.front()->contador;
                        theImage(i,j,0,2) = arr.front()->BLUE/arr.front()->contador;
                        arr.erase(arr.begin());
	                }
                }
            }
            theImage.display();
        }

        //TEST
         bool sonEmpty(Node *aux){
            for (int i=0;i<8;i++){
                if(aux->pSon[i]!=0){
                    return false;
                }
            }
            return true;
        }

        tuple<int,int,int> Reduccion_Image(vector<int> &positions, Node *temp){
            Node * aux  = root;
            while(!positions.empty()){
                int i = positions.front();
                if(sonEmpty(aux->pSon[i])==true){
                    return make_tuple(aux->pSon[i]->RED/aux->pSon[i]->contador,
                    aux->pSon[i]->GREEN/aux->pSon[i]->contador,
                    aux->pSon[i]->BLUE/aux->pSon[i]->contador);
                }
                positions.erase(positions.begin());
                aux = aux->pSon[i];
            }
        }


        vector<int> DesIndex(int r,int g,int b){
            string R = int_to_bin(r);
            string G = int_to_bin(g);
            string B = int_to_bin(b);
            vector<int> salida;
            for(int i=0;i<8;i++){
                string elemeto_aux;
                elemeto_aux.push_back(R[i]); elemeto_aux.push_back(G[i]); elemeto_aux.push_back(B[i]);
                salida.push_back(bin_to_int(stoi(elemeto_aux)));
            }
            auto it = Reduccion_Image(salida,root);
            salida.clear();
            salida[0]=get<0>(it);
            salida[1]=get<1>(it);
            salida[2]=get<2>(it);
            return salida;
        }
};

int main()
{
    Octree Raiz;
    string name_file;
    cout<<"Inserte nombre de imagen mas extencion: ";
    cin>>name_file;
    CImg<int> file(name_file.c_str());
    CImg<int> theImage(file.width(),file.height(),1,3,1);
    for(int i=0;i<file.width();i++){
        for(int j=0;j<file.height();j++){
            int r = file(i,j,0,0);
            int g = file(i,j,0,1);
            int b = file(i,j,0,2);
            //theImage(i,j,0,0)=r;
            //theImage(i,j,0,1)=g;
            //theImage(i,j,0,2)=b;
            vector<int> aa=Raiz.index(r,g,b);
        }
    }
    file.display();
    int entrada;
    cout<<"Numero de colores: ";
    cin >> entrada;

    Raiz.Quantizer_Color(entrada,Raiz.root);
    Raiz.generate_Pallete(Raiz.root);

    for(int i=0;i<file.width();i++){
        for(int j=0;j<file.height();j++){
            int r = file(i,j,0,0);
            int g = file(i,j,0,1);
            int b = file(i,j,0,2);
            vector<int> aa=Raiz.DesIndex(r,g,b);
            theImage(i,j,0,0)=aa[0];
            theImage(i,j,0,1)=aa[1];
            theImage(i,j,0,2)=aa[2];
        }
    }
    theImage.display();
    theImage.save_bmp("output.bmp");
    Raiz.Create_palette(entrada,Raiz.pallete);
  return 0;
}

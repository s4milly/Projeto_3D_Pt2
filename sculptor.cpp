#include "sculptor.h"
#include <iostream>
#include <stdlib.h>
#include <cmath>
#include <fstream>

using namespace std;

Sculptor::Sculptor(int _nx, int _ny, int _nz)
{
     nx = _nx;
     ny = _ny;
     nz = _nz;

     r = 0;
     g = 0;
     b = 0;
     a = 0;

     v = new Voxel**[_nx]; //alocação de memoria da 1 dimensao da matriz
     for(int i=0; i<_nx; i++){
         v[i] = new Voxel*[_ny]; //alocação de memoria da 2 dimensao da matriz

         for(int j=0; j<_ny; j++){
             v[i][j] = new Voxel [_nz]; //alocação de memoria da 3 dimensao da matriz

             for(int k=0; k<_nz; k++){
                 this -> v[i][j][k].r = 0;
                 this -> v[i][j][k].g = 0;
                 this -> v[i][j][k].b = 0;
                 this -> v[i][j][k].a = 0;
                 this -> v[i][j][k].isOn = false;
             }
         }
     }

}

Sculptor::~Sculptor()
{
   //liberacao da memoria alocada
    for(int i=0; i<nx; i++){
        for(int j=0; j<ny; j++){
            delete [] v[i][j]; //liberacao da ultima alocacao
        }
        delete [] v[i]; //liberacao da penultima
    }
    delete [] v; //liberacao da primeira
}

void Sculptor::setColor(float red, float green, float blue, float alpha){
    //atribuicao das cores a partir dos parametros
    this -> r = red;
    this -> g = green;
    this -> b = blue;
    this -> a = alpha;

}

void Sculptor::putVoxel (int x, int y, int z){
    //ativaçao de um unico voxel
    this -> v [x][y][z].r = this -> r;
    this -> v [x][y][z].g = this -> g;
    this -> v [x][y][z].b = this -> b;
    this -> v [x][y][z].a = this -> a;
    this -> v [x][y][z].isOn = true;

}

void Sculptor::cutVoxel (int x, int y, int z){
    this -> v [x][y][z].isOn = false; //desativaçao de uma unico voxel
}

void Sculptor::writeOFF(char *filename){
    int total_vox=0, cont_vox=0;

    ofstream arquivo; // objeto da classe ofstream
    arquivo.open(filename); //abrindo o fluxo para o arquivo

    for (int i = 0; i < nx ; i++){
        for (int j = 0; j < ny; j++){
            for (int k = 0; k < nz; k++){
                if(this -> v[i][j][k].isOn == true){
                        total_vox++;
                    }
                }
            }
        }

    arquivo << "OFF" << endl;
    arquivo << 8 * total_vox <<" "<< 6 * total_vox <<" "<<"0"<<endl;

 // definindo as coordenadas dos vertices do voxel
    for (int i = 0; i <nx ; i++){
        for (int j = 0; j <ny; j++){
            for (int k = 0; k <nz; k++){
                  if(this->v[i][j][k].isOn == true){

                     arquivo << i - 0.5 <<" "<< j + 0.5 <<" "<< k - 0.5 <<endl;
                     arquivo << i - 0.5 <<" "<< j - 0.5 <<" "<< k - 0.5 <<endl;
                     arquivo << i + 0.5 <<" "<< j - 0.5 <<" "<< k - 0.5 <<endl;
                     arquivo << i + 0.5 <<" "<< j + 0.5 <<" "<< k - 0.5 <<endl;
                     arquivo << i - 0.5 <<" "<< j + 0.5 <<" "<< k + 0.5 <<endl;
                     arquivo << i - 0.5 <<" "<< j - 0.5 <<" "<< k + 0.5 <<endl;
                     arquivo << i + 0.5 <<" "<< j - 0.5 <<" "<< k + 0.5 <<endl;
                     arquivo << i + 0.5 <<" "<< j + 0.5 <<" "<< k + 0.5 <<endl;

                  }
                }
            }
        }
    //especificaçoes das faces e apresentacao das cores no formato RGBA
        for (int i = 0; i <nx ; i++){
            for (int j = 0; j <ny; j++){
                for (int k = 0; k <nz; k++){
                    if(this->v[i][j][k].isOn == true){

                        arquivo << "4" << " " << 8 * cont_vox + 0 << " " << 8 * cont_vox + 3 << " " << 8 * cont_vox + 2 << " "  << 8 * cont_vox + 1 <<" " << v [i][j][k].r << " " << v [i][j][k].g << " " << v [i][j][k].b << " " << v [i][j][k].a << endl;
                        arquivo << "4" << " " << 8 * cont_vox + 4 << " " << 8 * cont_vox + 5 << " " << 8 * cont_vox + 6 << " "  << 8 * cont_vox + 7 <<" " << v [i][j][k].r << " " << v [i][j][k].g << " " << v [i][j][k].b << " " << v [i][j][k].a << endl;
                        arquivo << "4" << " " << 8 * cont_vox + 0 << " " << 8 * cont_vox + 1 << " " << 8 * cont_vox + 5 << " "  << 8 * cont_vox + 4 <<" " << v [i][j][k].r << " " << v [i][j][k].g << " " << v [i][j][k].b << " " << v [i][j][k].a << endl;
                        arquivo << "4" << " " << 8 * cont_vox + 0 << " " << 8 * cont_vox + 4 << " " << 8 * cont_vox + 7 << " "  << 8 * cont_vox + 3 <<" " << v [i][j][k].r << " " << v [i][j][k].g << " " << v [i][j][k].b << " " << v [i][j][k].a << endl;
                        arquivo << "4" << " " << 8 * cont_vox + 3 << " " << 8 * cont_vox + 7 << " " << 8 * cont_vox + 6 << " "  << 8 * cont_vox + 2 <<" " << v [i][j][k].r << " " << v [i][j][k].g << " " << v [i][j][k].b << " " << v [i][j][k].a << endl;
                        arquivo << "4" << " " << 8 * cont_vox + 1 << " " << 8 * cont_vox + 2 << " " << 8 * cont_vox + 6 << " "  << 8 * cont_vox + 5 <<" " << v [i][j][k].r << " " << v [i][j][k].g << " " << v [i][j][k].b << " " << v [i][j][k].a << endl;

                        cont_vox++;

                    }
                }
            }
        }

    arquivo.close();// fechando o fluxo
}

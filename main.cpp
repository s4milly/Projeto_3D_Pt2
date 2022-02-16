#include <iostream>
#include "sculptor.h"
#include "interpretador.h"
#include "putVoxel.h"
#include "putBox.h"
#include "putSphere.h"
#include "putEllipsoid.h"
#include "cutVoxel.h"
#include "cutBox.h"
#include "cutSphere.h"
#include "cutEllipsoid.h"

//using namespace std;

int main()
{
    Sculptor *s1;

    Interpretador parser;

    std::vector<FiguraGeometrica*> figs;
    figs = parser.parse("C:\\Users\\franc\\Documents\\entrada.txt");

    s1 = new Sculptor(parser.getDimx(), parser.getDimy(), parser.getDimz());

    for(size_t i=0; i<figs.size(); i++){
        std::cout << "draw\n";
        figs[i]->draw(*s1);
    }

    s1->writeOFF("C:\\Users\\franc\\Documents\\saida.off");

    for(size_t i=0; i<figs.size(); i++){
        delete figs[i];
    }
    delete s1;
    return 0;
}

#ifndef ABB_H_INCLUDED
#define ABB_H_INCLUDED
#include<iostream>
 using namespace std;

 ///Binary Search Tree
class NodoArbol
{
public:
    int iInfo;
    NodoArbol *pIzq, *pDer;
    NodoArbol( ){ pIzq = pDer = NULL; }
    NodoArbol(int iDato)
    { iInfo = iDato; pIzq = pDer = NULL; }
};

class ABB
{
private:
    NodoArbol *pRaiz;
public:
    //Constructor
    ABB( ) { pRaiz = NULL; }
    //Destructor
    ~ABB( ) { }
    //Otros métodos de la clase
    /// Determinar si un nodo está o no en el árbol



///Returns true if exists a node from a BST, using Recursiveness
bool buscar2(NodoArbol *pP,int valor){
    if(pP == NULL)
        return false;
    else if(pP->iInfo== valor)
        return true;
    else if( pP->iInfo >valor)
        buscar2(pP->pIzq,valor);
    else
        buscar2(pP->pDer,valor);
}

bool buscar(int valor){
    return buscar2(pRaiz,valor);
}


///Add all the nodes from a BST
int suma(NodoArbol *pP){
    if(pP == NULL)
        return 0;
    if(pP != NULL){
        return pP->iInfo + suma(pP->pIzq) + suma(pP->pDer);
    }
}

int sumaArbol(){
    return suma(pRaiz);
}

/// Calculates the height from a BST

int altura(NodoArbol *pP){

    if(pP==NULL)
        return 0;
    else{
            return 1 + max(altura(pP->pIzq),altura(pP->pDer));
    }

}

int alturaarbol(){
    return altura(pRaiz);
}
/// This functions finds the father from a Node
NodoArbol* encuentraPadre (int iValor)
{
        NodoArbol *pPadre, *pHijo;
        pHijo = pRaiz;
        pPadre = NULL;
        while (pHijo != NULL && pHijo->iInfo != iValor)
        {
            pPadre = pHijo;
            pHijo = (pHijo->iInfo > iValor ? pHijo->pIzq : pHijo->pDer);
        }
        return pPadre;
}

    void meterABB (int iValor)
    {
        NodoArbol *pPadre = encuentraPadre(iValor);
        NodoArbol *pNuevo = new NodoArbol (iValor);
        if( pPadre == NULL) //Agrega el primer nodo del árbol
            pRaiz = pNuevo;
        else
        { //Agrega un nodo hoja
            if ( pPadre->iInfo > iValor )
                pPadre->pIzq = pNuevo;
            else
                pPadre->pDer = pNuevo;
        }
    }


    //Mayor de los menores
    NodoArbol* predecesor (NodoArbol *pActual)
    {
        NodoArbol *pP = pActual->pIzq;
        while (pP->pDer != NULL )
            pP = pP->pDer;
        return pP;
    }

    //Menor de los mayores
    NodoArbol* sucesor (NodoArbol *pActual)
    {
        NodoArbol *pP = pActual->pDer;
        while (pP->pIzq != NULL )
            pP = pP->pIzq;
        return pP;
    }

    void sacarABB(int iValor)
    {
        NodoArbol *pPadre = encuentraPadre(iValor);
        NodoArbol *pNodoABorrar;
        if (pPadre == NULL)
            pNodoABorrar = pRaiz;
        else
            pNodoABorrar=(pPadre->iInfo > iValor? pPadre->pIzq : pPadre->pDer);
        //Encontrar substituto cuando el nodo a borrar tiene 2 hijos
        if (pNodoABorrar->pIzq != NULL && pNodoABorrar->pDer != NULL)
        {
            NodoArbol *pSubstituto = predecesor(pNodoABorrar);
            int iNuevovalor = pSubstituto->iInfo;
            sacarABB (pSubstituto->iInfo);
            pNodoABorrar->iInfo = iNuevovalor;
        }
        else if (pPadre == NULL)
        { //Borra nodo raíz el cual solo tiene un hijo
            if (pNodoABorrar->pDer == NULL)
                pRaiz = pNodoABorrar->pIzq;
            else
                pRaiz = pNodoABorrar->pDer;
        }
        else if (pPadre->iInfo > iValor) //Borra nodo con 0 o 1 hijo
            if (pNodoABorrar->pIzq == NULL)
                pPadre->pIzq = pNodoABorrar->pDer;
            else
                pPadre->pIzq = pNodoABorrar->pIzq;
            else if (pNodoABorrar->pDer == NULL)
                pPadre->pDer =pNodoABorrar->pIzq;
            else
                pPadre->pDer = pNodoABorrar->pDer;
    }
    void ancestor(int iValor);
    int single(NodoArbol *pP,int iCont);
    int singleParentCount();
    int singleParentcooount();
    int sinngle(NodoArbol *P);
};


void ABB::ancestor(int iValor){

    NodoArbol *pAncestor = NULL;
    NodoArbol *pP = pRaiz;
    if(buscar(iValor)== true){
        while (pP->iInfo != iValor){
            cout<<pP->iInfo<<" ";
            pP =(pP->iInfo > iValor ? pP->pIzq : pP->pDer);
        }
    }
    else{
        cout<<"No existe el nodo"<<endl;
    }
}

int ABB :: single(NodoArbol *pP,int iCont){

    if(pP != NULL){
        if( (pP->pIzq != NULL && pP->pDer == NULL) || (pP->pIzq == NULL && pP->pDer != NULL) ){
            iCont++;
        }
        iCont = single(pP->pIzq,iCont);
        iCont = single(pP->pDer,iCont);
    }
    return iCont;
}

int ABB::singleParentCount(){

    int iCont = 0;
    iCont = single(pRaiz,iCont);
    return iCont;
}



int ABB :: singleParentcooount(){

    return sinngle(pRaiz);

}

int ABB :: sinngle(NodoArbol *P){

    if(P !=NULL){
        if( (P->pDer != NULL && P->pIzq ==NULL) || (P->pDer == NULL && P->pIzq !=NULL)){
            return 1 + sinngle(P->pDer) + sinngle(P->pIzq);
        }
    }
    else{
        return 0;
    }

}



#endif // ABB_H_INCLUDED

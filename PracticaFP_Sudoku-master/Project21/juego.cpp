#include "juego.h"
//RECIBE UN JUEGO Y UN SUDOKU LO INICIALIZA Y CARGA EL TABLERO . DEVUELVE TRUE SI HA SIDO POSIBLE LA CARGA Y FALSE DE LO CONTRARIO
bool cargaJuego(tJuego & juego, const tSudoku &sudoku){
    bool devolver;
    iniciaTablero(juego.tablero);
    devolver=cargaTablero(sudoku.fichero,juego.tablero);
    return devolver;
}
//RECIBE UN JUEGO Y UN SUDOKU Y LOS INICIALIZA
void iniciaJuego(tJuego & juego, const tSudoku &sudoku){
    juego.terminado=false;
    cargaJuego(juego,sudoku);
    juego.sudoku.fichero=sudoku.fichero;
    juego.sudoku.nivel=sudoku.nivel;
}
//RECIBE UN JUEGO.MUESTRA TODA LA INFORMACION REVELANTE DEL JUEGO ACTUAL. EL SUDOKU JUGADO, LA DIFICULTAD Y EL TABLERO
void mostrarJuego(const tJuego &juego){
    cout<<"SUDOKU: "<<juego.sudoku.fichero<<endl;
    cout<<"DIFICULTAD ";
    switch (juego.sudoku.nivel) {
			case 0:
				cout << "FACIL"<<endl;
				break;
			case 1:
				cout << "MEDIO" << endl;
				break;
			case 2:
				cout << "DIFICIL" << endl;
				break;
		}
    cout<<endl<<endl;
    dibujarTablero(juego.tablero);
}
//Muestra todas las posibilidades y itera hasta que el usuario le introduzca una opcion posible
int mostrarMenuJugada(){
   int selector;
    do {
        cout<<"1: Ver posibles valores de una casilla vacia"<<endl;
        cout<<"2: Colocar valor en una casilla"<<endl;
        cout<<"3: Borrar valor de una casilla"<<endl;
        cout<<"4: Reiniciar el tablero"<<endl;
        cout<<"5: Autocompletar celdas simples"<<endl;
        cout<<"0: Abortar la resolucion y volver al menu principal"<<endl;
        cin>>selector;
    }while(selector>5||selector<0);
    return selector;
}
//RECIBE UN SUDOKU Y HACE TODO LO NECESARIO PARA JUGARLO, ASI COMO EL LOOP DE JUEGO.
int JugarUnSudoku(tSudoku &sudoku){
    int opcion=-1;
	bool exito = false;
	tJuego juego;
	iniciaJuego(juego, sudoku);
	mostrarJuego(juego);
    while(opcion!=0&&!exito){
		
        opcion=mostrarMenuJugada();
		
        switch(opcion){
            case 1:
                Opcion1(juego);
                break;
            case 2:
				Opcion2(juego);
                //colocar valor en una casilla
                break;
            case 3:
                Opcion3(juego);
                //borrar valor de una casilla
                break;
            case 4:
				Opcion4(juego,sudoku);
                //reiniciar tablero
                break;
            case 5:
                //autocompletaar simples
				Opcion5(juego);
                break;
        }
		system("pause");
		if (opcion != 0) {
			mostrarJuego(juego);
		}
		exito = tableroLleno(juego.tablero);
    }
	if (exito) {
		return sudoku.nivel+1;
	}
	return 0;
}
//
void Opcion1(tJuego &juego){
    int i,j;
    PedirCasilla(i,j);
    mostrar(juego.tablero[i][j].posibles);
}
void Opcion2(tJuego &juego) {
	int i, j, numero;
	bool Hasidoposible;
	PedirCasilla(i, j);

	do {
		cout << "Introduzca un numero entre 1 y 9" << endl;
		cin >> numero;
	} while (numero < 1 || numero>9);
	if (juego.tablero[i][j].estado == VACIO) {
		Hasidoposible = ponerNum(juego.tablero, i, j, numero);
		if (!Hasidoposible) {
			cout << "No es posible colocar el valor en la casilla seleccionada" << endl;
		}
	}
	else {
		cout << "No es posible poner un numero en una casilla no vacia" << endl;
	}
}

void Opcion3(tJuego &juego){
    
    int i,j;
    bool Hasidoposible;
    PedirCasilla(i,j);
	Hasidoposible = borraNum(juego.tablero, i, j);
	if(!Hasidoposible){
		cout<<"No ha sido posible borrar el numero, ya que no es una casilla rellena"<<endl;
	}
}

void Opcion4(tJuego &juego, tSudoku &sudoku){
    
    iniciaJuego(juego,sudoku);
    

}
void PedirCasilla(int &x,int &y){
    x=-1;
    y=-1;
    cout<<"Indique la casilla correspondiente;"<<endl;
    do {
    cout<<"FIL: ";
    cin>>x;
    }while(x<1||x>9);
    do {
    cout<<"COL: ";
    cin>>y;
    }while(y<1||y>9);
	x--;
	y--;
}
void Opcion5(tJuego &juego){
    rellenarSimples(juego.tablero);
    cout<<"Casillas simples rellenadas"<<endl;
}





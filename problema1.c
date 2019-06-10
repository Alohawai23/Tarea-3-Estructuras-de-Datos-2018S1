#include <stdio.h>
#include <stdlib.h>

struct graph{
    int **adj; //matriz
    int V; //cantidad de vertices
};

typedef struct graph *Grafo;
/*****
* int** crear_matriz
******
* Crea la matriz de adyacencia del grafo, inicializando todo en 0
******
* Input:
* int v: cantidad de vertices del grafo
* .......
******
* Returns:
* int** matriz, matriz de adyacencia del grafo
*****/
int **crear_matriz(int v){
	int i,j;
	int **matriz=malloc(v*sizeof(int *));
	for(i=0;i<v;i++)
	 	matriz[i]=malloc(v*sizeof(int));
	 	for(i=0;i<v;i++)
	 	for(j=0;j<v;j++)
	 		matriz[i][j]=0;
	 	return matriz;
}
/*****
* Grafo crear_grafo
******
* Inicializa el grafo con la cantidad de vertices entregados, sin arcos
******
* Input:
* int v: cantidad de vertices con el cual crear el grafo
* .......
******
* Returns:
* Grafo G, Grafo creado, sin arcos
*****/
Grafo crear_grafo(int v){
	Grafo G = malloc(sizeof*G); //crea cabecera del grafo
	G->V = v;
	G->adj = crear_matriz(v); //Crea la matriz de adyacencia con ceros
	return G;
}
/*****
* Grafo insertar
******
* Inserta un arco dentro del grafo, y actualiza la matriz de adyacencia
******
* Input:
* int o: vertice de origen del arco insertado
* int d: vertice de llegada del arco insertado
* Grafo G: Grafo en el cual se trabaja
* .......
******
* Returns:
* Grafo G, Grafo actualizado
*****/
Grafo insertar(int o, int d, Grafo G){
    G->adj[o][d] = 1;
    return G;
}
/*****
* void liberar
******
* Borra los nodos del grafo mediante liberada de memoria
******
* Input:
* Grafo G : grafo que sera eliminado
* .......
******
* Returns:
* vacio
*****/
void liberar(Grafo G){
  int i;
	int **t=G->adj;
	for(i=0;i<G->V;i++){
		free(t[i]);
    }
    free(t);
	free(G);
}
/*****
* int* DFS
******
* Hace un DFS del grafo, marcando los vertices como visitados.
******
* Input:
* int v: vertice sobre el cual se comienza el DFS
* int n: cantidad de vertices del grafo
* Grafo G: Grafo sobre el cual se realizara DFS
* int* visitado: arreglo que indica si un vertice ha sido visitado o no
* .......
******
* Returns:
* int* visitado, Arreglo de enteros con 0 y 1; posee 1 si la ciudad, representada con la posicion del arreglo, es alcanzable y 0 si no lo es.
*****/
int *DFS(int v, int n, Grafo G, int *visitado){
    int i;
    for(i = 0; i < n; i++){
        if(G->adj[v][i] == 1 && visitado[i] != 1){
            visitado[i] = 1;
            visitado = DFS(i,n,G, visitado);
        }
    }
    return visitado;
}
/*****
* int cantidad
******
* Calcula la cantidad de vertices no alcanzables por un vertice dado
******
* Input:
* int* visitado: Arreglo de enteros con 0 y 1; posee 1 si la ciudad, representada con la posicion del arreglo(ej: ciudad 2 = posicion 2 del arreglo), es alcanzable y 0 si no lo es.
* int n: cantidad de vertices del grafo
* .......
******
* Returns:
* int Nalcanzable, Cantidad de vertices inalcanzables
*****/
int cantidad(int *visitado,int n){
    int i, Nalcanzable = 0;
    for(i = 0; i < n; i++){
        if(visitado[i] != 1) Nalcanzable++;
    }
    return (Nalcanzable - 1); //Se resta 1 porque si no se consideraria el mismo nodo en el que se esta como inalcanzable
}
/*****
* int main
******
* Imprime las ciudades inalcanzables desde los vertices pedidos por medio de la utilizacion de grafos.
******
* Input:
* No recibe ningun parametro de input
* .......
******
* Returns:
* retorna 0 si la funcion compila correctamente
*****/
int main() {
    int i, j, N, M, Q, O, D, vertice, NOalcanzables;
    Grafo gra;
    scanf("%d\n",&N);
    scanf("%d\n",&M);
    gra = crear_grafo(N);
    for(i = 0; i < M; i++){
        scanf("%d %d\n",&O,&D);
        gra = insertar(O,D,gra);
    }
    scanf("%d\n",&Q);
    printf("%d\n",Q);
    for(i = 0; i < Q; i++){
        scanf("%d\n", &vertice);
        int *visitados = (int*)malloc(sizeof(int)*N);
        for(j = 0; j < N; j++) visitados[j] = 0;
        visitados = DFS(vertice, N, gra, visitados); //ENTEGA UN ARREGLO QUE CADA POSICION REPRESENTA UNA CIUDAD (Posicion 0 ciudad 0, posicion 1 ciudad 1, ...) Y SI SU VALOR ES 1, ENTONCES ESA CIUDAD ES ALCANZABLE POR EL VERTICE
        NOalcanzables = cantidad(visitados, N); // ENTREGA LA CANTIDAD DE CIUDADES NO ALCANZABLES POR EL VERTICE PEDIDO
        if(NOalcanzables == 0)printf("%d\n",NOalcanzables);
        if(NOalcanzables != 0)printf("%d ",NOalcanzables);
        for(j = 0; j < N; j++){
            if(j != vertice){ //Se pregunta si la ciudad con la que se esta viendo si es alcanzable es la propia ciudad
                if(visitados[j] != 1 && NOalcanzables == 1) printf("%d\n",j);
                if(visitados[j] != 1 && NOalcanzables != 1) {
                    printf("%d ",j);
                    NOalcanzables--;
                }
            }
        }
        free(visitados);
    }
    liberar(gra);
    return 0;
}

//Tarea 3 - Algoritmos y Estructuras de Datos
//Ignacio Marzotta (23.601.779-6)
//Cristobal Zapata (19.962.025-8)

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

//Definicion de lista dinamica
struct listNode
{
    char info;
    struct listNode *next;
};
typedef struct listNode tNode;
typedef tNode *List;

//Definicion de arbol binario
struct treeNode{
    char info;
    struct treeNode *left;
    struct treeNode *right;
};
typedef struct treeNode btNode;
typedef btNode *BT;


//Funcion encargada de determinar el tamaño/cantidad de nodos de una lista dinamica.
int listLength(List L)
{
    List aux;
    int cont;

    cont = 0;
    aux = L;  
    while(aux != NULL)
    {
        cont = cont+1;
        aux = aux->next;
    }
    return cont;
} 

//Funcion encargada de crear un nodo apto para lista dinamica
List createListNode(char x)
{
    List aux;

    aux = malloc(sizeof(tNode));
    if (aux != NULL)
    {
        aux->info = x;
        aux->next = NULL;
    }
    else
    {
        printf("\n No se pudo reservar memoria suficiente para un nuevo nodo, el programa se va a cerrar.\n");
        system ( "PAUSE" );
        exit(1);
    }
    return aux;
}

//Funcion encargada de insertar un nodo al final de la lista, con el fin de generar la traduccion final.
List insertInListPosition(List L, char newValue)
{
    List pNode, aux;
    int i;

    pNode = createListNode(newValue);    
    aux = L;

    if(L == NULL)
    {
        L = pNode;
    }
    else
    {
        while (aux->next != NULL)
        {
            aux = aux->next;
        }
        aux->next = pNode;
    }
    aux = NULL;
    pNode = NULL;
    return L;
}

//Crear un nodo apto para un arbol binario.
BT createNode(char value)
{
   BT aux;

   aux = (BT)malloc(sizeof(tNode));
   if (aux != NULL)
   {
      aux->info = value;
      aux->left = NULL;
      aux->right = NULL;
   }
   else
   {
       printf("\nNo hay memoria suficiente.");
       exit(1);
   }
   return aux;
}

//Funcion encargada de crear el arbol binario principal de codigo morse.
BT createMainBT()
{
    BT T;
    T = createNode('#');
    T->left = createNode('E');
    T->right = createNode('T');
    T->left->left = createNode('I');
    T->left->right = createNode('A');
    T->right->left = createNode('N');
    T->right->right = createNode('M');
    T->left->left->left = createNode('S');
    T->left->left->right = createNode('U');
    T->left->right->left = createNode('R');
    T->left->right->right = createNode('W');
    T->right->left->left = createNode('D');
    T->right->left->right = createNode('K');
    T->right->right->left = createNode('G');
    T->right->right->right = createNode('O');
    T->left->left->left->left = createNode('H');
    T->left->left->left->right = createNode('V');
    T->left->left->right->left = createNode('F');
    T->left->left->right->right = createNode('#');
    T->left->right->left->left = createNode('L');
    T->left->right->left->right = createNode('#');
    T->left->right->right->left = createNode('P');
    T->left->right->right->right = createNode('J');
    T->right->left->left->left = createNode('B');
    T->right->left->left->right = createNode('X');
    T->right->left->right->left = createNode('C');
    T->right->left->right->right = createNode('Y');
    T->right->right->left->left = createNode('Z');
    T->right->right->left->right = createNode('Q');
    T->right->right->right->left = createNode('#');
    T->right->right->right->right = createNode('#');
    T->left->left->left->left->left = createNode('5');
    T->left->left->left->left->right = createNode('4');
    T->left->left->left->right->right = createNode('3');
    T->left->left->right->right->left = createNode('#');
    T->left->left->right->right->right = createNode('2');
    T->left->right->left->left->left = createNode('&');
    T->left->right->left->left->right = createNode('#');
    T->left->right->left->right->left = createNode('+');
    T->left->right->right->left->right = createNode('#');
    T->left->right->right->right->right = createNode('1');
    T->right->left->left->left->left = createNode('6');
    T->right->left->left->left->right = createNode('=');
    T->right->left->left->right->left = createNode('/');
    T->right->left->right->left->right = createNode('#');
    T->right->left->right->right->left = createNode('(');
    T->right->right->left->left->left = createNode('7');
    T->right->right->left->left->right = createNode('#');
    T->right->right->left->right->right = createNode(165);// �
    T->right->right->right->left->left = createNode('8');
    T->right->right->right->right->left = createNode('9');
    T->right->right->right->right->right = createNode('0');
    T->left->left->right->right->left->left = createNode('?');
    T->left->left->right->right->left->right = createNode('_');
    T->left->right->left->left->right->left = createNode('"');
    T->left->right->left->right->left->right = createNode('.');
    T->left->right->right->left->right->left = createNode('@');
    T->left->right->right->right->right->left = createNode(39); // '
    T->right->left->left->left->left->right = createNode('-');
    T->right->left->right->left->right->left = createNode(';');
    T->right->left->right->left->right->right = createNode('!');
    T->right->left->right->right->left->right = createNode(')');
    T->right->right->left->left->right->right = createNode(',');
    T->right->right->right->left->left->left = createNode(':');

    return T;
}

//Esencialmente, funcion buscaElemento, busca si el elemento existe en un arbol y devuelve verdadero o falso.
bool findElement(BT A, char value)
{
    if (A == NULL) 
    {
	    return false;
    }
    if (A->info == value) 
    {
        return true;
    }
    return findElement(A->left, value) || findElement(A->right, value);
}

//Funcion recursiva para encontrar el camino desde la raiz hasta un caracter, por ende determinando que caracter agregar.
void translateCharacter(BT T, char value, FILE *fp)
{
    if (T->info == value)
    {
        return;
    }
    if (findElement(T->left, value))
    {
        fprintf(fp, ".");
        return translateCharacter(T->left, value, fp);
    }
    else
    {
        fprintf(fp, "-");
        return translateCharacter(T->right, value, fp);
    }
}

//Opcion 1: Lenguaje natural a morse.
//Esta funcion utiliza el arbol binario principal y un archivo solicitado al usuario que contiene texto en lenguaje natural. Devuelve el mismo archivo con la traduccion en morse agregado en una linea nueva; Esto se logra mediante el uso de una lista dinamica dada su flexibilidad y para agregar los caracteres en el orden correcto.
void naturalToMorse(BT mainTree)
{
    char fileName[100]="";      //Definicion nombre archivo
    char ch;                    //Var temporal para lectura de caracteres de archivo
    int cont = 0;               //Contador utilizado para reconocer espacios en el texto a traducir.
    BT aux = mainTree;          //Definicion de arbol binario auxiliar
    FILE *fp;                   //Puntero de archivo a abrir
    List L = NULL;              //Definicion de lista dinamica principal donde se almacena la traduccion.
    List auxList = NULL;        //Definicion de lista auxiliar para recorrer la lista principal.

    printf("\nIngresa el nombre del archivo: ");  //Solicitar nombre de archivo
    scanf("%s",&fileName);
    fp = fopen(fileName, "r");                  //Abrir en modo lectura

    //Chequear si el archivo existe, de ser asi, cerrarlo de modo lectura. Esto es para evitar que si no exista, el archivo se cree.
    if (fp == NULL)
    {
        //Si no se puede reservar la memoria para el archivo, o no se encontro un archivo con ese nombre, cerrar programa.
        printf("Archivo invalido, el programa se va a cerrar. \n");
        system ( "PAUSE" );
        exit(1);
    }
    else
    {
        fclose(fp);                     //Cerrar archivo de modo lectura una vez se confirma que existe

        fp = fopen(fileName, "a+");     //Abrirlo en modo edicion para agregar la nueva linea de la traduccion.
        fprintf(fp, "\n");              //Agregar linea nueva. Ese \n es utilizado por el loop de agregar los caracteres a la lista dinamica.
        fclose(fp);                     //Cerrar el archivo en modo edicion
        
        fp = fopen(fileName, "r");      //Abrir archivo en modo lectura para agregar cada uno de los caracteres a traducir a la lista dinamica.

        while ((ch = fgetc(fp)) != '\n')
        {
            L=insertInListPosition(L, ch);
        }
    }
    
    fclose(fp);                     //Cerrar archivo en modo lectura
    fp = fopen(fileName, "a");      //Abrir archivo en modo edicion para agregar el texto traducido.

    int totalNodes = listLength(L); //Obtener tamaño de lista
    auxList = L;                    //Inicializar lista auxiliar

    while(auxList != NULL)
    {
        if(auxList->info != ' ')
        {
            translateCharacter(mainTree, auxList->info, fp);
            fprintf(fp," ");
        }
        else
        {
            fprintf(fp," ");
        }
        auxList = auxList->next;
    }

    L = NULL;                       //Dejar la lista en nulo
    auxList = NULL;                 //Dejar la lista auxiliar en nulo
    fclose(fp);                     //Cerrar archivo definitivamente.
}

//Opcion 2: Codigo Morse a Lenguaje natural.
//Esta funcion utiliza el arbol binario principal y un archivo solicitado al usuario que contiene texto en codigo morse. Devuelve el mismo archivo con la traduccion en lenguaje natural agregado en una linea nueva; Esto se logra mediante el uso de una lista dinamica dada su flexibilidad y para agregar los caracteres en el orden correcto.
void morseToNatural(BT mainTree)
{
    char fileName[100]="";      //Definicion nombre archivo
    char ch;                    //Var temporal para lectura de caracteres de archivo
    int cont = 0;               //Contador utilizado para reconocer espacios en el texto a traducir.
    BT aux = mainTree;          //Definicion de arbol binario auxiliar
    FILE *fp;                   //Puntero de archivo a abrir
    List L = NULL;              //Definicion de lista dinamica principal donde se almacena la traduccion.
    List auxList = NULL;        //Definicion de lista auxiliar para recorrer la lista principal.

    //Solicitar nombre de archivo al usuario
    printf("\nIngresa el nombre del archivo: ");  
    scanf("%s",&fileName);

    //Abrir archivo
    fp = fopen(fileName, "r");

    //Chequear si el archivo existe, de ser asi, cerrarlo de modo lectura. Esto es para evitar que si no exista, el archivo se cree.
    if (fp == NULL)
    {
        //Si no se puede reservar la memoria para el archivo, o no se encontro un archivo con ese nombre, cerrar programa.
        printf("Archivo invalido, el programa se va a cerrar. \n");
        system ( "PAUSE" );
        exit(1);
    }
    else
    {
        fclose(fp);                     //Cerrar archivo de modo lectura una vez se confirma que existe
        fp = fopen(fileName, "a");      //Abrirlo en modo edicion para agregar la nueva linea de la traduccion
        fprintf(fp, "\n");              //Agregar linea nueva
        fclose(fp);                     //Cerrar el archivo en modo edicion
        fp = fopen(fileName, "r");      //Abrir archivo en modo lectura para traducir y popular la lista dinamica

        //Leer letra por letra hasta alcanzar fin de archivo
        while ((ch = fgetc(fp)) != '\n')
        {
            switch (ch)
            {
            case '.':
                cont = 0;               //Reiniciar contador de espacios
                aux = aux->left;        //De ser un '.', avanzar hacia el hijo izquierdo.
                break;
            case '-':
                cont = 0;               //Reiniciar contador de espacios.
                aux = aux->right;       //De ser un '-', avanzar hacia el hijo derecho.
                break;
            default:
                cont += 1;              //De ser otro caracter, se asume que es espacio, agregar 1 al contador
                if(cont == 2)
                {
                    //De ser 2 espacios consecutivos, agregar un espacio a la lista, a modo de separacion entre 2 palabras.
                    L=insertInListPosition(L, ' ');
                    cont = 0;
                }
                else
                {
                    //Agregar caracter a lista dinamica
                    L=insertInListPosition(L, aux->info);
                    aux = mainTree;
                }
                break;
            }
        }
    }
    
    fclose(fp);                     //Cerrar archivo en modo lectura
    fp = fopen(fileName, "a");      //Abrir archivo en modo edicion para agregar el texto traducido.

    int totalNodes = listLength(L); //Obtener tamaño de lista
    int i = 0;                      //Contador basico
    auxList = L;                    //Inicializar lista auxiliar

    //Recorrer la lista dinamica y agregar los caracteres al archivo
    while(i < totalNodes)
    {
        fprintf(fp, "%c", auxList->info);
        auxList = auxList->next;
        i++;
    }
    fclose(fp);                     //Cerrar archivo definitivamente.
}

//Funcion que muestra el menu de seleccion con cada iteracion.
int showSelectionMenu()
{
    int x;              //
    char temp;          //Variable temporal para limpiar el buffer. Sirve para casos en los que se le solicite al usuario un string luego de ingresar un entero.
    printf("1. Lenguaje natural a codigo morse. \n");
    printf("2. Codigo morse a lenguaje natural. \n");
    printf("3. Salir. \n");
    printf("Ingresa una opcion: ");
    
    scanf("%d", &x);    //Solicitar input de seleccion

    //Extracto necesario para que el programa no se caiga al ingresar chars en la seleccion de menu.
    while(!(x == 1) && !(x == 2) && !(x == 3))
    {
        printf("Por favor, ingrese una seleccion valida. \n>>");
        scanf("%c", &temp);
        scanf("%d", &x);
    }

    return x;
}

int main()
{
    int selection = 0;                      //Definicion de seleccion para el menu
    BT mainTree = createMainBT();               //Crear arbol principal
    
    //Ciclo principal de menu de seleccion
    while (selection != 3)
    {
        selection = showSelectionMenu();    //Mostrar menu de seleccion

        if(selection == 1)
        {
            //Natural a morse
            naturalToMorse(mainTree);
            printf("Se ha codificado el archivo.\n\n");
            system ( "PAUSE" );
        }
        else if(selection == 2)
        {
            //Morse a natural
            morseToNatural(mainTree);
            printf("Se ha decodificado el archivo.\n\n");
            system ( "PAUSE" );
        }
    }
    return 0;
}
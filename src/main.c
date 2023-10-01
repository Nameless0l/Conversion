 #include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

// Il est important de noter que nos conversions partent jusqu'a la base 36 
int searchIndex(char *table, char element)
{
    for (size_t i = 0; i < strlen(table); i++)
    {
        if (table[i] == element)
        {
            return i + 10;
        }
    }
    return -1;
}

//Ici nous parsons les  chaines de caracteres entrees eu clavier pour connaitre les monbres correspondant
int *parse(char *number, int b)
{
    // b est la base cible  et number est le nombre dans la base de depart
    int len = strlen(number);
    int *_number = (int *)malloc(len * sizeof(int));
    if (b <= 10)
    {
        for (size_t i = 0; i < len; i++)
        {
            _number[i] = number[i] - '0'; // we can also do _number[i]=atoi(&number[i])
        }
    }
    else
    {
        char tagBase[] = "ABCDEFGHIJKLMN";

        for (size_t i = 0; i < len; i++)
        {
            //
            if ((int)atoi(&number[i]))
            {
                _number[i] = atoi(&number[1]);
            }
            _number[i] = searchIndex(tagBase, number[i]);
        }
    }

    return _number;
}
bool LTB(int number, int baseDepart) //Less Than Base
{
    if (number>=baseDepart){
    return false;
    }
    return true;
}
//Ici nous nous rassurons que les valeurs entrees corespondent a la base en question Ex:  5  n'est pas dans la base 4 ou meme 5
bool isNormal(int *number ,int _len, int base) 
{
    for(size_t i=0; i<_len; i++)
    {
        if(LTB(number[i], base)==false) return false;
    }
    return true;
}

int converToDecimal(int *number, int taille, int base)
{
    int numberDecimal = 0, i = 0;
    for (size_t i = 0; i < taille; i++)
    {
      numberDecimal += number[i] * pow(base, taille - i-1);
    }
    return (int)numberDecimal;
}
// Ici nous allons prendre la longeur de notre nombre dans ce nouvelle base
int newLenght(char* number , int BB , int EB)
{
    int newLenght=0,_number;
    _number=converToDecimal(parse(number,BB),strlen(number),BB);
    while (_number>0)
    {
        _number=_number/EB;
        newLenght++;
    }
    
    return newLenght;
}

int *_test(int number ,int newLenght,int newBase){
    int *_number = (int*)malloc(newLenght*sizeof(int)) , i=0;
    while (number>0)
    {
        _number[newLenght-i-1]=number%newBase ;
        number=number/newBase;
        i++;
    }
    return  _number;
}
// Cette etape est celle de la conversion proprement dite utilisant toutes les fonctions que nous avons ecrites precedement
int *conversion(char *number , int BB, int EB) //BB: befin Base ;EB: End Base
{
    int *numberInNewBase , *numberInBeginBase;
    int *temp , lenNumber = strlen(number), temp1=0 , reste=0, quotient=0 , _newLenght=newLenght(number,BB,EB);

    temp= (int*)malloc(lenNumber*sizeof(int));
    numberInNewBase =(int *)malloc((_newLenght)*sizeof(int));
    
    numberInBeginBase=parse(number , BB);
    // return numberInBeginBase;
    
    int j=0,i , k=0 ;
    int *temp2 =(int*)malloc(2*sizeof(int));

    while (converToDecimal(numberInBeginBase,lenNumber,BB)>EB)
    {
        temp= (int*)malloc((lenNumber-1)*sizeof(int));

        if(isNormal(numberInBeginBase , lenNumber,BB))
        {
            i=0;
            j=0;
            while(i<lenNumber)
            {
                if (i==0)  //si on entre pour la premiere fois dans la boucle
                {
                    while (converToDecimal(numberInBeginBase, i,BB)<EB)
                    {
                        i=i+1;

                    }
                    temp1=converToDecimal(numberInBeginBase,i,BB);
                    quotient = temp1/EB;
                    reste=temp1%EB;
                    numberInBeginBase[i+1]=reste;
                }else // Sinon on fait ceci.
                {
                    // temp2[0]=reste;
                    // temp2[1]=numberInBeginBase[i];
                    temp1=reste+numberInBeginBase[i];
                    quotient = temp1/EB;
                    reste=temp1%EB;
                    i+=1;
                    numberInBeginBase[i]=reste;
                }
                
                temp[j]=quotient;
                j+=1;
            }
            numberInNewBase[k]=reste;
            k=k+1;
            // return temp2;
            lenNumber-=1;
        }else{

            return NULL;
        }
        lenNumber=j;
        return temp;
        numberInBeginBase=NULL;
        numberInBeginBase=temp;
        temp=NULL;
        // free(temp);
        
    }
    return numberInNewBase ;
    
}

void printNumberInNewBase(char *number,int BB, int EB){
    char tagBase[] = "ABCDEFGHIJKLMN";
    int *_number=_test(converToDecimal(parse(number,BB),strlen(number),BB),newLenght(number,BB,EB),EB);
    for(size_t i=0; i<newLenght(number,BB,EB);i++)
    {
        if (_number[i]>=10)
        {
            for (size_t j = 0; j <strlen(tagBase); j++)
            {
                if(_number[i]==j+10){
                    printf("%c",tagBase[j]);
                }
            }
            
        }else{
        printf("%d",_number[i]);
        }
    }
    
}

int main()
{

    char *table = "2356";
    printNumberInNewBase(table,7,16);
    return 0;
}
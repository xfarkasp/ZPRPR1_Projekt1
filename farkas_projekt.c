#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Jazdci{
    char krstne[100];
    char priezvisko[100];
    char pohlavie;
    int narodenie;
    char Auto[50];
    float kola[5];
}Jazdci;
int menu(){

}
int Pocet_riadkov(){
    FILE* subor;
    char ln[1000], *string;
    int Riadky=0;
    subor=fopen("jazdci.csv","r");
    if(subor==NULL){
        Riadky=0;
    }
    else{
        while (fgets(ln, 1000, subor)){
                Riadky++;
        }
    }
    return Riadky;
}
void vytvor(FILE* Subor,Jazdci* Jazdec, int *Poradie){
    char ln[1000], *string, meno[100];
    int pomoc=0;
        while (fgets(ln, 1000, Subor)){
                string=strtok(ln, ";");
                strcpy(meno ,string);
                string=strrchr(meno, ' ');
                strcpy(Jazdec[*Poradie].priezvisko,string+1);
                pomoc=strlen(meno)-strlen(Jazdec[*Poradie].priezvisko);
                strncpy(Jazdec[*Poradie].krstne, meno, pomoc-1);
                string=strtok(NULL, ";");
                Jazdec[*Poradie].pohlavie=string[0];
                string=strtok(NULL, ";");
                Jazdec[*Poradie].narodenie=atoi(string);
                string=strtok(NULL, ";");
                strcpy(Jazdec[*Poradie].Auto,string);
                for (int i = 0; i < 5; ++i) {
                    string=strtok(NULL, ";");
                    Jazdec[*Poradie].kola[i]=atof(string);
                }
            pomoc=0;
            *Poradie=*Poradie+1;
            //printf("%d\n", *Poradie);
    }

}
void sum(){
   FILE *subor;
   subor = fopen("jazdci.csv", "r");
   if(fopen("jazdci.csv", "r")==NULL)
   {
      printf("Neotvoreny subor\n");
    } else{
        printf("otvoreny subor\n");
        char ln[1000], *string;
        Jazdci Jazdec[100];
        int poradie=0;
        char meno[100];
        vytvor(subor, (Jazdci*) Jazdec, &poradie);
        fclose(subor);
        for(int i=0; i<poradie;i++){
            printf("%s", Jazdec[i].krstne);
            printf(" %s,", Jazdec[i].priezvisko);
            printf(" nar. %d,", Jazdec[i].narodenie);
            if(Jazdec[i].pohlavie=='m')
            {
                printf(" muz,");
            }
            else if(Jazdec[i].pohlavie=='f')
            {
                printf(" zena,");
            }
            else{printf(" NESPRAVNE POHLAVIE,");}
            printf(" Automobil: %s\n", Jazdec[i].Auto);
            printf("Casy okruhov %.3f; %.3f; %.3f; %.3f; %.3f\n", Jazdec[i].kola[0] , Jazdec[i].kola[1], Jazdec[i].kola[2], Jazdec[i].kola[3], Jazdec[i].kola[4]);

        }
    }
}
void driver(){
   FILE *subor;
   subor = fopen("jazdci.csv", "r");
   if(fopen("jazdci.csv", "r")==NULL)
   {
      printf("Neotvoreny subor\n");
    } else{
        printf("otvoreny subor\n");
        char ln[1000], *string, vstup[100];
        Jazdci Jazdec[100];
        char meno[10];
        int poradie=0;
        float mini=9999, maxi=0, avengers=0;
        printf("Zadaj priezvisko jazdca: ");
        scanf("%s", &vstup);
        printf("\n");
        vytvor(subor, (Jazdci*) Jazdec, &poradie);
        for(int i=0;i<poradie;i++){
            if(strcmp(vstup, Jazdec[i].priezvisko)==0){
                for(int j=0;j<5;j++){
                    if(Jazdec[i].kola[j]>maxi)
                        {
                            maxi=Jazdec[i].kola[j];
                        }
                    if(Jazdec[i].kola[j]<mini)
                        {
                            mini=Jazdec[i].kola[j];
                        }
                    avengers+=Jazdec[i].kola[j];

                }
            printf("%s %s\nnar. %d, ", Jazdec[i].krstne, Jazdec[i].priezvisko, Jazdec[i].narodenie);
            if(Jazdec[i].pohlavie=='m')
            {
                printf(" muz,\n");
            }
            else if(Jazdec[i].pohlavie=='f')
            {
                printf(" zena\n");
            }
            else{printf(" NESPRAVNE POHLAVIE,");}
            printf("Automobil: %s\n", Jazdec[i].Auto);
            printf("\nCasy okruhov: %.3f;%.3f;%.3f;%.3f;%.3f\n", Jazdec[i].kola[0], Jazdec[i].kola[1], Jazdec[i].kola[2], Jazdec[i].kola[3], Jazdec[i].kola[4]);
            printf("\nNajlepsie kolo: %.3f\nNajhorsie kolo: %.3f\nPriemerne: %.3f\n", mini, maxi, avengers/5);
            break;
            }
        }

    }
}
void lap(){
    Jazdci Jazdec[100];
    FILE* subor;
    char ln[1000], *string, meno[100];
    int poradie=0;
    subor=fopen("jazdci.csv","r");
    if(subor==NULL){
        printf("Subor nie je mozne precitat.");
    }else{
        vytvor(subor, (Jazdci*) Jazdec, &poradie);
        fclose(subor);
        float najlepsie_kolo=9999;
        int poradie_kola=0;
        int poradie_jazdca=0;
        for(int i=0; i<poradie;i++){
            for(int j=0; j<5; j++){
                    if(Jazdec[i].kola[j]<najlepsie_kolo&&Jazdec[i].kola[j]!=0)
                    {
                        najlepsie_kolo=Jazdec[i].kola[j];
                        poradie_kola=j+1;
                        poradie_jazdca=i;
                    }
            }
        }
        printf("Najlepsie kolo: %.3f\nJazdec: %s %s\ncislo kola: %d\n", najlepsie_kolo, Jazdec[poradie_jazdca].krstne, Jazdec[poradie_jazdca].priezvisko, poradie_kola);
    }
}
void gender(){
    Jazdci Jazdec[100];
    FILE* subor;
    int poradie=0;
    subor=fopen("jazdci.csv","r");
    if(subor==NULL){
        printf("Subor nie je mozne precitat.");
    }else{
        vytvor(subor, (Jazdci*) Jazdec, &poradie);
        fclose(subor);
        char volba=' ';
        float najlepsie_kolo=9999;
        int poradie_kola=0;
        int poradie_jazdca=0;
        printf("zadaj m pre muza alebo f pre zenu: ");
        scanf(" %c", &volba);
        if((volba=='m' || volba=='f'))
        {
            for(int i=0; i<poradie;i++){
            for(int j=0; j<5; j++){
                    if(Jazdec[i].kola[j]<najlepsie_kolo&&Jazdec[i].kola[j]!=0&&Jazdec[i].pohlavie==volba)
                    {
                        najlepsie_kolo=Jazdec[i].kola[j];
                        poradie_kola=j+1;
                        poradie_jazdca=i;
                    }
                }
            }
            printf("Najlepsie kolo: %.3f\nJazdec: %s %s\ncislo kola: %d\n", najlepsie_kolo, Jazdec[poradie_jazdca].krstne, Jazdec[poradie_jazdca].priezvisko, poradie_kola);
        }
        else{printf("nespravny vstup");}
    }
}
void brand(){
    struct Jazdci Jazdec[100];
    FILE* subor;
    int poradie=0;
    subor=fopen("jazdci.csv","r");
    if(subor==NULL){
        printf("Subor nie je mozne precitat.");
    }else{
        vytvor(subor, (Jazdci*) Jazdec, &poradie);
        fclose(subor);
        float najlepsie_kolo=9999;
        int poradie_kola=0;
        int poradie_jazdca=0;
        int poradie_opakovania=0;
        char opakovanie[poradie][8];
        for(int i=0; i<poradie;i++){
            for(int k=0; k<poradie; k++){
                    if(strcmp(Jazdec[i].Auto,Jazdec[k].Auto)==0)
                    {
                       if(strcmp(Jazdec[i].Auto,opakovanie[k])==0)
                       {
                           break;
                       }
                       else
                       {
                        for(int j=0; j<5; j++){
                            if(Jazdec[i].kola[j]<najlepsie_kolo&&Jazdec[i].kola[j]!=0)
                            {
                                najlepsie_kolo=Jazdec[i].kola[j];
                                poradie_kola=j+1;
                                poradie_jazdca=i;
                            }
                        }
                      }
                    }
                }
                if(najlepsie_kolo==9999)
                {
                    //break;
                }
                else
                {
                    printf("Znacka: %s\nNajlepsie kolo: %.3f\nJazdec: %s %s\ncislo kola: %d\n\n", Jazdec[poradie_jazdca].Auto,najlepsie_kolo, Jazdec[poradie_jazdca].krstne, Jazdec[poradie_jazdca].priezvisko, poradie_kola);
                }
                najlepsie_kolo=9999;
                poradie_kola=0;
                poradie_jazdca=0;
                strcpy(opakovanie[poradie_opakovania], Jazdec[i].Auto);
                poradie_opakovania++;
        }
    }
}
void year(){
    Jazdci Jazdec[100];
    FILE* subor;
    int poradie=0;
    subor=fopen("jazdci.csv","r");
    if(subor==NULL){
        printf("Subor nie je mozne precitat.");
    }else{
        vytvor(subor, (Jazdci*) Jazdec, &poradie);
        fclose(subor);
        int volba=0;
        float najlepsie_kolo=9999;
        int poradie_kola=0;
        int poradie_jazdca=0;
        printf("zadaj rok narodenia: ");
        scanf(" %d", &volba);
        if((999<volba&&volba<10000))
        {
            for(int i=0; i<poradie;i++){
            for(int j=0; j<5; j++){

                    if(Jazdec[i].kola[j]<najlepsie_kolo&&Jazdec[i].kola[j]!=0&&Jazdec[i].narodenie<volba)
                    {
                        najlepsie_kolo=Jazdec[i].kola[j];
                        poradie_kola=j+1;
                        poradie_jazdca=i;
                    }
                }
            }
            printf("Najlepsie kolo: %.3f\nJazdec: %s %s\ncislo kola: %d\n", najlepsie_kolo, Jazdec[poradie_jazdca].krstne, Jazdec[poradie_jazdca].priezvisko, poradie_kola);
        }
        else{printf("nespravny format roka");}

    }
}
void average(){
   FILE *subor;
   subor = fopen("jazdci.csv", "r");
   if(fopen("jazdci.csv", "r")==NULL)
   {
      printf("Neotvoreny subor\n");
    } else{
        printf("otvoreny subor\n");
        Jazdci Jazdec[100];
        int poradie=0;
        float avengers=0;
        float najlepsi_avenger=0;
        int najlepsi_avenger_poradie=0;
        int neodjazdene_kola=0;
        vytvor(subor, (Jazdci*) Jazdec, &poradie);
        for(int i=0;i<poradie;i++){
                for(int j=0;j<5;j++){
                    if(Jazdec[i].kola[j]==0){
                        neodjazdene_kola=1;
                        avengers=0;
                        break;
                    }
                    else{
                           // printf("%f\n", Jazdec[i].kola[j]);
                            avengers+=Jazdec[i].kola[j];}
                }
            if(neodjazdene_kola==1)
            {
                printf("%s %s - Neodjazdene vsetky kola\n", Jazdec[i].krstne, Jazdec[i].priezvisko);
                neodjazdene_kola=0;
            }
            else
            {
                printf("%s %s - %.3f\n", Jazdec[i].krstne, Jazdec[i].priezvisko, avengers/5);
                if(avengers>najlepsi_avenger)
                {
                    najlepsi_avenger=avengers/5;
                    najlepsi_avenger_poradie=i;
                }
                avengers=0;
            }

        }
        printf("\nNajlepsie:\n%s %s - %.3f\n", Jazdec[najlepsi_avenger_poradie].krstne, Jazdec[najlepsi_avenger_poradie].priezvisko, najlepsi_avenger);
    }
}


int main() {
    char Vstup=' ';
    while (1) {
        scanf(" %c", &Vstup);
        if (Vstup == 's') {
           sum();
        } else if (Vstup == 'd'){
            driver();
        } else if (Vstup == 'l'){
            lap();
        } else if (Vstup == 'g'){
            gender();
        } else if (Vstup == 'b'){
            brand();
        } else if (Vstup == 'y'){
            year();
        } else if (Vstup == 'a'){
            average();
        }else if (Vstup == 'u'){

        }else if (Vstup == 'c'){

        }else if (Vstup == 'n'){

        }else if (Vstup == 'r'){

        }else if (Vstup == 'x'){
            break;
        } else { printf("%c prikaz neexistuje, skuste znovu\n", Vstup); }
    }
    return 0;
}

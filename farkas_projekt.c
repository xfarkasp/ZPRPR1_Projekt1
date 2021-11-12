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
struct Jazdci *vytvor(){
    printf("%d\n", Pocet_riadkov());
    int riadky=Pocet_riadkov();
    Jazdci Jazdec[100];
    FILE* subor;
    char ln[1000], *string, meno[100];
    int poradie=0, pomoc=0;
    subor=fopen("jazdci.csv","r");
    if(subor==NULL){
        printf("Subor nie je mozne precitat.");
    }
    else{

        while (fgets(ln, 1000, subor)){

                string=strtok(ln, ";");
                strcpy(meno ,string);
                string=strrchr(meno, ' ');
                strcpy(Jazdec[poradie].priezvisko,string+1);

                pomoc=strlen(meno)-strlen(Jazdec[poradie].priezvisko);
                strncpy(Jazdec[poradie].krstne, meno, pomoc-1);
                string=strtok(NULL, ";");
                Jazdec[poradie].pohlavie=string[0];
                string=strtok(NULL, ";");
                Jazdec[poradie].narodenie=atoi(string);
                string=strtok(NULL, ";");
                strcpy(Jazdec[poradie].Auto,string);
                for (int i = 0; i < 5; ++i) {
                    string=strtok(NULL, ";");
                    Jazdec[poradie].kola[i]=atof(string);
                }

            pomoc=0;
            poradie++;
    }
    fclose(subor);
    for(int i=0; i<poradie;i++){
        printf("%s\n", Jazdec[i].krstne);
        printf(" %s", Jazdec[i].priezvisko);
        printf(" %c", Jazdec[i].pohlavie);
        printf(" %d", Jazdec[i].narodenie);
        printf(" %s", Jazdec[i].Auto);
        printf(" %.3f", Jazdec[i].kola[0]);
        printf(" %.3f", Jazdec[i].kola[1]);
        printf(" %.3f", Jazdec[i].kola[2]);
        printf(" %.3f", Jazdec[i].kola[3]);
        printf(" %.3f\n", Jazdec[i].kola[4]);
    }

    }
return &Jazdec;
}
void sum(void){
   FILE *subor;
   subor = fopen("jazdci.csv", "r");
   if(fopen("jazdci.csv", "r")==NULL)
   {
      printf("Neotvoreny subor\n");
    } else{
        printf("otvoreny subor\n");
        char ln[1000], *string;
        char c, meno[100], krstne[100], priezvisko[100], pohlavieC=' ', pohlavieStr[5], Auto[100];
        int narod=0, pomoc=0;
        float kola[5];
        while (fgets(ln, 1000, subor)){
                string=strtok(ln, ";");
                strcpy(meno ,string);
                string=strrchr(meno, ' ');
                strcpy(priezvisko,string+1);
                pomoc=strlen(meno)-strlen(priezvisko);
                strncpy(krstne, meno, pomoc-1);
                string=strtok(NULL, ";");
                pohlavieC=string[0];
                string=strtok(NULL, ";");
                narod=atoi(string);
                string=strtok(NULL, ";");
                strcpy(Auto,string);
                if(pohlavieC=='m'){
                    strcpy(pohlavieStr,"muz");
                }else if(pohlavieC=='f'){
                    strcpy(pohlavieStr,"zena");
                }else{
                    strcpy(pohlavieStr,"chyba");
                }
                printf("%s %s, nar. %d, %s, Automobil: %s\n", krstne, priezvisko, narod, pohlavieStr, Auto);
                memset(meno, 0, sizeof(meno));
                memset(krstne, 0, sizeof(krstne));
                memset(priezvisko, 0, sizeof(priezvisko));
                memset(pohlavieStr, 0, sizeof(pohlavieStr));

            }
            fclose(subor);
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
        char c, meno[100], krstne[100], priezvisko[100], pohlavieC=' ', pohlavieStr[5], Auto[100];
        int narod=0, pomoc=0;
        float kola[5];
        printf("Zadaj priezvisko jazdca: ");
        scanf("%s", &vstup);
        printf("\n");
        while (fgets(ln, 1000, subor)){
                string=strtok(ln, ";");
                strcpy(meno ,string);
                string=strrchr(meno, ' ');
                strcpy(priezvisko,string+1);
                pomoc=strlen(meno)-strlen(priezvisko);
                strncpy(krstne, meno, pomoc-1);
                string=strtok(NULL, ";");
                pohlavieC=string[0];
                string=strtok(NULL, ";");
                narod=atoi(string);
                string=strtok(NULL, ";");
                strcpy(Auto,string);
                for (int i = 0; i < 5; ++i) {
                    string=strtok(NULL, ";");
                    kola[i]=atof(string);
                }
                if(pohlavieC=='m'){
                    strcpy(pohlavieStr,"muz");
                }else if(pohlavieC=='f'){
                    strcpy(pohlavieStr,"zena");
                }else{
                    strcpy(pohlavieStr,"chyba");
                }
                if(strcmp(vstup, priezvisko)==0){
                float mini=9999, maxi=0, avengers=0;
                for(int i=0;i<5;i++){
                    if(kola[i]>maxi)
                        {
                            maxi=kola[i];
                        }
                    if(kola[i]<mini)
                        {
                            mini=kola[i];
                        }
                    avengers+=kola[i];

                }
                printf("%s %s\nnar. %d, %s\nAutomobil: %s\n", krstne, priezvisko, narod, pohlavieStr, Auto);
                printf("\nCasy okruhov: %.3f;%.3f;%.3f;%.3f;%.3f\n", kola[0], kola[1], kola[2], kola[3], kola[4]);
                printf("\nNajlepsie kolo: %.3f\nNajhorsie kolo: %.3f\nPriemerne: %.3f\n", maxi, mini, avengers/5);
                memset(meno, 0, sizeof(meno));
                memset(krstne, 0, sizeof(krstne));
                memset(priezvisko, 0, sizeof(priezvisko));
                memset(pohlavieStr, 0, sizeof(pohlavieStr));
                memset(Auto, 0, sizeof(Auto));
                break;}
                else{memset(meno, 0, sizeof(meno));
                memset(krstne, 0, sizeof(krstne));
                memset(priezvisko, 0, sizeof(priezvisko));
                memset(pohlavieStr, 0, sizeof(pohlavieStr));}

            }

            fclose(subor);
    }

}
void lap(){
    Jazdci Jazdec[100];
    FILE* subor;
    char ln[1000], *string, meno[100];
    int poradie=0, pomoc=0;
    subor=fopen("jazdci.csv","r");
    if(subor==NULL){
        printf("Subor nie je mozne precitat.");
    }else{
        while (fgets(ln, 1000, subor)){
                string=strtok(ln, ";");
                strcpy(meno ,string);
                string=strrchr(meno, ' ');
                strcpy(Jazdec[poradie].priezvisko,string+1);
                pomoc=strlen(meno)-strlen(Jazdec[poradie].priezvisko);
                strncpy(Jazdec[poradie].krstne, meno, pomoc-1);
                string=strtok(NULL, ";");
                Jazdec[poradie].pohlavie=string[0];
                string=strtok(NULL, ";");
                Jazdec[poradie].narodenie=atoi(string);
                string=strtok(NULL, ";");
                strcpy(Jazdec[poradie].Auto,string);
                for (int i = 0; i < 5; ++i) {
                    string=strtok(NULL, ";");
                    Jazdec[poradie].kola[i]=atof(string);
                }

                pomoc=0;
                poradie++;
            }
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
    char ln[1000], *string, meno[100];
    int poradie=0, pomoc=0;
    subor=fopen("jazdci.csv","r");
    if(subor==NULL){
        printf("Subor nie je mozne precitat.");
    }else{
        while (fgets(ln, 1000, subor)){
                string=strtok(ln, ";");
                strcpy(meno ,string);
                string=strrchr(meno, ' ');
                strcpy(Jazdec[poradie].priezvisko,string+1);
                pomoc=strlen(meno)-strlen(Jazdec[poradie].priezvisko);
                strncpy(Jazdec[poradie].krstne, meno, pomoc-1);
                string=strtok(NULL, ";");
                Jazdec[poradie].pohlavie=string[0];
                string=strtok(NULL, ";");
                Jazdec[poradie].narodenie=atoi(string);
                string=strtok(NULL, ";");
                strcpy(Jazdec[poradie].Auto,string);
                for (int i = 0; i < 5; ++i) {
                    string=strtok(NULL, ";");
                    Jazdec[poradie].kola[i]=atof(string);
                }

                pomoc=0;
                poradie++;
            }
        fclose(subor);
        char volba=' ';
        float najlepsie_kolo=9999;
        int poradie_kola=0;
        int poradie_jazdca=0;
        printf("zadaj m pre muza alebo f     pre zenu: ");
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
    char ln[1000], *string, meno[100];
    int poradie=0, pomoc=0;
    subor=fopen("jazdci.csv","r");
    if(subor==NULL){
        printf("Subor nie je mozne precitat.");
    }else{
        while (fgets(ln, 1000, subor)){
                string=strtok(ln, ";");
                strcpy(meno ,string);
                string=strrchr(meno, ' ');
                strcpy(Jazdec[poradie].priezvisko,string+1);
                pomoc=strlen(meno)-strlen(Jazdec[poradie].priezvisko);
                strncpy(Jazdec[poradie].krstne, meno, pomoc-1);
                string=strtok(NULL, ";");
                Jazdec[poradie].pohlavie=string[0];
                string=strtok(NULL, ";");
                Jazdec[poradie].narodenie=atoi(string);
                string=strtok(NULL, ";");
                strcpy(Jazdec[poradie].Auto,string);
                for (int i = 0; i < 5; ++i) {
                    string=strtok(NULL, ";");
                    Jazdec[poradie].kola[i]=atof(string);
                }
                pomoc=0;
                poradie++;
            }
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

        } else if (Vstup == 'a'){

        }else if (Vstup == 'u'){

        }else if (Vstup == 'c'){

        }else if (Vstup == 'n'){

        }else if (Vstup == 'r'){

        Jazdci* JJazdec=vytvor();

        printf("%s\n", JJazdec);




        }else if (Vstup == 'x'){
            break;
        } else { printf("%c prikaz neexistuje, skuste znovu\n", Vstup); }
    }
    return 0;
}

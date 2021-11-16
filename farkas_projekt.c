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
    fclose(subor);
    return Riadky;
}
void vytvor(FILE *Subor,Jazdci *Jazdec){
    char ln[1000], *string, meno[100];
    int pomoc=0, poradie=0;
        while (fgets(ln, 1000, Subor)){
                memset(meno, 0, sizeof(meno));//toto tam musi byt, inak struktura vypisuje nezmiselne krstne mena
                string=strtok(ln, ";");//rozdeluje nacitany riadok po ;
                strcpy(Jazdec[poradie].krstne ,string);
                string=strrchr(Jazdec[poradie].krstne, ' ');
                strcpy(Jazdec[poradie].priezvisko,string+1);

                pomoc=strlen(Jazdec[poradie].krstne)-strlen(Jazdec[poradie].priezvisko);

                strncpy(meno, Jazdec[poradie].krstne, pomoc-1);
                strcpy(Jazdec[poradie].krstne, meno);

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
    // for(int i=0; i<poradie;i++){
    //             printf("%s", Jazdec[i].krstne);
    //             printf(" %s", Jazdec[i].priezvisko);
    //             printf(" %c", Jazdec[i].pohlavie);
    //             printf(" %d", Jazdec[i].narodenie);
    //             printf(" %s", Jazdec[i].Auto);
    //             printf(" %.3f", Jazdec[i].kola[0]);
    //             printf(" %.3f", Jazdec[i].kola[1]);
    //             printf(" %.3f", Jazdec[i].kola[2]);
    //             printf(" %.3f", Jazdec[i].kola[3]);
    //             printf(" %.3f\n\n", Jazdec[i].kola[4]);
    // }
}
void sum(){
   FILE *subor;
   subor = fopen("jazdci.csv", "r");
   if(subor==NULL)
   {
      printf("Neotvoreny subor\n");
    } else{
        printf("otvoreny subor\n");
        Jazdci Jazdec[Pocet_riadkov()];
        vytvor(subor,(Jazdci *) &Jazdec);
        if(fclose(subor)== 0)
        {
        printf("\nFILE SUCCESSFULLY CLOSED\n");
        }
        else{printf("subor sa nezavrel");}
        for(int i=0; i<Pocet_riadkov();i++){
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
   FILE* subor;
   subor = fopen("jazdci.csv", "r");
   if(subor==NULL)
   {
      printf("Neotvoreny subor\n");
    } else{
        char vstup[100];
        int poradie=0;
        float mini=9999, maxi=0, avengers=0;
        printf("Zadaj priezvisko jazdca: ");
        scanf("%s", &vstup);
        printf("\n");
        Jazdci Jazdec[Pocet_riadkov()];
        vytvor(subor,(Jazdci *) &Jazdec);

        if(fclose(subor)== 0)
        {
        printf("\nFILE SUCCESSFULLY CLOSED\n");
        }
        else{printf("subor sa nezavrel");}
        for(int i=0;i<Pocet_riadkov();i++){
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
    FILE* subor;
    subor=fopen("jazdci.csv","r");
    if(subor==NULL){
        printf("Subor nie je mozne precitat.");
    }else{
        int poradie=0;
        Jazdci Jazdec[Pocet_riadkov()];
        vytvor(subor,(Jazdci *) &Jazdec);
        if(fclose(subor)== 0)
        {
        printf("\nFILE SUCCESSFULLY CLOSED\n");
        }
        else{printf("subor sa nezavrel");}
        float najlepsie_kolo=9999;
        int poradie_kola=0;
        int poradie_jazdca=0;
        for(int i=0; i<Pocet_riadkov();i++){
            for(int j=0; j<5; j++){
                    if(Jazdec[i].kola[j]<najlepsie_kolo&&Jazdec[i].kola[j]!=0)
                    {
                        najlepsie_kolo=Jazdec[i].kola[j];
                        poradie_kola=j+1;
                        poradie_jazdca=i;
                    }
            }
        }
        printf("Najlepsie kolo: %.3f\nJazdec: %s %s\ncislo kola: %d", najlepsie_kolo, Jazdec[poradie_jazdca].krstne, Jazdec[poradie_jazdca].priezvisko, poradie_kola);
    }
}
void gender(){
    FILE* subor;
    subor=fopen("jazdci.csv","r");
    if(subor==NULL){
        printf("Subor nie je mozne precitat.");
    }else{
        int poradie=0;
        Jazdci Jazdec[Pocet_riadkov()];
        vytvor(subor,(Jazdci *) &Jazdec);
        if(fclose(subor)== 0)
        {
        printf("\nFILE SUCCESSFULLY CLOSED\n");
        }
        else{printf("subor sa nezavrel");}
        char volba=' ';
        float najlepsie_kolo=9999;
        int poradie_kola=0;
        int poradie_jazdca=0;
        printf("zadaj m pre muza alebo f pre zenu: ");
        scanf(" %c", &volba);
        if((volba=='m' || volba=='f'))
        {
            for(int i=0; i<Pocet_riadkov();i++){
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
    FILE* subor;
    subor=fopen("jazdci.csv","r");
    if(subor==NULL){
        printf("Subor nie je mozne precitat.");
    }else{
        int poradie=0;
        Jazdci Jazdec[Pocet_riadkov()];
        vytvor(subor,(Jazdci *) &Jazdec);
        if(fclose(subor)== 0)
        {
        printf("\nFILE SUCCESSFULLY CLOSED\n");
        }
        else{printf("subor sa nezavrel");}
        float najlepsie_kolo=9999;
        int poradie_kola=0;
        int poradie_jazdca=0;
        int poradie_opakovania=0;
        char opakovanie[100][Pocet_riadkov()];
        for(int i=0; i<Pocet_riadkov();i++){
            for(int k=0; k<Pocet_riadkov(); k++){
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
    FILE* subor;
    subor=fopen("jazdci.csv","r");
    if(subor==NULL){
        printf("Subor nie je mozne precitat.");
    }else{
        int poradie=0;
        Jazdci Jazdec[Pocet_riadkov()];
        vytvor(subor,(Jazdci *) &Jazdec);
        if(fclose(subor)== 0)
        {
        printf("\nFILE SUCCESSFULLY CLOSED\n");
        }
        else{printf("subor sa nezavrel");}
        int volba=0;
        float najlepsie_kolo=9999;
        int poradie_kola=0;
        int poradie_jazdca=0;
        printf("zadaj rok narodenia: ");
        scanf(" %d", &volba);
        if((999<volba&&volba<10000))
        {
            for(int i=0; i<Pocet_riadkov();i++){
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
   if(subor==NULL)
   {
      printf("Neotvoreny subor\n");
    } else{
        printf("otvoreny subor\n");
        Jazdci Jazdec[Pocet_riadkov()];
        int poradie=0;
        vytvor(subor,(Jazdci *) &Jazdec);
        if(fclose(subor)== 0)
        {
        printf("\nFILE SUCCESSFULLY CLOSED\n");
        }
        else{printf("subor sa nezavrel");}
        float avengers=0;
        float najlepsi_avenger=9999;
        int najlepsi_avenger_poradie=0;
        int neodjazdene_kola=0;
        for(int i=0;i<Pocet_riadkov();i++){
                for(int j=0;j<5;j++){
                    if(Jazdec[i].kola[j]==0){
                        neodjazdene_kola=1;
                        avengers=0;
                        break;
                    }
                    else{
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
                if(avengers/5<najlepsi_avenger)
                {
                    najlepsi_avenger=avengers/5;
                    najlepsi_avenger_poradie=i;
                }
                avengers=0;
            }
        }
        printf("\nNajlepsie:\n%s %s - %.3f\n", Jazdec[najlepsi_avenger_poradie].krstne, Jazdec[najlepsi_avenger_poradie].priezvisko, najlepsi_avenger);
   }
    //memset(Jazdec,0,sizeof(Jazdec));
}
void under(){
   FILE *subor;
   subor = fopen("jazdci.csv", "r");
   if(subor==NULL)
   {
      printf("Neotvoreny subor\n");
    } else{
        printf("otvoreny subor\n");
        Jazdci Jazdec[Pocet_riadkov()];
        int poradie=0, nenaslo=0;
        vytvor(subor,(Jazdci *) &Jazdec);
        if(fclose(subor)== 0)
        {
        printf("\nFILE SUCCESSFULLY CLOSED\n");
        }
        else{printf("subor sa nezavrel");}
        float vstup;
        printf("zadaj cas kola: ");
        scanf(" %f", &vstup);
        printf("\n");
       int pocet_najdenych=0;
        for(int i=0;i<Pocet_riadkov();i++){
                float najdene_kola[5];
                for(int j=0;j<5;j++){
                    if(Jazdec[i].kola[j]<=vstup&&Jazdec[i].kola[j]!=0)
                    {
                          najdene_kola[pocet_najdenych]=Jazdec[i].kola[j];
                          pocet_najdenych++;
                    }
                    else{nenaslo++;}
            }
            if(nenaslo<5){
                    printf("%s %s - %d kola", Jazdec[i].krstne, Jazdec[i].priezvisko, pocet_najdenych);
                    for(int k=0;k<pocet_najdenych;k++){
                        printf(", %d(%.3f)", k+1, najdene_kola[k]);
                    }
                    printf("\n");
            }
            nenaslo=0;
            pocet_najdenych=0;
        }
    }
}
void newdriver(){
   FILE *subor;
   subor = fopen("jazdci.csv", "a");
   if(subor==NULL)
   {
      printf("Neotvoreny subor\n");
    } else{
        char krstne[100], priezvisko[100], pohlavie=' ', znacka[50], vloz[1000];
        int rok=0;
        float kolo1=0, kolo2=0, kolo3=0, kolo4=0, kolo5=0;
        printf("zadaj meno jazdca: ");
        scanf(" %s %s", &krstne, &priezvisko);
        printf("zadaj rok narodenia: ");
        scanf(" %d", &rok);
        printf("zadaj pohlavie jazdca: ");
        scanf(" %c",&pohlavie);
        printf("zadaj auto jazdca: ");
        scanf(" %s",&znacka);
        printf("\n");
        printf("zadaj 5 casov jazdca: ");
        scanf(" %f;%f;%f;%f;%f", &kolo1, &kolo2, &kolo3, &kolo4, &kolo5);
        printf("\n");
        fprintf(subor,"\n%s %s;%c;%d;%s;%f;%f;%f;%f;%f", krstne, priezvisko, pohlavie, rok, znacka, kolo1, kolo2, kolo3, kolo4, kolo5);
        fclose(subor);
    }
}

void change(){
   FILE *subor;
   subor = fopen("jazdci.csv", "r+");
   if(subor==NULL)
   {
      printf("Neotvoreny subor\n");
    } else{
        char priezvisko[100], c;
        int poradie_jazdca=1, poradie_kola=0, offsetik=0;
        float nove_kolo=0, kola[5], jezis_pomoz=0;
        printf("zadaj meno jazdca: ");
        scanf(" %s", &priezvisko);
        printf("zadaj poradie kola: ");
        scanf(" %d", &poradie_kola);
        printf("zadaj novy cas jazdca: ");
        scanf(" %f", &nove_kolo);
        printf("\n");
        Jazdci Jazdec[Pocet_riadkov()];
        int riadok=0, nenaslo=1, hviezdicka=0, original_pocet_riadkov=Pocet_riadkov();
        vytvor(subor,(Jazdci *) &Jazdec);
        printf("pocet riadok1: %d\n", Pocet_riadkov()); 

        for(int i=0;i<Pocet_riadkov();i++){
            riadok++;
            if(strcmp(priezvisko, Jazdec[i].priezvisko)==0){
                break;
            }
        }
        printf("riadok: %d\n", riadok);
        
        fseek(subor, 0,SEEK_SET);
        while((c = fgetc(subor)) != EOF ){
                hviezdicka++;
                //printf("%c", c);
                if(c=='\n')
                {
                    printf("\nkoniec riadku\n");
                    nenaslo++;
                    if (nenaslo==riadok)
                    {   int prvy_cas=0;
                        printf("\nnasiel som gazembera\n");
                        while((c = fgetc(subor)) != '\n' ){
                            printf("%c", c);
                            hviezdicka++;
                
                            if(c==';'){
                                prvy_cas++;
                                printf("bodkociarka\n");
                                printf("prvy cas: %d\n", prvy_cas);
                            }
                            if(prvy_cas-3>=poradie_kola)
                                {
                                     while((c = fgetc(subor)) != EOF ){
                                        //hviezdicka++;
                                            ungetc(c,subor);
                                            fputc('*', subor);
                                            
                                    }
                                    break;
                                }
                        }
                        break;
                    }
                } 
        }
       FILE *subor2;
        subor2 = fopen("docasne.csv", "w");
        fseek(subor, 0,SEEK_SET);
        while((c = fgetc(subor)) != EOF ){
            if(c!='*'){
                //printf("%c", c);
                fputc(c, subor2);
            }
        }
        fseek(subor2, hviezdicka,SEEK_SET);
        fprintf(subor2,"%.3f", nove_kolo);
                for (int i = poradie_kola; i < 5; ++i)
                {
                    fprintf(subor2,";%.3f", Jazdec[riadok].kola[i]);
                }
                fprintf(subor2,"\n");
        printf("pocet riadok: %d\n", Pocet_riadkov()); 

        for(int i=riadok;i<original_pocet_riadkov;i++)
        {
            fprintf(subor2,"%s %s;%c;%d;%s", Jazdec[i].krstne, Jazdec[i].priezvisko, Jazdec[i].pohlavie, Jazdec[i].narodenie, Jazdec[i].Auto);
            for(int j=0;j<5;j++)
            {
                fprintf(subor2,";%.3f", Jazdec[i].kola[j]);
            }
            fprintf(subor2,"\n");
        }
        
        fclose(subor);
        fclose(subor2);
        remove("jazdci.csv");
        rename("docasne.csv", "jazdci.csv");
        //sum();
    }
}

void rmdriver(){
   FILE *subor;
   subor = fopen("jazdci.csv", "r+");
   if(subor==NULL)
   {
      printf("Neotvoreny subor\n");
    } else{
        char priezvisko[100];
        printf("zadaj meno jazdca: ");
        scanf(" %s", &priezvisko);
        printf("\n");
        char ln[1000],ln2[1000],*string;
        int pocet=0;
        while (fgets(ln, 1000, subor)){
                pocet++;
                printf("ln1: %s", ln);
                strcpy(ln2, ln);
                int gazember=0;
                char hladaj_priezvisko[100];
                string=strtok(ln, ";");//rozdeluje nacitany riadok po ;
                strcpy(hladaj_priezvisko, string);
                string=strrchr(hladaj_priezvisko, ' ');
                strcpy(hladaj_priezvisko,string+1);
                //printf("%s", hladaj_priezvisko);
                string=strtok(NULL, ";");
                string=strtok(NULL, ";");
                string=strtok(NULL, ";");
                for (int i = 1; i <= 5; ++i) {
                    string=strtok(NULL, ";");
                }
                if (strcmp(hladaj_priezvisko, priezvisko)==0)
                {
                    break;
                }
        }
        printf("\nln2: %s", ln2);
        printf("\nln2: %ld", strlen(ln2));
        if(pocet==Pocet_riadkov()){
            fseek(subor, -strlen(ln2)-2,SEEK_CUR);

        }
        else if(1<pocet){
            fseek(subor, -strlen(ln2)-1,SEEK_CUR);
        }
        else{
            fseek(subor, 0,SEEK_SET);
        }

        for(int i=0;i<=strlen(ln2);i++){//vo Windowse musi byt i<=strlen(ln2) a na linuxe i<strlen(ln2), aby sa vymazal endl znak
            fprintf(subor,"*");
             }

        char c;
        FILE *subor2;
        subor2 = fopen("docasne.csv", "w");
        fseek(subor, 0,SEEK_SET);
        while((c = fgetc(subor)) != EOF ){
            if(c!='*'){
                printf("%c", c);
                fputc(c, subor2);
            }
        }
        fclose(subor);
        fclose(subor2);
        remove("jazdci.csv");
        rename("docasne.csv", "jazdci.csv");
        sum();
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
            under();
        }else if (Vstup == 'c'){
            change();
        }else if (Vstup == 'n'){
            newdriver();
        }else if (Vstup == 'r'){
            rmdriver();
        }else if (Vstup == 'x'){
            break;
        } else { printf("%c prikaz neexistuje, skuste znovu\n", Vstup); }
    }
    return 0;
}

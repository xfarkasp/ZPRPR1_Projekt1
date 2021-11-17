//program bol vyvyjany na operacnom systeme Linux Mint 19.3 Cinnamon Version 4.4.8
#include <stdio.h>//tuto kniznicu potrebujem predovsetkym na pracu so suborormi
#include <stdlib.h>//tuto kniznicu potrebujem napr. na konvetovanie stringov na ine typy a na pracu s pametou
#include <string.h>//tuto kniznicu pouzivam na pracu so stringami
//tu si definujem strukturu pre jazdcov, nazov struktury, jej atributy a jej alias
typedef struct Jazdci{
    char krstne[100];
    char priezvisko[100];
    char pohlavie;
    int narodenie;
    char Auto[50];
    float kola[5];
}Jazdci;

//tuto funkciu som si vytvoril na spocitanie riadkov v subore
int Pocet_riadkov(){
    FILE* subor;
    char ln[1000], *string;
    int Riadky=0;
    subor=fopen("jazdci.csv","r");//program vzdy rata ze bude pracovat so suborom nazvu jazdci.csv, lebo tak sa volal subor, ku ktoremu ste nam dali pristup na drive
    if(subor==NULL){
        Riadky=0;
    }
    else{
        while (fgets(ln, 1000, subor)){
            if(ln[0] != '\n'){Riadky++;}
        }
    }
    fclose(subor);
    return Riadky;
}
/*
tato funkcia kontroluje subor riadok po riadku a pocita pocet ';', ak ich nieje presne 8 vypise na ktorom riadku ich je iny pocet a ich pocet na danom riadku
vracia hodnotu chybna struktura, od ktorej sa odvyja, ci ostatne funkcie prebehnu alebo vypisu ze struktura je chybna
*/
int Kontrola_struktury(FILE *Subor)
{
   system("clear");//zmaze predosle vypisi z konzle, system("clear"); funguje na unixovych OS, na windowse treba pouzit clrscr();
   int poradie=1, pocet_bc=0, chybna_struktura=0, skuska=0;
   char c;
    while((c = fgetc(Subor)) != EOF ){
        if(c!='\n')
        {
            if(c==';')
            {
                pocet_bc++;
            }
        }
        else{
             if(pocet_bc!=8)
                {   
                    printf("nespravny pocet udajov na riadku: %d\n", poradie);
                    printf("pocet ciarok v riadku %d: %d\n", poradie, pocet_bc);
                    chybna_struktura++;
                }
            poradie++;
            pocet_bc=0;
        }
    }
    if(pocet_bc!=8)
    {   
        printf("nespravny pocet udajov na riadku: %d\n", poradie);
        printf("pocet ciarok v riadku %d: %d\n", poradie, pocet_bc);
        chybna_struktura++;
    }
    return chybna_struktura;
}
/*
kazda funkcia si otvori subor, ak funkcia Kontrola_struktury nenasla chybu,
tak sa nasledne deklaruje pole struktur o velkosti poctu riadkov a zavola sa funkcia vytvor
do ktorej sa posle otvoreny subor a struktura Jazdec
*/
void vytvor(FILE *Subor,Jazdci *Jazdec){
    char ln[1000], *string, meno[100];
    int pomoc=0, poradie=0;
    fgets(ln, 1000, Subor);
    
        fseek(Subor, 0,SEEK_SET);//pre istotu zakazdym posuniem kurzor na zaciatok suboru, aby som sa vyhol nespravnej polohe
        //nacitam si riadok po riadku cely subor, riadky si rozdelim po ';' a ulozim si ich do jednotlivych atributov struktury
        while (fgets(ln, 1000, Subor)){
             if(ln[0] != '\n'){
                memset(meno, 0, sizeof(meno));//toto tam musi byt na vynulovanie stringu krstneho mena, inak struktura vypisuje nezmiselne krstne mena kvoli tomu, ze ak nove krstne meno je kratsie, tak tam zostanu zvysne znaky z predosleho dlhsieho
                string=strtok(ln, ";");//rozdeluje nacitany riadok po ;
                strcpy(Jazdec[poradie].krstne ,string);
                string=strrchr(Jazdec[poradie].krstne, ' ');//posledny vyskyt medzere v udaji meno
                strcpy(Jazdec[poradie].priezvisko,string+1);//preto tam je +1, aby sa do stringu nenakopirovala medzera na zaciatku
                pomoc=strlen(Jazdec[poradie].krstne)-strlen(Jazdec[poradie].priezvisko);//od celeho mena odratam priezvisko, aby som dostal krstne meno
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
        }
    
}

void sum(){
   system("clear");
   char hocico=' ';
   FILE *subor;
   subor = fopen("jazdci.csv", "r");
   if(subor==NULL)//ak sa subor neotvori, vypise neotvoreny subor
   {
      printf("Neotvoreny subor\n");
    }
    else if(Kontrola_struktury(subor)!=0)//ak je nespravna struktura, vypise nespravna struktura
        {printf("Nespravna struktura\n");}
    else{
        Jazdci Jazdec[Pocet_riadkov()];//deklaracia pola struktur o velkosti poctu riadkov subore pomocou funkcie Pocet_riadkov()
        vytvor(subor,(Jazdci *) &Jazdec);//vytvorenie struktury funkciou vytvor
        fclose(subor);//uzavretie suboru
        for(int i=0; i<Pocet_riadkov();i++){//vypis udajov zo struktury
            printf("%s", Jazdec[i].krstne);
            printf(" %s,", Jazdec[i].priezvisko);
            printf(" nar. %d,", Jazdec[i].narodenie);
            if(Jazdec[i].pohlavie=='m')//ak na mieste pohlavia je pismeno m, vypise na miesto pismena m muz
            {
                printf(" muz,");
            }
            else if(Jazdec[i].pohlavie=='f')//ak na mieste pohlavia je pismeno f, vypise na miesto pismena f zena
            {
                printf(" zena,");
            }
            else{printf(" NESPRAVNE POHLAVIE,");}//ak na mieste pohlavia je ine pismeno, vypise na miesto pismena nespravne pohlavie
            printf(" Automobil: %s\n", Jazdec[i].Auto);
            printf("Casy okruhov %.3f; %.3f; %.3f; %.3f; %.3f\n", Jazdec[i].kola[0] , Jazdec[i].kola[1], Jazdec[i].kola[2], Jazdec[i].kola[3], Jazdec[i].kola[4]);
        }
    }
    printf("\nPre pokracovanie stlacte hociaku klavesu: ");
    scanf(" %c", &hocico);
    printf("\n\n");
    system("clear");
}
void driver(){
   system("clear");
   char hocico=' ';
   FILE* subor;
   subor = fopen("jazdci.csv", "r");
   if(subor==NULL)
   {
      printf("Neotvoreny subor\n");
    }
    else if(Kontrola_struktury(subor)!=0)
        {printf("Nespravna struktura\n");}
    else{
        char vstup[100];
        int nenaslo=0;
        float mini=9999, maxi=0, avengers=0;//mini ma velku deklarovanu hodnotu, aby ked sa najde nizsi cas, tak ho nahradi pre maxi plati to iste naopak
        printf("Zadaj priezvisko jazdca: ");
        scanf("%s", &vstup);
        printf("\n");
        Jazdci Jazdec[Pocet_riadkov()];
        vytvor(subor,(Jazdci *) &Jazdec);
        fclose(subor);
        for(int i=0;i<Pocet_riadkov();i++){
            if(strcmp(vstup, Jazdec[i].priezvisko)==0){//ak sa vstupne priezvisko zhoduje s nejakym priezviskom v stukture
                for(int j=0;j<5;j++){//porovnava vsetky kola najdeneho jazdca a urci jeho najlepsie, najhorsie a priemer
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
            else{nenaslo++;}//ak sa priezvisko nezhoduje, nenaslo sa zvysi o 1
        }
        if(nenaslo==Pocet_riadkov())//ak sa nenaslo bude rovnat poctu riadkov, bude to znamenat, ze sa jazdec nenachadza ani na jednom riadku 
            {printf("Jazdec sa nenasiel\n");}//program vypise jazdec sa nenasiel
    }
    printf("\nPre pokracovanie stlacte hociaku klavesu: ");
    scanf(" %c", &hocico);
    printf("\n\n");
    system("clear");
}
void lap(){
    system("clear");
    char hocico=' ';
    FILE* subor;
    subor=fopen("jazdci.csv","r");
    if(subor==NULL)
    {
      printf("Neotvoreny subor\n");
    }
    else if(Kontrola_struktury(subor)!=0)
        {printf("Nespravna struktura\n");}
    else{
        Jazdci Jazdec[Pocet_riadkov()];
        vytvor(subor,(Jazdci *) &Jazdec);
        fclose(subor);
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
        printf("Najlepsie kolo: %.3f\nJazdec: %s %s\ncislo kola: %d\n", najlepsie_kolo, Jazdec[poradie_jazdca].krstne, Jazdec[poradie_jazdca].priezvisko, poradie_kola);
    }
    printf("\nPre pokracovanie stlacte hociaku klavesu: ");
    scanf(" %c", &hocico);
    printf("\n\n");
    system("clear");
}
void gender(){
    system("clear");
    char hocico=' ';
    FILE* subor;
    subor=fopen("jazdci.csv","r");
    if(subor==NULL)
   {
      printf("Neotvoreny subor\n");
    }
    else if(Kontrola_struktury(subor)!=0)
        {printf("Nespravna struktura\n");}
    else{
        Jazdci Jazdec[Pocet_riadkov()];
        vytvor(subor,(Jazdci *) &Jazdec);
        char volba=' ';
        float najlepsie_kolo=9999;
        int poradie_kola=0;
        int poradie_jazdca=0;
        printf("zadaj m pre muza alebo f pre zenu: ");
        scanf(" %c", &volba);
        if((volba=='m' || volba=='f'))//ak je vstup m alebo f, spusti sa cyklu ktory porovnava jazdcov s rovnakym pohlavim, aky bol na vstupe
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
        else{printf("nespravny vstup\n");}//ak na vstup bolo zadane nieco ine ako m alebo f, program vypise nespravny vstup
    }
    printf("\nPre pokracovanie stlacte hociaku klavesu: ");
    scanf(" %c", &hocico);
    printf("\n\n");
    system("clear");
}
void brand(){
    system("clear");
    char hocico=' ';
    FILE* subor;
    subor=fopen("jazdci.csv","r");
    if(subor==NULL)
   {
      printf("Neotvoreny subor\n");
    }
    else if(Kontrola_struktury(subor)!=0)
        {printf("Nespravna struktura\n");}
    else{
        Jazdci Jazdec[Pocet_riadkov()];
        vytvor(subor,(Jazdci *) &Jazdec);
        fclose(subor);
        float najlepsie_kolo=9999;
        int poradie_kola=0;
        int poradie_jazdca=0;
        int poradie_opakovania=0;
        char opakovanie[100][Pocet_riadkov()];//do tohto pola ukladam znacki aut, z ktorych uz bol ureceny najlepsi vysledok
        for(int i=0; i<Pocet_riadkov();i++){
            for(int k=0; k<Pocet_riadkov(); k++){
                    if(strcmp(Jazdec[i].Auto,Jazdec[k].Auto)==0)//ak sa prvy vyskyt auta rovna s dalsimi vyskytmi, prebehne porovnavanie casov
                    {
                       if(strcmp(Jazdec[i].Auto,opakovanie[k])==0)//ak sa ale porovnavana znacka uz nachadza na zozname opakovanie, cyklus sa prerusi
                       {
                           break;
                       }
                       else
                       {
                        for(int j=0; j<5; j++){// porovnavanie casov, na urcenie najlepsieho kola
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
                if(najlepsie_kolo!=9999)//ak san jalepsie kolo nerovna 9999, respektive bolo zmenene cyklom, tak program vypise udaje
                {
                    printf("Znacka: %s\nNajlepsie kolo: %.3f\nJazdec: %s %s\ncislo kola: %d\n\n", Jazdec[poradie_jazdca].Auto,najlepsie_kolo, Jazdec[poradie_jazdca].krstne, Jazdec[poradie_jazdca].priezvisko, poradie_kola);
                }
                //resetovanie premennych
                najlepsie_kolo=9999;
                poradie_kola=0;
                poradie_jazdca=0;
                strcpy(opakovanie[poradie_opakovania], Jazdec[i].Auto);//vlozenie znacky do pola opakovani
                poradie_opakovania++;//zvysenie indexu pola opakovanie
        }
        memset(opakovanie, 0, sizeof(opakovanie));//musim vynulovat pole "opakovanie", inak zostane zaplnene a funkcia neprebehne spravne
    }
    printf("\nPre pokracovanie stlacte hociaku klavesu: ");
    scanf(" %c", &hocico);
    printf("\n\n");
    system("clear");
}

void year(){
    system("clear");
    char hocico=' ';
    FILE* subor;
    subor=fopen("jazdci.csv","r");
    if(subor==NULL)
   {
      printf("Neotvoreny subor\n");
    }
    else if(Kontrola_struktury(subor)!=0)
        {printf("Nespravna struktura\n");}
    else{
        Jazdci Jazdec[Pocet_riadkov()];
        vytvor(subor,(Jazdci *) &Jazdec);
        int volba=0;
        float najlepsie_kolo=9999;
        int poradie_kola=0;
        int poradie_jazdca=0;
        printf("zadaj rok narodenia vo formate YYYY: ");
        scanf(" %d", &volba);
        if((999<volba&&volba<10000))//vo formate YYYY su len roky od 1000-9999, vsetko ostatne sa berie ako nespravny vstup
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
        else{printf("nespravny format roka\n");}
    }
    printf("\nPre pokracovanie stlacte hociaku klavesu: ");
    scanf(" %c", &hocico);
    printf("\n\n");
    system("clear");
}
void average(){
   system("clear");
   char hocico=' ';
   FILE *subor;
   subor = fopen("jazdci.csv", "r");
   if(subor==NULL)
   {
      printf("Neotvoreny subor\n");
    }
    else if(Kontrola_struktury(subor)!=0)
        {printf("Nespravna struktura\n");}
    else{
        printf("otvoreny subor\n");
        Jazdci Jazdec[Pocet_riadkov()];
        vytvor(subor,(Jazdci *) &Jazdec);
        float avengers=0;//easter egg, na miesto nazvu premennej average som pouzil nazov avengers, lebo mi to prislo vtipne a uzivatel sa to realne nema ako dozvediet 
        float najlepsi_avenger=9999;
        int najlepsi_avenger_poradie=0;
        int neodjazdene_kola=0;
        for(int i=0;i<Pocet_riadkov();i++){
                for(int j=0;j<5;j++){
                    if(Jazdec[i].kola[j]==0){//ak ma jazdec aspon jedno kolo 0, je vyradeny z priemerovania
                        neodjazdene_kola=1;
                        avengers=0;
                        break;
                    }
                    else{
                            avengers+=Jazdec[i].kola[j];}
                }
            if(neodjazdene_kola==1)//ak jazdec dostane 1 do premennej neodjazdene_kola, vypise sa pri jeho mene neodjazdene vsetky kola
            {
                printf("%s %s - Neodjazdene vsetky kola\n", Jazdec[i].krstne, Jazdec[i].priezvisko);
                neodjazdene_kola=0;
            }
            else
            {
                printf("%s %s - %.3f\n", Jazdec[i].krstne, Jazdec[i].priezvisko, avengers/5);//hodnotu priemer treba este vydelit s poctom kol, teda 5
                if(avengers/5<najlepsi_avenger)//ak je aktualny priemer mensi ako hodnota najlepsi_avenger, tak sa do nej prepise hodnota aktualneho priemeru
                {
                    najlepsi_avenger=avengers/5;
                    najlepsi_avenger_poradie=i;
                }
                avengers=0;//nulovanie piremeru pre dalsieho jazdca
            }
        }
        printf("\nNajlepsie:\n%s %s - %.3f\n", Jazdec[najlepsi_avenger_poradie].krstne, Jazdec[najlepsi_avenger_poradie].priezvisko, najlepsi_avenger);
   }
   printf("\nPre pokracovanie stlacte hociaku klavesu: ");
    scanf(" %c", &hocico);
    printf("\n\n");
    system("clear");
}
void under(){
   system("clear");
   char hocico=' ';
   FILE *subor;
   subor = fopen("jazdci.csv", "r");
   if(subor==NULL)
   {
      printf("Neotvoreny subor\n");
    }
    else if(Kontrola_struktury(subor)!=0)
        {printf("Nespravna struktura\n");}
    else{
        printf("otvoreny subor\n");
        Jazdci Jazdec[Pocet_riadkov()];
        int nenaslo=0;
        vytvor(subor,(Jazdci *) &Jazdec);
        fclose(subor);
        float vstup;
        printf("zadaj cas kola: ");
        scanf(" %f", &vstup);
        printf("\n");
       int pocet_najdenych=0;
        for(int i=0;i<Pocet_riadkov();i++){
                float najdene_kola[5];
                for(int j=0;j<5;j++){
                    if(Jazdec[i].kola[j]<=vstup&&Jazdec[i].kola[j]!=0)//ak je zadane kolo mensie-rovne vstupu a zaroven nieje 0
                    {
                          najdene_kola[pocet_najdenych]=Jazdec[i].kola[j];
                          pocet_najdenych++;
                    }
                    else{nenaslo++;}//ak porovnavane kolo nieje mensie rovne ako vstup a zaroven sa nerovna 0, zvysi sa nenaslo o 1
            }
            /*
             kym je nenaslo menej ako 5, jazdec ma aspon jedno kolo lepsie alebo rovne ako hladane,
             ak nenaslo nieje menej ako 5, jazdec nema ani jedno kolo lepsie rovne, tympadom sa jazdec nevypise
            */
            if(nenaslo<5){
                    printf("%s %s - %d kola", Jazdec[i].krstne, Jazdec[i].priezvisko, pocet_najdenych);
                    for(int k=0;k<pocet_najdenych;k++){
                        printf(", %d(%.3f)", k+1, najdene_kola[k]);
                    }
                    printf("\n");
            }
            //resetovanie premennych pre dalsieho jazdca v poradi
            nenaslo=0;
            pocet_najdenych=0;
        }
    }
    printf("\nPre pokracovanie stlacte hociaku klavesu: ");
    scanf(" %c", &hocico);
    printf("\n\n");
    system("clear");
}
void newdriver(){
   system("clear");
   char hocico=' ';
   FILE *subor;
   subor = fopen("jazdci.csv", "r");//subor sa najprv otvori len pre citanie, na kontrolu struktury
   if(subor==NULL)
   {
      printf("Neotvoreny subor\n");
    }
    else if(Kontrola_struktury(subor)!=0)
        {printf("Nespravna struktura\n");}
    else{

        //subor sa nasledne zavrie a otvori sa ako append, na pridanie udajov na jeho koniec
        fclose(subor);
        subor = fopen("jazdci.csv", "a");
        if(subor==NULL)
        {
          printf("Neotvoreny subor\n");
        }
        else{
            char krstne[100], priezvisko[100], pohlavie=' ', znacka[50], vloz[1000];
            int rok=0;
            float kolo1=0, kolo2=0, kolo3=0, kolo4=0, kolo5=0;
            //program si vypyta jednotlive udaje o jazdcovi
            printf("zadaj krstne meno a priezvisko jazdca jazdca: ");
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
            //program nasledne ulozi zadane udaje na koniec suboru v nasledovnom formate
            if(rok<999||rok>10000)
            {
                printf("nespravny format roka\n");
            }
            else if(pohlavie!='m' && pohlavie!='f')
            {
                printf("nespravne pohlavie\n");
            }
            else{
                fprintf(subor,"\n%s %s;%c;%d;%s;%.3f;%.3f;%.3f;%.3f;%.3f", krstne, priezvisko, pohlavie, rok, znacka, kolo1, kolo2, kolo3, kolo4, kolo5);
                fclose(subor);
            }
            
        }
    }
    printf("\nPre pokracovanie stlacte hociaku klavesu: ");
    scanf(" %c", &hocico);
    printf("\n\n");
    system("clear");
}
void change(){
   system("clear");
   char hocico=' ';
   FILE *subor;
   subor = fopen("jazdci.csv", "r+");//subor sa otvori v rezime r+(citanie a pisanie), preto nie w+, lebo w+ najprv premaze cely subor
   if(subor==NULL)
   {
      printf("Neotvoreny subor\n");
    }
    else if(Kontrola_struktury(subor)!=0)
        {printf("Nespravna struktura\n");}
    else{
        /*
            Tato funkcia funguje tak, ze si zavola funkciu Vytvor na vytvorenie struktury, nasledne si vypyta priezvisko, poradie kola a nove kolo 
            pretekara, ktoremu chceme zmenit cas. Program si tohto pretekara, ak sa nachadza v subore najde, prepise hodnotu zvoleneho kola v strukture
            na hodnotu noveho kola a nasledne prepise cely subor uz s novou hodnotou. Ak sa jazdec v subore nenachadza, tak vypise jazdec sa nenasiel
        */
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
        int riadok=0, nenaslo=1, hviezdicka=0, original_pocet_riadkov=Pocet_riadkov(), nenasiel=0;
        vytvor(subor,(Jazdci *) &Jazdec);
        for(int i=0;i<Pocet_riadkov();i++){
            riadok++;
            if(strcmp(priezvisko, Jazdec[i].priezvisko)==0){
                Jazdec[i].kola[poradie_kola-1]=nove_kolo;
                break;
            }
            else{nenasiel++;}
        }
        if(nenasiel==Pocet_riadkov())
            {
                printf("Jazdec sa nenasiel\n");
                printf("\nPre pokracovanie stlacte hociaku klavesu: ");
                scanf(" %c", &hocico);
                printf("\n\n");
                system("clear");
            }
        else{
            FILE *subor2;
            subor2 = fopen("docasne.csv", "w");
            fseek(subor2, hviezdicka,SEEK_SET);
            for(int i=0;i<Pocet_riadkov();i++){
                fprintf(subor2,"%s %s;%c;%d;%s", Jazdec[i].krstne, Jazdec[i].priezvisko, Jazdec[i].pohlavie, Jazdec[i].narodenie, Jazdec[i].Auto);
                for(int j=0;j<5;j++)
                {
                    fprintf(subor2,";%.3f", Jazdec[i].kola[j]);
                }
                if(Pocet_riadkov()-1!=i)
                {fprintf(subor2,"\n");}
            }
            fclose(subor);
            fclose(subor2);
            remove("jazdci.csv");
            rename("docasne.csv", "jazdci.csv");
            sum();
        }
    }
}
void rmdriver(){
   system("clear");
   char hocico=' '; 
   FILE *subor;
   subor = fopen("jazdci.csv", "r+");
   if(subor==NULL)
   {
      printf("Neotvoreny subor\n");
    }
    else if(Kontrola_struktury(subor)!=0)
        {printf("Nespravna struktura\n");}
    else{
        //v tejto funkcii nevytvaram strukturu, lebo mi to prislo zbytocne
        char priezvisko[100], cele_meno[100], hladaj_priezvisko[100];
        printf("zadaj meno jazdca: ");
        scanf(" %s", &priezvisko);
        printf("\n");
        char ln[1000],ln2[1000],*string;
        int pocet=0;
        fseek(subor, 0,SEEK_SET);
        /*
            po zadani priezviska, ktore ma byt odstranene, ho program zacne hladat v subore.
            Ak ho najde, cely riadok na ktorom sa nachadza az po koniec riadku prepise na '*'.
            Potom si do dalsieho docasneho suboru ulozim vsetko zo suboru okrem znakov '*'.
            Nasledne stary subor zmazem a ten novy pomenujem rovnakym nazvom, aky mal ten povodny subor.
        */
        while (fgets(ln, 1000, subor)){
                pocet++;
                strcpy(ln2, ln);
                int gazember=0;
                string=strtok(ln, ";");//rozdeluje nacitany riadok po ;
                strcpy(hladaj_priezvisko, string);
                strcpy(cele_meno, string);
                string=strrchr(hladaj_priezvisko, ' ');
                strcpy(hladaj_priezvisko,string+1);
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
         if (strcmp(hladaj_priezvisko, priezvisko)==0){

            if(pocet==Pocet_riadkov()){
                fseek(subor, -strlen(ln2)-2,SEEK_CUR);

            }
            else if(1<pocet){
                fseek(subor, -strlen(ln2)-1,SEEK_CUR);
            }
            else{
                fseek(subor, 0,SEEK_SET);
            }

            for(int i=0;i<strlen(ln2);i++){//vo Windowse musi byt i<=strlen(ln2) a na linuxe i<strlen(ln2), aby sa vymazal endl znak
                fprintf(subor,"*");
                 }

            char c;
            FILE *subor2;
            subor2 = fopen("docasne.csv", "w");
            fseek(subor, 0,SEEK_SET);
            while((c = fgetc(subor)) != EOF ){
                if(c!='*'){
                    fputc(c, subor2);
                }
            }
            fclose(subor);
            fclose(subor2);
            remove("jazdci.csv");
            rename("docasne.csv", "jazdci.csv");
            printf("Jazdec %s bol uspesne odstraneny\n", cele_meno);

        }
        else{printf("Jazdec neexistuje\n");}
    }
    printf("\nPre pokracovanie stlacte hociaku klavesu: ");
    scanf(" %c", &hocico);
    printf("\n\n");
    system("clear");
}    
void vypisy_menu()
{   //toto je len vypis pre menu, ake funkcie ma program a strucny popis toho, co robia

    system("clear");
    printf("----------------------------------------\n");
    printf("-    aplikacia automobilove preteky    -\n");
    printf("----------------------------------------\n");
    printf("Prikaz s: vypis pretekarov\n");
    printf("Prikaz d: vyhladanie udajov o jazdcovi\n");
    printf("Prikaz l: najlepsi vysledok\n");
    printf("Prikaz g: najlepsie vysledky podla pohlavia\n");
    printf("Prikaz b: najlepsie vysledky na jednotlivych znackach\n");
    printf("Prikaz y: najlepsie vysledky pretekarov narodenych pred zadanym rokom\n");
    printf("Prikaz a: priemer pretekarov\n");
    printf("Prikaz u: vysledky pretekarov, ktore su lepsie ako zadany cas\n");
    printf("Prikaz c: zmena casu pretekara\n");
    printf("Prikaz n: pridanie pretekara\n");
    printf("Prikaz r: zmazanie pretekara \n");
    printf("Pre ukoncenie stlacte x \n");
    printf("----------------------------------------\n");
    printf("Vasa volba: ");
}

void menu()
{   //funkcia, ktora riesi menu

 while (1) {
    system("clear");
    printf("----------------------------------------\n");
    printf("-    aplikacia automobilove preteky    -\n");
    printf("----------------------------------------\n");
    printf("Prikaz s: vypis pretekarov\n");
    printf("Prikaz d: vyhladanie udajov o jazdcovi\n");
    printf("Prikaz l: najlepsi vysledok\n");
    printf("Prikaz g: najlepsie vysledky podla pohlavia\n");
    printf("Prikaz b: najlepsie vysledky na jednotlivych znackach\n");
    printf("Prikaz y: najlepsie vysledky pretekarov narodenych pred zadanym rokom\n");
    printf("Prikaz a: priemer pretekarov\n");
    printf("Prikaz u: vysledky pretekarov, ktore su lepsie ako zadany cas\n");
    printf("Prikaz c: zmena casu pretekara\n");
    printf("Prikaz n: pridanie pretekara\n");
    printf("Prikaz r: zmazanie pretekara \n");
    printf("Pre ukoncenie stlacte x \n");
    printf("----------------------------------------\n");
    printf("Vasa volba: ");
    char Vstup=' ';
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
            //nepouzival som funkcie na alokaciu pamate malloc, callo, ani realloc, nemam pamat, ktoru by som funkciou free() mohol uvolnit
            break;
        } else
         {
            printf("Volba %c neexistuje, pre pokracovanie zadajte hociaky znak: ", Vstup);
            scanf(" %c", &Vstup);
            system("clear");
        }
    }
}

int main() {
    menu();
    return 0;
}
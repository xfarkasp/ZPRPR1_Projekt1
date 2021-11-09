#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void s(void){
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
void d(){
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
                //printf("%s\n", vstup);
                //printf("%s\n", priezvisko);

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

int main() {
    char Vstup=' ';
    while (1) {
        scanf(" %c", &Vstup);
        if (Vstup == 's') {
            s();
        } else if (Vstup == 'd'){
            d();
        } else if (Vstup == 'l'){

        } else if (Vstup == 'g'){

        } else if (Vstup == 'b'){

        } else if (Vstup == 'y'){

        } else if (Vstup == 'a'){

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

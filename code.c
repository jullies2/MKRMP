#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <windows.h>
#define nts 5
#define N 41
/*
В файле содержатся сведения о спортсменах: фамилия, пол,
вид спорта, год рождения, рост. Найти самого высокого спортсмена,
занимающегося плаванием, среди мужчин. Вывести сведения о
спортсменках, выступающих в юниорском разряде (14-17 лет).
*/

struct man createstruct(void);
struct man createstructrandom(void);
void printfMan();
void addRecord(struct man record);
void deleteRecord();
void printRecord(struct man record);
void redactRecord();
int StrPadding(char str[], int n);
void PoiskRosta();
void Poiskjuniors();
void creaetFile();
struct man{
    char name[40];
    double height;
    int year;
    char sport[40];
    char gender[7];
};
char FileName[80];
int main(int argc, char *argv[])
{
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
    int choice;
    int stWork=1;
    //system("chcp 1251&&cls");
    srand(time(NULL));
    if (argc == 2) {
        strcpy(FileName, argv[1]);
    }
    else if (argc == 1) {
        printf("Введите имя файла: ");
        gets(FileName);
    }
    else
    {
        printf("Слишком много аргументов!\n");
        return -1;
    }
    do{
    system("CLS");
    puts("0.Создать файл");
    puts("1.Создать запись вручную");
    puts("2.Создать случайную запись");
    puts("3.Вывести содержимое файла");
    puts("4.Удаление");
    puts("5.Редактирование");
    puts("6.Поиск самого высокого пловца из файла");
    puts("7.Поиск спортсменок выступающих в юниорском разряде(2004г.р-2007г.р)(14-17 лет)");
    printf("8.Выход");
    printf("\n\nВведите пункт меню: ");
    if (scanf("%d",&choice)!=1)
    fflush(stdin);
    switch (choice){
       case 0:
         creaetFile();
         break;
       case 1:
         addRecord(createstruct());
         break;
       case 2:
         addRecord(createstructrandom());
         break;
      case 3:
         printfMan();
         break;
       case 4:
         deleteRecord();
         break;
       case 5:
         redactRecord();
         break;
       case 6:
         PoiskRosta();
         break;
       case 7:
         Poiskjuniors();
         break;
       case 8:
           stWork=0;
           puts("\n\nВСЕГО ХОРОШЕГО");
           break;
       default:
        puts("Неверная команда");
    }
    system("pause");

    }
    while(stWork);
    return 0;
}
void creaetFile()
{
 FILE *f=fopen(FileName,"w");
    if(f)
    {
        printf("Файл создан!\n");
        fclose(f);
    }
}
struct man createstruct(void){
   struct man record;
   char num;
   puts("Создание новой записи\n");
   fflush(stdin);
   printf("Фамилия: ");
   fflush(stdin);
   gets(record.name);
   printf("Год рождения: ");
   scanf("%d",&record.year);
   printf("Рост: ");
   scanf("%lf",&record.height);
   printf("Пол(муж-1 или жен-2):");
   fflush(stdin);
   scanf("%c",&num);
   while (num!='1'&&num!='2')
    {puts("неккоректный ввод введите потовроно");
    scanf("%c",&num);}
         if (num=='1')
            strcpy(record.gender,"муж");
         else
            strcpy(record.gender,"жен");
   printf("Спорт(ввод с заглавной буквы): ");
   fflush(stdin);
   gets(record.sport);
   return record;
   };
void addRecord(struct man record){
   FILE *f=fopen(FileName,"a+b");
   if (f)
    {
     fwrite(&record,1,sizeof(record),f);
     fclose(f);
     puts("Запись успешно добавлена");
    }
   else
    puts("Не удалось добавить запись");
}
struct man createstructrandom(void){
     struct man record;
     char names[][40]={"Петров","Иванов","Александров","Алексеев","Jhonson","Black","White","Kim","Андреев","АПА"};
     char sports[][40]={"Шахматы","Футбол","Баскетбол","Волейбол","Хоккей","Теннис","Плавание","Бег"};
     char genders[][7]={"муж","жен"};
     strcpy(record.name,names[rand()%10]);
     record.year=1950+rand()%80;
     strcpy(record.gender,genders[rand()%2]);
     record.height=rand()%187+11+rand()%100/100.0;
     strcpy(record.sport,sports[rand()%8]);


     puts("Random note was created");
     return record;
};
void printfMan()
{
     FILE *f=fopen(FileName,"r+b");
     if (f)
        {
          int cnt,num,i,j;
          char choice;
          struct man record;
          fseek(f, 0, SEEK_END);
          cnt = ftell(f)/sizeof(struct man);
          num=cnt/nts + 1;
          while(cnt>=nts)
              cnt=cnt-nts;
          fseek(f,0,SEEK_SET);
          for (i=0;i<num;i++) {
            system("CLS");
            printf("╔═══════════════════════╦═════╦═════════╦═════════════════════╦═════╗\n");
            printf("║    ФАМИЛИЯ            ║ Г.Р ║  РОСТ   ║        СПОРТ        ║ ПОЛ ║\n");
            //printf("╚═══════════════════════╩═════╩════════╩═════════════════════╩═════╝\n");
            if(i+1==num&&cnt==0)
                break;
            for (j=0;j<nts;j++)
                {
                  fread(&record,sizeof(struct man),1,f);
                  if(feof(f))
                    break;
                puts("╠═══════════════════════╬═════╬═════════╬═════════════════════╬═════╣");
            printf("║%s%*s║%-5d║%-9.2lf║%s%*s║%-5s  ║\n",record.name,StrPadding(record.name, 23)," ",record.year,record.height,record.sport,StrPadding(record.sport,21)," ",record.gender);
           // printf("║%-5d",record.year);
           // printf("║%-7.2lf",record.height);
            //printf("║%-21s",record.sport);
            //printf("║%-5s ║\n",record.gender);
            }
            puts("╚═══════════════════════╩═════╩═════════╩═════════════════════╩═════╝");
            printf("<--a   s-выход   d-->\n");

            do {
                printf("Ввод: ");

                while(getchar() != '\n');
                while (!scanf("%c", &choice))
                {
                  printf("Ошибка ввода!\nВведите еще раз: ");
                  while(getchar() != '\n');
                }

                if(choice != 'a' && choice != 's' && choice != 'd')
                    printf("Неизвестная команда!\n");
               }
               while(choice != 'a' && choice != 's' && choice != 'd');

            if(choice=='a') {
                if(i==0)
                    break;
                else if(i+1==num)
                    fseek(f,-sizeof(struct man)*(cnt+nts),SEEK_CUR);
                else
                    fseek(f,(long int)-sizeof(struct man)*nts*2,SEEK_CUR);
                i-=2;
            }
            else if (choice == 's') {
                break;
            }
        }
          fclose(f);
       }
      else
            puts("Не удалось открыть файл для вывода записей");

}
void deleteRecord()
  {
    FILE *f=fopen(FileName,"r+b");
    FILE *ft=fopen("__________temp","w+b");
    int nothingWasDeleted=1;
    if (f&&ft)
     {
      char name[40];
      fflush(stdin);
      printf("Введите имя для поиска: ");
      gets(name);
      struct man record;
      while (fread(&record,1,sizeof(record),f))
        {
         if (strcmp(name,record.name)==0)
           {
            printRecord(record);
            puts("Эту запись Вы хотите удалить? '1'-да,'2'-нет");
            char answer;
            fflush(stdin);
            answer=getchar();
            while (answer!='1'&&answer!='2')
            {
             puts("Неккоректный ввод. Введите еще раз.");
             answer=getchar();
            }
            if (answer=='2')
               fwrite(&record,1,sizeof(record),ft);
            else
            {
                puts("Запись успешно удалена");
                nothingWasDeleted=0;
            }}
        else
               fwrite(&record,1,sizeof(record),ft);

     }
     fclose(f);
     fclose(ft);
     remove(FileName);
     rename("__________temp",FileName);
     if (nothingWasDeleted)
        puts("Ничего не было удалено из файла");
  }
  else
    puts("Не удалось открыть файл для удаления записи");
  }
  void printRecord(struct man record)
 {
      printf("Фамилия: %-20s\n",record.name);
      printf("Год рождения: %-4d\n",record.year);
      printf("Рост: %-7.2lf\n",record.height);
      printf("Вид спрота: %-20s\n",record.sport);
      printf("Пол: %4s \n",record.gender);
 }
 void redactRecord()
 {
    FILE *f=fopen(FileName,"r+b");
    char s[20];
    int answer;
    if (f)
     {
      puts("Введите имя спортсмена, данные о котором нужно изменить: ");
      fflush(stdin);
      gets(s);
      struct man record;
      int flag=0;
      while (fread(&record,1,sizeof(record),f))
       {if (strcmp(s,record.name)==0)
        {{
         flag=1;
         puts("Эту запись вы хотите изменить? 1-да,2-нет.");
         printf("Фамилия: %-20s\n",record.name);
         printf("Год рождения: %-4d\n",record.year);
         printf("Рост: %-7.2lf\n",record.height);
         printf("Вид спрота: %-20s\n",record.sport);
         printf("Пол: %4s|\n",record.gender);
        }
        if (flag==1)
         {flag=0;
          scanf("%d",&answer);
          while (answer!=1&&answer!=2)
          {
            puts("Неккоректный ввод. Введите повторно. 1-да, 2-нет: ");
            scanf("%d",&answer);
          }
          if (answer==1)
          {
            puts("Какую часть информации вы хотите изменить?");
            int m;
            char num;
            printf("1.Фамилия\n");
            printf("2.Год родления\n");
            printf("3.Рост\n");
            printf("4.Вид спорта\n");
            printf("5.Пол\n");
            scanf("%d",&m);
            int flagtoswitch=1;
            while (flagtoswitch)
            {switch (m)
             {
              case 1:
                  puts("Введите новую фамилию: ");
                  fflush(stdin);
                  gets(record.name);
                  flagtoswitch=0;
                  break;
              case 2:
                  puts("Введите новый год рождения: ");
                  scanf("%d",&record.year);
                  flagtoswitch=0;
                  break;
              case 3:
                  puts("Введите новый рост: ");
                  scanf("%lf",&record.height);
                  flagtoswitch=0;
                  break;
              case 4:
                  puts("Введите новый вид спорта: ");
                  fflush(stdin);
                  gets(record.sport);
                  flagtoswitch=0;
                  break;
              case 5:
                  puts("Выберите новый пол('1'-муж, '2'-жен): ");
                  fflush(stdin);
                  scanf("%c",&num);
                  while (num!='1'&&num!='2')
                    {fflush(stdin);
                     puts("Неккоректный ввод введите потовроно('1'-муж, '2'-жен)");
                     scanf("%c",&num);}
                  if (num=='1')
                     strcpy(record.gender,"муж");
                  else
                     strcpy(record.gender,"жен");
                  flagtoswitch=0;
                  break;
              default:
                  puts("Неверная команда.");
             }}
              fseek(f, (long int)-sizeof(struct man), SEEK_CUR);
              fwrite(&record, sizeof(struct man), 1, f);
              fseek(f, 0, SEEK_END);
           }}}}
     fclose(f);
     puts("Запись успешно отредактирована");
      }
     else
       puts("Не удалось открыть файл для редактирования");
 }
 void PoiskRosta()
{
  FILE *f=fopen(FileName,"r+b");
  double maxrost=0;
  if (f)
  {
   struct man record;
   while (fread(&record,1,sizeof(record),f))
    {
     if ((record.height>maxrost)&&(strcmp("Плавание",record.sport)==0)&&(strcmp("муж",record.gender)==0))
        maxrost=record.height;
    }

  if (maxrost!=0)
   {f=freopen(FileName,"r+b",f);
   double eps=0.00001;
   if (f)
    {
     while (fread(&record,1,sizeof(record),f))
       {
         if ((fabs(record.height-maxrost)<eps)&&(strcmp("Плавание",record.sport)==0)&&(strcmp("муж",record.gender)==0))
           printRecord(record);
       }
    }
   else
      puts("Не удалось открыть файл для поиска максимального роста среди плавцов(men)");
    fclose(f);
    puts("Поиск выполнен");
  }
  else
    puts("Нет спортсменов соответствующим требуемым параметрам поиска");
  }
  else
    puts("Не удалось открыть файл для поиска максимального роста среди плавцов(men)");
}
void Poiskjuniors()
{
  FILE *f=fopen(FileName,"r+b");
  int flag=0;
  if (f)
  {
   struct man record;
   while (fread(&record,1,sizeof(record),f))
    {
     if ((strcmp("жен",record.gender)==0)&&(record.year>=2004)&&(record.year<=2007))
        {
         printRecord(record);
         flag=1;
        }
    }
  fclose(f);
  if (flag==1)
    puts("Поиск выполнен");
  else
    puts("Нет спортсменок, выступающих в юниорском разряде(14-17 лет).");
  }
  else
    puts("Не удалось открыть файл для поиска");
}
int StrPadding(char str[], int n) {
    int i;
    for(i=0; i<N; i++)
    {
        if(str[i]=='\0')
            break;
        else if(str[i]< 0)
            i++;
        n--;
    }
    return n;
}


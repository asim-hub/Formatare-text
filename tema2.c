#include <stdio.h>
#include <string.h>
#include<stdlib.h>

//functii
void Wrap(int max_line_length,char original[][1000], int *original_line_count){
  int i,j,maxim=0,strl=0,nr=0,l;
  char chr[100000],copy[1000][1000];
  //copiez original in copy
  for (i = 0; i < (*original_line_count); i++) {
    strcpy(copy[i], original[i]);
  }


i=0;
while(  i < (*original_line_count) ){
  l=strlen(original[i]);
  while(original[i][(l-1)]=='\n' && original[i][(l-2)]==' '){
    original[i][(l-1)]='\0';original[i][(l-2)]='\n';l--;
  }
  //parcurg linia i
for(j=0;j<=l;j++){
//in mod normal daca dupa un cuvant urmeaza un caracter lipit de el, nu face parte din cuvant
//asa ar fi normal , dar in out se considera ca facand parte si nu am voie sa despart
  if(original[i][j] != ' ' && original[i][j] != '\n' && strchr(".,:?!",original[i][j])==NULL)
    nr++;  
      else{
        if(nr>maxim)
          maxim=nr;
          nr=0;
      }
}
i++;
}

if(max_line_length<maxim){
  printf("Cannot wrap!\n");
  for (i = 0; i < (*original_line_count); i++) {
    strcpy(original[i], copy[i]);
  }
}
else{
//aici modific matricea;  
  strl=0;
  for(i=0;i<(*original_line_count);i++){
  j=0;
  while(original[i][j]!='\n'){
    chr[strl]=original[i][j];j++;strl++; 
  }
//ultimul cuvant este urmat de spatiu si apoi '\n''\0'
//fie asta fie la inceput merg pe pozitia finala din fiecare rand al matricei
//si verific ca randul sa nu se termine in ..' '/n/0 ci in ..litere/n/0.
  if(original[i][j]=='\n' && j!=0){
    chr[strl]='\n';strl++;
  }
    else
      if(original[i][j]=='\n' && j==0){
        chr[strl]='$';strl++;
      }    
  }       
int s=0,m=0;
i=0;
nr=0;
while(i<strl){
  while(chr[i]==' ' || chr[i]=='\n')
    i++;
  j=i;
  s=j;
  while(j<(i+max_line_length) && j<strl){
    if(chr[j]!='$')
    s++;
      else
        if(chr[j]=='$'){
          j=i+max_line_length;
        }
  j++;
}
  s--;
  while(chr[s]!=' ' && chr[s]!='\n' && chr[s]!='$' && strchr("?!.,;:",chr[s])==NULL && chr[s+1]!=' ' && chr[s+1]!='\n' && chr[s+1]!='$' /*&& strchr("?!.,;:",chr[s+1])==NULL*/)
    s--;
  nr=0;
  while(i<=s)
  if(chr[i]!='\n'){
    original[m][nr]=chr[i];nr++;i++;
  }
    else
      if(chr[i]=='\n'){
        original[m][nr]=' ';nr++;i++;
      }

  while(original[m][nr-1]==' ' || original[m][nr-1]=='\n')
    nr--;

  original[m][nr]='\n';
  original[m][(nr+1)]='\0';
  s++;
  i=s;
  if(chr[i]=='$'){
    m++;original[m][0]='\n';original[m][1]='\0';s++;
  }
  m++;
  i=s;
  }
  (*original_line_count)=m;
  }
}

void Center(char original[][1000],int start_line, int end_line, int original_line_count)
{ int i,lmax=0,j,k,p;
  if(end_line>original_line_count && start_line<original_line_count)
    end_line=original_line_count-1; 
  if(start_line>end_line)
    printf("Invalid operation!");
      else
        if(start_line<original_line_count){
        /*Aflu pe cea mai lunga*/ 
          for (i=0;i<original_line_count;i++)
            if(lmax<strlen(original[i]))
              lmax=strlen(original[i]);
  if( lmax % 2 == 1)
    for(i=start_line;i<=end_line;i++)
      if(original[i][0]!='\n'){ 
        p=strlen(original[i]);
        if(p%2==1)
        k=((lmax/2)-(p/2)); 
          else
            if(p%2==0)
              k=((lmax/2)-(p/2) +1);
        while(k!=0){
          for(j=(p+2);j>=1;j--)
            original[i][j]=original[i][j-1];
            original[i][0]=' ';k--;p++;}
      }
  if( lmax % 2 == 0 )  
    for(i=start_line;i<=end_line;i++)
      if(original[i][0]!='\n'){ 
        p=strlen(original[i]);
        k=((lmax/2)-(p/2)); //refolosesc p
        while(k!=0){
          for(j=(p+2);j>=1;j--)
            original[i][j]=original[i][j-1];
            original[i][0] = ' ';k--;p++;
          }
}
} 
}

void Left(char original[][1000],int start_line, int end_line, int original_line_count)
{
  int i,j,l;
  //Trebuie eliminate spatiile de la final
  for(i=0;i<original_line_count;i++){
    l=strlen(original[i]);
    while(original[i][l-1]=='\n' && original[i][(l-2)]==' '){
      original[i][l-1]='\0';original[i][(l-2)]='\n';l--;
    }
  }

  if(end_line>original_line_count && start_line<original_line_count)
    end_line=original_line_count-1; 
  if(start_line>end_line)
    printf("Invalid operation!");
      else
        if(start_line<original_line_count){
          for(i=start_line;i<=end_line;i++) 
            while(original[i][0]==' ')
              for(j=0;j<(strlen(original[i]));j++)
                original[i][j]=original[i][j+1];
        }
}

void Right(char original[][1000],int start_line, int end_line, int original_line_count)
{
  int i=0,j,l,maxim=0;
  while(i<original_line_count){
   l=strlen(original[i]);
  while(original[i][(l-1)]=='\n' && original[i][(l-2)]==' ')
    {original[i][(l-1)]='\0';original[i][(l-2)]='\n';l--;}
  l=strlen(original[i]);
  if(l>maxim)
    maxim=l; 
  i++;
  }
  if(end_line>original_line_count && start_line<original_line_count)
    end_line=original_line_count-1; 
if(start_line>end_line)
  printf("Invalid operation!");
    else
    if(start_line<original_line_count)
      for(i=start_line;i<=end_line;i++){
        while(original[i][maxim-1]!='\n' && original[i][0]!='\n'){
          l=strlen(original[i]);
          l++;
          while(l>0){
            original[i][l]=original[i][(l-1)];l--;}
original[i][0]=' ';
}
}
}

void Justify(char original[][1000],int start_line, int end_line, int original_line_count)
{
  int i=0,j,l,ok=0,max=0,k;
  //aflu linia maxima inainte sa elimin spatiile din fata
  while(i<original_line_count){
    l=strlen(original[i]);
    if(l>max)
      max=l; 
  i++;
  }
  //Trebuie eliminate spatiile de la final
  for(i=0;i<original_line_count;i++){
    l=strlen(original[i]);
    while(original[i][l-1]=='\n' && original[i][(l-2)]==' '){
      original[i][l-1]='\0';original[i][(l-2)]='\n';l--;
    }
  }
//elimin spatile de la inceput
  if(end_line>original_line_count && start_line<original_line_count)
    end_line=original_line_count-1; 
  if(start_line>end_line)
    printf("Invalid operation!");
      else
        if(start_line<original_line_count){
          ok=1;
          for(i=start_line;i<=end_line;i++) 
            while(original[i][0]==' ' || (int)original[i][0]==9)
              for(j=0;j<(strlen(original[i]));j++)
                original[i][j]=original[i][j+1];
        }
  if(ok==1){
  //aici fac operatiile
    while((int)original[i][0]==9)
    for(j=0;j<(strlen(original[i]));j++)
      original[i][j]=original[i][j+1];
    for(i=start_line;i<=end_line;i++){ 
      l=strlen(original[i]);
      j=0;
      if(original[i+1][0]!='\n' && i<=end_line  && original[i][0]!='\n' && strlen(original[i])!=max && i!=original_line_count-1){
      while(original[i][max-1]!='\n' && j<(strlen(original[i]))){
        while(original[i][j]!=' ' && original[i][j]!='\n')j++;
        while(original[i][j]==' ')j++;
      //acum sigur ma aflu pe litera imediat urmatoare de dupa spatiu;
    if(strlen(original[i])-1>j){
      l=l+1;
      for(k=l;k>=j;k--)
      original[i][k]=original[i][k-1];
      j++;
    }
    if(j==strlen(original[i])-1){
      j=0;
      l=strlen(original[i]);
    }
      }
    }
    }
  }
}

void Paragraf(char original[][1000],int indent_length,int start_line, int end_line){

int i,k,l,j;
for(i=start_line;i<=end_line;i++)
if( (i!=0 && original[i-1][0]=='\n') || i==0){
  k=indent_length;
  l=strlen(original[i]);
  while(k!=0){
    l++;
  for(j=l;j>0;j--)
    original[i][j]=original[i][j-1];
  original[i][0]=' ';
  k--;
  }
}
}
void ListI(char original[][1000],char list_type,char special_character,int start_line,int end_line,int original_line_count)
{
  int i=0,k=1,l,cp,j;
  //elimin tot ce am inainte de null si e diferit de litera;
  while(i<original_line_count){
   l=strlen(original[i]);
    while(original[i][(l-1)]=='\n' && ((int)original[i][(l-2)]==9 || (int)original[i][l-2]==32)){
      original[i][(l-1)]='\0';original[i][(l-2)]='\n';l--;
    } 
  i++;
  } 
//incerc sa elimin spatiile de la inceput doar din intervalul dat
  for (i=start_line;i<=end_line;i++)
    while(original[i][0]==' ')
      for(j=0;j<strlen(original[i]);j++)
        original[i][j]=original[i][j+1]; 
  if(list_type=='n'){
  //Pun spatiu!
    for (i=start_line;i<=end_line;i++){
      l=strlen(original[i]);l++;
        for(j=l;j>0;j--)
          original[i][j]=original[i][j-1];
          original[i][0]=' ';
    }
    //Pun special_character 
for (i=start_line;i<=end_line;i++){
  l=strlen(original[i]);
  l++;
  for(j=l;j>0;j--)
    original[i][j]=original[i][j-1];
    original[i][0]=special_character;
}
//numerotez
  for(i=start_line;i<=end_line;i++){
    l=strlen(original[i]);
    cp=k;
    l++;
    while(cp!=0){
      for(j=l;j>0;j--)
        original[i][j]=original[i][j-1];
//trebuie sa transform pe k in char;
        original[i][0]=(cp%10 + '0');
        cp=cp/10;l++;
      }
    k++;
  }
}
    else
      if(list_type=='a' || list_type=='A'){
      //pun spatiu
        for (i=start_line;i<=end_line;i++){
          l=strlen(original[i]);l++;
          for(j=l;j>0;j--)
            original[i][j]=original[i][j-1];
            original[i][0]=' ';
          }  
//pun special_character
  for (i=start_line;i<=end_line;i++){
    l=strlen(original[i]);
    l++;
    for(j=l;j>0;j--)
      original[i][j]=original[i][j-1];
      original[i][0]=special_character;
  }  
//numerotez
  for (i=start_line;i<=end_line;i++){
    l=strlen(original[i]);
    l++;
    for(j=l;j>0;j--)
    original[i][j]=original[i][j-1];
    original[i][0]=list_type;
    list_type=list_type+1;
  }  
}
else
  if(list_type=='b'){
  //pun spatiu
    for (i=start_line;i<=end_line;i++){
      l=strlen(original[i]);
      l++;
      for(j=l;j>0;j--)
        original[i][j]=original[i][j-1];
        original[i][0]=' ';
    }
//pun special-character
    for (i=start_line;i<=end_line;i++){
      l=strlen(original[i]);
      l++;
      for(j=l;j>0;j--)
        original[i][j]=original[i][j-1];
      original[i][0]=special_character;
    }    
}
 //elimin tot ce am inainte de null si e diferit de litera;
  i=0;
  while(i<original_line_count){
    l=strlen(original[i]);
    while(original[i][(l-1)]=='\n' && ((int)original[i][(l-2)]==9 || (int)original[i][l-2]==32)){
      original[i][(l-1)]='\0';original[i][(l-2)]='\n';l--;
    } 
  i++;
  }
}

void ListO(char original[][1000],char list_type,char special_character,char ordering,int start_line,int end_line,int original_line_count){
  int i=0,k=1,l,cp,j;
  char aux[1000];
  //elimin tot ce am inainte de null si e diferit de litera;  
  while(i<original_line_count){
    l=strlen(original[i]);
    while(original[i][(l-1)]=='\n' && ((int)original[i][(l-2)]==9 || (int)original[i][l-2]==32)){
      original[i][(l-1)]='\0';
      original[i][(l-2)]='\n';
      l--;
    } 
  i++;
  }

  if(ordering=='a')
    for(i=start_line;i<end_line;i++)
      for(j=i+1;j<=end_line;j++){
        k=0;
        while(original[i][k]==original[j][k]) k++;
        if(original[i][k]>original[j][k]){
        strcpy(aux,original[i]);
        strcpy(original[i],original[j]);
        strcpy(original[j],aux);
        }
      }
  if(ordering=='z')
   for(i=start_line;i<end_line;i++)
      for(j=i+1;j<=end_line;j++){
        k=0;  
        while(original[i][k]==original[j][k]) k++; 
        if( original[i][k]<original[j][k] ){
          strcpy(aux,original[i]);
          strcpy(original[i],original[j]);
          strcpy(original[j],aux);
        }
      }
  for (i=start_line;i<=end_line;i++)
    while(original[i][0]==' ')
      for(j=0;j<strlen(original[i]);j++)
        original[i][j]=original[i][j+1]; 
  if(list_type=='n'){
    //pun spatiu
      for (i=start_line;i<=end_line;i++){
        l=strlen(original[i]);
        l++;
        for(j=l;j>0;j--)
          original[i][j]=original[i][j-1];
        original[i][0]=' ';
      }
    //Pun special_character 
    for (i=start_line;i<=end_line;i++){
      l=strlen(original[i]);
      l++;
        for(j=l;j>0;j--)
          original[i][j]=original[i][j-1];
        original[i][0]=special_character;
    }
//numerotez
    for(i=start_line;i<=end_line;i++){
      l=strlen(original[i]);
      cp=k;
      l++;
      while(cp!=0){
        for(j=l;j>0;j--)
          original[i][j]=original[i][j-1];
  //trebuie sa transform pe k in char;
        original[i][0]=(cp%10 + '0');
        cp=cp/10;l++;
      }
    k++;
    }
  }
    else
      if(list_type=='a' || list_type=='A'){
        //pun spatiu
        for (i=start_line;i<=end_line;i++){
          l=strlen(original[i]);l++;
          for(j=l;j>0;j--)
            original[i][j]=original[i][j-1];
          original[i][0]=' ';
        }  
      //pun special_character
        for (i=start_line;i<=end_line;i++){
          l=strlen(original[i]);l++;
          for(j=l;j>0;j--)
            original[i][j]=original[i][j-1];
          original[i][0]=special_character;
        }  
//numerotez
   for (i=start_line;i<=end_line;i++){
    l=strlen(original[i]);l++;
      for(j=l;j>0;j--)
        original[i][j]=original[i][j-1];
      original[i][0]=list_type;
      list_type=list_type+1;
    }  
  }
    else
      if(list_type=='b'){
      //pun spatiu
      for (i=start_line;i<=end_line;i++){
        l=strlen(original[i]);l++;
        for(j=l;j>0;j--)
        original[i][j]=original[i][j-1];
      original[i][0]=' ';
      }
//pun special-character
      for (i=start_line;i<=end_line;i++){
        l=strlen(original[i]);
        l++;
        for(j=l;j>0;j--)
          original[i][j]=original[i][j-1];
        original[i][0]=special_character;
      }    
    }
  }

int main(int argc, char *argv[]) {
  char buf[1000],               // buffer used for reading from the file
      original[1000][1000],    // original text, line by line
      result[1000][1000];      // text obtained after applying operations
  int original_line_count = 0,  // number of lines in the input file
      result_line_count = 0,    // number of lines in the output file
      i,j;

  if (argc != 4) {  // invalid number of arguments
    fprintf(stderr,
            "Usage: %s operations_string input_file output_file\n",
            argv[0]);
    return -1;
  }

  // Open input file for reading
  FILE *input_file = fopen(argv[2], "r");

  if (input_file == NULL) {
    fprintf(stderr, "File \"%s\" not found\n", argv[2]);
    return -2;
  }

  // Read data in file line by line
  while (fgets(buf, 1000, input_file)) {
    strcpy(original[original_line_count], buf);
    original_line_count++;
  }

  fclose(input_file);
  
  int max_line_length=0,k=0,start_line,end_line,a,arg,indent_length,okay;
  int l=strlen(argv[1]);
  char list_type,special_character,ordering;
  while(k<l){
    while(argv[1][k]==(char)32 && k<l)
      k++;
    if(argv[1][k]==',' && k<l)
      k++;
    while(argv[1][k]==(char)32 && k<l)
      k++;
    if((argv[1][k]=='W' || argv[1][k]=='w' )&& k<l ){
      k++;
      max_line_length=0;
      while(argv[1][k]==(char)32 && k<l)
        k++;
      while(argv[1][k]<=(char)57 && argv[1][k]>=(char)48 && k<l){  
        a=argv[1][k] - '0';
        max_line_length=max_line_length*10 + a;
        k++;
      }
      //apelez functia W  
    Wrap(max_line_length,original,&original_line_count);
  }
  while(argv[1][k]==(char)32 && k<l)
    k++;
    if(argv[1][k]==',' && k<l)
      k++;
    while(argv[1][k]==(char)32 && k<l)
      k++;
  char apel[]={"CRLJ"};
  //de aici
  for(j=0;j<4;j++){
    while(argv[1][k]==(char)32 && k<l)
      k++;
  if(argv[1][k]==',' && k<l)
    k++;
  while(argv[1][k]==(char)32 && k<l)
    k++;
  if((argv[1][k]==apel[j] || argv[1][k]==(apel[j]+32)) && k<l){
    start_line=0;end_line=original_line_count-1;
    k++;
    while(argv[1][k]==(char)32 && k<l)
      k++;
    a=-1;
    arg=0;
    while(argv[1][k]<=(char)57 && argv[1][k]>=(char)48 && k<l){  
      a=argv[1][k] - '0';
      arg=arg*10 + a;
      k++;
    }
  if (a!=-1)
    start_line=arg;
  while(argv[1][k]==(char)32 && k<l)
    k++;
  a=-1;
  arg=0;
  while(argv[1][k]<=(char)57 && argv[1][k]>=(char)48 && k<l){  
    a=argv[1][k] - '0';
    arg=arg*10 + a;
    k++;    
  }
  if (a!=-1)
    end_line=arg;
  if(j==0){
    Center(original,start_line,end_line,original_line_count);
  }
  if(j==1){
    Right(original,start_line,end_line,original_line_count);
  }
  if(j==2){
    Left(original,start_line,end_line,original_line_count);
  }
  if(j==3){    
    Justify(original,start_line,end_line,original_line_count);
  }
  }
  
}
//pana aici 4 in 1

  while(argv[1][k]==(char)32 && k<l)
    k++;
  if(argv[1][k]==',' && k<l)
    k++;
  while(argv[1][k]==(char)32 && l<k)
    k++;
  //pentru paragraph
  if((argv[1][k]=='P' || argv[1][k]=='p') && k<l){
    start_line=0;end_line=original_line_count-1;
    k++;
    while(argv[1][k]==(char)32 && k<l)
      k++;
  a=-1;
  arg=0;
  while(argv[1][k]<=(char)57 && argv[1][k]>=(char)48 && k<l){  
      a=argv[1][k] - '0';
      arg=arg*10 + a;
      k++;
  }
  if (a!=-1)
      indent_length=arg;
  while(argv[1][k]==(char)32 && k<l)
    k++;
  a=-1;
  arg=0;
  while(argv[1][k]<=(char)57 && argv[1][k]>=(char)48 && k<l){  
    a=argv[1][k] - '0';
    arg=arg*10 + a;
    k++;
  }
  if (a!=-1)
    start_line=arg;
  while(argv[1][k]==(char)32 && k<l)
    k++;
  a=-1;
  arg=0;
  while(argv[1][k]<=(char)57 && argv[1][k]>=(char)48 && k<l){  
    a=argv[1][k] - '0';
    arg=arg*10 + a;
    k++;    
  }
  if (a!=-1)
    end_line=arg;
  Paragraf(original,indent_length,start_line,end_line);
  }

  //pentru liste
  while(argv[1][k]==(char)32 && k<l)
    k++;
  if(argv[1][k]==',' && k<l)
    k++;
  while(argv[1][k]==(char)32 && k<l)
    k++;
  if((argv[1][k]=='i' || argv[1][k]=='I') && k<l){
    start_line=0;
    end_line=original_line_count-1;
    k++;
    while(argv[1][k]==(char)32 && k<l)
      k++;
    if((argv[1][k]=='n' || argv[1][k]=='a' || argv[1][k]=='A' || argv[1][k]=='b') && k<l){
      list_type=argv[1][k];
      k++;
    }
  while(argv[1][k]==(char)32 && k<l)
    k++;
  if(strchr(")*+-.",argv[1][k])!=NULL && k<l){
    special_character=argv[1][k];
    k++;
  }
  while(argv[1][k]==(char)32 && k<l)
    k++;
  a=-1;
  arg=0;
  while(argv[1][k]<=(char)57 && argv[1][k]>=(char)48 && k<l){  
    a=argv[1][k] - '0';
    arg=arg*10 + a;
    k++;
  }
  if (a!=-1)
    start_line=arg;
  while(argv[1][k]==(char)32 && k<l)
    k++;
  a=-1;
  arg=0;
  while(argv[1][k]<=(char)57 && argv[1][k]>=(char)48 && k<l){  
    a=argv[1][k] - '0';
    arg=arg*10 + a;
    k++;    
  }
  if (a!=-1)
    end_line=arg;
  ListI(original,list_type,special_character,start_line,end_line,original_line_count); 
  }
//pt functia O
  while(argv[1][k]==(char)32 && k<l)
    k++;
  if(argv[1][k]==',' && k<l)
    k++;
  while(argv[1][k]==(char)32 && k<l)
    k++;
  if ((argv[1][k]=='O' || argv[1][k]=='o') && k<l){
    start_line=0;end_line=original_line_count-1;
    k++;
    while(argv[1][k]==(char)32 && k<l)
      k++;
    if((argv[1][k]=='n' || argv[1][k]=='a' || argv[1][k]=='A' || argv[1][k]=='b') && k<l){
      list_type=argv[1][k];
      k++;  
    }
  while(argv[1][k]==(char)32 && k<l)
    k++;
  if(strchr(")*+-.",argv[1][k])!=NULL && k<l){
    special_character=argv[1][k];
    k++;
    }//trebuie ca cele doua sa fie in paranteze
  while(argv[1][k]==(char)32 && k<l)
    k++;
  if ((argv[1][k]=='a' || argv[1][k]=='z') && k<l)
    ordering=argv[1][k];
  k++;
  while(argv[1][k]==(char)32 && k<l)
    k++;
  a=-1;
  arg=0;
  while(argv[1][k]<=(char)57 && argv[1][k]>=(char)48 && k<l){  
    a=argv[1][k] - '0';
    arg=arg*10 + a;
    k++;
  }
  if (a!=-1)
    start_line=arg;
  while(argv[1][k]==(char)32 && k<l)
    k++;
  a=-1;
  arg=0;
  while(argv[1][k]<=(char)57 && argv[1][k]>=(char)48 && k<l){  
    a=argv[1][k] - '0';
    arg=arg*10 + a;
    k++;    
  }
  if (a!=-1)
    end_line=arg;
  ListO(original,list_type,special_character,ordering,start_line,end_line,original_line_count);
  }
  while(argv[1][k]==(char)32 && k<l)
    k++;
  if(argv[1][k]==',' && k<l)
    k++;
  while(argv[1][k]==(char)32 && k<l)
    k++;
  if(strchr("WwCcLlRrJjPpIiOo",argv[1][k])==NULL){
  k++;
  printf("Invalid operation!\n");k=l+1;
  }//in cazul in care o comanda este gresita sa sara la 
//cealalta comanda
  }

//copiez in result modificarile aduse lui original
  for (i = 0; i < original_line_count; i++) {
    strcpy(result[i], original[i]);
  }
  result_line_count = original_line_count;


  // Open output file for writing
  FILE *output_file = fopen(argv[3], "w");

  if (output_file == NULL) {
    fprintf(stderr, "Could not open or create file \"%s\"\n", argv[3]);
    return -2;
  }

  // Write result in output file
  for (i = 0; i < result_line_count; i++) {
    fputs(result[i], output_file);
  }

  fclose(output_file);
return 0;}


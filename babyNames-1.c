/*
*  Homework 3
*  C Programming
*  Created on: Jan 22, 2016
*      Author: Kevin Nguyen
*/


#include <stdio.h>
#include <string.h>
#define MAX_LEN 15
#define MAX_NAME 1000

//sort array sorts the array. It also sorts the ranks as it sorts the names in alphabetical order.
void sortarray(char names[MAX_NAME][MAX_LEN],int ranks[MAX_NAME][MAX_LEN],int size){
    char temp[MAX_LEN]; // temp for moving names.
    int temp2[10][MAX_LEN]; //temp2 for moving ranks.
    int n,t,i;
    for(n=0;n<size;n++){
        for(t=n+1;t<size;t++){
            if(strcmp(names[n],names[t])>0){
                strcpy(temp,names[n]);
                strcpy(names[n],names[t]);
                strcpy(names[t],temp);
                
                for(i=0;i<MAX_LEN;i++){
                    temp2[0][i] = ranks[n][i];
                }
                
                for(i=0;i<MAX_LEN;i++){
                    ranks[n][i] = ranks[t][i];
                }
                
                for(i=0;i<MAX_LEN;i++){
                    ranks[t][i] = temp2[0][i];
                }
            }
        }
    }
}
//into the array adds the name and rank of the baby names into the main array from the files passed over. This method also recieves the column & size to update it.
void intothearray(FILE *current, char names[MAX_NAME][MAX_LEN],int ranks[MAX_NAME][MAX_LEN],int *col,int *size){
    
    int r,t;
    int k=0;
    char f;
    char name[MAX_LEN];
    
    for(r=0;r<100;r++){
        int count=0;
        fscanf(current,"%[a-zA-Z],",name);
        fscanf(current,"%[a-zA-Z],",&f);
        fscanf(current,"%d",&k);
        
        fscanf(current,"%[a-zA-Z],",name);
        fscanf(current,"%[a-zA-Z],",&f);
        fscanf(current,"%d",&k);
        for(t=0;t<*size;t++){
            if(strcmp(name,names[t])==0){
                ranks[t][*col]=r+1;
                count++;
            }
        }
        if(count==0){
            strcpy(names[*size],name);
            ranks[*size][*col]=r+1;
            *size+=1;
        }
        
    }
    *col+=1;
}
//processing single file can be called once the baby names and ranks are completed. Passing the arrays and the section on the array along with the file will print 
//the name, rank, and year it was placed in.
void processsinglefile(char names[MAX_NAME][MAX_LEN],int ranks[MAX_NAME][MAX_LEN], int section, int year){
    printf("%s,",names[section]);
    if(year==1920){
        printf("%d,1920\n",ranks[section][0]);
        }else if(year==1930){
        printf("%d,1930\n",ranks[section][1]);
        }else if(year==1940){
        printf("%d,1940\n",ranks[section][2]);
        }else if(year==1950){
        printf("%d,1950\n",ranks[section][3]);
        }else if(year==1960){
        printf("%d,1960\n",ranks[section][4]);
        }else if(year==1970){
        printf("%d,1970\n",ranks[section][5]);
        }else if(year==1980){
        printf("%d,1980\n",ranks[section][6]);
        }else if(year==1990){
        printf("%d,1990\n",ranks[section][7]);
        }else if(year==2000){
        printf("%d,2000\n",ranks[section][8]);
        }else if(year==2010){
        printf("%d,2010\n",ranks[section][9]);
        
}else{}
    
}
//read single file returns a file pointer, it reads a char[] as a parameter and opens the file with that text.
FILE *readsinglefile(char text[]){
    return fopen(text,"r");
}
//read all files calls the single file method so that each file could point to a file it is required to. Files are sent in as the parameter from main for read all files so that
//main could use the files that are open for arrays.
void readAllFiles(FILE ** one,FILE **two,FILE **three,FILE **four,FILE **five,FILE **six,FILE **seven,FILE **eigth,FILE **nine,FILE **ten){
    
    *one=readsinglefile("yob1920.txt");
    *two=readsinglefile("yob1930.txt");
    *three=readsinglefile("yob1940.txt");
    *four=readsinglefile("yob1950.txt");
    *five=readsinglefile("yob1960.txt");
    *six=readsinglefile("yob1970.txt");
    *seven=readsinglefile("yob1980.txt");
    *eigth=readsinglefile("yob1990.txt");
    *nine=readsinglefile("yob2000.txt");
    *ten=readsinglefile("yob2010.txt");
}


//outfile creates a outfile that soons prints out the baby names and ranks.
void outfile( char names[MAX_NAME][MAX_LEN],int ranks[MAX_NAME][MAX_LEN], int size){
    FILE*output;
    output=fopen("summary.csv","w");
    int p,q;
    char start[]="Name,1920,1930,1940,1950,1960,1970,1980,1990,2000,2010";
    fprintf(output,"%s\n",start);
    for(p=0;p<size;p++){
        fprintf(output,"%s",names[p]);
        for(q=0;q<10;q++){
            if(ranks[p][q]==0){
            fprintf(output,",");}
            else{
                fprintf(output,",%d",ranks[p][q]);
            }
        }
        fprintf(output,"\n");
    }
    
}
//starting terms adds the names and ranks for the first text file that came up, 1920. 
void startingTerms(char names[MAX_NAME][MAX_LEN],int ranks[MAX_NAME][MAX_LEN],FILE*one){
    int r;
    int k=0;
    char f;
    for(r=0;r<100;r++){
        fscanf(one,"%[a-zA-Z],",names[r]);
        fscanf(one,"%[a-zA-Z],",&f);
        fscanf(one,"%d",&k);
        fscanf(one,"%[a-zA-Z],",names[r]);
        fscanf(one,"%[a-zA-Z],",&f);
        fscanf(one,"%d",&k);
        ranks[r][0]=r+1;
    }
}

int main(void) {
    char names[MAX_NAME][MAX_LEN];
    int ranks[MAX_NAME][MAX_LEN];
    int size=100;
    int col=1;
    FILE*one,*two,*three,*four,*five,*six,*seven,*eigth,*nine,*ten;
    readAllFiles(&one,&two,&three,&four,&five,&six,&seven,&eigth,&nine,&ten);
    startingTerms(names,ranks,one);
    intothearray(two,names,ranks,&col,&size);
    intothearray(three,names,ranks,&col,&size);
    intothearray(four,names,ranks,&col,&size);
    intothearray(five,names,ranks,&col,&size);
    intothearray(six,names,ranks,&col,&size);
    intothearray(seven,names,ranks,&col,&size);
    intothearray(eigth,names,ranks,&col,&size);
    intothearray(nine,names,ranks,&col,&size);
    intothearray(ten,names,ranks,&col,&size);
    sortarray( names,ranks,size);
    outfile(names,ranks, size);
    //processsinglefile(names,ranks, 0, 2010);
    
    return 0;
}

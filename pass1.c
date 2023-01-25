// to simulate pass1 of a 2 pass assembler
#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#include<string.h>

bool SYMcheck ( char label[20])
{
    FILE* f5;
    char l1[20],l2[20];
    f5=fopen("SYMTAB.txt","r");
    while(!feof(f5))
    {
         fscanf(f5,"%s%s",l1,l2);
         if(strcmp(label,l1)==0)
         {fclose(f5);
         return true;
         }

    }
    fclose(f5);
    return false;

}

void main()
{
    FILE *f1, *f2, *f3, *f4, *f5;
    int lc=0,sa=0; //lc: location_counter, sa: starting_address
    char op[20],opc[20],label[20],opT[20];
    int sadd,len,op1, pglen=0,flag=0;
    
    f1=fopen("sourcecode.txt","r");
    f2=fopen("SYMTAB.txt","w");
    f3=fopen("intermediate.txt","w");

    fscanf(f1,"%s%s%x",label,opc,&op1);

    if(strcmp(opc,"START")==0)
    {  
        sadd=op1;
        lc=sadd;
        fprintf(f3,"%x\t%s\t%s\t%x\n",lc,label,opc,op1);
    }
    else lc=0;
    while(!feof(f1))
    {
       fscanf(f1,"%s%s%s",label,opc,&op);
       fprintf(f3,"%x\t%s\t%s\t%s\n",lc,label,opc,op);
       
       if(strcmp(label,"**")!=0)
       {
          if(SYMcheck(label)==false)
          {
            fprintf(f2,"%x\t%s\n",lc,label);
          }
          else if (SYMcheck(label)==true)
          {
            exit(0);
          }
       }
       
       f4=fopen("OPTAB.txt","r");
      
       while(!feof(f4))
       {
         fscanf(f4,"%s%x",opT,&op1);
         if(strcmp(opc,opT)==0)
       {
        flag=1;
         break;
    
       }
       else flag=0;
       }
       fclose(f4);
       if(flag==1){
        lc+=3;
       }
       else if(strcmp(opc,"WORD")==0)
       {
        lc=lc+3;
       } 
       else if(strcmp(opc,"RESW")==0)
       { 
         op1=atoi(op);
         lc+= 3*op1;

       }
       else if(strcmp(opc,"BYTE")==0)
       {
        if(op[0]=='X')
        lc+=1;
        else{
            len=strlen(op)-1;
            lc+=len;
        }
       }
        else if(strcmp(opc,"RESB")==0)
        { 

          op1=atoi(op);
          lc+=op1;
        }
        else if(strcmp(opc,"END")==0)
        {
          pglen=lc-sadd;
          f5=fopen("programLen.txt","w");
         
          fprintf(f5,"%x", pglen);
          fclose(f5);
        }
    }
      fclose(f1);
      fclose(f2);
      fclose(f3);
}

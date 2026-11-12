#include<stdio.h>
#include<string.h>
#include<stdlib.h>
void header(FILE  *,FILE *);
void mstrcat(char*,char*);
typedef struct stu{
        char name[20];
        char value[20];
        struct stu *next;
}sll;
char * mystrcat(char *,char *,char *,char *);
void repmacro(FILE *,FILE *,sll *);
void comment(FILE *);
void macro(FILE *,sll **);
void prepro(FILE *,FILE *,sll **);
int main(int argc,char **argv){
        FILE *fs,*fp,*ft;
        int l=0,b=0,i;
        char ch,temp[100],file[50],result[50];
if(argc!=2){
printf("myprocessor filename\n");
return 0;
}
strcpy(file,argv[1]);
strcpy(result,file);
i=0;
while(result[i]){
if(result[i]=='.')
break;
i++;
}
result[++i]='i';

        ft=fopen(file,"r+");
        fp=fopen(result,"w");
        if(ft==0){
                printf("file not there");
                return 0;
        }
        comment(ft);
        fs=fopen("temp.c","r");
        rewind(fs);
        //fgets(temp,100,fs);
        sll *hptr;
        hptr=NULL;
        prepro(fs,fp,&hptr);


        repmacro(fs,fp,hptr);
        while((ch=fgetc(fs))!=EOF)
        {
                if(ch=='\n')
                        l++;
                b++;
        }
        fseek(fs,-b,SEEK_CUR);
        char **s;
        s=malloc(sizeof(char*)*l);
        for(i=0;i<l;i++)
                s[i]=malloc(sizeof(char)*100);
        for(i=0;i<l;i++){
                fgets(s[i],100,fs);
        }
        remove("temp.c");
}
void repmacro(FILE *fs,FILE *fp,sll *hptr){
        sll *node;
        char *s,*t,f,ch='"',*r;
        int c,i,l=0;
        s=malloc(sizeof(char)*100);
        while(fgets(s,100,fs)>0){
                node=hptr;
                l=0;
                while(node!=NULL){
                        if((t=strstr(s+l,node->name))){
                                c=0;
                                i=0;
                                while(t[i]){
                                        if(t[i++]=='"')
                                                c++;
                                }
                                if ((c%2==0))
                                        mystrcat(s,t,node->value,node->name);
                                l=l+(t-s);
                        }
                        else{
                                node=node->next;
                                l=0;
                        }
                }
                fputs(s,fp);
        }
}
char* mystrcat(char *s,char *s2,char *v,char *name){
        char t[100],*temp;
        int len;
        len=strlen(name);
        strncpy(t,s,(s2-s));
        t[s2-s]='\0';
        strcat(t,v);
        strcat(t,s+(s2-s)+len);
        strcpy(s,t);
}

void comment(FILE *fs){
        char **s,ch,ch2;
        int l=0,i,j;
        while((ch=fgetc(fs))!=EOF){
                if(ch=='\n')
                        l++;
        }
        rewind(fs);
        s=malloc(sizeof(char *)*l);
        for(i=0;i<l;i++)
                s[i]=malloc(sizeof(char)*100);
        i=0;
        j=0;
        while((ch=fgetc(fs))!=EOF){
                if(ch=='\n'){
                        s[i][j]='\n';
                        ch2=0;
                        i++;
                        j=0;
                }
                else if(ch=='/'){
                        ch2=fgetc(fs);
                        if(ch2=='/'){
                                while((ch=fgetc(fs))!=EOF)
                                        if(ch=='\n')
                                                break;
                                s[i][j]='\n';
                                i++;j=0;
                        }
                        else if(ch2=='*'){
                                while((ch=fgetc(fs))!=EOF){
                                        if(ch=='*'){
                                                if((ch2=fgetc(fs))=='/'){
                                                        s[i][j]='\n';
                                                        i++;j=0;
                                                        break;
                                                }
                                        }

                                }
                        }
                        else
                                s[i][j++]=ch2;
                }
                else
                        s[i][j++]=ch;
        }
        rewind(fs);
        fs=fopen("temp.c","w");
        for(i=0;i<l;i++)
                fprintf(fs,"%s",s[i]);
        rewind(fs);
}

void macro(FILE *fs, sll **hptr){
        char s[100],t[20];
        int l=0;
        fgets(s,100,fs);
        if(*hptr==NULL){
                sll *node;
                node=malloc(sizeof(sll));
                sscanf(s+7,"%s",node->name);
                l=strlen(node->name);
                sscanf(s+7+l+2,"%s",node->value);
                node->next=NULL;
                *hptr=node;
                return ;
        }
        else{
                sll *node,*new;
                node=*hptr;
                while(node->next!=NULL)
                        node=node->next;
                new=malloc(sizeof(sll));
                sscanf(s+7,"%s",new->name);
                l=strlen(new->name);
                sscanf(s+7+l+2,"%s",new->value);
                new->next=NULL;
                node->next=new;
                return ;
        }

}

void prepro(FILE *fs,FILE *fp,sll **hptr){
        char s[]="#include",s2[]="#define",s3[]="main",t[20];
        int len;
        while(fscanf(fs,"%s",t)>0){
                len=strlen(t);
                if(strncmp(s,t,8)==0){
                        fseek(fs,-len,SEEK_CUR);
                        header(fs,fp);
                }
                else if(strncmp(s2,t,7)==0){
                        fseek(fs,-len,SEEK_CUR);
                        macro(fs,hptr);

                }
                else if(strstr(t,s3)){
                        fputs(t,fp);
                        break;

                }
                else{
                        fputs(t,fp);
                        fputc(' ',fp);
                }
        }
}

void header(FILE *fs,FILE *fp){
        char s[20],t[]="#include",t2[]="main",h[20],path[50]="/usr/include/",h1[100];
        int len,i=0,f=0,hlen;
        FILE *fh;
        fscanf(fs,"%s",s);
        if(f==1){
                strncpy(path,path,13);
                path[13]='\0';
                f=0;
        }
        if(strncmp(t,s,8)==0){
                len=strlen(s);
                if(len==8){
                        fscanf(fs,"%s",h);
                }
                else{
                        sscanf(s+8,"%s",h);
                }
                while(h[i]){
                        h[i]=h[i+1];
                        i++;
                }
                h[i-2]=h[i-1];
                i=0;
                fh=fopen(h,"r");
                if(fh==0){
                        strcat(path,h);
                        fh=fopen(path,"r");
                        f=1;
                }
                while(fgets(h1,100,fh)!=NULL)
                        fputs(h1,fp);

        }
}

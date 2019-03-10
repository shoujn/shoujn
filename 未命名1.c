#include<stdio.h>
#include<stdlib.h>
#include<conio.h> 
#include<dos.h> 
#include<string.h>
#define LEN sizeof(struct student)
#define FORMAT "%-8d%-15s%-12d%-12d%-12d%-12d\n"
#define DATA stu[i].num,stu[i].name,stu[i].chinese,stu[i].math,stu[i].english,stu[i].ave
void in();
void out();
void sort();
void del();
void change();
void menu();
void search();
int login();

//����ṹ��//
struct student
{
	int num;
	char name[15];
	int chinese;
	int math;
	int english;
	int ave;
};
struct student stu[50];

//���˵�//
void menu()
{
	system("cls");
	printf("\n\n\n\n\n");
	printf("\t\t|---------------��ӭ�������ϵͳ---------------|\n");
	printf("\t\t|               1.¼��ѧ����Ϣ                 |\n");
	printf("\t\t|               2.��ʾѧ����Ϣ                 |\n");
	printf("\t\t|               3.ѧ����Ϣ����                 |\n");
	printf("\t\t|               4.ɾ��ѧ����Ϣ                 |\n");
	printf("\t\t|               5.�޸�ѧ����Ϣ                 |\n");
	printf("\t\t|               6.����ѧ����Ϣ                 |\n");
	printf("\t\t|               0.�˳�����ϵͳ                 |\n");
	printf("\t\t|----------------------------------------------|\n");
	printf("��ѡ����ţ�0-6��"); 
}
 
//�˺������½// 
int login()
{
	char pwd[11];
	int c;
	int i,times=3;
	while(times)
	{
		i=0;
		printf("�˺ţ��ٿ���\n");
		printf("���룺");	
		while((c=getch())!='\r')  
		{
			putch('*');
			pwd[i++]=c ;     
		}	
		pwd[i]='\0';
            if(strcmp(pwd,"123")) 
			printf("\t���벻��ȷ,����������!\n\n");	
		else
			break;
		times--;     
	}
	if(0 == times)   
	{
		printf("��������˳�����!\n");
	    exit(1);
	}
	printf("\n\n");
	printf("��½�ɹ�!\n\n");
	return 1;
}


//¼��ѧ����Ϣ//
void in()
{
	int i,m=0;
	char ch[2];
	FILE *fp;
	if((fp=fopen("data.txt","a+"))==NULL)
	{
		printf("�޷��ҵ��ļ�\n");
		return;
	}
	for(i=0;i<m;i++)
	   fwrite(&stu[i],LEN,1,fp);
	printf("�Ƿ����루y/n��:");
	scanf("\n%s",ch);
	while(strcmp(ch,"Y")==0||strcmp(ch,"y")==0)
	{
		printf("ѧ�ţ�");
		scanf("%d",&stu[m].num);
		for(i=0;i<m;i++)
		if(stu[i].num==stu[m].num)
		{
			 printf("ѧ���Ѿ����ڣ����س���������");
			 getch();
			 fclose(fp);
			 return;
		}
		printf("����:");
		scanf("%s",stu[m].name);
		printf("���ĳɼ���");
		scanf("%d",&stu[m].chinese);
		printf("��ѧ�ɼ���");
		scanf("%d",&stu[m].math);
		printf("Ӣ��ɼ���"); 
		scanf("%d",&stu[m].english);
		stu[m].ave=(stu[m].chinese+stu[m].math+stu[m].english)/3.0;
		if(fwrite(&stu[m],LEN,1,fp)!=1)
		{
			printf("���ܱ��棡��");
			getch();
		}
		else
		{
			printf("%s����ɹ�\n",stu[m].name);
			m++;
		}
		printf("��������y/n��:");
		scanf("%s",ch); 
	}
	fclose(fp);
	printf("OK!\n");
} 

//��ʾѧ����Ϣ// 
void out()
{
	FILE *fp;
	int i,m=0;
	fp=fopen("data.txt","r");
	while(!feof(fp))
	{
		if(fread(&stu[m],LEN,1,fp)==1)
		      m++;
	}
	fclose(fp); 
	printf("ѧ��   ����             ����        ��ѧ       Ӣ��        ƽ��\t\n");
	for(i=0;i<m;i++)
	{
		printf(FORMAT,DATA);
	} 
}


//����ƽ���ɼ�����//
void sort()
{
	FILE *fp;
	struct student t;
	int i=0,j=0,m=0;
	if((fp=fopen("data.txt","r"))==NULL)
	{
		printf("�޷��򿪣�\n");
		return;
	}
	while(!feof(fp))
	    if(fread(&stu[m],LEN,1,fp)==1)
	       m++;
	fclose(fp);
	if(m==0)
	{
		printf("û����Ϣ!\n");
		return;
	}
	if((fp=fopen("data.txt","w"))==NULL)
	{
		printf("�޷��򿪣�\n");
		return;
	}
	for(i=0;i<m-1;i++)
	   for(j=i+1;j<m;j++)
	if(stu[i].ave<stu[j].ave)
	{
		t=stu[i];
		stu[i]=stu[j];
		stu[j]=t;
	}
		if((fp=fopen("data.txt","w"))==NULL)
	{
		printf("�޷��򿪣�\n");
		return;
	}
	for(i=0;i<m;i++)
	if(fwrite(&stu[i],LEN,1,fp)!=1)
	{
		printf("%s�޷����棡\n");
		getch();
	}
	fclose(fp);;
	printf("����ɹ�!\n");
} 


//ɾ��ѧ����Ϣ//
void del()
{
	FILE *fp;
	int snum,i,j,m=0;
	char ch[2];
	if((fp=fopen("data.txt","r+"))==NULL)
	{
		printf("�޷��򿪣�\n");
		return;
	} 
	while(!feof(fp))
	    if(fread(&stu[m],LEN,1,fp)==1)
	        m++;
	fclose(fp);
	if(m==0)
	{
		printf("û����Ϣ��\n");
		return;
	}
	printf("������ѧ�ţ�");
	scanf("%d",&snum);
	for(i=0;i<m;i++)
	      if(snum==stu[i].num)
	          break;
	printf("�Ѿ��ҵ����Ƿ�ɾ����y/n��");
	scanf("%s",ch);
	if(strcmp(ch,"Y")==0||strcmp(ch,"y")==0)
	{
		for(j=i;j<m;j++)
		    stu[j]=stu[j+1];
		m--;
		if((fp=fopen("data.txt","w"))==NULL)
		{
			printf("�޷����ļ�\n");
			return;
		}
		    for(j=0;j<m;j++)
		if(fwrite(&stu[j],LEN,1,fp)!=1)
		{
			printf("�޷�����\n");
			getch();
		}
		printf("����ɹ���\n");	    
	}
	else
	    return;
	fclose(fp);		           
} 
 
 
 //������Ϣ//
 void search()
 {
 	FILE *fp;
 	int snum,i,m=0;
 	char ch[2];
 	if((fp=fopen("data.txt","r"))==NULL)
 	 {
	 	printf("�޷���\n");
	 	return;
     }
	 while(!feof(fp))
	     if(fread(&stu[m],LEN,1,fp)==1)
	        m++;
	 fclose(fp);
	 if(m==0)
	 {
 		printf("����Ϣ\n");
 		return;
 	 }
	 printf("������ѧ�ţ�");
	 scanf("%d",&snum);
	 for(i=0;i<m;i++)
	     if(snum==stu[i].num)      
	 {
 		printf("�ҵ�ѧ�����Ƿ����/(y/n)");
 		scanf("%s",ch);
 		if(strcmp(ch,"Y")==0||strcmp(ch,"y")==0)
 		{
 			printf("ѧ��   ����             ����     ��ѧ    Ӣ��    ƽ��\t\n");
 			printf(FORMAT,DATA);
 			break;
		 } 
 	}
	 if(i==m)
	    printf("δ�ҵ���ѧ����\n");	
 }
 
 
 
 //�޸���Ϣ//
 void change()
 {
 	FILE *fp;
 	int i,j,m=0,snum;
 	if((fp=fopen("data.txt","r+"))==NULL)
 	{
	 	printf("�޷���!\n");
	 	return;
	 }
	 while(!feof(fp))
	     if(fread(&stu[m],LEN,1,fp)==1)
	        m++;
      if(m==0)
      {
      	printf("û����Ϣ!\n");
      	fclose(fp);
      	return;
      }
      printf("����������Ҫ�޸ĵ�ѧ����ѧ�ţ�\n");
      scanf("%d",&snum);
      for(i=0;i<m;i++)
         if(snum==stu[i].num)
             break;
      printf("�Ѿ��ҵ���ѧ����\n");
	  printf("������\n");
	  scanf("%s",stu[i].name);
	  printf("\n���ģ�");
	  scanf("%d",&stu[i].chinese);
	  printf("\n��ѧ��");
	  scanf("%d",&stu[i].math);
	  printf("\nӢ�");
	  scanf("%d",&stu[i].english);
	  stu[i].ave=(stu[i].chinese+stu[i].math+stu[i].english)/3.0 ;
	  if((fp=fopen("data.txt","w"))==NULL)
	  {
  		printf("�޷���\n");
  		return;
  	  }
	  for(j=0;j<m;j++)
	  if(fwrite(&stu[j],LEN,1,fp)!=1)
	  {
  		 printf("�޷����룡\n");
  		 getch();
  	  }
	  fclose(fp);	 
 } 
 
 
 
 //������//
 main()
 {
 	int n;
 	login();
 	menu();
 	scanf("%d",&n);
 	while(n)
 	{
	 	switch(n)
	 	{
	 		case 1:
                  in();
                  break;
            case 2:
                  out();
                  break;
            case 3:
                  sort();
                  break;
            case 4:
                  del();
                  break;
            case 5:
                  change();
                  break;
            case 6:
                  search();
                  break;
            default:
                  break;
	 	}
	 	getch();
	 	menu();
	 	scanf("%d",&n);
	 }
 	
 } 
 

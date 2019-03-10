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

//定义结构体//
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

//主菜单//
void menu()
{
	system("cls");
	printf("\n\n\n\n\n");
	printf("\t\t|---------------欢迎进入管理系统---------------|\n");
	printf("\t\t|               1.录入学生信息                 |\n");
	printf("\t\t|               2.显示学生信息                 |\n");
	printf("\t\t|               3.学生信息排序                 |\n");
	printf("\t\t|               4.删除学生信息                 |\n");
	printf("\t\t|               5.修改学生信息                 |\n");
	printf("\t\t|               6.查找学生信息                 |\n");
	printf("\t\t|               0.退出管理系统                 |\n");
	printf("\t\t|----------------------------------------------|\n");
	printf("请选择序号（0-6）"); 
}
 
//账号密码登陆// 
int login()
{
	char pwd[11];
	int c;
	int i,times=3;
	while(times)
	{
		i=0;
		printf("账号：寿俊男\n");
		printf("密码：");	
		while((c=getch())!='\r')  
		{
			putch('*');
			pwd[i++]=c ;     
		}	
		pwd[i]='\0';
            if(strcmp(pwd,"123")) 
			printf("\t密码不正确,请重新输入!\n\n");	
		else
			break;
		times--;     
	}
	if(0 == times)   
	{
		printf("按任意键退出程序!\n");
	    exit(1);
	}
	printf("\n\n");
	printf("登陆成功!\n\n");
	return 1;
}


//录入学生信息//
void in()
{
	int i,m=0;
	char ch[2];
	FILE *fp;
	if((fp=fopen("data.txt","a+"))==NULL)
	{
		printf("无法找到文件\n");
		return;
	}
	for(i=0;i<m;i++)
	   fwrite(&stu[i],LEN,1,fp);
	printf("是否输入（y/n）:");
	scanf("\n%s",ch);
	while(strcmp(ch,"Y")==0||strcmp(ch,"y")==0)
	{
		printf("学号：");
		scanf("%d",&stu[m].num);
		for(i=0;i<m;i++)
		if(stu[i].num==stu[m].num)
		{
			 printf("学号已经存在，按回车继续！！");
			 getch();
			 fclose(fp);
			 return;
		}
		printf("名字:");
		scanf("%s",stu[m].name);
		printf("语文成绩：");
		scanf("%d",&stu[m].chinese);
		printf("数学成绩：");
		scanf("%d",&stu[m].math);
		printf("英语成绩："); 
		scanf("%d",&stu[m].english);
		stu[m].ave=(stu[m].chinese+stu[m].math+stu[m].english)/3.0;
		if(fwrite(&stu[m],LEN,1,fp)!=1)
		{
			printf("不能保存！！");
			getch();
		}
		else
		{
			printf("%s保存成功\n",stu[m].name);
			m++;
		}
		printf("继续？（y/n）:");
		scanf("%s",ch); 
	}
	fclose(fp);
	printf("OK!\n");
} 

//显示学生信息// 
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
	printf("学号   名字             语文        数学       英语        平均\t\n");
	for(i=0;i<m;i++)
	{
		printf(FORMAT,DATA);
	} 
}


//按照平均成绩排序//
void sort()
{
	FILE *fp;
	struct student t;
	int i=0,j=0,m=0;
	if((fp=fopen("data.txt","r"))==NULL)
	{
		printf("无法打开！\n");
		return;
	}
	while(!feof(fp))
	    if(fread(&stu[m],LEN,1,fp)==1)
	       m++;
	fclose(fp);
	if(m==0)
	{
		printf("没有信息!\n");
		return;
	}
	if((fp=fopen("data.txt","w"))==NULL)
	{
		printf("无法打开！\n");
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
		printf("无法打开！\n");
		return;
	}
	for(i=0;i<m;i++)
	if(fwrite(&stu[i],LEN,1,fp)!=1)
	{
		printf("%s无法保存！\n");
		getch();
	}
	fclose(fp);;
	printf("保存成功!\n");
} 


//删除学生信息//
void del()
{
	FILE *fp;
	int snum,i,j,m=0;
	char ch[2];
	if((fp=fopen("data.txt","r+"))==NULL)
	{
		printf("无法打开！\n");
		return;
	} 
	while(!feof(fp))
	    if(fread(&stu[m],LEN,1,fp)==1)
	        m++;
	fclose(fp);
	if(m==0)
	{
		printf("没有信息！\n");
		return;
	}
	printf("请输入学号：");
	scanf("%d",&snum);
	for(i=0;i<m;i++)
	      if(snum==stu[i].num)
	          break;
	printf("已经找到，是否删除（y/n）");
	scanf("%s",ch);
	if(strcmp(ch,"Y")==0||strcmp(ch,"y")==0)
	{
		for(j=i;j<m;j++)
		    stu[j]=stu[j+1];
		m--;
		if((fp=fopen("data.txt","w"))==NULL)
		{
			printf("无法打开文件\n");
			return;
		}
		    for(j=0;j<m;j++)
		if(fwrite(&stu[j],LEN,1,fp)!=1)
		{
			printf("无法保存\n");
			getch();
		}
		printf("保存成功！\n");	    
	}
	else
	    return;
	fclose(fp);		           
} 
 
 
 //查找信息//
 void search()
 {
 	FILE *fp;
 	int snum,i,m=0;
 	char ch[2];
 	if((fp=fopen("data.txt","r"))==NULL)
 	 {
	 	printf("无法打开\n");
	 	return;
     }
	 while(!feof(fp))
	     if(fread(&stu[m],LEN,1,fp)==1)
	        m++;
	 fclose(fp);
	 if(m==0)
	 {
 		printf("无信息\n");
 		return;
 	 }
	 printf("请输入学号：");
	 scanf("%d",&snum);
	 for(i=0;i<m;i++)
	     if(snum==stu[i].num)      
	 {
 		printf("找到学生，是否输出/(y/n)");
 		scanf("%s",ch);
 		if(strcmp(ch,"Y")==0||strcmp(ch,"y")==0)
 		{
 			printf("学号   名字             语文     数学    英语    平均\t\n");
 			printf(FORMAT,DATA);
 			break;
		 } 
 	}
	 if(i==m)
	    printf("未找到该学生！\n");	
 }
 
 
 
 //修改信息//
 void change()
 {
 	FILE *fp;
 	int i,j,m=0,snum;
 	if((fp=fopen("data.txt","r+"))==NULL)
 	{
	 	printf("无法打开!\n");
	 	return;
	 }
	 while(!feof(fp))
	     if(fread(&stu[m],LEN,1,fp)==1)
	        m++;
      if(m==0)
      {
      	printf("没有信息!\n");
      	fclose(fp);
      	return;
      }
      printf("请输入你想要修改的学生的学号！\n");
      scanf("%d",&snum);
      for(i=0;i<m;i++)
         if(snum==stu[i].num)
             break;
      printf("已经找到该学生！\n");
	  printf("姓名：\n");
	  scanf("%s",stu[i].name);
	  printf("\n语文：");
	  scanf("%d",&stu[i].chinese);
	  printf("\n数学：");
	  scanf("%d",&stu[i].math);
	  printf("\n英语：");
	  scanf("%d",&stu[i].english);
	  stu[i].ave=(stu[i].chinese+stu[i].math+stu[i].english)/3.0 ;
	  if((fp=fopen("data.txt","w"))==NULL)
	  {
  		printf("无法打开\n");
  		return;
  	  }
	  for(j=0;j<m;j++)
	  if(fwrite(&stu[j],LEN,1,fp)!=1)
	  {
  		 printf("无法存入！\n");
  		 getch();
  	  }
	  fclose(fp);	 
 } 
 
 
 
 //主程序//
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
 

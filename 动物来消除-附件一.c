#include<graphics.h>
#include<conio.h>
#include<time.h>
#include<stdio.h>
#pragma comment(lib,"Winmm.lib") 

typedef struct position  //���λ��
{
    int x;
	int y;;
}posType;
typedef struct picition  //ͼƬλ��
{
    int x;
	int y;
    int  flag;
}picType;

#define KEY_DOWN(vk_c) (GetAsyncKeyState(vk_c)&0x8000)

void drawcursor(posType,COLORREF); //�ػ���
void gameplay(void);
void getsamepicture(posType cur);  
void drawtime(int);  //�ػ�ʱ��
void drawscore(int); //�ػ����
void picruresfall(void); 
int picturFind(int x,int y); //�ж�����ͼƬ�Ƿ���ͬ
void pictureout(int m,int x,int y);//����ͼƬ
int  posFind(int x,int y);
int isValid(posType tmpPos);  //�ж��Ƿ����ͼƬ���ظ�

posType  cur; //��ǰ�������λ��
picType  allpic[180]; //��¼����ͼƬ����
posType picArr[180];  //��¼ͬɫͼƬ
int index;
void main()
{
	mciSendString("open music.mp3 alias mymusic",NULL,0,NULL);
	mciSendString("play mymusic",NULL,0,NULL);       //���ű�������
    initgraph(1000,700);
	//���Ʊ߿�
	IMAGE img;
	loadimage(&img, "E:\\backpicture\\����ͼƬ.jpg");
    putimage(0, 0, &img); 
	setlinecolor(RGB(50,50,50));
	setlinestyle(PS_SOLID | PS_JOIN_ROUND, 10);
	rectangle(253,82,745,695);
	//�������ͼƬ
	srand((unsigned) time(NULL)); 
	int m,p=0;
	for(int x=280;x<740;x+=40)
	{
		for(int y=110;y<690;y+=40)
		{
			 m=rand()%6;
			IMAGE img1;
			if(m==0)
			{
                loadimage(&img1, "E:\\user_picture\\0.jpg");
				putimage(x-20, y-20, &img1); 
				allpic[p].x=x;
				allpic[p].y=y;
				allpic[p].flag=0;
                p++;
			}
			else if(m==1)
			{
                loadimage(&img1, "E:\\user_picture\\1.jpg");
				putimage(x-20, y-20, &img1); 
				allpic[p].x=x;
				allpic[p].y=y;
				allpic[p].flag=1;
                p++;
			}
			else if(m==2)
			{
                loadimage(&img1, "E:\\user_picture\\2.jpg");
				putimage(x-20, y-20, &img1); 
				allpic[p].x=x;
				allpic[p].y=y;
				allpic[p].flag=2;
                p++;
			}
			else if(m==3)
			{
                loadimage(&img1, "E:\\user_picture\\3.jpg");
				putimage(x-20, y-20, &img1); 
				allpic[p].x=x;
				allpic[p].y=y;
				allpic[p].flag=3;
                p++;
			}
			else if(m==4)
			{
                loadimage(&img1, "E:\\user_picture\\4.jpg");
				putimage(x-20, y-20, &img1);
			    allpic[p].x=x;
				allpic[p].y=y;
				allpic[p].flag=4;
                p++;
			}
			else if(m==5)
			{
                loadimage(&img1, "E:\\user_picture\\5.jpg");
				putimage(x-20, y-20, &img1); 
			    allpic[p].x=x;
				allpic[p].y=y;
				allpic[p].flag=5;
                p++;
			}
			
		}
		
	}
	setlinestyle(PS_SOLID | PS_JOIN_ROUND, 2);
	//���ƹ��
    cur.x=480;
    cur.y=430;
	drawcursor(cur,RGB(0,200,0));
	drawscore(0);
	drawtime(30);
	gameplay();
	getch();
	closegraph();

}
void drawcursor(posType cur,COLORREF cl)
{
	setlinecolor(cl);
	rectangle(cur.x-21,cur.y-21,cur.x+19,cur.y+19);
}
void gameplay()
{
    int score=0;
    for(int i=299;i>-1;i--)
	{
		if(i%10==0)
		{
			drawtime(i/10);
		}
		if(KEY_DOWN(VK_UP)&& cur.y>130)
		{
			drawcursor(cur,RGB(209,180,140));
			cur.y-=40;
			drawcursor(cur,RGB(0,200,0));
		}
		else if(KEY_DOWN(VK_DOWN)&&cur.y<650)
		{
			drawcursor(cur,RGB(209,180,140));
			cur.y+=40;
			drawcursor(cur,RGB(0,200,0));
		}
		else if(KEY_DOWN(VK_LEFT)&&cur.x>300)
		{
			drawcursor(cur,RGB(209,180,140));
			cur.x-=40;
			drawcursor(cur,RGB(0,200,0));
		}
		else if(KEY_DOWN(VK_RIGHT)&&cur.x<700)
		{
			drawcursor(cur,RGB(209,180,140));
			cur.x+=40;
			drawcursor(cur,RGB(0,200,0));
		}
		else if(KEY_DOWN(VK_RETURN)||KEY_DOWN(VK_SPACE))
        {
             getsamepicture(cur);
			 //������ͼƬ�滻�ɷ���ɫ����ͼƬһ��ʱ��
			 if(index>1)
			 {
			    for(int k=0;k<index;k++)
				 {
					IMAGE img6;
					loadimage(&img6, "E:\\user_picture\\6.jpg");
				    putimage(picArr[k].x-20,picArr[k].y-20, &img6);
				 }
				Sleep(500);
				picruresfall();
				//ˢ�·���
				 score+=index;
				 drawscore(score);
				 //ˢ��ʱ��
                 drawtime((i/10)+(index*index)/10);
				 i=i+(index*index)*2;
			  
			 }
			 index=0;
			 
		 
		}
		Sleep(100);
	}
	//��Ϸ����
	cleardevice();
	settextcolor(RGB(255,0,0));
	settextstyle(80, 0, _T("����"));
	outtextxy(300, 330, "Game Over");
}
void getsamepicture(posType cur)
{
     picArr[index].x=cur.x;
     picArr[index].y=cur.y;
	 index++;

	 posType tmpPos;   
	 for(int k=0;k<4;k++)
	{
		 switch(k)
		{
			  case 0:tmpPos.x=cur.x;tmpPos.y=cur.y-40;break; //��
			  case 1:tmpPos.x=cur.x;tmpPos.y=cur.y+40;break; //��
			  case 2:tmpPos.x=cur.x-40;tmpPos.y=cur.y;break; //��
			  case 3:tmpPos.x=cur.x+40;tmpPos.y=cur.y;break; //��
		 }
              if(isValid(tmpPos))
			  {
			        getsamepicture(tmpPos);
			  }

	}

}
void drawtime(int sec)
{
	char str[30];
	setbkmode(TRANSPARENT);
	settextcolor(RGB(255,255,0));
	settextstyle(25, 0, _T("����"));
	sprintf(str,"ʣ��ʱ�䣺%2d s",sec); 
	setfillcolor(RGB(209,180,140));
	solidrectangle(150,50,190,75);
	outtextxy(30, 50, str);
}

void drawscore(int score)
{
	char str[30];
    setbkmode(TRANSPARENT);
	settextcolor(RGB(255,0,0));
	settextstyle(25, 0, _T("����"));
	sprintf(str,"������%d",score);
	setfillcolor(RGB(209,180,140));
	solidrectangle(95,600,180,625);
	outtextxy(30, 600, str);
}
void turn()
{
   int i,j;posType temp;
	for(j=0;j<index-1;j++)
	for(i=0;i<index-1-j;i++)
	{
		if(picArr[i].x>picArr[i+1].x)
		{
			temp=picArr[i];
			picArr[i]=picArr[i+1];
			picArr[i+1]=temp;
		}
		if(picArr[i].y>picArr[i+1].y)
		{
			temp=picArr[i];
			picArr[i]=picArr[i+1];
			picArr[i+1]=temp;
		}
	}

}
void picruresfall(void)
{
	turn();
	for(int i=0;i<index;i++)
	{
		for(int k=picArr[i].y;k>70;k-=40)
		{
			int m;
		    m=picturFind(picArr[i].x,k-40);
			pictureout(m,picArr[i].x,k);
			allpic[posFind(picArr[i].x,k)].flag=m;
		}
		int m ;
		m=rand()%6;
		pictureout(m,picArr[i].x,110);
		allpic[posFind(picArr[i].x,110)].flag=m;
	}
}
int picturFind(int x,int y)
{
   int i;
   for(i=0;i<180;i++)
   {
      while(x==allpic[i].x && y==allpic[i].y)
	  {
	     if(allpic[i].flag==0)
		 {
		    return 0;
		 }
		 else if(allpic[i].flag==1)
		 {
		    return 1;
		 }
		 else if(allpic[i].flag==2)
		 {
		    return 2;
		 }
		 else if(allpic[i].flag==3)
		 {
		    return 3;
		 }
		 else if(allpic[i].flag==4)
		 {
		    return 4;
		 }
		 else if(allpic[i].flag==5)
		 {
		    return 5;
		 }
	
		
	  }
   }
}
void pictureout(int m,int x,int y)
{
           IMAGE img1;
			if(m==0)
			{
                loadimage(&img1, "E:\\user_picture\\0.jpg");
				putimage(x-20, y-20, &img1); 
			}
			else if(m==1)
			{
                 loadimage(&img1, "E:\\user_picture\\1.jpg");
				 putimage(x-20, y-20, &img1);  
			}
			else if(m==2)
			{
                  loadimage(&img1, "E:\\user_picture\\2.jpg");
				  putimage(x-20, y-20, &img1);  
			}
			else if(m==3)
			{
                  loadimage(&img1, "E:\\user_picture\\3.jpg");
				  putimage(x-20, y-20, &img1);  
			}
			else if(m==4)
			{
                 loadimage(&img1, "E:\\user_picture\\4.jpg");
				 putimage(x-20, y-20, &img1);  
			}
			else if(m==5)
			{
                 loadimage(&img1, "E:\\user_picture\\5.jpg");
				 putimage(x-20, y-20, &img1);  
			}
}
int  posFind(int x,int y)
{
   
   int i;
   for(i=0;i<180;i++)   /*�ҵ�����Ԫ���е�����*/
   {
      while(allpic[i].x==x && allpic[i].y==y)
	  {
		  return i;
	  }
   }
}
int isValid(posType tmpPos)
{
	if(picturFind(tmpPos.x,tmpPos.y)!=picturFind(cur.x,cur.y))
	{
		return 0;
	}
	else
	{
		for(int i=0;i<index;i++)  //�ж�������֮ǰ�Ƿ��Ѵ���
		{
			if(tmpPos.x==picArr[i].x&&tmpPos.y==picArr[i].y)
			{
				return 0;
			}
		}
		return 1;
	}
}
  





#include <graphics.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <dos.h>

union REGS in,out;

void points(int &pnts)
{
	char ch[20];
	sprintf(ch,"Points = %d/10",pnts);
	outtextxy(80,4,ch);
}

void xlimits()
{
	in.x.ax = 7;
	in.x.cx = 62;
	in.x.dx = 590;
	int86(51,&in,&out);
}

void ylimits()
{
	in.x.ax = 8;
	in.x.cx = 30;
	in.x.dx = 410;
	int86(51,&in,&out);
}

void mousehide()
{
	in.x.ax = 2;
	int86(51,&in,&out);
}

void pos(int *x, int *y, int *b)
{
	in.x.ax = 3;
	int86(51,&in,&out);
	*x = out.x.cx;
	*y = out.x.dx;
	*b = out.x.bx;
}

void Mainscreen()
{
	setbkcolor(1);
	setcolor(15);
	settextstyle(GOTHIC_FONT,HORIZ_DIR,9);
	outtextxy(150,130,"SHOOT");
	settextstyle(SMALL_FONT,HORIZ_DIR,9);
	outtextxy(170,230,"Find And Shoot->");
	setcolor(RED);
	setfillstyle(SOLID_FILL,RED);
	circle(452,248,5);
	floodfill(452,248,RED);
	setcolor(15);
	settextstyle(DEFAULT_FONT,HORIZ_DIR,1);
}

void loading()
{
	outtextxy(0,470,"Do not press any key while loading");
	for(int i=0;i<=10;i++)
	{
		if(kbhit())
		{
			cleardevice();
			closegraph();
			exit(0);
		}
		Mainscreen();
		outtextxy(260,390,"Loading.");
		delay(70);
		Mainscreen();
		outtextxy(260,390,"Loading..");
		delay(70);
		Mainscreen();
		outtextxy(260,390,"Loading...");
		delay(70);
		setbkcolor(1);
		settextstyle(GOTHIC_FONT,HORIZ_DIR,9);
		outtextxy(150,130,"SHOOT");
		settextstyle(SMALL_FONT,HORIZ_DIR,9);
		outtextxy(170,230,"Find And Shoot->");
		setcolor(RED);
		setfillstyle(SOLID_FILL,RED);
		circle(452,248,5);
		floodfill(452,248,RED);
		setcolor(15);
		settextstyle(DEFAULT_FONT,HORIZ_DIR,1);
		outtextxy(0,470,"Do not press any key while loading");
		delay(70);
		cleardevice();
		outtextxy(0,470,"Do not press any key while loading");
	}
}
void mindisplay()
{
	settextstyle(DEFAULT_FONT,HORIZ_DIR,1);
	setcolor(RED);
	setfillstyle(SOLID_FILL,RED);
	circle(100,310,5);
	floodfill(100,310,RED);
	setcolor(WHITE);
	circle(230,280,10);
	line(220,280,240,280);
	line(230,270,230,290);
	line(140,310,140,375);   //Aim line
	line(110,310,140,310);   //Aim line
	outtextxy(110,307,"<");  //Aim arrow
	line(275,280,275,375);   //Shooter line
	line(245,280,275,280);   //Shooter line
	outtextxy(245,277,"<");  //Shooter Arrow
	outtextxy(130,380,"Aim");
	outtextxy(260,380,"Shooter");
}

void SHOOT_RULES()
{
	setbkcolor(1);
	rectangle(10,70,375,440);
	settextstyle(TRIPLEX_FONT,HORIZ_DIR,6);
	outtextxy(10,2,"RULES :");
	settextstyle(SANS_SERIF_FONT,HORIZ_DIR,6);
	outtextxy(420,150,"GOOD");
	outtextxy(420,190,"LUCK!");
	settextstyle(DEFAULT_FONT,HORIZ_DIR,1);
	outtextxy(30,90,"1)An object with red colour will appears");
	outtextxy(30,102,"  10 times on your screen. You have to");
	outtextxy(30,114,"  shoot it in the given time(3 seconds).");
	outtextxy(30,154,"2)Press the mouse left button to shoot the");
	outtextxy(30,166,"  object.");
	outtextxy(30,206,"3)You can exit from the game by pressing");
	outtextxy(30,218,"  any key.");
	rectangle(30,230,355,411);
	mindisplay();
	settextstyle(DEFAULT_FONT,HORIZ_DIR,1);
	outtextxy(30,418," This game will help you to improve your");
	outtextxy(30,430," reflexes form mind to hand.");
	setlinestyle(SOLID_LINE,1,1);
}

void main()
{
	int gd = DETECT, gm;
	initgraph(&gd,&gm,"C:\\TC\\BGI");
	settextstyle(DEFAULT_FONT,HORIZ_DIR,1);
	loading();
	cleardevice();
	setcolor(15);
	settextstyle(GOTHIC_FONT,HORIZ_DIR,9);
	outtextxy(150,130,"SHOOT");
	settextstyle(SMALL_FONT,HORIZ_DIR,9);
	outtextxy(170,230,"Find And Shoot->");
	setcolor(RED);
	setfillstyle(SOLID_FILL,RED);
	circle(452,248,5);
	floodfill(452,248,RED);
	setcolor(15);
	settextstyle(DEFAULT_FONT,HORIZ_DIR,1);
	outtextxy(210,390,"Press any key to continue...");
	getch();
	cleardevice();
	SHOOT_RULES();
	outtextxy(0,460,"Press any key to continue...");
	getch();
	randomize();
	char ch[20];
	int objects = 10,pnts = 0, trg = 80, tm = 0, entry = 0;
	int x, y, b, press, rx, ry;
	pos(&x,&y,&b);
	int hl1 = x-5,hl2 = x+5;
	int vl1 = y-5,vl2 = y+5;
	cleardevice();
	setbkcolor(BLUE);
	settextstyle(TRIPLEX_FONT,HORIZ_DIR,4);
	outtextxy(280,200,"GET");
	delay(800);
	cleardevice();
	outtextxy(270,200,"READY");
	delay(800);
	cleardevice();
	outtextxy(275,200,"SHOOT");
	delay(800);
	cleardevice();
	settextstyle(DEFAULT_FONT,HORIZ_DIR,1);
	in.x.ax = 1;
	int86(51,&in,&out);
	rx = random(580 - 70 + 1) + 70;
	ry = random(400 - 40 + 1) + 40;
	setcolor(RED);
	setfillstyle(SOLID_FILL,RED);
	circle(rx,ry,5);
	floodfill(rx,ry,RED);
	setcolor(WHITE);
	rectangle(50,20,600,420);
	circle(x,y,10);
	line(hl1,y,hl2,y);
	line(x,vl1,x,vl2);
	mousehide();
	xlimits();
	ylimits();
	points(pnts);
	while((!kbhit())&&(objects > 0))
	{
		setlinestyle(SOLID_LINE,1,1);
		points(pnts);
		pos(&x,&y,&b);
		hl1 = x-5;
		hl2 = x+5;
		vl1 = y-5;
		vl2 = y+5;
		pos(&x,&y,&b);
		if((rx >= hl1)&&(rx <= hl2)&&(ry >= vl1)&&(ry <= vl2)&&(b == 1))
		{
			sound(300);
			entry++;
			pnts++;
			delay(50);
			nosound();
		}
		if((entry != 0)||(tm >= 80))
		{
			sound(600);
			rx = random(580 - 70 + 1) + 70;
			ry = random(400 - 40 + 1) + 40;
			entry = 0;
			tm = 0;
			trg = 80;
			objects--;
			delay(50);
			nosound();
		}
		setcolor(WHITE);
		rectangle(50,20,600,420);
		setcolor(RED);
		setfillstyle(SOLID_FILL,RED);
		circle(rx,ry,5);
		floodfill(rx,ry,RED);
		setcolor(WHITE);
		circle(x,y,10);
		line(hl1,y,hl2,y);
		line(x,vl1,x,vl2);
		rectangle(489,3,571,13);
		bar(490,4,490+tm,12);
		outtextxy(340,4,"Time remaining ==>");
		delay(20);
		tm++;
		trg--;
		cleardevice();
		setcolor(WHITE);
		rectangle(50,20,600,420);
		setcolor(RED);
		setfillstyle(SOLID_FILL,RED);
		circle(rx,ry,5);
		floodfill(rx,ry,RED);
		setcolor(WHITE);
		circle(x,y,10);
		line(hl1,y,hl2,y);
		line(x,vl1,x,vl2);
		rectangle(489,3,571,13);
		bar(490,4,490+tm,12);
		outtextxy(340,4,"Time remaining ==>");
	}
	objects = 0;
	cleardevice();
	if(objects <= 0)
	{
		settextstyle(TRIPLEX_FONT,HORIZ_DIR,9);
		outtextxy(30,70,"GAME  OVER");
		settextstyle(TRIPLEX_FONT,HORIZ_DIR,7);
		sprintf(ch,"Points : %d/10",pnts);
		outtextxy(100,300,ch);
		for(int i = 100; i <= 1000; i+= 100)
		{
			sound(i);
			delay(300);
			nosound();
		}
	}
	cleardevice();
	settextstyle(GOTHIC_FONT,HORIZ_DIR,7);
	outtextxy(10,10,"Made by :");
	settextstyle(TRIPLEX_FONT,HORIZ_DIR,9);
	outtextxy(10,150,"Anirudh");
	outtextxy(300,250,"Verma");
	settextstyle(DEFAULT_FONT, HORIZ_DIR,2);
	outtextxy(0,440," Press any key to exit.");
	getch();
	cleardevice();
}
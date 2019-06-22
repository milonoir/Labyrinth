/* Labyrinth ver:1.0 SE */
/*  by: Dogtagman 2001  */
/*  start: 24th MARCH   */
/*    end:  6th APRIL   */

/* changez on 13th AUGUST */

#include <graphics.h>
#include <string.h>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <dos.h>
#include <math.h>
#include <window.h>
#include "labs.h"
#include "pals.h"
#include "draws.h"
#include "logo.h"

#define	CLRBIGWINDOW			setcolor(0);setfillstyle(1,0);bar(247,140,388,245);
#define	CLRSMALLWINDOW			setcolor(0);setfillstyle(1,0);bar(31,368,604,443);
#define	CLRBUFF					while(kbhit()) getch();
#define	GRPATH					"drivers\\"
#define	SCOREFILE				"scores.dat"
#define	EASY						2
#define	MEDIUM					1
#define	HARD						0
#define	NORTH						0
#define	EAST						1
#define	SOUTH						2
#define	WEST						3
#define	UP							72
#define	DOWN						80
#define	LEFT						75
#define	RIGHT						77

void LoadScreen(int x1, int y1, int x2, char fname[]);
void show_map(int size, int px, int py);
void about(void);
void diff_select(void);
void draw_maze(int x, int y, int face);
void score(int level);
void show_hiscore(void);
void clr_hiscore(void);
void quit(void);
void checksys(void);
int submenu(void);
int main_menu(void);
int new_game(int level);

int	a,q,s,p;
int	game_difficulty,steps,helps,total_score;

struct	scores {
						char	player[25];
						char	level[10];
						int	score;
					 };
struct	scores hi[10];

void main(void)
{
	int	gd=DETECT,gm;

	checksys();

	initgraph(&gd,&gm,GRPATH);
	logo_anim();CLRBUFF
	/* main-menu */

	while(1)
	{
		getpalette(&pal);darkness();
		settextstyle(DEFAULT_FONT,0,1);setcolor(6);outtextxy(280,470,"Loading...");
		setactivepage(1);LoadScreen(144,47,494,"mazehelp.dat");
		setactivepage(0);LoadScreen(0,0,640,"labtitle.dat");
		setvisualpage(0);
		defpalette();getch();
		main_menu();
	}
}

void checksys(void)
{
	int	chk;
	FILE	*ch;

	window(1,1,80,25);textcolor(LIGHTGRAY);textbackground(BLACK);clrscr();
	textbackground(RED);textcolor(YELLOW);gotoxy(1,1);clreol();
	CENTER("Labyrinth v1.0 SE");
	textcolor(LIGHTGRAY);textbackground(BLACK);
	gotoxy(1,3);cprintf("Checking the files of Labyrinth...");
	gotoxy(4,4);cprintf("\"LABTITLE.DAT\"");
	gotoxy(4,5);cprintf("\"MAZEHELP.DAT\"");
	gotoxy(4,6);cprintf("\"GMSCREEN.DAT\"");
	gotoxy(4,8);cprintf("\"SCORES.DAT\"");

	chk=0;
	ch=fopen("labtitle.dat","r");
	if (ch==NULL)
	{
		chk++;gotoxy(20,4);cprintf("Missing!!");
	}
	else
	{
		fclose(ch);
		gotoxy(20,4);cprintf("OK!");
	}
	ch=fopen("mazehelp.dat","r");
	if (ch==NULL)
	{
		chk++;gotoxy(20,5);cprintf("Missing!!");
	}
	else
	{
		fclose(ch);
		gotoxy(20,5);cprintf("OK!");
	}
	ch=fopen("gmscreen.dat","r");
	if (ch==NULL)
	{
		chk++;gotoxy(20,6);cprintf("Missing!!");
	}
	else
	{
		fclose(ch);
		gotoxy(20,6);cprintf("OK!");
	}

	ch=fopen("scores.dat","r");
	if (ch==NULL)
	{
		gotoxy(20,8);cprintf("Creating...done!");clr_hiscore();
	}
	else
	{
		fclose(ch);
		gotoxy(20,8);cprintf("OK!");
	}

	if (chk!=0)
	{
		gotoxy(1,10);cprintf("Some of the important files are missing! You can't play with Labyrinth!");
		gotoxy(1,11);cprintf("SORRY! Try to get another copy!");
		exit(-1);
	}
	else
	{
		gotoxy(1,10);cprintf("Checking files succesfully! All files OK! Running Labyrinth...");
		delay(1000);
	}
}

void show_map(int size, int px, int py)
{
	long	ims;
	short int	*s1;
	int color,x,y,posx,posy;

	ims=imagesize(160,80,480,400);
	s1=(short int*)malloc(ims);
	getimage(160,80,480,400,s1);
	if (size==2)
	{
		x=15;y=15;posx=270;posy=180;
	}
	else if (size==1)
	{
		x=31;y=31;posx=230;posy=160;
	}
	else if (size==0)
	{
		x=63;y=63;posx=160;posy=80;
	}

	for (i=1;i<=y;i++)
	{
		for (j=1;j<=x;j++)
		{
			if ((j==px)&&(i==py))
			{
				color=4;
			}
			else if ((j==x-1)&&(i==y-1))
			{
				color=13;
			}
			else if (map[j][i]==0)
			{
				color=0;
			}
			else if (map[j][i]==1)
			{
				color=14;
			}
			setfillstyle(1,color);bar(posx+5*j,posy+5*i,posx+5+5*j,posy+5+5*i);
		}
	}
	getch();
	putimage(160,80,s1,COPY_PUT);free(s1);
}

void LoadScreen(int x1, int y1, int x2, char fname[])
{
	int	a,x,y,lng,col;
	FILE	*img;

	img=fopen(fname,"rb");

	x=x1;y=y1;lng=1;col=0;
	while(lng!=0)
	{
		fread(&lng,1,1,img);fread(&col,1,1,img);
		if (lng==0)
		{
			break;
		}
		for(a=1;a<=lng;a++)
		{
			if (x==x2+1)
			{
				x=x1,y++;
			}
			putpixel(x,y,col);
			x++;
		}
	}
	fclose(img);
}

int main_menu(void)
{
	char	menu[4][15] = { "Start game",
								 "Hi-scores",
								 "About",
								 "Exit game" };
	long	ptc;
	short int *p1;

	ptc=imagesize(150,120,490,350);
	p1=(short int*)malloc(ptc);
	getimage(150,120,490,350,p1);

	setcolor(0);rectangle(150,120,490,350);
	for (i=152;i<=490;i=i+2)
	{
		for (j=122;j<=350;j=j+2)
		{
			line(i-2,j-2,i,j);
		}
	}
	settextstyle(installuserfont("TSCR"),0,6);
	setcolor(BLACK);
	for (i=0;i<4;i++)
	{
		outtextxy(160,125+50*i,menu[i]);outtextxy(161,125+50*i,menu[i]);
	}

	while(1)
	{
		a=0;s=0;q=0;p=1;
		while (q==0)
		{
			setcolor(BLACK);
			outtextxy(160,125+50*p,menu[p]);outtextxy(161,125+50*p,menu[p]);
			setcolor(YELLOW);
			outtextxy(160,125+50*s,menu[s]);outtextxy(161,125+50*s,menu[s]);
			a=getch();
			if (a==13)
			{
				setcolor(BLACK);
				outtextxy(160,125+50*s,menu[s]);outtextxy(161,125+50*s,menu[s]);
				q=1;break;
			}
			else if (a==UP)
			{
				if (s==0)
				{
					continue;
				}
				else
					p=s;s--;continue;
			}
			else if (a==DOWN)
			{
				if (s==3)
				{
					continue;
				}
				else
					p=s;s++;continue;
			}
			else
				continue;
		}
		/* options */
		CLRBUFF
		if (s==0)
		{
			putimage(150,120,p1,COPY_PUT);free(p1);
			diff_select();break;
		}
		else if (s==1)
		{
			putimage(150,120,p1,COPY_PUT);free(p1);darkness();delay(100);
			show_hiscore();break;
		}
		else if (s==2)
		{
			about();
		}
		else if (s==3)
		{
			putimage(150,120,p1,COPY_PUT);free(p1);
			quit();
		}
		else
			continue;
	}
}

void quit(void)
{
	for (i=0;i<=40;i++)
	{
		line(i, 0, i, 480); line(i+20, 0, i+20, 480); line(i+40, 0, i+40, 480);
		line(i+60, 0, i+60, 480); line(i+80, 0, i+80, 480); line(i+100, 0, i+100, 480);
		line(i+120, 0, i+120, 480); line(i+140, 0, i+140, 480); line(i+160, 0, i+160, 480);
		line(i+180, 0, i+180, 480); line(i+200, 0, i+200, 480); line(i+220, 0, i+220, 480);
		line(i+240, 0, i+240, 480); line(i+260, 0, i+260, 480); line(i+280, 0, i+280, 480);
		line(i+300, 0, i+300, 480); line(i+320, 0, i+320, 480); line(i+340, 0, i+340, 480);
		line(i+360, 0, i+360, 480); line(i+380, 0, i+380, 480); line(i+400, 0, i+400, 480);
		line(i+420, 0, i+420, 480); line(i+440, 0, i+440, 480); line(i+460, 0, i+460, 480);
		line(i+480, 0, i+480, 480); line(i+500, 0, i+500, 480); line(i+520, 0, i+520, 480);
		line(i+540, 0, i+540, 480); line(i+560, 0, i+560, 480); line(i+580, 0, i+580, 480);
		line(i+600, 0, i+600, 480); line(i+620, 0, i+620, 480); delay(10);
	}
	closegraph();
	printf("\n");
	printf("Labyrinth(TM) SE, by: Dogtagman\n");
	printf("Cathedral Entertainment, 1996-2001.\n");
	exit(-1);
}

void about(void)
{
	long	is;
	short int	*s1,*hl;

	is=imagesize(144,97,494,383);
	s1=(short int*)malloc(is);
	getimage(144,97,494,383,s1);

	setactivepage(1);
	is=imagesize(144,47,494,333);
	hl=(short int*)malloc(is);
	getimage(144,47,494,333,hl);
	setactivepage(0);
	putimage(144,97,hl,COPY_PUT);
	getch();
	putimage(144,97,s1,COPY_PUT);
	free(s1);free(hl);
	CLRBUFF
}

void diff_select(void)
{
	char	level[3][10] = { "Hard",
								  "Medium",
								  "Easy" };
	long	is;
	short int *s1;

	is=imagesize(150,120,490,350);
	s1=(short int*)malloc(is);
	getimage(150,120,490,350,s1);

	setcolor(0);rectangle(150,120,490,350);
	for (i=152;i<=490;i=i+2)
	{
		for (j=122;j<=350;j=j+2)
		{
			line(i-2,j-2,i,j);
		}
	}
	setcolor(WHITE);settextstyle(installuserfont("TRIP"),0,4);
	outtextxy(200,125,"Select difficulty");

	settextstyle(installuserfont("TSCR"),0,6);
	setcolor(BLACK);
	for (i=0;i<3;i++)
	{
		outtextxy(160,165+50*i,level[i]);outtextxy(161,165+50*i,level[i]);
	}

	a=0;game_difficulty=0;q=0;p=1;
	while (q==0)
	{
		setcolor(BLACK);
		outtextxy(160,165+50*p,level[p]);outtextxy(161,165+50*p,level[p]);
		setcolor(YELLOW);
		outtextxy(160,165+50*game_difficulty,level[game_difficulty]);
		outtextxy(161,165+50*game_difficulty,level[game_difficulty]);
		a=getch();
		if (a==13)
		{
			setcolor(BLACK);
			outtextxy(160,165+50*game_difficulty,level[game_difficulty]);
			outtextxy(161,165+50*game_difficulty,level[game_difficulty]);
			q=1;break;
		}
		else if (a==UP)
		{
			if (game_difficulty==0)
			{
				continue;
			}
			else
				p=game_difficulty;game_difficulty--;continue;
		}
		else if (a==DOWN)
		{
			if (game_difficulty==2)
			{
				continue;
			}
			else
				p=game_difficulty;game_difficulty++;continue;
		}
		else
			continue;
	}
	putimage(150,120,s1,COPY_PUT);free(s1);
	new_game(game_difficulty);
}

int new_game(int level)
{
	int	xpoz,ypoz,dir;
	int	sta;

	getpalette(&pal);darkness();LoadScreen(0,0,640,"gmscreen.dat");
	defpalette();

	setactivepage(0);setvisualpage(0);
	map_gen(level);
	xpoz=2;ypoz=2;dir=SOUTH;					// starting pozition: left-top corner facing to downwards
	draw_maze(xpoz,ypoz,dir);show_map(level,xpoz,ypoz);
	q=0;a=0;
	while(q==0)
	{
		if ((level==EASY)&&(xpoz==14)&&(ypoz==14))
		{
			score(EASY);q=1;break;
		}
		if ((level==MEDIUM)&&(xpoz==30)&&(ypoz==30))
		{
			score(MEDIUM);q=1;break;
		}
		if ((level==HARD)&&(xpoz==62)&&(ypoz==62))
		{
			score(HARD);q=1;break;
		}
		a=getch();
		if (a==UP)
		{
			if (dir==NORTH)
			{
				if (map[xpoz][ypoz-1]==0)
				{
					ypoz--;steps++;draw_maze(xpoz,ypoz,dir);continue;
				}
				else
					continue;
			}
			else if (dir==SOUTH)
			{
				if (map[xpoz][ypoz+1]==0)
				{
					ypoz++;steps++;draw_maze(xpoz,ypoz,dir);continue;
				}
				else
					continue;
			}
			else if (dir==EAST)
			{
				if (map[xpoz+1][ypoz]==0)
				{
					xpoz++;steps++;draw_maze(xpoz,ypoz,dir);continue;
				}
				else
					continue;
			}
			else if (dir==WEST)
			{
				if (map[xpoz-1][ypoz]==0)
				{
					xpoz--;steps++;draw_maze(xpoz,ypoz,dir);continue;
				}
				else
					continue;
			}
		}
		else if (a==LEFT)
		{
			if (dir==NORTH)
			{
				dir=WEST;draw_maze(xpoz,ypoz,dir);continue;
			}
			else
				dir--;draw_maze(xpoz,ypoz,dir);continue;
		}
		else if (a==RIGHT)
		{
			if (dir==WEST)
			{
				dir=NORTH;draw_maze(xpoz,ypoz,dir);continue;
			}
			else
				dir++;draw_maze(xpoz,ypoz,dir);continue;
		}
		else if ((a==63)||(a==9))				// "?" or [TAB] - show_map
		{
			helps++;show_map(level,xpoz,ypoz);continue;
		}
		else if (a==27)							// [ESC] - exit or continue
		{
			sta=submenu();
			if (sta==0)
			{
				q=0;continue;
			}
			else if (sta==1)
			{
				q=1;break;
			}
		}
		else
			continue;
	}
}

int submenu(void)
{
	char	smenu[2][12] = { "Continue",
								  "Abort game" };
	long	ss;
	short int *sp;

	ss=imagesize(150,170,490,300);
	sp=(short int*)malloc(ss);
	getimage(150,170,490,300,sp);

	setcolor(0);rectangle(150,170,490,300);
	for (i=152;i<=490;i=i+2)
	{
		for (j=172;j<=300;j=j+2)
		{
			line(i-2,j-2,i,j);
		}
	}
	settextstyle(installuserfont("TSCR"),0,6);
	setcolor(BLACK);
	for (i=0;i<2;i++)
	{
		outtextxy(160,175+50*i,smenu[i]);outtextxy(161,175+50*i,smenu[i]);
	}

	a=0;s=0;q=0;p=1;
	while (q==0)
	{
		setcolor(BLACK);
		outtextxy(160,175+50*p,smenu[p]);outtextxy(161,175+50*p,smenu[p]);
		setcolor(YELLOW);
		outtextxy(160,175+50*s,smenu[s]);outtextxy(161,175+50*s,smenu[s]);
		a=getch();
		if (a==13)
		{
			setcolor(BLACK);
			outtextxy(160,175+50*s,smenu[s]);outtextxy(161,175+50*s,smenu[s]);
			q=1;break;
		}
		else if ((a==UP)||(a==DOWN))
		{
			if (s==0)
			{
				p=s;s=1;continue;
			}
			else if (s==1)
			{
				p=s;s=0;continue;
			}
		}
		else
			continue;
	}

	putimage(150,170,sp,COPY_PUT);free(sp);
	return s;
}

void draw_maze(int x, int y, int face)
{
	long	img;
	short int *i1,*i2;
	int	color,color2;
	char	facing[10];

	setvisualpage(0);setactivepage(1);
	CLRBIGWINDOW
	/* ceiling */
	setcolor(BLACK);setfillstyle(9,RED);
	bar(31,31,604,140);
	/* draw the floor */
	if ((face==NORTH)||(face==SOUTH))
	{
		if (y%2==0)
		{
			color=LIGHTGRAY;color2=DARKGRAY;
		}
		else if (y%2!=0)
		{
			color=DARKGRAY;color2=LIGHTGRAY;
		}
	}
	else if ((face==EAST)||(face==WEST))
	{
		if (x%2==0)
		{
			color=LIGHTGRAY;color2=DARKGRAY;
		}
		else if (x%2!=0)
		{
			color=DARKGRAY;color2=LIGHTGRAY;
		}
	}
	setcolor(color);setfillstyle(1,color);
	fillpoly(4,floor1);fillpoly(4,floor3);
	fillpoly(4,lfloor2);fillpoly(4,rfloor2);
	setcolor(color2);setfillstyle(1,color2);
	fillpoly(4,floor2);
	fillpoly(3,lfloor1);fillpoly(3,rfloor1);
	fillpoly(4,lfloor3);fillpoly(4,rfloor3);
	/* walls */
	setcolor(BLUE);setfillstyle(1,LIGHTBLUE);
	if (face==NORTH)
	{
		strcpy(facing, "NORTH");
		if (map[x-1][y-3]==1)
		{
			fillpoly(4,wall3l);
		}
		if (map[x][y-3]==1)
		{
			fillpoly(4,wall3);
		}
		if (map[x+1][y-3]==1)
		{
			fillpoly(4,wall3r);
		}
		if (map[x-1][y-2]==1)
		{
			fillpoly(4,lwall3);fillpoly(4,wall2l);
		}
		if (map[x+1][y-2]==1)
		{
			fillpoly(4,rwall3);fillpoly(4,wall2r);
		}
		if (map[x-1][y-1]==1)
		{
			fillpoly(4,lwall2);fillpoly(4,wall1l);
		}
		if (map[x+1][y-1]==1)
		{
			fillpoly(4,rwall2);fillpoly(4,wall1r);
		}
		if (map[x-1][y]==1)
		{
			fillpoly(4,lwall1);
		}
		if (map[x+1][y]==1)
		{
			fillpoly(4,rwall1);
		}
		if (map[x][y-2]==1)
		{
			fillpoly(4,wall2);
		}
		if (map[x][y-1]==1)
		{
			fillpoly(4,wall1);
		}
	}
	else if (face==SOUTH)
	{
		strcpy(facing, "SOUTH");
		if (map[x+1][y+3]==1)
		{
			fillpoly(4,wall3l);
		}
		if (map[x][y+3]==1)
		{
			fillpoly(4,wall3);
		}
		if (map[x-1][y+3]==1)
		{
			fillpoly(4,wall3r);
		}
		if (map[x+1][y+2]==1)
		{
			fillpoly(4,lwall3);fillpoly(4,wall2l);
		}
		if (map[x-1][y+2]==1)
		{
			fillpoly(4,rwall3);fillpoly(4,wall2r);
		}
		if (map[x+1][y+1]==1)
		{
			fillpoly(4,lwall2);fillpoly(4,wall1l);
		}
		if (map[x-1][y+1]==1)
		{
			fillpoly(4,rwall2);fillpoly(4,wall1r);
		}
		if (map[x+1][y]==1)
		{
			fillpoly(4,lwall1);
		}
		if (map[x-1][y]==1)
		{
			fillpoly(4,rwall1);
		}
		if (map[x][y+2]==1)
		{
			fillpoly(4,wall2);
		}
		if (map[x][y+1]==1)
		{
			fillpoly(4,wall1);
		}
	}
	else if (face==WEST)
	{
		strcpy(facing, "WEST");
		if (map[x-3][y+1]==1)
		{
			fillpoly(4,wall3l);
		}
		if (map[x-3][y]==1)
		{
			fillpoly(4,wall3);
		}
		if (map[x-3][y-1]==1)
		{
			fillpoly(4,wall3r);
		}
		if (map[x-2][y+1]==1)
		{
			fillpoly(4,lwall3);fillpoly(4,wall2l);
		}
		if (map[x-2][y-1]==1)
		{
			fillpoly(4,rwall3);fillpoly(4,wall2r);
		}
		if (map[x-1][y+1]==1)
		{
			fillpoly(4,lwall2);fillpoly(4,wall1l);
		}
		if (map[x-1][y-1]==1)
		{
			fillpoly(4,rwall2);fillpoly(4,wall1r);
		}
		if (map[x][y+1]==1)
		{
			fillpoly(4,lwall1);
		}
		if (map[x][y-1]==1)
		{
			fillpoly(4,rwall1);
		}
		if (map[x-2][y]==1)
		{
			fillpoly(4,wall2);
		}
		if (map[x-1][y]==1)
		{
			fillpoly(4,wall1);
		}
	}
	else if (face==EAST)
	{
		strcpy(facing, "EAST");
		if (map[x+3][y-1]==1)
		{
			fillpoly(4,wall3l);
		}
		if (map[x+3][y]==1)
		{
			fillpoly(4,wall3);
		}
		if (map[x+3][y+1]==1)
		{
			fillpoly(4,wall3r);
		}
		if (map[x+2][y-1]==1)
		{
			fillpoly(4,lwall3);fillpoly(4,wall2l);
		}
		if (map[x+2][y+1]==1)
		{
			fillpoly(4,rwall3);fillpoly(4,wall2r);
		}
		if (map[x+1][y-1]==1)
		{
			fillpoly(4,lwall2);fillpoly(4,wall1l);
		}
		if (map[x+1][y+1]==1)
		{
			fillpoly(4,rwall2);fillpoly(4,wall1r);
		}
		if (map[x][y-1]==1)
		{
			fillpoly(4,lwall1);
		}
		if (map[x][y+1]==1)
		{
			fillpoly(4,rwall1);
		}
		if (map[x+2][y]==1)
		{
			fillpoly(4,wall2);
		}
		if (map[x+1][y]==1)
		{
			fillpoly(4,wall1);
		}
	}
	img=imagesize(31,30,604,329);
	i1=(short int*)malloc(img);
	getimage(31,30,604,250,i1);
	img=imagesize(31,250,604,329);
	i2=(short int*)malloc(img);
	getimage(31,250,604,329,i2);
	setactivepage(0);setvisualpage(0);
	putimage(31,30,i1,COPY_PUT);putimage(31,250,i2,COPY_PUT);
	free(i1);free(i2);
	CLRSMALLWINDOW
	setcolor(WHITE);settextstyle(DEFAULT_FONT,0,1);
	outtextxy(33,370,"Direction: ");outtextxy(120,370,facing);
}

void score(int level)
{
	int	basic_score, hlp, st;
	int	x, y;
	int	score1, score2;
	char	player[25], k[1], sco[10],lvl[10];
	FILE	*hs;

	for (s=0; s<=30; s++)
	{  player[s]=0;	}
	k[0]=0;k[1]=0;

	if (level==EASY)
	{
		basic_score=1000;hlp=200;st=5;strcpy(lvl,"EASY");
	}
	else if (level==MEDIUM)
	{
		basic_score=4000;hlp=50;st=2;strcpy(lvl,"MEDIUM");
	}
	else if (level==HARD)
	{
		basic_score=10000;hlp=10;st=1;strcpy(lvl,"HARD");
	}
	total_score = basic_score - (st*steps + hlp*helps);
	if (total_score<0) total_score=0;
	itoa(total_score,sco,10);

	CLRSMALLWINDOW
	setcolor(WHITE);settextstyle(DEFAULT_FONT,0,1);
	outtextxy(33,370,"Congratulations! You have found the way to go out of the maze!");
	setcolor(BLACK);rectangle(200,200,440,300);
	setfillstyle(1,LIGHTGRAY);bar(201,201,439,299);rectangle(202,202,438,298);
	setfillstyle(1,YELLOW);bar(232,280,409,290);rectangle(231,279,410,291);
	outtextxy(280,210,"GAME OVER!");
	outtextxy(210,230,"Game difficulty: ");outtextxy(360,230,lvl);
	outtextxy(210,245,"     Your score: ");outtextxy(360,245,sco);
	outtextxy(260,268,"Enter your name");
	q=0;a=0;s=0;x=233;y=282;
	while(q==0)
	{
		setcolor(BLACK);outtextxy(x,y,"\xdb");
		a=getch();
		if ((a==13)&&(s==0))
		{
			setcolor(YELLOW);outtextxy(x, y, "\xdb");
			setcolor(BLACK);outtextxy(x, y, "-");player[0]=45;break;
		}
		if ((a==13)&&(s>0))
		{
			setcolor(YELLOW);outtextxy(x, y, "\xdb");q=1;break;
		}
		else if (a==27) continue;
		else if ((a==8)&&(s==0)) continue;
		else if ((a==8)&&(s>0))
		{
			setcolor(YELLOW);outtextxy(x, y, "\xdb");
			x=x-7;s--;k[0]=player[s];player[s]=0;
			outtextxy(x, y, k);
		}
		else if (s!=24)
		{
			setcolor(YELLOW);outtextxy(x, y, "\xdb");
			k[0]=a;player[s]=a;
			setcolor(BLACK);outtextxy(x, y, k);x=x+7;s++;
		}
		else continue;
	}

	hs=fopen(SCOREFILE,"rb");
	fread(&hi,sizeof(hi),1,hs);
	fclose(hs);
	if (total_score>hi[9].score)
	{
		strcpy(hi[9].player, player);
		strcpy(hi[9].level, lvl);
		hi[9].score=total_score;
		for (x=0;x<10-1;x++)
		{
			for (y=x+1;y<10;y++)
			{
				if (hi[y].score>hi[x].score)
				{
					// step 1
					strcpy(player, hi[x].player);
					strcpy(lvl, hi[x].level);
					score1=hi[x].score;
					// step 2
					strcpy(hi[x].player, hi[y].player);
					strcpy(hi[x].level, hi[y].level);
					hi[x].score=hi[y].score;
					// step 3
					strcpy(hi[y].player, player);
					strcpy(hi[y].level, lvl);
					hi[y].score=score1;
				}
			}
		}
		hs=fopen(SCOREFILE,"w+b");
		fwrite(&hi,sizeof(hi),1,hs);
		fclose(hs);
	}
	darkness();delay(100);show_hiscore();
}

void show_hiscore(void)
{
	char	str[10];
	FILE	*hs;

	setfillstyle(1,BLUE);bar(0,0,640,480);
	setcolor(YELLOW);settextstyle(installuserfont("LCOM"),0,2);
	for (i=0;i<13;i++)
	{
		for (j=0;j<5;j++)
		{
			outtextxy(4+j*160,10+i*60,"Hall of Fame");
		}
	}
	setcolor(BLACK);rectangle(80,100,560,380);
	for (i=82;i<=560;i=i+2)
	{
		for (j=102;j<=380;j=j+2)
		{
			line(i-2,j-2,i,j);
		}
	}
	setcolor(WHITE);settextstyle(installuserfont("TRIP"),0,4);
	outtextxy(160,110,"Top-10 Leaderboard");
	hs=fopen(SCOREFILE,"rb");
	fread(&hi,sizeof(hi),1,hs);
	fclose(hs);
	settextstyle(DEFAULT_FONT,0,1);
	for (i=0;i<10;i++)
	{
		outtextxy(90,170+i*20,hi[i].player);
		outtextxy(340,170+i*20,hi[i].level);
		itoa(hi[i].score,str,10);
		outtextxy(500,170+i*20,str);
	}
	defpalette();
	a=0;q=0;
	while (q==0)
	{
		a=getch();
		if (a==83)					// "DEL" button
		{
			clr_hiscore();q=1;break;
		}
		else if ((a==32)||(a==13))
		{
			q=1;break;
		}
		else
			continue;
	}
}

void clr_hiscore(void)
{
	FILE *hs;

	for (i=0;i<10;i++)
	{
		strcpy(hi[i].player, "------------------------");
		strcpy(hi[i].level, "------");
		hi[i].score=0;
	}

	hs=fopen("scores.dat","w+b");
	fwrite(&hi,sizeof(hi),1,hs);
	fclose(hs);
}
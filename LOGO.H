/*        Name: Cathedral Entertainment's logo */
/*      Author: Mr.M.                          */
/* Last modify: 31 December 2000               */

void logo_anim(void)
{
	int	x,y;
	char	a;
	long	ims;
	short int	*pic;

	delay(1000);							// Wait till monitor's refreshed
	cleardevice();
	setrgbpalette(MAGENTA,0,0,0);
	setfillstyle(1,MAGENTA);bar(0,50,640,430);
	for (x=0;x<=63;x++)
	{
		setrgbpalette(MAGENTA,x,x,x);delay(5);
	}
	setcolor(0);
	/* icon of the logo */
	y=0;x=0;
	while (y!=60)
	{
		line(190,190,190,190+y);	   // Line to down   from top/left
		line(230,250,230,250-y);      // Line to up     from bottom/right
		if (y<=40)
		{
			line(190,250,190+x,250);	// Line to right  from bottom/left
			line(230,190,230-x,190);   // Line to left   from top/right
			x++;y++;delay(10);
		}
		else
			y++;delay(5);
	}
	line(190,250,215,230);line(215,230,230,250);		// roof
	line(210,234,210,185);line(190,225,230,200);		// cross
	rectangle(230,190,233,250);							// border

	/* text of the logo */
	setactivepage(1);setvisualpage(0);
	setfillstyle(1,MAGENTA);bar(245,190,430,250);
	settextstyle(installuserfont("TRIP"),0,4);
	outtextxy(250,190,"CATHEDRAL");
	settextstyle(installuserfont("LCOM"),0,1);
	outtextxy(255,220,"ENTERTAINMENT");
	for (x=1;x<=185;x++)
	{
		setactivepage(1);
		ims=imagesize(430,190,430-x,250);
		pic=(short int*)malloc(ims);
		getimage(430,190,430-x,250,pic);
		setactivepage(0);
		putimage(245,190,pic,COPY_PUT);free(pic);
		delay(1);
	}
	delay(2000);
	for (x=63;x>=0;x--)
	{
		setrgbpalette(MAGENTA,x,x,x);delay(5);
	}
	setactivepage(0);setvisualpage(0);
}
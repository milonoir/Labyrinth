/* labyrinth generator functions */
/* easy (16x16)                  */
/* medium (32x32)                */
/* hard (64x64)                  */

int	map[64][64];
int	hv[64],hf[64];
int	mv[32],mf[32];
int	ev[16],ef[16];
int	i,j,k;

double round(double num)
{
	double	fraction, integer;
	fraction = modf(num, &integer);
	if (fraction>=0.5)
	{
		num=ceil(num);
	}
	else if (fraction<0.5)
	{
		num=floor(num);
	}
	return num;
}

int map_gen(int size)
{
	int	xf,yf,x,y;
	int	ir,n,a,b;

	if (size==2)			// easy
	{
		x=15;y=15;
	}
	else if (size==1)		// medium
	{
		x=31;y=31;
	}
	else if (size==0)		// hard
	{
		x=63;y=63;
	}
	randomize();
	ir=0;
	xf=round((x-3)/2);
	yf=round((y-3)/2);

	/* Initializing */
	for (i=1;i<=yf;i++)
		hf[i]=0;
	for (i=1;i<=xf;i++)
		hv[i]=0;
	for (i=1;i<=y;i++)
	{
		for (j=1;j<=x;j++)
		{
			map[i][j]=0;
		}
	}

	/* The border of the lab. */
	for (i=1;i<=y;i++)
	{
		map[i][1]=1;
		map[i][x]=1;
	}
	for (i=2;i<=x;i++)
	{
		map[1][i]=1;
		map[y][i]=1;
	}

	/* Main generating cycle */
	a=0;b=0;
	do
	{
		ir++;
		ir=ir & 3;
		if (ir<2)					// Horizontal
		{
			do
			{
				k=random(yf)+1;
			} while (!hf[k]==0);
			hf[k]=1;a++;k=2*k+1;
			if (ir==1)									// ------>>
			{
				for (i=1;i<=x;i++)
				{
					if (map[k][i+1]==0)
					{
						map[k][i]=1;
					}
				}
			}
			else											// <<------
			{
				for (i=x;i>=1;i--)
				{
					if (map[k][i-1]==0)
					{
						map[k][i]=1;
					}
				}
			}
		}
		else								// Vertical
		{
			do
			{
				k=random(xf)+1;
			} while(!hv[k]==0);
			hv[k]=1;b++;k=2*k+1;
			if (ir==3)									// downwards
			{
				for (i=1;i<=y;i++)
				{
					if (map[i+1][k]==0)
					{
						map[i][k]=1;
					}
				}
			}
			else											// upwards
			{
				for (i=y;i>=1;i--)
				{
					if (map[i-1][k]==0)
					{
						map[i][k]=1;
					}
				}
			}
		}
	} while ((a!=yf)||(b!=xf));
}
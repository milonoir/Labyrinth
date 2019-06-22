int DefaultRGBpal[16][3] =
	 {
		{0,0,0},              //Black           0
		{0,0,42},             //Blue            1
		{0,42,0},             //Green           2
		{0,42,42},            //Cyan            3
		{42,0,0},             //Red             4
		{42,0,42},            //Magenta         5
		{42,21,0},            //Brown           6
		{42,42,42},           //Lightgray       7
		{21,21,21},           //Darkgray        8
		{21,21,63},           //Lightblue       9
		{21,63,21},           //Lightgreen      10
		{32,63,63},           //Lightcyan       11
		{63,21,21},           //Lightred        12
		{63,21,63},           //Lightmagenta    13
		{63,63,21},           //Yellow          14
		{63,63,63}            //White           15
	 };
struct palettetype pal;

void defpalette(void)					//Eredeti paletta
{
	int	i;
	for (i=0;i<pal.size;i++)
		setrgbpalette(pal.colors[i],
						DefaultRGBpal[i][0],
						DefaultRGBpal[i][1],
						DefaultRGBpal[i][2]);
}

void darkness(void)
{
	int	i;
	for (i=0;i<pal.size;i++)
	{
		setrgbpalette(pal.colors[i],0,0,0);
	}
	setrgbpalette(pal.colors[6],42,0,0);
}

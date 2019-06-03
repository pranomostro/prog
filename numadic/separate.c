#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

static char *argv0;
const int MAXCOLS=64;
const int MAXROWS=64;

/*
	find the next row with a (non) matrix[0][0] value
	params of interest:
	currx: the starting point of the search in the matrix
	empty: if this is true, return the next empty row, if not,
		return the next row with a non-empty value

	returns:
	the next row or -1 in case of the end of the matrix
*/

int nextcol(uint8_t **matrix, int width, int height, int currx, int channels, int empty)
{
	int yit, linefull;

	for(; currx<width; currx+=channels)
	{
		linefull=0;
		for(yit=0; yit<height; yit++)
			if(memcmp(matrix[0], matrix[yit]+currx, channels))
			{
				if(!empty)
					return currx;
				else
				{
					linefull=1;
					break;
				}
			}
		if(empty&&!linefull)
			return currx-channels;
	}

	if(currx==width&&empty&&linefull)
		return currx;

	return -1; /* end of the matrix */
}

/*
	find the next row with a (non) matrix[0][0] value
	params of interest:
	curry: the starting point of the search in the matrix
	empty: if this is true, return the next empty row, if not,
		return the next row with a non-empty value

	returns:
	the next row or -1 in case of the end of the matrix
*/

int nextrow(uint8_t **matrix, int left, int right, int height, int curry, int channels, int empty)
{
	int xit, linefull;

	for(; curry<height; curry++)
	{
		linefull=0;
		for(xit=left; xit<right; xit+=channels)
			if(memcmp(matrix[0], matrix[curry]+xit, channels))
			{
				if(!empty)
					return curry;
				else
				{
					linefull=1;
					break;
				}
			}
		if(empty&&!linefull)
			return curry-1;
	}

	if(curry==height&&empty&&linefull)
		return curry;

	return -1; /* end of the matrix */
}

/*
	print the usage of the program and then exit
	takes no arguments
	does not return
*/

void usage(void)
{
	fprintf(stderr, "usage: %s file.(png|jpg|jpeg|...)\n", argv0);
	exit(1);
}

int main(int argc, char **argv)
{
	int i, j, k, row, col, width, height, channels, left, right, up, low;
	unsigned char *data=NULL, *out=NULL;
	char file[16];
	uint8_t **matrix;
	int rows[MAXROWS], cols[MAXCOLS];

	argv0 = argv[0], argc--, argv++;

	if(argc!=1)
		usage();

	data=stbi_load(argv[0], &width, &height, &channels, 0);

	if(data==NULL)
	{
		fprintf(stderr, "%s: could not load image %s\n", argv0, argv[0]);
		exit(2);
	}

	matrix=malloc(height*sizeof(uint8_t *));

	if(matrix==NULL)
	{
		fprintf(stderr, "%s: malloc returned NULL\n", argv0);
		exit(3);
	}

	/* make the data easier to access by making it a matrix */

	for(i=0; i<height; i++)
		matrix[i]=data+(channels*width*i);

	/* load the rows */

	for(row=low=up=0; row<MAXROWS; row+=2)
	{
		up=nextrow(matrix, 0, width*channels, height, up, channels, 0);
		low=nextrow(matrix, 0, width*channels, height, up+1, channels, 1);

		if(low<0||up<0)
			break;

		rows[row]=up;
		rows[row+1]=low;

		up=low+1;
	}

	/* load the columns */

	for(col=left=right=0; col<MAXCOLS; col+=2)
	{
		left=nextcol(matrix, width*channels, height, left, channels, 0);
		right=nextcol(matrix, width*channels, height, left+channels, channels, 1);

		if(right<0||left<0)
			break;

		cols[col]=left;
		cols[col+1]=right;

		left=right+channels;
	}

	/* each pair of values in cols/rows now contains one square that contains one image */
	/* the following code extracts the exact coordinates of this image */

	mkdir("subimages", 0755);
	chdir("subimages");

	for(i=0; i<col; i+=2)
		for(j=0; j<row; j+=2)
		{
			/* continue if the row/column is empty */
			if(cols[i]==cols[i+1]||rows[j]==rows[j+1])
				continue;

			/* search for the exact area of interest */
			/* the values in rows[] and cols[] are only maxima */

			left=nextcol(matrix+rows[j], cols[i+1], rows[j+1]-rows[j], cols[i], channels, 0);
			right=nextcol(matrix+rows[j], cols[i+1], rows[j+1]-rows[j], left, channels, 1);

			up=nextrow(matrix, left, right, rows[j+1], rows[j], channels, 0);
			low=nextrow(matrix, left, right, rows[j+1], up, channels, 1);

			printf("left: %d, right: %d, exactleft: %d, exactright: %d\n", cols[i], cols[i+1], left, right);
			printf("up: %d, down: %d, exactup: %d, exactdown: %d\n", rows[j], rows[j+1], up, low);

			out=malloc((right-left)*(low-up));
			if(!out)
			{
				fprintf(stderr, "%s: could not allocate memory\n", out);
				continue;
			}

			strncpy(file, "XXXXXXX", 16);
			if(!mktemp(file))
			{
				fprintf(stderr, "%s: could not create file with a unique name\n", argv0);
				exit(5);
			}
			strcpy(file+strlen("XXXXXXX"), ".png");

			for(k=0; k<low-up; k++)
				memcpy(out+k*(right-left), matrix[k+up]+left, right-left);

			if(!stbi_write_png(file, (right-left)/channels, low-up, channels, out, 0))
				fprintf(stderr, "%s: could not write image data to %s\n", argv0, file);

			free(out);
		}

	stbi_image_free(data);
	free(matrix);

	return 0;
}

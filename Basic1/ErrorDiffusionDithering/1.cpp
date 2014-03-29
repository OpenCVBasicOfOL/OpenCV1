
#include <cv.h>
#include <highgui.h>
#include <stdio.h>
#include <stdlib.h>

void makeEDD(IplImage *origImg)
{
	int y, x;
	double e;
	double point = 0;
	double **store;

	store = (double**)malloc(sizeof(double)*origImg->height);

	for ( y = 0 ; y < origImg->height ; y ++)
	{
		store[y] = (double*)malloc(sizeof(double) * origImg->width);
	}

	
	for ( y = 0 ; y < origImg->height ; y ++)
	{
		for ( x = 0 ; x< origImg->width  ; x++ )
		{
			CvScalar itensity = cvGet2D(origImg, y, x);
			store[y][x] = (double)itensity.val[0];
		}
	}


	for ( y = 0 ; y < origImg->height - 1 ; y ++)
	{
		for ( x = 1 ; x<origImg->width - 1 ; x++ )
		{
			if(store[y][x] > 127)
			{
				e = (store[y][x] - 255);
			}
			else
			{
				e = (store[y][x]);
			}

			store[y][x+1] += e*7/16;
			store[y+1][x-1] += e*3/16;
			store[y+1][x] += e*5/16;
			store[y+1][x+1] += e/16;
		}
	}
	
	for ( y = 0 ; y < origImg->height ; y ++)
	{
		for ( x = 0 ; x< origImg->width ; x++ )
		{
			if((store[y][x]) > 127 )
			{
				cvSet2D(origImg, y, x, cvScalar(255));
			}
			else
			{
				cvSet2D(origImg, y, x, cvScalar(0));
			}
			
		}
	}
	/*
	for ( y = 1 ; y < origImg->height - 1 ; y ++)
	{
		for ( x = 1 ; x< origImg->width - 1; x++ )
		{
			CvScalar itensity1 = cvGet2D(origImg, y, x);
			point = cvGet2D(origImg, y, x + 1).val[0] + cvGet2D(origImg, y + 1, x + 1).val[0] + cvGet2D(origImg, y - 1, x + 1).val[0];
			point += cvGet2D(origImg, y, x).val[0] + cvGet2D(origImg, y + 1, x).val[0] + cvGet2D(origImg, y - 1, x).val[0];
			point += cvGet2D(origImg, y, x - 1).val[0] + cvGet2D(origImg, y + 1, x - 1).val[0] + cvGet2D(origImg, y - 1, x - 1).val[0];
			cvSet2D(resultImg, y, x, cvScalar(point/9));
			
			
		}
	}*/
	free(store);

}

int main()
{
	IplImage *billy = cvLoadImage("lena.jpg", CV_LOAD_IMAGE_GRAYSCALE);

	IplImage *herrington = cvLoadImage("lena.jpg");

	makeEDD(billy);


	IplImage *Rh = cvCreateImage(cvGetSize(herrington), 8, 1);
	IplImage *Gh = cvCreateImage(cvGetSize(herrington), 8, 1);
	IplImage *Bh = cvCreateImage(cvGetSize(herrington), 8, 1);

	cvSplit(herrington, Rh, Gh, Bh, 0);

	makeEDD(Rh);
	makeEDD(Gh);
	makeEDD(Bh);

	cvCvtPlaneToPix(Rh, Gh, Bh, NULL, herrington);

	cvSaveImage("lena_Gray_Error_Diffusion_Filtered.png", billy);
	cvSaveImage("lena_Colour_Error_Diffusion_Filtered.png", herrington);
	
	

	cvReleaseImage(&billy);
	cvReleaseImage(&herrington);
	cvReleaseImage(&Rh);
	cvReleaseImage(&Gh);
	cvReleaseImage(&Bh);

	return 0;
}

#include <cv.h>
#include <highgui.h>
#include <stdio.h>
#include <math.h>

void makeGF(IplImage *origImg, IplImage *resultImg)
{
	int y, x;
	int i, j;
	double e;
	double point = 0;

	double pi = 4*atan(1.0);  //π
	double o = 2; //σ
	double A = 1 / (2*pi*o*o);
	double B;
	double total = 0;
	double m = 0;

	IplImage *temp = cvCreateImage(cvGetSize(origImg), IPL_DEPTH_8U, 1);
	
	//-2~2 5x5필터.
	for ( y = 2 ; y < origImg->height - 2 ; y ++)
	{
		for ( x = 2 ; x<origImg->width - 2 ; x++ )
		{
			CvScalar itensity = cvGet2D(origImg, y, x);

			e = (itensity.val[0]);

			for ( i = -2 ; i <= 2 ; i ++ )
			{
				for ( j = -2 ; j <= 2 ; j++)
				{
					B = A * exp( -((i*i) + (j*j)) / 2*o*o );
					total += cvGet2D(origImg, y - i, x - j ).val[0] * B;
					m += B;
				}
			}


			cvSet2D(resultImg, y, x, cvScalar(total/m));
			//결과값에 m값을 나누어 정규화 하였습니다.

			total = 0;
			m = 0;
			

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

}

int main()
{
	IplImage *billy = cvLoadImage("lena.jpg", CV_LOAD_IMAGE_GRAYSCALE);

	IplImage *filtered = cvCreateImage(cvGetSize(billy), IPL_DEPTH_8U, 1);

	IplImage *herrington = cvLoadImage("lena.jpg");

	
	
	makeGF(billy, filtered);

	IplImage *Rh = cvCreateImage(cvGetSize(herrington), 8, 1);
	IplImage *Gh = cvCreateImage(cvGetSize(herrington), 8, 1);
	IplImage *Bh = cvCreateImage(cvGetSize(herrington), 8, 1);


	IplImage *Rr = cvCreateImage(cvGetSize(herrington), 8, 1);
	IplImage *Gr = cvCreateImage(cvGetSize(herrington), 8, 1);
	IplImage *Br = cvCreateImage(cvGetSize(herrington), 8, 1);

	cvSplit(herrington, Rh, Gh, Bh, 0);
	
	makeGF(Rh, Rr);
	makeGF(Bh, Br);
	makeGF(Gh, Gr);
	cvCvtPlaneToPix(Rr, Gr, Br, NULL, herrington);

	cvSaveImage("lena_Gray_Gaussain_Filtered.png", filtered);
	cvSaveImage("lena_Colour_Gaussain_Filtered.png", herrington);

		

	cvReleaseImage(&billy);
	cvReleaseImage(&filtered);
	cvReleaseImage(&herrington);
	cvReleaseImage(&Rh);
	cvReleaseImage(&Rr);
	cvReleaseImage(&Gh);
	cvReleaseImage(&Gr);
	cvReleaseImage(&Gh);
	cvReleaseImage(&Gr);

	return 0;
}
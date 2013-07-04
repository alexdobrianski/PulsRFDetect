// testfileread.cpp : Defines the entry point for the console application.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "stdafx.h"

#include "JPEGLIB.H"
void
write_JPEG_file (char * filename, 
				 int quality, 
				 int SizeW, 
				 int SizeH, 
				 int SizeB, 
				 unsigned char *bArray, 
				 J_COLOR_SPACE ColorCode
				 );

#define IMAGE_W 1280
#define IMAGE_H 720
//int RGBReferenceBody = EARTH;
unsigned char bRGBImage[IMAGE_W*IMAGE_H*3];
int bRGBImageW = IMAGE_W;
int bRGBImageH = IMAGE_H;
unsigned char PiCRGB[3] = {0x00,0x00,0x00};
unsigned char PiCRGBBlue[3] = {0x00,0x00,0xFF};

void putpixel(unsigned char *bRGB, int X, int Y)
{
    int iRow = (X) + (bRGBImageH - (Y))*bRGBImageW;
    if ((iRow*3 >=0) && (iRow*3 < (sizeof(bRGBImage) -3)))
    {
        memcpy(&bRGBImage[iRow*3],bRGB, 3);
    }
}


typedef struct  WAV_HEADER
{
char                RIFF[4];        
int                 ChunkSize;     
char                WAVE[4];       
char                fmt[4];        
int                 Subchunk1Size;                              
short int           AudioFormat;  
short int           NumOfChan;      
int                 SamplesPerSec;  
int                 bytesPerSec;    
short int           blockAlign;    
short int           bitsPerSample;  
char                Subchunk2ID[4];
int                 Subchunk2Size; 
}wav_hdr; 

int iNPulsars = 0;
int ATNFcatalogN[5000];
int J2000RAJ_hms[5000];
int J2000DECJ_dms[5000];
double TPeriod[5000];

int main(int argc, char* argv[])
{
    char szFileName[_MAX_PATH];
    char szFileName2[_MAX_PATH];
    char szFileName3[_MAX_PATH];
    char PulasrLine[1024];
    short int *FiveSecData;
    int *FiveSecData32;
    char *FiveSecData8;
    long int iPeriodSec = 10000;
    long int iPeriod = 50000;
    long int iPeriod2 = 50000;
    long int iCount = 0;
    wav_hdr wavHeader;
    double *Ch1;
    double Ch2;
    double ChMin;
    double ChMax;
    double Ch3;
    double *MAXCh;
	double MAXlist[30];
	int iMAXlist;
    iPeriod = atol(&argv[4][0]);
    iPeriod2 = atol(&argv[5][0]);
    iPeriodSec = atol(&argv[6][0]);
    strcpy(szFileName, &argv[0][0]);
    strcpy(szFileName2, &argv[0][0]);
    strcpy(szFileName3, &argv[0][0]);
    if (strrchr(szFileName,'\\') != NULL)
    {
        strcpy(strrchr(szFileName,'\\')+1,&argv[1][0]);
        strcpy(strrchr(szFileName2,'\\')+1,&argv[2][0]);
        strcpy(strrchr(szFileName3,'\\')+1,&argv[3][0]);
    }
    else
    {
        strcpy(szFileName,&argv[1][0]);
        strcpy(szFileName2,&argv[2][0]);
        strcpy(szFileName3,&argv[3][0]);
    }
    printf("files are: %s, %s %s", szFileName,szFileName2,szFileName3);

    // read pulsar's parameters
    FILE *pulsar = fopen("pulsar.txt","r");
    if (pulsar)
    {
        while(fgets(PulasrLine, sizeof(PulasrLine),pulsar))
        {
            int LineNumber = atoi(PulasrLine);
            if (LineNumber> 0)
            {
                ATNFcatalogN[iNPulsars] = LineNumber;
                char *StrComm = strchr(PulasrLine,',');
                if (StrComm)
                {
                    J2000RAJ_hms[iNPulsars] = atoi(StrComm+2);
                    J2000DECJ_dms[iNPulsars] = atoi(StrComm+6);
                    StrComm = strchr(StrComm+5,',');
                    if (StrComm)
                    {
                        StrComm = strchr(StrComm+1,','); // that is a period of the pulsar
                        if (StrComm)
                        {
                            TPeriod[iNPulsars++] = atof(StrComm+1);
                        }
                    }

                }
            }
        }
        fclose(pulsar);
    }

    MAXCh = (double*)malloc(sizeof(double)*(iPeriod2-iPeriod));
    if (MAXCh == NULL)
    {
        printf("\n period= %d and period2= %d are wrong",iPeriod2, iPeriod);
    }
    for (int m= 0; m < (iPeriod2-iPeriod); m++)
    {
        MAXCh[m] = 0.0;
    }
    for (long int k= iPeriod; k < iPeriod2; k++)
    {
        iCount = 0;
        FILE * FileData = fopen(szFileName,"rb");
        if (FileData)
        {
            fread(&wavHeader,sizeof(wavHeader),1,FileData);
            FILE * FileDataOut = fopen(szFileName2,"wb");
            if (FileDataOut != NULL)
            {
                fwrite(&wavHeader,sizeof(wavHeader),1,FileDataOut);
                int iBufferSize = ((double)wavHeader.bytesPerSec*(double)k)/(double)iPeriodSec;
                //if ((iBufferSize % 2) == 1)
                //iBufferSize+=(iBufferSize % 4);
                int iSampleSize = iBufferSize/(wavHeader.bitsPerSample/8)/ wavHeader.NumOfChan; // tow channels mean ammount of samples is twice smaller
                iBufferSize = iSampleSize * wavHeader.NumOfChan * (wavHeader.bitsPerSample/8);
                FiveSecData = (short int *)malloc(iBufferSize);
                Ch1 = (double*)malloc(sizeof(double)*iSampleSize);
                if (FiveSecData!= NULL && Ch1 != NULL)
                {
                    FiveSecData32 = (int*)FiveSecData;
                    FiveSecData8 = (char*)FiveSecData;
                    //wavHeader.ChunkSize -= sizeof(wavHeader)+8;
                    for (int j= 0; j < iSampleSize ; j++)
                    {
                        Ch1[j] = 0;
                    }
                    while(wavHeader.Subchunk2Size >0)
                    {
                        int iSize = iBufferSize;
                        if (wavHeader.Subchunk2Size < iSize)
                            iSize = wavHeader.Subchunk2Size;
                        fread(FiveSecData,iSize,1,FileData);
                        for (int i= 0; i < iSampleSize ; i++)
                        {
                            switch(wavHeader.bitsPerSample)
                            {
                            case 32:
                                if (wavHeader.NumOfChan == 2)
                                {
                                    Ch1[i] += (double)FiveSecData32[i*2] + (double)FiveSecData32[i*2+1];
                                    FiveSecData32[i*2] = 0;
                                }
                                else
                                {
                                    Ch1[i] += (double)FiveSecData32[i];
                                    //FiveSecData32[i*2] = 0;
                                }
                                break;
                            case 16:
                                Ch1[i] += (double)FiveSecData[i*2] + (double)FiveSecData[i*2+1];
                                FiveSecData[i*2] = 0;
                                break;
                            case 8:
                                Ch1[i] += (double)FiveSecData8[i*2] + (double)FiveSecData8[i*2+1];
                                FiveSecData8[i*2] = 0;
                                break;
                            }
                        }
                        fwrite(FiveSecData,iSize,1,FileDataOut);
                        wavHeader.Subchunk2Size-= iSize;
                        iCount++;
                    }
                    FILE * FileDataRes = fopen(szFileName3,"wb");
                    if (FileDataRes != NULL)
                    {
                        Ch2 = 0;
                        Ch3 = 0;
                        for (int i= 0; i < iSampleSize ; i++)
                        {
                            Ch1[i] = Ch1[i]/(double)wavHeader.NumOfChan/(double)iCount;  // two channels 
                            switch(wavHeader.bitsPerSample)
                            {
                            case 32: 
                                if (wavHeader.NumOfChan == 2)
                                {
                                    FiveSecData32[i*2+1] = FiveSecData32[i*2] = Ch1[i];
                                }
                                else
                                    FiveSecData32[i] = Ch1[i];
                                break;
                            case 16: FiveSecData[i*2+1] = FiveSecData[i*2] = Ch1[i];break;
                            case 8:  FiveSecData8[i*2+1] = FiveSecData8[i*2] = Ch1[i];break;
                            }
                            Ch2+=Ch1[i];
                            if (i==0)
                            {
                                ChMin = Ch1[0];
                                ChMax = Ch1[0];
                            }
                            else
                            {
                                if (ChMin > Ch1[i])
                                    ChMin = Ch1[i];
                                if (ChMax < Ch1[i])
                                    ChMax = Ch1[i];
                            }
                        }
                        Ch2/=iSampleSize;
                        wavHeader.Subchunk2Size = iBufferSize;
                        wavHeader.ChunkSize = iBufferSize + sizeof(wavHeader);
                        fwrite(&wavHeader,sizeof(wavHeader),1,FileDataRes);
                        fwrite(FiveSecData,iBufferSize,1,FileDataRes);
                        fclose(FileDataRes);
                        //Ch3 = 0;
                        for (int i= 0; i < iSampleSize ; i++) // two channels 
                        {
                            Ch3 += (Ch1[i]-Ch2)*(Ch1[i]-Ch2);
                        }
                        printf("\n%ld = %018g c= %05d d=%018g o=%018g", k, Ch2, iCount, Ch3/iSampleSize, sqrt(Ch3/iSampleSize));
                        MAXCh[k-iPeriod] = sqrt(Ch3/iSampleSize);
                    }
                    if ((iPeriod2-iPeriod) == 1)
                    {
                        memset(bRGBImage, 0xff, sizeof(bRGBImage));
						double CoefSec = ((double)IMAGE_W)/(double)iSampleSize
							       * ((double)k)/(double)iPeriodSec;
						
                        for (int i = 0; i < IMAGE_H;i++)
						{
							for(int j=0;j <10;j++)
							{
								putpixel(PiCRGBBlue, j*IMAGE_W/10, i);
								
							}
						}
						for (int i= 0; i < iSampleSize ; i++)
                        {
                            int X = ((double)i)*CoefSec;
                            int Y = (Ch1[i] - ChMin)/(ChMax-ChMin) * (double)IMAGE_H;
                            putpixel(PiCRGB, X, Y);

                        }
						
                        write_JPEG_file ("IMG.JPG", 80, bRGBImageW, bRGBImageH, 3,  bRGBImage, JCS_RGB);
                    }
                    free(FiveSecData);FiveSecData= NULL;
                    free(Ch1);Ch1=NULL;
                }
                fclose(FileDataOut);
            }
            fclose(FileData);
        }
        else
            printf("\nfile 1 =%s can not be opened",szFileName);
    }
	int istarts = 0;
	if ((iPeriod2-iPeriod) == 1)
		return 0;

	FILE * FileDataBatch = fopen("afterrun.bat","wb");

	for (int ilist = 0; ilist < sizeof(MAXlist)/sizeof(double); ilist++)
	{
		double MaxVal = MAXCh[istarts];
		int imax = istarts;
		BOOL FoundMatch = FALSE;
		for (int icheck = 0; icheck < ilist; icheck++)
		{
			if (MaxVal == MAXlist[icheck])
			{
				FoundMatch = TRUE;
				break;
			}
		}
		if (FoundMatch)
		{
			ilist--;
			istarts++;
			continue;
		}

		for (int m= imax+1; m < (iPeriod2-iPeriod); m++)
		{
			if (MaxVal < MAXCh[m])
			{
				BOOL FoundMatch = FALSE;
				for (int icheck = 0; icheck < ilist; icheck++)
				{
					if (MAXCh[m] == MAXlist[icheck])
					{
						FoundMatch = TRUE;
						break;
					}
				}
				if (FoundMatch == FALSE)
				{
					MaxVal = MAXCh[m];
					imax = m;
				}
			}
		}
		printf("\n Max at = %d == %018g",iPeriod+imax,MaxVal);
		MAXlist[ilist] = MaxVal;
		if (FileDataBatch)
		{
			fprintf(FileDataBatch,"\npulsRFdetect.exe %s %s %s %d %d %d",&argv[1][0],&argv[2][0],&argv[3][0],
				iPeriod+imax, iPeriod+imax+1, iPeriodSec);
			fprintf(FileDataBatch,"\ncopy img.jpg %d%s.jpg",iPeriod+imax,&argv[1][0]);
		}
    }
	if (FileDataBatch)
	{
		fclose(FileDataBatch);
	}
    
	return 0;
}


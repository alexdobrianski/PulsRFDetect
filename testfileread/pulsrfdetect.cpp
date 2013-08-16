/*****************************************************************************
    2013 (C) Alex Dobrianski pulsar pattern recognition software
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>
    Design and development by Team "Plan B" is licensed under 
    a Creative Commons Attribution-ShareAlike 3.0 Unported License.
    http://creativecommons.org/licenses/by-sa/3.0/ 
******************************************************************************/
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
double dPulsarCycle[5000];


void AnalizePattern(long int Iteration,
                   char *szFileData,
                   char *szFileCheck1Ch,
                   char *szFileDataRes,
                   double *dTCycle,
                   double *MAXCh
                  )
{
    long int iCount = 0;
    wav_hdr wavHeader;
    short int *FiveSecData;
    double *Ch1;
    int *FiveSecData32;
    char *FiveSecData8;
    double Ch2;
    double ChMin;
    double ChMax;
    double Ch3;
    for (long int k= 0; k < Iteration; k++)
    {
        iCount = 0;
        FILE * FileData = fopen(szFileData,"rb");
        if (FileData)
        {
            fread(&wavHeader,sizeof(wavHeader),1,FileData);
            FILE * FileCheck1Ch = fopen(szFileCheck1Ch,"wb");
            if (FileCheck1Ch != NULL)
            {
                fwrite(&wavHeader,sizeof(wavHeader),1,FileCheck1Ch);
                int iBufferSize = (double)wavHeader.bytesPerSec*dTCycle[k];
                //if ((iBufferSize % 2) == 1)
                //iBufferSize+=(iBufferSize % 4);
                int iSampleSize = iBufferSize/(wavHeader.bitsPerSample/8)/ wavHeader.NumOfChan; // two channels mean ammount of samples is twice smaller
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
                        if (iSize == 0)
                            break;
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
                        fwrite(FiveSecData,iSize,1,FileCheck1Ch);
                        wavHeader.Subchunk2Size-= iSize;
                        iCount++;
                    }
                    FILE * FileDataRes = fopen(szFileDataRes,"wb");
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
                        printf("\n%#11.7g = %018g c= %05d o=%018g", dTCycle, Ch2, iCount/*, Ch3/iSampleSize*/, sqrt(Ch3/iSampleSize));

                        MAXCh[k] = sqrt(Ch3/iSampleSize);
                    }
                    // if it is just one period == needs to draw the plot as img.jpg file
                    if (Iteration == 1)
                    {
                        memset(bRGBImage, 0xff, sizeof(bRGBImage));
						//double CoefSec = ((double)IMAGE_W)/(double)iSampleSize
						//	       * ((double)k)/(double)iSecDuration;
						double CoefSec = ((double)IMAGE_W)/(double)iSampleSize * dTCycle[k];
						// draw vertical lines
                        for (int i = 0; i < IMAGE_H;i++)
						{
							for(int j=0;j <10;j++)
							{
								putpixel(PiCRGBBlue, j*IMAGE_W/10, i);
								
							}
						}
                        // draw plot
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
                fclose(FileCheck1Ch);
            }
            fclose(FileData);
        }
        else
            printf("\nfile 1 =%s can not be opened",szFileData);
    }
}

int main(int argc, char* argv[])
{
    char szFileData[_MAX_PATH];
    char szFileCheck1Ch[_MAX_PATH];
    char szFileDataRes[_MAX_PATH];
    char PulasrLine[1024];
    short int *FiveSecData;
    int *FiveSecData32;
    char *FiveSecData8;
    long int iSecDuration = 10000;
    long int iFromTCycle = 50000;
    long int iToTCycle = 50000;
    long int iCount = 0;
    wav_hdr wavHeader;
    double *Ch1;
    double Ch2;
    double ChMin;
    double ChMax;
    double Ch3;
    double *MAXCh;
    double *dTCycle;
	double MAXlist[300];
    long int Iteration;
    long int *IterCounter;
	int iMAXlist;
	if (argc == 7) // <source wav file> <one ch only wav> <out wav len=period> 9000 11000 10000
	{
	    iFromTCycle = atol(&argv[4][0]);      //from period i.e.  9000 msk (or  9000000)
        iToTCycle = atol(&argv[5][0]);     // to  period i.e. 11000 msk (or 11000000)
        iSecDuration = atol(&argv[6][0]);   //  1 sec      ==  10000 msk (or 10000000)

        MAXCh = (double*)malloc(sizeof(double)*(iToTCycle-iFromTCycle));
        dTCycle = (double*)malloc(sizeof(double)*(iToTCycle-iFromTCycle));
        IterCounter = (long int*)malloc(sizeof(long int)*(iToTCycle-iFromTCycle));
        if (MAXCh == NULL || dTCycle == NULL || IterCounter == NULL)
        {
            printf("\n period= %d and period2= %d are wrong",iToTCycle, iFromTCycle);
            return 2;
        }
        for (int m= 0; m < (iToTCycle-iFromTCycle); m++)
        {
            MAXCh[m] = 0.0;
            dTCycle[m] = (double)(m+iFromTCycle)/(double)iSecDuration;
            IterCounter[m] = iFromTCycle + m;
        }
        Iteration = iToTCycle-iFromTCycle;
    }
    else
    {
        if ((argc == 1) || ((argc == 2) && (argv[1][1] == '?')))
        {

            printf("\n Pulsar pattern detection utility");
            printf("\n    Design and development by Team PlanB is licensed under"); 
            printf("\n    a Creative Commons Attribution-ShareAlike 3.0 Unported License.");
            printf("\n usage:");
            printf("\n  PulsRFdetect <source file> <out check> <pattern.wav> <from> <to> <1 sec>      ");
            printf("\n   where:");
            printf("\n    <source file>- source wav file captured from two separate channels of ");
            printf("\n                   two radio reseptors");
            printf("\n    <out check>  - output check file with one channel");
            printf("\n    <pattern.wav>- output pattern len = period");
            printf("\n    <from>       - number representing starting period");
            printf("\n    <to>         - number representing end testing period");
            printf("\n    <1 sec>      - number representing 1 second");
            
            printf("\n  PulsRFdetect <source file> <out check> <pattern.wav>");
            printf("\n   compare periods against pulsar.txt with real pulsar periods"); 
            return 0;
        }

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
                                if (atof(StrComm+1) < 1.0)
                                    dPulsarCycle[iNPulsars++] = atof(StrComm+1);
                            }
                        }

                    }
                }
            }
            fclose(pulsar);
        }
        if (iNPulsars)
        {
            MAXCh = (double*)malloc(sizeof(double)*(iNPulsars));
            dTCycle = (double*)malloc(sizeof(double)*(iNPulsars));
            IterCounter = (long int*)malloc(sizeof(long int)*(iNPulsars));
            if (MAXCh == NULL || dTCycle == NULL || IterCounter == NULL)
            {
                printf("\n period= %d and period2= %d are wrong",iToTCycle, iFromTCycle);
                return 2;
            }
            for (int m= 0; m < iNPulsars; m++)
            {
                MAXCh[m] = 0.0;
                dTCycle[m] = dPulsarCycle[m];
                IterCounter[m] =  ATNFcatalogN[m];
            }
            Iteration = iNPulsars;
        }
        else
        {
              printf("\n error in pulsar file read");
              return 3;
        }
    }
    strcpy(szFileData, &argv[0][0]);
    strcpy(szFileCheck1Ch, &argv[0][0]);
    strcpy(szFileDataRes, &argv[0][0]);
    if (strrchr(szFileData,'\\') != NULL)
    {
        strcpy(strrchr(szFileData,'\\')+1,&argv[1][0]);
        strcpy(strrchr(szFileCheck1Ch,'\\')+1,&argv[2][0]);
        strcpy(strrchr(szFileDataRes,'\\')+1,&argv[3][0]);
    }
    else
    {
        strcpy(szFileData,&argv[1][0]);
        strcpy(szFileCheck1Ch,&argv[2][0]);
        strcpy(szFileDataRes,&argv[3][0]);
    }
    printf("files are: %s, %s %s", szFileData,szFileCheck1Ch,szFileDataRes);

    
    //if (iNPulsars)
    //{
    //}
    //else
    {

        
    }
    AnalizePattern(Iteration, szFileData, szFileCheck1Ch, szFileDataRes, dTCycle, MAXCh );
    
	int istarts = 0;
	if ((Iteration) == 1)
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

		for (int m= imax+1; m < Iteration; m++)
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
        
		printf("\n Max at = %#011.7G (%d)== %018g",dTCycle[imax],IterCounter[imax],MaxVal);
		MAXlist[ilist] = MaxVal;
		if (FileDataBatch)
		{
            long int iDec=1000000;
            if (iSecDuration)
                iDec = iSecDuration;
            long int i1 = dTCycle[imax] * (double)iDec;

			fprintf(FileDataBatch,"\npulsRFdetect.exe %s %s %s %ld %ld %ld",&argv[1][0],&argv[2][0],&argv[3][0],
				//IterCounter[imax], IterCounter[imax+1], iSecDuration);
                i1, i1+1, iDec);
            //fprintf(FileDataBatch,"\ncopy img.jpg %s%#011.7G.jpg",&argv[1][0],dTCycle[imax]);
            fprintf(FileDataBatch,"\ncopy img.jpg %s%d.jpg",&argv[1][0],IterCounter[imax]);
		}
    }
	if (FileDataBatch)
	{
		fclose(FileDataBatch);
	}
    
	return 0;
}


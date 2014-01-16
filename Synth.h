#define SAMPLE_RATE		44100
#define BITS			32

#define SYNTHCURSORDISTANCE 66150

#define BUFFER_MS		2000
#define BUFFER_SAMPLES	88200
#define BUFFER_BYTES    705600

#define BLOCKALIGN     8
#define AVGBYTESPERSEC 352800

#define SYNTHBAR_NOTE       0
#define SYNTHBAR_POS        1
#define SYNTHBAR_DURATION   2
#define SYNTHBAR_PROCESSED  3

#define NOTEAMP 0.25f

#define delayDelayL   14000
#define delayDelayR   16000
#define delayFeedback 0.5f
/*
#define SYNTH_BPM				120
#define SYNTH_BARSPERMINUTE		(SYNTH_BPM / 8)
#define SYNTH_TICKSPERBAR		320
#define SYNTH_TICKSPERMINUTE	(SYNTH_BARSPERMINUTE * SYNTH_TICKSPERBAR)
#define SYNTH_TICKSPERSECOND	((float) TICKSPERMINUTE / 60.f)
#define SYNTH_FRAMESPERTICK		((float) (SAMPLE_RATE * 60.f) / SYNTH_TICKSPERMINUTE)
#define SYNTH_FRAMESPERBAR      ((SAMPLE_RATE * 60) / SYNTH_BARSPERMINUTE)
*/
#define SYNTH_BPM				 120
#define SYNTH_BARSPERMINUTE		  15  // (SYNTH_BPM / 8)
#define SYNTH_TICKSPERBAR		 320
#define SYNTH_TICKSPERMINUTE	4800  // (SYNTH_BARSPERMINUTE * SYNTH_TICKSPERBAR)
#define SYNTH_TICKSPERSECOND	   8  // ((float) TICKSPERMINUTE / 60.f)
#define SYNTH_FRAMESPERTICK		551.25f //((float) (SAMPLE_RATE * 60.f) / SYNTH_TICKSPERMINUTE)
#define SYNTH_FRAMESPERBAR      176400 // ((SAMPLE_RATE * 60) / SYNTH_BARSPERMINUTE)

float waveBuffer[BUFFER_SAMPLES][2];
float tempBuffer[BUFFER_SAMPLES][2];

float delayBuffer[BUFFER_SAMPLES][2];


WAVEHDR  synthHeader;
HWAVEOUT synthHandle;

long synthPlayPosition = 0;
long synthWritePosition = SYNTHCURSORDISTANCE;


struct note
{
	bool on;
	float step;
	int pos;
	int stop;
	float amp;
	float ampInterval;
};

extern int song[][2];

note notes[10];

int currentPattern = 0;
int synthCounter   = 0;

void synthMainLoop()
{
	// get current play position
	MMTIME time;

	time.wType = TIME_SAMPLES;

	waveOutGetPosition(synthHandle, &time, sizeof(time));

	synthPlayPosition = time.u.sample;

	timer = (int) (synthPlayPosition * 0.022675f) - 1500;

	int length = (synthPlayPosition + SYNTHCURSORDISTANCE) - synthWritePosition;

	// render
	int relPlayPosition  = synthPlayPosition  % BUFFER_SAMPLES;
	int relWritePosition = synthWritePosition % BUFFER_SAMPLES;

	int i, j, k;

	for (i = 0; i < length; i++)
	{
		note* pNote = notes;

		// update notes values
		if ((synthCounter % 128) == 0)
		{
			int tempPattern = synthCounter / SYNTH_FRAMESPERBAR;
			int tempCounter = synthCounter % SYNTH_FRAMESPERBAR;

			int tick = (int) ((float) tempCounter / SYNTH_FRAMESPERTICK);

			if (tempPattern > currentPattern)
			{
				short* bar = (short*) song[currentPattern][0];

				for (j = 0; j < song[currentPattern][1]; j++)
				{
					bar[SYNTHBAR_PROCESSED] = 0;
					bar += 4;
				}

				currentPattern = tempPattern;
			}

			// close notes that are finished
			for (k = 0; k < 10; k++)
			{
				if (pNote->on)
				{
					int dif = pNote->stop - pNote->pos;

					if (dif < 0)
					{
						pNote->on = false;
					}
					else
					{
						if (pNote->pos > 500) pNote->ampInterval = 0;
						if (dif < 500) pNote->ampInterval = -NOTEAMP / 500.f;
					}
				}

				pNote++;
			}

			pNote -= 10;

			short* bar = (short*) song[currentPattern][0];

			// pattern selection
			for (j = 0; j < (int) song[currentPattern][1]; j++)
			{
				pNote = notes;

				if ((bar[SYNTHBAR_PROCESSED] == 0) && (tick >= bar[SYNTHBAR_POS]))
				{
					bar[SYNTHBAR_PROCESSED] = 1;

					float freq = 440.f * (float) pow(2.f, -(57 - bar[SYNTHBAR_NOTE]) / 12.f);

					// find free note slot
					for (int k = 0; k < 10; k++)
					{
						if (!pNote->on)
						{
							pNote->on   = true;
							pNote->step = (float) (freq * _2PI) / 44100.f;
							pNote->pos  = 0;
							pNote->stop = (int) (bar[SYNTHBAR_DURATION] * SYNTH_FRAMESPERTICK);
							pNote->amp  = 0.0f;
							pNote->ampInterval = NOTEAMP / 500.f; 
							break;
						}
						pNote++;
					}
				}

				bar += 4;
			}
		}

		float v1 = 0, v2;

		// play notes
		pNote = notes;
		for (k = 0; k < 10; k++)
		{
			if (pNote->on)
			{
				float tt = sin(pNote->pos++ * pNote->step) * pNote->amp * 0.25f;

				v1 += (tt < 0 ? -0.25f : 0.25f) * pNote->amp + tt;

				pNote->amp += pNote->ampInterval;
			}

			pNote++;
		}

		v2 = v1;

		v1 += delayBuffer[(relWritePosition + i) % BUFFER_SAMPLES][0];
		v2 += delayBuffer[(relWritePosition + i) % BUFFER_SAMPLES][1];

		delayBuffer[(relWritePosition + i + delayDelayL) % BUFFER_SAMPLES][0] = v1 * delayFeedback;
		delayBuffer[(relWritePosition + i + delayDelayR) % BUFFER_SAMPLES][1] = v2 * delayFeedback;

		tempBuffer[i][0] = v1;
		tempBuffer[i][1] = v2;

		synthCounter++;
	}
	// render

	// write to sound buffer
	if ((relWritePosition + length) <=  BUFFER_SAMPLES)	// no need to loop
	{
		rj_memcpy((char*)waveBuffer + (relWritePosition * (BITS >> 3) * 2), 
			      tempBuffer, 
				  length * (BITS >> 3) * 2);

	}
	else												// need to loop
	{		
		long remainder = (relWritePosition + length) - BUFFER_SAMPLES;

		rj_memcpy((char*)waveBuffer + (relWritePosition * (BITS >> 3) * 2), 
			      tempBuffer, 
				  (length - remainder) * (BITS >> 3) * 2);
		rj_memcpy(waveBuffer, 
			      (char*)tempBuffer + ((length - remainder) * (BITS >> 3) * 2), 
				  remainder * (BITS >> 3) * 2);
	}

	synthWritePosition += length;
}


void synthInit()
{
	//synthCursorDistance = (long) (SAMPLE_RATE * 1.5f);

//	synthPlayPosition	= 0;
//	synthWritePosition  = SYNTHCURSORDISTANCE;

	// clear buffers, to preserve ourselves of major ear damage
	rj_memset(waveBuffer,  0, BUFFER_SAMPLES * 4 * 2);
	rj_memset(tempBuffer,  0, BUFFER_SAMPLES * 4 * 2);
	rj_memset(delayBuffer, 0, BUFFER_SAMPLES * 4 * 2);

	// create wave out handle
	WAVEFORMATEX format;

	format.nSamplesPerSec  = SAMPLE_RATE;
	format.wBitsPerSample  = BITS;
	format.nChannels       = 2;
	format.nBlockAlign     = BLOCKALIGN;//(format.wBitsPerSample >> 3) * format.nChannels;
	format.nAvgBytesPerSec = AVGBYTESPERSEC;//format.nSamplesPerSec * format.nBlockAlign;
	format.wFormatTag      = WAVE_FORMAT_IEEE_FLOAT;
	format.cbSize          = 0;

	waveOutOpen(&synthHandle, WAVE_MAPPER, &format, 0, 0, 0);

	synthHeader.lpData          = (char*) waveBuffer;
	synthHeader.dwBufferLength  = sizeof(waveBuffer);
	synthHeader.dwBytesRecorded = 0;
	synthHeader.dwUser          = 0;
	synthHeader.dwFlags         = WHDR_BEGINLOOP | WHDR_ENDLOOP;
	synthHeader.dwLoops         = -1;
	synthHeader.reserved        = 0;
	synthHeader.lpNext          = 0;

	waveOutPrepareHeader(synthHandle, &synthHeader, sizeof(synthHeader));
	waveOutWrite(synthHandle, &synthHeader, sizeof(synthHeader));
}

void synthShutdown()
{
	waveOutReset(synthHandle);
	waveOutUnprepareHeader(synthHandle, &synthHeader, sizeof(synthHeader));
	waveOutClose(synthHandle);
}

short bar04[][4] = // 30
{
	{ 59,   0,  20, 0},
	{ 62,  20,  20, 0},
	{ 71,  40,  20, 0},
	{ 62,  60,  20, 0},
	{ 71,  80,  20, 0},
	{ 57, 100,  20, 0},
	{ 62, 120,  20, 0},
	{ 69, 140,  20, 0},
	{ 55, 160,  20, 0},
	{ 62, 180,  20, 0},
	{ 67, 200,  20, 0},
	{ 54, 220,  20, 0},
	{ 62, 240,  20, 0},
	{ 66, 260,  20, 0},
	{ 62, 280,  20, 0},
	{ 66, 300,  20, 0},

	{ 35,   0, 160, 0},
	{ 31, 160,  60, 0},
	{ 30, 220, 100, 0},

	{ 26,   0,  20, 0},
	{ 26,  40,  20, 0},
	{ 26,  80,  20, 0},
	{ 26, 120,  20, 0},
	{ 26, 160,  20, 0},
	{ 26, 200,  20, 0},
	{ 26, 240,  20, 0},
	{ 26, 280,  20, 0},

	{ 71,   0, 160, 0},
	{ 74, 160,  60, 0},
	{ 78, 220, 100, 0}
};

short bar05[][4] = // 30
{
	{ 59,   0,  20, 0},
	{ 62,  20,  20, 0},
	{ 71,  40,  20, 0},
	{ 62,  60,  20, 0},
	{ 71,  80,  20, 0},
	{ 57, 100,  20, 0},
	{ 62, 120,  20, 0},
	{ 69, 140,  20, 0},
	{ 55, 160,  20, 0},
	{ 62, 180,  20, 0},
	{ 67, 200,  20, 0},
	{ 54, 220,  20, 0},
	{ 62, 240,  20, 0},
	{ 66, 260,  20, 0},
	{ 62, 280,  20, 0},
	{ 66, 300,  20, 0},

	{ 35,   0, 160, 0},
	{ 31, 160,  60, 0},
	{ 30, 220, 100, 0},

	{ 26,   0,  20, 0},
	{ 26,  40,  20, 0},
	{ 26,  80,  20, 0},
	{ 26, 120,  20, 0},
	{ 26, 160,  20, 0},
	{ 26, 200,  20, 0},
	{ 26, 240,  20, 0},
	{ 26, 280,  20, 0},

	{ 71,   0, 160, 0},
	{ 79, 160,  60, 0},
	{ 78, 220, 100, 0}
};

short bar07[][4] = // 30
{
	{ 55,   0,  20, 0},
	{ 59,  20,  20, 0},
	{ 67,  40,  20, 0},
	{ 59,  60,  20, 0},
	{ 67,  80,  20, 0},
	{ 54, 100,  20, 0},
	{ 57, 120,  20, 0},
	{ 66, 140,  20, 0},
	{ 57, 160,  20, 0},
	{ 61, 180,  20, 0},
	{ 69, 200,  20, 0},
	{ 59, 220,  20, 0},
	{ 62, 240,  20, 0},
	{ 71, 260,  20, 0},
	{ 62, 280,  20, 0},
	{ 71, 300,  20, 0},

	{ 31,   0, 160, 0},
	{ 33, 160,  60, 0},
	{ 35, 220, 100, 0},

	{ 26,   0,  20, 0},
	{ 26,  40,  20, 0},
	{ 26,  80,  20, 0},
	{ 26, 120,  20, 0},
	{ 26, 160,  20, 0},
	{ 26, 200,  20, 0},
	{ 26, 240,  20, 0},
	{ 26, 280,  20, 0},

	{ 71,   0, 160, 0},
	{ 73, 160,  60, 0},
	{ 74, 220, 100, 0}
};

short bar08[][4] = // 30
{
	{ 55,   0,  20, 0},
	{ 59,  20,  20, 0},
	{ 67,  40,  20, 0},
	{ 59,  60,  20, 0},
	{ 67,  80,  20, 0},
	{ 54, 100,  20, 0},
	{ 57, 120,  20, 0},
	{ 66, 140,  20, 0},
	{ 57, 160,  20, 0},
	{ 61, 180,  20, 0},
	{ 69, 200,  20, 0},
	{ 59, 220,  20, 0},
	{ 62, 240,  20, 0},
	{ 71, 260,  20, 0},
	{ 62, 280,  20, 0},
	{ 71, 300,  20, 0},

	{ 31,   0, 160, 0},
	{ 33, 160,  60, 0},
	{ 35, 220, 100, 0},

	{ 26,   0,  20, 0},
	{ 26,  40,  20, 0},
	{ 26,  80,  20, 0},
	{ 26, 120,  20, 0},
	{ 26, 160,  20, 0},
	{ 26, 200,  20, 0},
	{ 26, 240,  20, 0},
	{ 26, 280,  20, 0},

	{ 79,   0, 160, 0},
	{ 78, 160,  60, 0},
	{ 74, 220, 100, 0}
};

int song[][2] =
{
	{(int) &bar04[0][0], 16},
	{(int) &bar04[0][0], 16},
	{(int) &bar04[0][0], 19},
	{(int) &bar04[0][0], 19},
	{(int) &bar04[0][0], 27},
	{(int) &bar04[0][0], 27},
	{(int) &bar04[0][0], 27},
	{(int) &bar04[0][0], 27},
	{(int) &bar07[0][0], 27},
	{(int) &bar07[0][0], 27},
//	{(int) &bar07[0][0], 27},
//	{(int) &bar07[0][0], 27},
	{(int) &bar04[0][0], 30},
	{(int) &bar05[0][0], 30},
	{(int) &bar04[0][0], 30},
	{(int) &bar05[0][0], 30},
	{(int) &bar07[0][0], 30},
	{(int) &bar08[0][0], 30},
	{(int) &bar07[0][0], 30},
	{(int) &bar08[0][0], 30},
	{(int) &bar08[0][0], 0},
	{(int) &bar08[0][0], 0}
};
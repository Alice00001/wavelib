#ifndef WAVELIB_H_
#define WAVELIB_H_

#ifdef __cplusplus
extern "C" {
#endif

#ifndef fft_type
#define fft_type double
#endif

typedef struct wave_set* wave_object;

wave_object wave_init(char* wname);

struct wave_set{
	char wname[50];
	int filtlength;// When all filters are of the same length. [Matlab uses zero-padding to make all filters of the same length]
	int lpd_len;// Default filtlength = lpd_len = lpr_len = hpd_len = hpr_len
	int hpd_len;
	int lpr_len;
	int hpr_len;
	double *lpd;
	double *hpd;
	double *lpr;
	double *hpr;
	double params[0];
};

typedef struct fft_t {
  fft_type re;
  fft_type im;
} fft_data;

typedef struct fft_set* fft_object;

fft_object fft_init(int N, int sgn);

struct fft_set{
	int N;
	int sgn;
	int factors[64];
	int lf;
	int lt;
	fft_data twiddle[1];
};

typedef struct fft_real_set* fft_real_object;

fft_real_object fft_real_init(int N, int sgn);

struct fft_real_set{
	fft_object cobj;
	fft_data twiddle2[1];
};

typedef struct conv_set* conv_object;

conv_object conv_init(int N, int L);

struct conv_set{
	fft_real_object fobj;
	fft_real_object iobj;
	int ilen1;
	int ilen2;
	int clen;
};

typedef struct wt_set* wt_object;

wt_object wt_init(wave_object wave,char* method, int siglength, int J);

struct wt_set{
	wave_object wave;
	conv_object cobj;
	char method[10];
	int siglength;// Length of the original signal.
	int outlength;// Length of the output DWT vector
	int lenlength;// Length of the Output Dimension Vector "length"
	int J; // Number of decomposition Levels
	int MaxIter;// Maximum Iterations J <= MaxIter
	int even;// even = 1 if signal is of even length. even = 0 otherwise
	char ext[10];// Type of Extension used - "per" or "sym"
	char cmethod[10]; // Convolution Method - "direct" or "FFT"

	int N; // 
	int cfftset; 
	int zpad;
	int length[102];
	double *output;
	double params[0];
};

void dwt11(wt_object wt, double *Vin, int M, double *Wout,
	double *Vout);

void dwt(wt_object wt, double *inp);

void idwt(wt_object wt, double *dwtop);

void swt(wt_object wt, double *inp);

void iswt(wt_object wt, double *swtop);

void modwt(wt_object wt, double *inp);

void imodwt(wt_object wt, double *dwtop);

void setDWTExtension(wt_object wt, char *extension);

void setWTConv(wt_object wt, char *cmethod);

void wave_summary(wave_object obj);

void wt_summary(wt_object wt);

void wave_free(wave_object object);

void wt_free(wt_object object);


#ifdef __cplusplus
}
#endif


#endif /* WAVELIB_H_ */



#include <vector>
#include <algorithm>
#include <complex>
#include "Drawer1.h"
#include <time.h>
#define Pi 3.1415926535
#define  NUMBER_IS_2_POW_K(x)   ((!((x)&((x)-1)))&&((x)>1))  // x is pow(2, k), k=1,2, ...
#define  FT_DIRECT        -1    // Direct transform.
#define  FT_INVERSE        1    // Inverse transform.

using namespace std;

class Signal {
public:
	Drawer* dr;
	
	double
		N,
		fd,		
		A1, 
		A2,
		A3,
		A4,
		A5,
		G1,
		G2,
		G3,
		G4,
		G5,
		niu1,
		niu2,
		niu3,
		niu4,
		niu5
		;
	vector<double>
		X,
		XR,
		H, //модуль сигнала
		keys,
		keysH,
		buf;
	
	//конструктор по умолчанию
	Signal() {};

	//Деструктор
	~Signal() {
		X.~vector();
		XR.~vector();
		H.~vector();
		keys.~vector();
		keysH.~vector();
	}

	//заполнение сигнала
	void FillSignal(double n, double Fd, double A1, double A2, double A3, double A4, double A5,
		double G1, double G2, double G3, double G4, double G5,
		double niu1, double niu2, double niu3, double niu4, double niu5, Drawer *dr) {
		this->N = n;		
		this->fd = Fd;
		this->A1 = A1;
		this->A2 = A2;
		this->A3 = A3;
		this->A4 = A4;
		this->A5 = A5;
		this->G1 = G1;
		this->G2 = G2;
		this->G3 = G3;
		this->G4 = G4;
		this->G5 = G5;
		this->niu1 = niu1;
		this->niu2 = niu2;
		this->niu3 = niu3;
		this->niu4 = niu4;
		this->niu5 = niu5;
		this->dr = dr;
		Create();
	}

	//отчистка сигнала
	void ClearSignal() {
		X.clear();
		XR.clear();
		H.clear();		
		keys.clear();
		keysH.clear();		
	}

	//создание сигнала
	void Create() {			
		for (int i = 0; i < N; i++) {			
			keys.push_back(i / fd);
			X.push_back(				
			A1 * exp(-(keys[i] - niu1/fd)* (keys[i] - niu1/fd) / ( G1 * G1 )) +
			A2 * exp(-(keys[i] - niu2/fd)* (keys[i] - niu2/fd) / ( G2 * G2)) +
			A3 * exp(-(keys[i] - niu3/fd)* (keys[i] - niu3/fd) / ( G3 * G3 )) + 
			A4 * exp(-(keys[i] - niu4 / fd) * (keys[i] - niu4 / fd) / (G4 * G4)) +
			A5 * exp(-(keys[i] - niu5 / fd) * (keys[i] - niu5 / fd) / (G5 * G5))
			);		
		}	

		////спектр		
		Get_Spectrum(H, keysH);
	}

	//Быстрое Фурье
	bool  FFT(int Ft_Flag, double * Rdat, double* Idat)
	{
		int LogN = log2(N);		

		register int  i, j, n, k, io, ie, in, nn;
		float         ru, iu, rtp, itp, rtq, itq, rw, iw, sr;

		static const float Rcoef[14] =
		{ -1.0000000000000000F,  0.0000000000000000F,  0.7071067811865475F,
			0.9238795325112867F,  0.9807852804032304F,  0.9951847266721969F,
			0.9987954562051724F,  0.9996988186962042F,  0.9999247018391445F,
			0.9999811752826011F,  0.9999952938095761F,  0.9999988234517018F,
			0.9999997058628822F,  0.9999999264657178F
		};
		static const float Icoef[14] =
		{ 0.0000000000000000F, -1.0000000000000000F, -0.7071067811865474F,
		   -0.3826834323650897F, -0.1950903220161282F, -0.0980171403295606F,
		   -0.0490676743274180F, -0.0245412285229122F, -0.0122715382857199F,
		   -0.0061358846491544F, -0.0030679567629659F, -0.0015339801862847F,
		   -0.0007669903187427F, -0.0003834951875714F
		};

		nn = (int)N >> 1;
		ie = N;
		for (n = 1; n <= LogN; n++)
		{
			rw = Rcoef[LogN - n];
			iw = Icoef[LogN - n];
			if (Ft_Flag == FT_INVERSE) iw = -iw;
			in = ie >> 1;
			ru = 1.0F;
			iu = 0.0F;
			for (j = 0; j < in; j++)
			{
				for (i = j; i < N; i += ie)
				{
					io = i + in;
					rtp = Rdat[i] + Rdat[io];
					itp = Idat[i] + Idat[io];
					rtq = Rdat[i] - Rdat[io];
					itq = Idat[i] - Idat[io];
					Rdat[io] = rtq * ru - itq * iu;
					Idat[io] = itq * ru + rtq * iu;
					Rdat[i] = rtp;
					Idat[i] = itp;
				}

				sr = ru;
				ru = ru * rw - iu * iw;
				iu = iu * rw + sr * iw;
			}

			ie >>= 1;
		}

		for (j = i = 1; i < N; i++)
		{
			if (i < j)
			{
				io = i - 1;
				in = j - 1;
				rtp = Rdat[in];
				itp = Idat[in];
				Rdat[in] = Rdat[io];
				Idat[in] = Idat[io];
				Rdat[io] = rtp;
				Idat[io] = itp;
			}

			k = nn;

			while (k < j)
			{
				j = j - k;
				k >>= 1;
			}

			j = j + k;
		}

		if (Ft_Flag == FT_DIRECT) return true;

		rw = 1.0F / N;

		for (i = 0; i < N; i++)
		{
			Rdat[i] *= rw;
			Idat[i] *= rw;
		}

		return true;
	}

	//Спектр
	void Get_Spectrum(vector<double>& data, vector<double>& keys) {
		double
			* Re = new double[N],
			* Im = new double[N];
		for (int i = 0; i < N; i++) {
			Re[i] = X[i];
			Im[i] = 0.;
		}

		FFT(-1, Re, Im);

		for (int i = 0; i < N; i++) {
			data.push_back(sqrt((Im[i] * Im[i]) + (Re[i] * Re[i])));
			keys.push_back(fd * i / N);
		}

		delete Re;
		delete Im;
	}

	// метод Фиенупа
	void FienupMethod(MSG msg, double de, double &e) {
		double
			* Im1 = new double[N],
			* Im2 = new double[N],
			* Re1 = new double[N],
			* Re2 = new double[N],
			s1 = 1,
			s2 = 0;
		int calc = 0;
		
		srand(time(0));
		//начальная инициализация
		for (int i = 0; i < N; i++) {
			double phi = ((double)rand() / RAND_MAX) * 2 * Pi;			
			Im2[i] = H[i] * sin(phi);			
			Re2[i] = H[i] * cos(phi);
		}	

		while (abs(s1 - s2) > de) {
			while (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);				
			}			

			//сохранение результатов предыдущей итерации
			s1 = s2;
			for (int i = 0; i < N; i++) {				
				Im1[i] = Im2[i];
				Re1[i] = Re2[i];
			}

			//ограничения во временной области
			FFT(1, Re2, Im2);
			FFT(1, Re1, Im1);

			if (!(calc % 100)) {
				for (int i = 0; i < N; i++)
					XR.push_back(Re2[i]);

				dr->DrawTwo(XR, X,
					*min_element(keys.begin(), keys.end()),
					*max_element(keys.begin(), keys.end()),
					min(*min_element(XR.begin(), XR.end()), *min_element(X.begin(), X.end())),
					max(*max_element(XR.begin(), XR.end()), *max_element(X.begin(), X.end())),
					't', 'A', keys, keys);
				XR.clear();
			}
			
			for (int i = 0; i < N; i++) {
				if (Re2[i] < 0) {
					Re2[i] = 0;
					
				}
				Im2[i] = 0;
					
			}
			FFT(-1, Re2, Im2);
			
			//замена спектра
			double phase;
			for (int j = 0; j < N; j++) {						
				phase = arg(complex<double>(Re2[j], Im2[j]));
				Re2[j] = H[j] * cos(phase);
				Im2[j] = H[j] * sin(phase);
			}			
			
			FFT(1, Re2, Im2);
			
			//подчсет отклонения
			s2 = 0;
			for (int i = 0; i < N; i++) 
				s2 += sqrt((Re1[i] - Re2[i]) * (Re1[i] - Re2[i]));
			FFT(-1, Re2, Im2);
			e = abs(s1 - s2);

			calc++;
		}//end of while

		
		FFT(1, Re2, Im2);
		for (int i = 0; i < N; i++)
			XR.push_back(Re2[i]);

		dr->DrawTwo(XR, X,
			*min_element(keys.begin(), keys.end()),
			*max_element(keys.begin(), keys.end()),
			min(*min_element(XR.begin(), XR.end()), *min_element(X.begin(), X.end())),
			max(*max_element(XR.begin(), XR.end()), *max_element(X.begin(), X.end())),
			't', 'A', keys, keys);

		
		delete[] Im1;
		delete[] Im2;
		delete[] Re1;
		delete[] Re2;		
	}
		
	//Нахождение ошибки
	double GetError() {
		for (int i = 0; i < N; i++) {
			buf.push_back(abs((X[i] - XR[i])));
		}
		double res = *max_element(buf.begin(),buf.end());
		buf.clear();
		return res;
	}

	//сдвиг
	void Shift() {
		buf = XR;	
		for (int i = 0; i < N - 1; i++) {
			XR[i + 1] = buf[i];
		}
		XR[0] = buf[N - 1];
		buf.clear();
	}

	//отражение
	void Reflection() {
		buf = XR;
		for (int i = 0; i < N; i++) {
			XR[i] = buf[N - 1 - i];
		}
		buf.clear();
	}

	//корректировка сигнала
	void Correct(bool &isSolve) {
		for (int i = 0; i < 2 * N; i++) {
			Shift();

			if (GetError() <= 0.2 * (*max_element(X.begin(), X.end()))) {
				MessageBoxA(NULL, (LPCSTR)"Complete!", (LPCSTR)"", MB_OK);
				dr->DrawTwo(XR, X,
					*min_element(keys.begin(), keys.end()),
					*max_element(keys.begin(), keys.end()),
					min(*min_element(XR.begin(), XR.end()), *min_element(X.begin(), X.end())),
					max(*max_element(XR.begin(), XR.end()), *max_element(X.begin(), X.end())),
					't', 'A', keys, keys);
				isSolve = true;
				break;
			}

			if ((i == N - 1) && (GetError() >= 0.2 * (*max_element(X.begin(), X.end())))) {
				Reflection();			
			}
		}
	}

	//Решение
	void Solve(MSG msg, double de, double& e) {
		bool isSolve = false;
		for (int j = 0; j < 10; j++) {
			if (isSolve)
				break;
			FienupMethod(msg, de, e);
			Correct(isSolve);
			
			XR.clear();
		}	
	}
};

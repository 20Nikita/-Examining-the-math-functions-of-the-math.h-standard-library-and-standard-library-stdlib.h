//#include <locale.h>	//нужна для подключения русского языка
//#include <stdio.h>	//основная библиотека 
//#include <math.h>	//нужна для подсчета sin(x),cos(x),fabs
////число пи
//const double M_PI = 3.14159265358979323846;
////вункция
//double F(double x) { return (2 * sin(x) * sin(x)) / 3 - 0.75 * cos(x) * cos(x); }
////возвращает 0 если знаки F(a) и F(b) одинаковые и 1 если разные
//int Znak(double a, double b);
//
//void korenb();
//void integral();
//
//int main() {
//	korenb();
//	integral();
//}
//void korenb() {
//	setlocale(LC_ALL, "Russian");		// подключаю русский язык
//	double	a = 0;						// начало интервала
//	double	b = M_PI/2;					// конец интервала
//	double	x = 0;						// переменная
//	double Eps = 0.001;					// точностьа
//
//	while (fabs(F(x)) > Eps)			//пока не найдем решение с заданой точностью
//	{
//		//точка пересечения хорды с осью абсцисс
//		x = (a * F(b) - b * F(a)) / (F(b) - F(a));
//
//		if (Znak(F(a), F(x)))			//F(a) и F(x) разных знаков
//			b = x;						//меняем границы отрезка
//		else if (Znak(F(x), F(b)))		//F(x) и F(b) разных знаков
//			a = x;						//меняем границы отрезка
//	}
//	//печать результата
//	printf("\tЗАДАЧА 1\tрешение уравнения (2 * sin(x) * sin(x)) / 3 - 0.75 * cos(x) * cos(x) = 0 х: [0;п/2]\n\n\tx = %g\tf(x) = %g\n\n", x, F(x));
//
//}
//
//int Znak(double a, double b) {
//	if (a > 0 && b > 0)
//		return 0;
//	else if (a < 0 && b < 0)
//		return 0;
//	else
//		return 1;
//}
//
//
//double S(double a, double b, int n) {
//	double	h = (b - a) / n;			// длинна отрезка
//	double	S = 0;						// площадь
//	for (int i = 0; i < n; i++)
//		S = S + h * sqrt(tan((a + h * i + h / 2)));
//	return S; 
//}
//int t = 0.257824531073655;				//точная площадь 
//void integral() {
//	setlocale(LC_ALL, "Russian");		// подключаю русский язык
//	double	a = 0;						// начало интервала
//	double	b = M_PI / 6;				// конец интервала
//	double Eps = 0.0005;				// точностьа
//	int k = 5;
//	int n = 10;
//	while (fabs(S(a, b, n) - S(a, b, n + k)) > Eps)
//		n = n + k;
//	printf("\tЗАДАЧА 2\tнахождение значения собственного интеграла sqrt(tan(x)) х: [0;п/6]\n\n\tS = %g\n\n", S(a, b, n + k));
//}
//
#include <stdio.h>
#include <math.h>
#include <locale.h>
const double M_PI = 3.14159265358979323846;
float chord(float (*)(float), float a, float b, float e);
float trapeze(float (*)(float), float a, float b, int n, float e);
float f1(float x)
{
	return (2 * powf(sinf(x), 2)) / 3 - 0.75 * powf(cosf(x), 2);
}
float f2(float x)
{
	return sqrtf(tanf(x));
}
int main()
{
	setlocale(LC_ALL, "Russian");
	printf("Корень уравнений 2*sin(x)^2)/3 - 0.75*c" \
		"os(x)^2 в [%f; %f]: %f\n", \
		0.0, M_PI / 2, chord(f1, 0.0, M_PI / 2, 0.001));

	printf("Численный интеграл функции sqrt(tan(x))" \
		"на промежутке [%f; %f]: %f\n", \
		0.0, M_PI / 6, trapeze(f2, 0.0, M_PI / 6, 10, 0.0005));
}
float chord(float (*f)(float), float a, float b, float e)
{
	float x = (a * f(b) - b * f(a)) / (f(b) - f(a));
	float fx = f(x);

	return (fabs(fx) <= e) ? x :
		(f(a) * fx > 0.0) ? chord(f, x, b, e) :
		chord(f, a, x, e);
}
float trapeze(float (*f)(float), float a, float b, int n, float e)
{
	float old = 0.0;
	float sum = 0.0;
	do {
		float h = (b - a) / n;
		old = sum;
		sum = 0.0;

		for (int j = 0; j < n; ++j)
			sum += f(a + j * h) * h;
		sum += h * (f(a) + f(b)) / 2;

		n += 5;
	} while (sum - old > e);

	return sum;
}

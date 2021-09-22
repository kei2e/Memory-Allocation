#ifndef iostream_h
#define iostream_h
#include <iostream>
#endif

#ifndef cmath_h
#define cmath_h
#include <cmath>
#endif

#ifndef vector_h
#define vector_h
#include <vector>
#endif

#include "../header/header.h"

using double_vec = std::vector<double>;

const int N1 = 1000;
const int N2 = 1000;
const int N3 = 1000;

short int concat(const short int &D,
				 const short int *N,
				 const short int *n)
{
	short int ind = 0;
	for (int d = D - 1; d >= 0; d--)
	{
		int temp = n[d];
		for (int i = d - 1; i >= 0; i--)
		{
			temp = temp * N[i];
		}
		ind = ind + temp;
	}

	return (ind);
}

//  TEST
bool test(double ***V)
{
	for (int n1 = 0; n1 < N1; n1++)
	{
		for (int n2 = 0; n2 < N2; n2++)
		{
			for (int n3 = 0; n3 < N3; n3++)
			{
				try
				{
					if (abs(V[n1][n2][n3] - 1.0) > double(1.e-20))
						return (false);
				}
				catch (std::out_of_range o)
				{
					std::cout << o.what() << std::endl;
					return (false);
				}
			}
		}
	}

	return (true);
}

bool test(const std::vector<std::vector<double_vec>> &V)
{
	for (int n1 = 0; n1 < N1; n1++)
	{
		for (int n2 = 0; n2 < N2; n2++)
		{
			for (int n3 = 0; n3 < N3; n3++)
			{
				try
				{
					if (abs(V[n1][n2].at(n3) - 1.0) > double(1.e-20))
						return (false);
				}
				catch (std::out_of_range o)
				{
					std::cout << o.what() << std::endl;
					return (false);
				}
			}
		}
	}

	return (true);
}

bool test(const double_vec &V)
{
	// short int n[3];
	// const short int D = 3;
	// const short int N[] = {N1, N2, N3};

	std::cout << "here \n\n";

	/*
	//	Either, use concatenation:
	for (int n1 = 0; n1 < N1; n1++)
	{
		for (int n2 = 0; n2 < N2; n2++)
		{
			for (int n3 = 0; n3 < N3; n3++)
			{
				try
				{
					//	Either use concat(...) function:
					n[0] = n1;
					n[1] = n2;
					n[2] = n3;

					if (abs(V[concat(D, N, n)] - 1.0) > double(1.e-20))
						return (false);

					//	Or, simply:
					if (abs(V.at(n3 * (N1 * N2) + n2 * N1 + n1) - 1.0) > double(1.e-20))
						return (false);
				}
				catch (std::out_of_range o)
				{
					std::cout << o.what() << std::endl;
					return (false);
				}
			}
		}
	} */

	//	Or don't concatenate at all:
	for (int i_n = 0; i_n < (N1 * N2 * N3); i_n++)
	{
		try
		{
			if (abs(V.at(i_n) - 1.0) > double(1.e-20))
				return (false);
		}
		catch (std::out_of_range o)
		{
			std::cout << o.what() << std::endl;
			return (false);
		}
	}

	return (true);
}


bool allocate(const char &m)
{
	if (m == 2)
	{
		//  VECTOR METHOD 2
		std::vector<std::vector<double_vec>> V;
		V.reserve(N1);

		for (int n1 = 0; n1 < N1; n1++)
		{
			std::vector<double_vec> tmpVV;
			tmpVV.reserve(N2);

			for (int n2 = 0; n2 < N2; n2++)
			{
				double_vec tmpV(N3, double(1.0));

				tmpVV.push_back(std::move(tmpV));
			}

			V.push_back(std::move(tmpVV));
		}

		return (test(V));
	}
	else if (m == 3)
	{
		//  VECTOR METHOD 3
		std::vector<std::vector<double_vec>> V;
		V.reserve(N1);

		std::vector<double_vec> tmpVV;
		tmpVV.reserve(N2);

		for (int n2 = 0; n2 < N2; n2++)
		{
			double_vec tmpV(N3, double(1.0));
			tmpVV.push_back(std::move(tmpV));
		}

		for (int n1 = 0; n1 < N1; n1++)
		{
			V.push_back(tmpVV);
		}

		return (test(V));
	}
	else if (m == 4)
	{
		//  VECTOR METHOD 4--CONCATINATED VECTOR
		double_vec V;
		V.reserve(N1 * N2 * N3);
		for (int i_n = 0; i_n < (N1 * N2 * N3); i_n++)
		{
			V.push_back(double(1.0));
		}

		return (test(V));
	}
	else
	{
		// POINTER METHOD
		double ***V = new double **[N1];
		for (int n1 = 0; n1 < N1; n1++)
		{
			V[n1] = new double *[N2];
			for (int n2 = 0; n2 < N2; n2++)
			{
				V[n1][n2] = new double[N3];
				for (int n3 = 0; n3 < N3; n3++)
				{
					V[n1][n2][n3] = 1.0;
				}
			}
		}

		bool success = test(V);

		for (int n1 = 0; n1 < N1; n1++)
		{
			for (int n2 = 0; n2 < N2; n2++)
			{
				delete[] V[n1][n2];
			}
			delete[] V[n1];
		}
		delete[] V;

		return (success);
	}

	return (false);
}

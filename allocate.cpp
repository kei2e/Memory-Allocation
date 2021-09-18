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

using double_vec = std::vector<double>;

const int N1 = 1000;
const int N2 = 1000;
const int N3 = 500;

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

bool test(std::vector<std::vector<double_vec>> V)
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

bool allocate(const char &m)
{
	if (m == 1)
	{
		//  VECTOR METHOD 1
		std::vector<std::vector<double_vec>> V;
		V.reserve(N1);
		for (int n1 = 0; n1 < N1; n1++)
		{
			V[n1].reserve(N2);
			for (int n2 = 0; n2 < N2; n2++)
			{
				double_vec tmpV(N3, double(1.0));
				V[n1].push_back(std::move(tmpV));
			}
		}

		return (test(V));
	}
	else if (m == 2)
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

#ifndef VECTOR_H
#define VECTOR_H

class Vec3
{
private:
	double vec[3];

public:
	Vec3(void);									//make a vector default values 0
	Vec3(double a, double b, double c);			//make a vector
	Vec3(float a[3]);							
	explicit Vec3(double *a);
	void setx(double x);						//set x variable of vector
	void sety(double y);						//set y variable of vector
	void setz(double z);						//set z variable of vector
	Vec3 operator+(const Vec3 &v);				//+ operator
	Vec3 operator-(const Vec3 &v);				//- operator
	Vec3 operator*(const double scaler);		//* operator
	Vec3 operator/(const double scaler);		/// operator
	bool operator==(const Vec3 &v);				//== operator
	bool operator!=(const Vec3 &v);				//!= operator
	void operator=(float *a);					//= operator
	double dotProduct(const Vec3 &v);			//dot product
	void crossProduct(const Vec3 &a, const Vec3 &b, Vec3 &c);	//cross product with 2 vectors and 1 output vector
	Vec3 crossProduct(const Vec3 &a);							//cross product with 1 vector
	void negation();							//negations of a vector
	double length();							//find length of vector
	double squaredLength();						//find squared length of vector
	double &operator[](const size_t index);		//[] operator
	void printresults();						//print vector contents
	~Vec3(){};									//deconstructor
};

void Normalize(Vec3 &v);						//normalize a vector
Vec3 operator*(double y, Vec3 x);				//* operator for different equation type
#endif
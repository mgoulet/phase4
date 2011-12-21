////////////////////////////////////////////////
//	Martin Goulet
//	Project: Phase3
//	BS.h
////////////////////////////////////////////////

#ifndef BS_H
#define BS_H

/////////////////////////////////////////////
struct BS
{
public:

	//radius of bounding sphere
	float fRadius;

	//default constructor
	BS();
	//copy constructor
	BS(const BS& bs_ref);
	//parameterized construction
	BS(float fRadius);
	//destructor
	~BS();


};

#endif BS_H
#ifndef _ENCODER_H
#define _ENCODER_H

class Encoder
{
public:
	Encoder();
	virtual ~Encoder();

protected:
	void printError(int err_code);
};

#endif

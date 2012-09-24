#ifndef INCLUDE_navigateplusplus
#define INCLUDE_navigateplusplus

#include "libnavigate/c++/sentence.hpp"

namespace libnavigate
{

NAVI_EXTERN_CLASS(class, Navigate_t)
{
public:
	// returns the number of characters written
	// in case of error throws an exception
	int CreateMessage(const Message_t &msg, char *buffer, int maxsize);

//	// returns the number of characters read
//	// in case of error throws an exception
//	Message_t ParseMessage(char *buffer, int maxsize, int *nmread);
};

}

#endif // INCLUDE_navigateplusplus


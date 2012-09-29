#ifndef INCLUDE_navigateplusplus
#define INCLUDE_navigateplusplus

#include <libnavigate/c++/aam.hpp>
#include <libnavigate/c++/ack.hpp>
#include <libnavigate/c++/alm.hpp>
#include <libnavigate/c++/dtm.hpp>
#include <libnavigate/c++/gbs.hpp>
#include <libnavigate/c++/gga.hpp>
#include <libnavigate/c++/gll.hpp>
#include <libnavigate/c++/gns.hpp>
#include <libnavigate/c++/grs.hpp>
#include <libnavigate/c++/gsa.hpp>
#include <libnavigate/c++/gst.hpp>
#include <libnavigate/c++/gsv.hpp>
#include <libnavigate/c++/mla.hpp>
#include <libnavigate/c++/rmc.hpp>
#include <libnavigate/c++/vtg.hpp>
#include <libnavigate/c++/zda.hpp>

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


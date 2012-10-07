#ifndef INCLUDE_navigateplusplus
#define INCLUDE_navigateplusplus

#include "aam.hpp"
#include "ack.hpp"
#include "alm.hpp"
#include "alr.hpp"
#include "dtm.hpp"
#include "gbs.hpp"
#include "gga.hpp"
#include "gll.hpp"
#include "gns.hpp"
#include "grs.hpp"
#include "gsa.hpp"
#include "gst.hpp"
#include "gsv.hpp"
#include "mla.hpp"
#include "rmc.hpp"
#include "txt.hpp"
#include "vtg.hpp"
#include "zda.hpp"

namespace libnavigate
{

NAVI_EXTERN_CLASS(Navigate_t)
{
public:
	// returns the number of characters written
	// in case of error throws an exception
	size_t CreateMessage(const Message_t &msg, char *buffer, size_t maxsize);

	// returns the parsed message
	// in case of error throws an exception
	Message_t ParseMessage(char *buffer, size_t maxsize, size_t *nmread);
};

}

#endif // INCLUDE_navigateplusplus

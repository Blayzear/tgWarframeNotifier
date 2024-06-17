#include <string>
#include "usersDB.h"

class MessageWrapper{
public:
	std::string onEvent( std::string event, int64_t id );
};
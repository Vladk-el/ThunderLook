#include "meeting.h"

Meeting::Meeting(const Meeting & meeting)
{
    this->_id = meeting._id;
    this->_pos = meeting._pos;
    this->_size = meeting._size;
}

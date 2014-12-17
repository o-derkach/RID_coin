#ifndef USER_H_
#define USER_H_

#include <list>

class User {
	public:
		User();
		virtual ~User();
};

typedef std::list<User> Users;

#endif /* USER_H_ */

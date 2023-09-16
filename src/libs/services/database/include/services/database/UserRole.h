#pragma once
#include <orm/tiny/model.hpp>


#ifndef USERROLES_HPP
#define USERROLES_HPP


using Orm::Tiny::Model;

class UserRole final: public Model<UserRole>{



    friend Model;
    using Model::Model;
private:
    QString u_table {"User_roles"};
    bool u_timestamps = false;
    QString u_primaryKey {"Id"};


};

#endif

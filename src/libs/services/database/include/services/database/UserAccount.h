#pragma once
#include <orm/tiny/model.hpp>


#ifndef UserAccounts_HPP
#define UserAccounts_HPP


using Orm::Tiny::Model;

class UserAccount final: public Model<UserAccount>{

    friend Model;
    using Model::Model;

private:
    QString u_table {"User_accounts"};
    bool u_timestamps = false;
    QString u_primaryKey {"UserId"};


};

#endif

#pragma once

#ifndef UTILS_H
#define UTILS_H

#define VARIABLE_NAME(Variable) (#Variable)

namespace Orm::Tiny{

    struct AttributeItem;

}

namespace Database {

    using TableItem = Orm::Tiny::AttributeItem;

}

#endif // UTILS_H

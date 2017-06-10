//
//  Weapon.cpp
//  forfinal
//
//  Created by Quentin on 04/06/2017.
//
//

#include <stdio.h>
#include "Weapon.h"

//创建默认武器参数
bool Weapon::init(std::string WeaponKind) {
    _weapon = WeaponKind;
    _speed = 1.0f;
    _damage = 2;
    _range = 2;
    return true;
}

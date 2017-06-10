//
//  Weapon.h
//  forfinal
//
//  Created by Quentin on 04/06/2017.
//
//

#ifndef Weapon_h
#define Weapon_h

#include "cocos2d.h"
USING_NS_CC;

class Weapon : public Sprite{
public:
    virtual bool init(std::string WeaponKind);
    
    std::string _weapon;
    float _speed;
    int _damage;
    int _range;    
};
#endif /* Weapon_h */

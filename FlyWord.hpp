//
//  FlyWord.hpp
//  FinalProject
//
//  Created by Logan luo on 2017/6/15.
//
//
/*
#ifndef FlyWord_hpp
#define FlyWord_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;
class FlyWord: public CCNode{
public:
    static FlyWord* create(const char *word,const int fontSize,CCPoint begin);
   
    bool init(const char *word,const int fontSize,CCPoint begin);

    void Flying();

    void Flyend();
    
    
private:
    int _fontSize;
    Point _begin;
    LabelTTF* m_plabel;
    
};
#endif /* FlyWord_hpp */

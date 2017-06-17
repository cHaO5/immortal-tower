#include "GameManager.h"
#include "iostream"

GameManager* GameManager::instance;

GameManager* GameManager::getInstance()
{
	if (instance == NULL)
		instance = new GameManager();//由于instance是static每次new都是同一个，相当于创造了一个单例
	return instance;
}

void GameManager::loadMap(int level)
{
    rapidjson::Document loadMap;
    ssize_t size = 0;
    unsigned char *pBytes = NULL;
    switch (level) {
        case 0:
            pBytes = cocos2d::FileUtils::sharedFileUtils()->getFileData("map1.json", "r", &size);
            break;
        case 1:
            pBytes = cocos2d::FileUtils::sharedFileUtils()->getFileData("map2.json", "r", &size);
            break;
        case 2:
            pBytes = cocos2d::FileUtils::sharedFileUtils()->getFileData("map3.json", "r", &size);
            break;
        default:
            break;
    }
    //CC_BREAK_IF(pBytes == NULL || strcmp((char*)pBytes, "") == 0);
    
    log("111111");
    std::string load_m((const char*)pBytes, size);
    //CC_SAFE_DELETE_ARRAY(pBytes);
    loadMap.Parse<0>(load_m.c_str());
    CCLOG("Error%u", loadMap.GetParseError());
    const rapidjson::Value &monster = loadMap["map"];
    log("222222");
    //log("%d", pArray.GetInt());
    for (int l = 0; l < loadMap["map"].Size(); l++)
    {
        for (int n = 0; n < loadMap["map"][l].Size(); n++)
        {
           LevelLogicMap[level][l][n] = loadMap["map"][l][n].GetInt();
        }
    }
    return;
}
//void GameManager::initWIthJsonFile(const char* filename)
//{
    //reloadGameData = FileUtils::getInstance()->getStringFromFile(filename);
//}
void GameManager::loadGame()
{
    rapidjson::Document load;
    //bool bRet = false;
    ssize_t size = 0;
    unsigned char *pBytes = NULL;
    //string *pBytes = NULL;
    pBytes = cocos2d::FileUtils::sharedFileUtils()->getFileData("hero.json", "r", &size);
    //CC_BREAK_IF(pBytes == NULL || strcmp((char*)pBytes, "") == 0);
    
    //log("111111");
    std::string load_str((const char*)pBytes, size);
    //CC_SAFE_DELETE_ARRAY(pBytes);
    load.Parse<0>(load_str.c_str());
//    CCLOG("Error%u", _doc.GetParseError());
//    //生成json文档对像
//    
//    if(!_doc.IsObject())
//        CCLOG("NoObject");
//    log("222222");
//    
//    //是否有此成员
//    if(!_doc.HasMember("map"))
//        CCLOG("Nomember");
//    
    const rapidjson::Value &pArray = load["hero"];
    
    //log("%d", pArray.GetInt());
    if (pArray.IsArray()) {
        for (int i = 0; i < pArray.Size(); ++i) {
            log("333333");
            Player_type[i] = pArray[i]["heroName"].GetInt();
            Player_life[i] = pArray[i]["heroBlood"].GetDouble();
            Player_speed[i] = pArray[i]["heroSpeed"].GetInt();
        }
    }
    
    
    rapidjson::Document loadWeapon;
    pBytes = cocos2d::FileUtils::sharedFileUtils()->getFileData("weapon.json", "r", &size);
    //CC_BREAK_IF(pBytes == NULL || strcmp((char*)pBytes, "") == 0);
    
    log("111111");
    std::string load_w((const char*)pBytes, size);
    //CC_SAFE_DELETE_ARRAY(pBytes);
    loadWeapon.Parse<0>(load_w.c_str());
    CCLOG("Error%u", loadWeapon.GetParseError());
    const rapidjson::Value &weapon = loadWeapon["weapon"];
    log("222222");
    //log("%d", pArray.GetInt());
    if (weapon.IsArray()) {
        log("333333");
        for (int i = 0; i < weapon.Size(); ++i) {
            Weapon_type[i] = weapon[i]["weaponType"].GetInt();
            Weapon_range[i] = weapon[i]["weaponRange"].GetInt();
            Weapon_damage[i] = weapon[i]["weaponDamage"].GetInt();//小怪的血以次记
            Weapon_speed[i] = weapon[i]["weaponSpeed"].GetDouble();//目前不能随便换
            Weapon_texture[i]= weapon[i]["weaponTexture"].GetString();
        }
    }
    
    rapidjson::Document loadM;
    pBytes = cocos2d::FileUtils::sharedFileUtils()->getFileData("monster.json", "r", &size);
    //CC_BREAK_IF(pBytes == NULL || strcmp((char*)pBytes, "") == 0);
    
    log("111111");
    std::string load_m((const char*)pBytes, size);
    //CC_SAFE_DELETE_ARRAY(pBytes);
    loadM.Parse<0>(load_m.c_str());
    CCLOG("Error%u", loadM.GetParseError());
    const rapidjson::Value &monster = loadM["monster"];
    log("222222");
    //log("%d", pArray.GetInt());
    if (monster.IsArray()) {
        log("333333");
        for (int i = 0; i < monster.Size(); ++i) {
            Monster_type[i] = monster[i]["monsterType"].GetInt();
            Monster_life[i] = monster[i]["monsterBlood"].GetInt();
            Monster_damage[i] = monster[i]["monsterDamage"].GetInt();//小怪的血以次记
            Monster_speed[i] = monster[i]["monsterSpeed"].GetDouble();//目前不能随便换
            //Monster_texture[i]= weapon[i]["monsterTexture"].GetString();
        }
    }

    for (int i = 0; i < 3; ++i) {
        log("44444");
        loadMap(i);
    }
    log("%d", Weapon_type[1]);
    log("%d", Weapon_range[1]);
    log("%f", Weapon_speed[1]);
    
    currentPlayerState_type = Player_type[0]+1;
    currentPlayerState_life = Player_life[0];
    currentPlayerState_speed = Player_speed[0]+1;
    //UserDefault::getInstance()->getIntegerForKey("PlayerPositionX", 0);
    //UserDefault::getInstance()->getIntegerForKey("playerPositionY", 0);
    currentWeaponType = Weapon_type[0];
    currentWeaponSpeed = Weapon_speed[0];
    currentWeaponDamage = Weapon_damage[0];
    currentWeaponRange = Weapon_range[0];
    return;

}
//void GameManager::reLoadGame(int archive)
//{
//    //UserDefault::getInstance()->getIntegerForKey("map", 0);
//    //UserDefault::getInstance()->getBoolForKey("musicOn", true);
//    //UserDefault::getInstance()->getBoolForKey("effectOn", true);
//    currentPlayerState_type = UserDefault::getInstance()->getIntegerForKey("playerType");
//    currentPlayerState_life = UserDefault::getInstance()->getFloatForKey("playerBlood");
//    currentPlayerState_speed = UserDefault::getInstance()->getIntegerForKey("playerSpeed");
//    //UserDefault::getInstance()->getIntegerForKey("PlayerPositionX", 0);
//    //UserDefault::getInstance()->getIntegerForKey("playerPositionY", 0);
//    currentWeaponType = UserDefault::getInstance()->getIntegerForKey("weaponType");
//    currentWeaponSpeed = UserDefault::getInstance()->getIntegerForKey("weaponSpeed");
//    currentWeaponDamage = UserDefault::getInstance()->getIntegerForKey("weaponDamage");
//    currentWeaponRange = UserDefault::getInstance()->getIntegerForKey("weaponRange");
//    //UserDefault::getInstance()->getIntegerForKey("monsterKilled", 0);
//    //UserDefault::getInstance()->getIntegerForKey("monsterOnMap", 0);
//    
//    log("%d", currentPlayerState_type);
//        log("%f", currentPlayerState_life);
//        log("%d", currentPlayerState_speed);
//        log("%d", currentWeaponType);//player's weapontype
//        log("%d", currentWeaponDamage);
//        log("%d", currentWeaponSpeed);
//        log("%d", currentWeaponRange);
//
//}
//
//void GameManager::saveData(int archive)
//{
//    UserDefault::getInstance()->setIntegerForKey("map", 0);
//    UserDefault::getInstance()->setBoolForKey("musicOn", true);
//    UserDefault::getInstance()->setBoolForKey("effectOn", true);
//    UserDefault::getInstance()->setIntegerForKey("playerType", currentPlayerState_type);
//    UserDefault::getInstance()->setFloatForKey("playerBlood", currentPlayerState_life);
//    UserDefault::getInstance()->setIntegerForKey("playerSpeed", currentPlayerState_speed);
//    UserDefault::getInstance()->setIntegerForKey("PlayerPositionX", 0);
//    UserDefault::getInstance()->setIntegerForKey("playerPositionY", 0);
//    UserDefault::getInstance()->setIntegerForKey("weaponType", currentWeaponType);
//    UserDefault::getInstance()->setIntegerForKey("weaponSpeed", currentWeaponSpeed);
//    UserDefault::getInstance()->setIntegerForKey("weaponDamage", currentWeaponDamage);
//    UserDefault::getInstance()->setIntegerForKey("weaponRange", currentWeaponRange);
//    UserDefault::getInstance()->setIntegerForKey("monsterKilled", 0);
//    UserDefault::getInstance()->setIntegerForKey("monsterOnMap", 0);
//    UserDefault::getInstance()->flush();
//}
void GameManager::reLoadGame(int archive)
{
    //可以用
    rapidjson::Document _doc;
    //bool bRet = false;
    ssize_t size = 0;
    unsigned char *pBytes = NULL;
    string Bytes;
    //string *pBytes = NULL;
    Bytes = cocos2d::FileUtils::getInstance()->getWritablePath();
    switch (archive) {
        case 0:
            Bytes.append("archive0.json");
            break;
        case 1:
            Bytes.append("archive1.json");
            break;
        case 2:
            Bytes.append("archive2.json");
            break;
        default:
            break;
    }
    //pBytes = cocos2d::FileUtils::sharedFileUtils()->getFileData("archive2.json", "r", &size);
    //CC_BREAK_IF(pBytes == NULL || strcmp((char*)pBytes, "") == 0);
    
    log("111111");
    
    unsigned char* titlech = FileUtils::getInstance()->getFileData(Bytes, "r", &size);
    string load_str = std::string((const char*)titlech,size);
    //std::cout << Bytes << std::endl;
    //std::string load_str((const char*)pBytes, size);
    CC_SAFE_DELETE_ARRAY(pBytes);
    //_doc.Parse<0>(load_str.c_str());
    _doc.Parse<0>(load_str.c_str());
    CCLOG("Error%u", _doc.GetParseError());
    //生成json文档对像

    if(!_doc.IsObject())
        CCLOG("NoObject");
    log("222222");

    //是否有此成员
    if(!_doc.HasMember("playerType"))
        CCLOG("Nomember");

    //rapidjson::Value &pArray = _doc["map"];
    log("333333");
    
    //log("%d", pArray.GetInt());
    
    currentPlayerState_type = _doc["playerType"].GetInt();
    currentPlayerState_life = _doc["playerBlood"].GetDouble();
    currentPlayerState_speed = _doc["playerSpeed"].GetInt();
    currentWeaponType = _doc["weaponType"].GetInt();//player's weapontype
    currentWeaponDamage = _doc["weaponDamage"].GetInt();
    currentWeaponSpeed = _doc["weaponSpeed"].GetInt();
    currentWeaponRange = _doc["weaponRange"].GetInt();
    
    log("archive");
    log("%d", currentPlayerState_type);
    log("%f", currentPlayerState_life);
    log("%d", currentPlayerState_speed);
    log("%d", currentWeaponType);//player's weapontype
    log("%d", currentWeaponDamage);
    log("%d", currentWeaponSpeed);
    log("%d", currentWeaponRange);
    /////////////////设置内容和monster的死亡信息以及人物坐标还没有导入
    return;
}

void GameManager::saveData(int archive)
{
    //*** 生成 json 文件，存储在 getWritablePath 文件夹下 ***
    rapidjson::Document writedoc;
    writedoc.SetObject();
    rapidjson::Document::AllocatorType& allocator = writedoc.GetAllocator();
//    rapidjson::Value array(rapidjson::kArrayType);
//    rapidjson::Value object(rapidjson::kObjectType);
    
    // json object 格式添加 “名称/值” 对
    writedoc.AddMember("playerType", currentPlayerState_type, allocator);
    writedoc.AddMember("playerBlood", currentPlayerState_life, allocator);
    writedoc.AddMember("playerSpeed", currentPlayerState_speed, allocator);
    writedoc.AddMember("weaponType", currentWeaponType, allocator);
    writedoc.AddMember("weaponDamage", currentWeaponDamage, allocator);
    writedoc.AddMember("weaponSpeed", currentWeaponSpeed, allocator);
    writedoc.AddMember("weaponRange", currentWeaponRange+1888, allocator);
    
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    writedoc.Accept(writer);
    
//    FileUtils::getInstance()->addSearchPath("json");
//    string filePath1 = FileUtils::getInstance()->getDefaultResourceRootPath("archive3.json");
//    string filePath = FileUtils::getInstance()->getWritablePath();
    string filePath = FileUtils::getInstance()->getWritablePath();
    //string filePath = "./Resources/archive4.json";
    std:cout << filePath << std::endl;
    //CCLOG("%s", filePath);
    switch (archive) {
        case 0:
            filePath.append("archive0.json");
            break;
        case 1:
            filePath.append("archive1.json");
            break;
        case 2:
            filePath.append("archive2.json");
            break;
        default:
            break;
    }
    //filePath.append("archive3.json");
    FILE* fp = fopen(FileUtils::getInstance()->fullPathForFilename(filePath).c_str(),"w+");//具有读写属性，写的时候如果文件存在，会被清空，从头开始写。
    //FILE* fp = fopen(filePath.c_str(),"w+");//具有读写属性，写的时候如果文件存在，会被清空，从头开始写。

    if (!fp)
    {
        CCASSERT(fp,"file open faild!");
        //return false;
    }
    fwrite(buffer.GetString(),sizeof(char),buffer.GetSize(),fp);
    fclose(fp);
    
    CCLOG("%s %s ---> %s", __FUNCTION__, filePath.c_str(), buffer.GetString());
    return;
}

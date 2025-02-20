#ifndef IAPP_H
#define IAPP_H

#define PUBLIC
#define PRIVATE
#define PROTECTED
#define STATIC
#define VIRTUAL
#define CONSTRUCTER

class IScene;
class IScene;
class ISprite;
class IGraphics;
class IInput;
class IAudio;
class IINI;

#include <Utils/Standard.h>
#include <Engine/IGraphics.h>
#include <Engine/IAchievement.h>
#include <Engine/IInput.h>
#include <Engine/IAudio.h>
#include <Engine/IScene.h>
#include <Engine/IMath.h>
#include <Engine/IINI.h>

class IApp {
public:
    IScene* Scene = NULL;
    IScene* NextScene = NULL;
    ISprite* NullSprite = NULL;
    IGraphics* G = NULL;
    IInput* Input = NULL;
    IAudio* Audio = NULL;
    IINI* Settings = NULL;
    IAchievement* Achievements = NULL;
    float FPS = 60.f;
    bool Running = false;
    int WIDTH = 424;
    int HEIGHT = 240;
    int SCALE = 1;
    //0 LETTERBOX
    //1 WS
    //2 18:9
    //3 UWS
    //4 NTSCGEN
    //5 GENWS
    int AspectRatio;
    const bool DEBUG = true;
    const bool DEV = true;
    bool viewObjectCollision = false;
    uint32_t MetricUpdateTime = -1;
    uint32_t MetricRenderTime = -1;
    bool UnlockedFramerate = false;
    static Platforms Platform; //
    static bool Mobile;
    static IApp* GlobalApp;
    //DEV MENU
    bool DevMenuEnabled;
    bool DevMenuActive = false;
    Uint32 DevMenuColour = 0x000084;
    Uint8 DevMenuSelected = 0;
    Uint8 DevMenuCurMenu = 0;
    Uint8 DevMenuFlagA = 0;
    Uint8 DevMenuFlagB = 0;
    Uint8 DevMenuFlagC = 0;
    Uint8 Major = 0;
    Uint8 Minor = 0;
    short Build = 1;
    char VersionString[10];
    char Title[256];
    char Categories[0xFF][0x20];
    char Levels[0xFF][0xFF][0x04];
    int ActCount[0xFF][0xFF];
    int CategoryCount = 0;
    int LevelCount[0xFF];
    int isSharp = 1;

    IApp();
    void LoadSettings();
    void OnEvent(Uint32 event);
    void ExecuteCommand(char* cmd);
    void Run();
    void Cleanup();
    static const char* Format(const char* string, ...);
    static void Print(int sev, const char* string, ...);
};

#endif /* IAPP_H */

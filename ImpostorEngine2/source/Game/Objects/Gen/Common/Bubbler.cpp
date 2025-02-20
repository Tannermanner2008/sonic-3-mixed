// Object ID: 0x54
// Object Name: Bubbler.cpp

#include "Bubbler.h"

typedef IMath Math;

void Bubbler::Create() {
    Object::Create();
    this->W = 16;
    this->H = 32;
    this->Active = true;
    this->Priority = false;
    Sprite = LevelScene::LoadSpriteFromBin("Global/Water.bin", SaveGame::CurrentMode);
    this->Frame = 0;
    this->CurrentAnimation = 2;
    this->Sprite = Scene->WaterSprite;
    UnkFlag = (SubType & 0x80) == 0x80;
    UnkValue = SubType & 0x7F;
    AutoAnimate = true;
    Timer = 1;
    SubTimer = 1;
    BubblesToMake = 1;
}

void Bubbler::Update() {
    if (Y < Scene->WaterLevel) {
        Active = false;
        return;
    }

    if (Timer > 0) {
        Timer--;
        if (Timer == 0) {
            Timer = Math::randRange(0x00, 0x7F) + 0x80;
            BubblesToMake = Math::randRange(1, 6);
            SubTimer = Math::randRange(0x01, 0x1F);
        }

    }

    if (BubblesToMake > 0) {
        if (SubTimer > 0) {
            SubTimer--;
            if (SubTimer == 0) {
                SubTimer = Math::randRange(0x01, 0x1F);
                Scene->AddNewObject(Obj_BubbleAir, 0, X + Math::randRange(-8, 8), Y, false, false);
                BubblesToMake--;
            }

        }

    }

    Object::Update();
}


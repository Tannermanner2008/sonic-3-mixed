// Object ID: 0xFFFFFFFF
// Object Name: MonkeyDudeCoconut.cpp

#include "MonkeyDudeCoconut.h"

typedef IMath Math;

void MonkeyDudeCoconut::Create() {
    Enemy::Create();
    Active = true;
    Priority = true;
    W = 16;
    H = 16;
    Sprite = LevelScene::LoadSpriteFromBin("AIZ/Monkey Dude.bin", SaveGame::CurrentMode);
    Invincible = true;
    BounceOffShield = true;
    VisualLayer = 1;
}

void MonkeyDudeCoconut::Update() {
    YSpeed += 0x38;
    SubX += XSpeed << 8;
    SubY += YSpeed << 8;
    if (!OnScreen) {
        X = -16;
        Y = -16;
        XSpeed = 0;
        YSpeed = 0;
    }

    Object::Update();
}

void MonkeyDudeCoconut::Render(int CamX, int CamY) {
    if (DrawCollisions) {
        G->SetDrawAlpha(0x80);
        G->DrawRectangle(X - CamX, Y - CamY, W, H, DrawCollisionsColor);
        G->SetDrawAlpha(0xFF);
    }

    G->DrawSprite(Sprite, CurrentAnimation, 6, X - CamX, Y - CamY, 0, IE_NOFLIP);
    }


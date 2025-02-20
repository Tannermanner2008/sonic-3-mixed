// Object ID: 0x97
// Object Name: MegaChomper.cpp

#include "MegaChomper.h"

typedef IMath Math;

void MegaChomper::Create() {
    Enemy::Create();
    Active = true;
    Priority = false;
    W = 16;
    H = 16;
    Sprite = LevelScene::LoadSpriteFromBin("HCZ/MegaChomper.bin", SaveGame::CurrentMode);
    CurrentAnimation = Sprite->FindAnimation("Main");
    Flip = 1;
    if (FlipX) Flip = -1;

    HitCount = 1;
    Routine = 2;
    MaximumSpeed = 0x200;
    Acceleration = 0x8;
    SubX = X << 16;
    SubY = Y << 16;
    StuckX = 0;
    VisualLayer = 1;
    Harmful = false;
    LRTimer = 100;
    LRAmount = 0;
}

int MegaChomper::OnHit() {
    return OnDeath();
}

void MegaChomper::Update() {
    if (X > Scene->Player->EZX - 10 && X < Scene->Player->EZX + 10 && Y > Scene->Player->EZY - 16 && Y < Scene->Player->EZY + 16 && Routine < 6) {
        StuckX = X - (Scene->Player->EZX);
        Invincible = true;
        Routine = 6;
    }

    if (!Scene->maxLayer && Routine == 6) {
        Routine = 8;
        XSpeed = 0x200;
        YSpeed = -0x400;
        Scene->Player->InputLockLeftRight = false;
    }

    if (Routine == 6) {
        LRTimer = LRTimer == 0 ? 0 : LRTimer - 1;
        if (LRTimer == 0) {
            LRAmount = 0;
        }

        if (LastFlip != Scene->Player->DisplayFlip) {
            LRTimer = 100;
            LRAmount += 1;
            LastFlip = Scene->Player->DisplayFlip;
        }

    }

    if (Routine == 2 && Scene->Player->Action != ActionType::Dead) {
        if (Scene->Player->EZX < X) {
            if (XSpeed > -MaximumSpeed) XSpeed -= Acceleration;

        }
        else {
            if (XSpeed < MaximumSpeed) XSpeed += Acceleration;

        }
        if (XSpeed < 0) Flip = -1;
        else if (XSpeed > 0) Flip = 1;

        if (Scene->Player->EZY < Y) {
            YSpeed = -0x24;
        }
        else if (Scene->Player->EZY > Y) {
            YSpeed = 0x24;
        }

        if (Y <= Scene->WaterLevel + 8) {
            Routine = 4;
            if (Scene->Player->EZX < X) {
                XSpeed = -0x200;
                Flip = -1;
            }
            else {
                XSpeed = 0x200;
                Flip = 1;
            }
            YSpeed = -0x400;
        }

    }
    else if (Routine == 4) {
        if (YSpeed < 0 || Y <= Scene->WaterLevel + 8) {
            YSpeed += 0x20;
        }

        if (Y > Scene->WaterLevel + 8) Routine = 2;

    }
    else if (Routine == 6 && Scene->Player->Action != ActionType::Dead) {
        XSpeed = 0;
        YSpeed = 0;
        if (Scene->Player->EZX < X) Flip = -1;
        else Flip = 1;
        if (Scene->Player->DisplayFlip < 0) SubX = (Scene->Player->EZX - StuckX) << 16;
        else SubX = (Scene->Player->EZX + StuckX) << 16;
        SubY = (Scene->Player->EZY - 16) << 16;
        if (Y < Scene->WaterLevel) {
            Routine = 8;
            XSpeed = 0x200;
            YSpeed = -0x400;
            Scene->Player->InputLockLeftRight = false;
        }

        if (LRAmount > 6) {
            Routine = 8;
            XSpeed = 0x200;
            YSpeed = -0x400;
            Scene->Player->InputLockLeftRight = false;
        }

        if (Scene->Frame % 60 == 0) {
            Scene->Player->InputLockLeftRight = true;
            if (Scene->Player->Rings > 0) {
                Scene->Player->Rings -= 1;
                Sound::Play(Sound::SFX_RING);
            }
            else {
                Scene->Player->Die(false);
                Routine = 8;
                XSpeed = 0x200;
                YSpeed = -0x400;
                Scene->Player->InputLockLeftRight = false;
            }
        }

    }
    else if (Routine == 8) {
        YSpeed += 0x20;
    }

    SubX += XSpeed << 8;
    SubY += YSpeed << 8;
    if (Routine < 6) Frame = (Scene->Frame % 6) << 8;
    else Frame = (Scene->Frame % 12) << 8;
    X = SubX >> 16;
    Y = SubY >> 16;
    Object::Update();
}

void MegaChomper::Render(int CamX, int CamY) {
    G->DrawSprite(Sprite, CurrentAnimation, Frame >> 8, X - CamX, Y - CamY, 0, Flip < 0 ? IE_NOFLIP : IE_FLIPX);
    if (App->viewObjectCollision) {
        G->SetDrawAlpha(0x80);
        G->DrawRectangle(X - (W / 2) - CamX, Y - (H / 2) - CamY, W, H, DrawCollisionsColor);
        G->SetDrawAlpha(0xFF);
    }

    }


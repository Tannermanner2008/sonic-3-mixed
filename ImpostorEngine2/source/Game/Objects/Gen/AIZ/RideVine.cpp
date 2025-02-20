// Object ID: 0x06
// Object Name: RideVine.cpp

#include "RideVine.h"

typedef IMath Math;

void RideVine::Create() {
    Object::Create();
    Active = true;
    Priority = false;
    RopeLength = 4;
    AngleOffset = 0;
    Oscello = 0;
    VisW = RopeLength << 4;
    VisH = RopeLength << 4;
    LastX = X;
    LastY = Y;
    BaseX = InitialX;
    BaseY = InitialY;
    EndX = InitialX + ((SubType & 0x7F) << 4);
    Fireable = SubType >> 7;
    OnFire = false;
    ZipActive = false;
    Spinning = false;
    PlayersControlled = 0;
    Amp = 4;
    ClassicStyle = !Scene->Thremixed;
    ClassicStyle = false;
    VisualLayer = 0;
    Timer = 0;
    Sprite = LevelScene::LoadSpriteFromBin("AIZ/Ride Vine.bin", SaveGame::CurrentMode);
    CurrentAnimation = Sprite->FindAnimation("Ride Vine");
}

int RideVine::OnLeaveScreen() {
    Create();
    return 1;
}

void RideVine::Update() {
    int nX;
    int nY;
    int framedAngle;
    int frame;
    if (PlayersControlled > 0 && !ZipActive) {
        ZipActive = true;
        Oscello = 0;
    }

    if (ZipActive) {
        if (BaseX < EndX) {
            BaseX += 8;
            BaseY += 2;
            VisualLayer = 1;
            Oscello = (Oscello + 0x100) & 0xFFFF;
        }
        else {
            if (Fireable) {
                BaseX += 8;
                if (!OnFire) {
                    OnFire = true;
                    YSpeed = 0x38;
                    BaseY = BaseY << 8;
                    for (int i = 0; i < 8; i++)
{
                        if (PlayersControlled & (1 << i)) {
                            if (!Scene->Players[i]->OnScreen) {
                                Scene->Players[i]->ObjectControlled = 0;
                                PlayersControlled &= (1 << i) ^ 0xFF;
                            }

                            if (Scene->Players[i]->Action == ActionType::Dead) {
                                Scene->Players[i]->ObjectControlled = 0;
                                PlayersControlled &= (1 << i) ^ 0xFF;
                                continue;
                            }

                            Scene->Players[i]->XSpeed = 0x300;
                            Scene->Players[i]->YSpeed = 0x200;
                            Scene->Players[i]->ObjectControlled = 0;
                            Scene->Players[i]->Action = ActionType::Normal;
                            Scene->Players[i]->Ground = false;
                            Scene->Players[i]->Angle = 0;
                            PlayersControlled &= (1 << i) ^ 0xFF;
                        }

                    }
                }

            }
            else {
                if (!Spinning) {
                    Oscello = 0;
                }

                Spinning = true;
                Oscello = (Oscello + 0x10000 - 0x200) & 0xFFFF;
            }
        }
        Amp = -8;
    }
    else {
        Amp = -4;
        Oscello = (Oscello + 0x200) & 0xFFFF;
    }
    nX = BaseX;
    nY = BaseY;
    if (OnFire) {
        YSpeed += 0x38;
        BaseY += YSpeed;
        nY = BaseY >> 8;
    }

    Rotation = Math::sinHex(Oscello >> 8) * Amp;
    if (Spinning) {
        Rotation = (Oscello << 9);
    }

    framedAngle = Rotation;
    if (Spinning) {
        framedAngle = 0;
    }

    if (ClassicStyle) {
        frame = ((Rotation >> 16) + 4 * Math::sign(Rotation)) / 8;
        for (int i = 0; i < RopeLength; i++)
{
            nX += Math::sinHex((frame & 0x1F) * 8) >> 12;
            nY += Math::cosHex((frame & 0x1F) * 8) >> 12;
            Rotation = Rotation + framedAngle;
            frame = ((Rotation >> 16) + 4 * Math::sign(Rotation)) / 8;
        }
    }
    else {
        frame = Rotation / 0x10000;
        for (int i = 0; i < RopeLength; i++)
{
            nX += Math::sinHex(frame) / 0x1000;
            nY += Math::cosHex(frame) / 0x1000;
            Rotation = Rotation + framedAngle;
            frame = Rotation / 0x10000;
        }
    }
    if (Math::abs(X - nX) > 0) {
        LastX = X;
    }

    if (Math::abs(Y - nY) > 0) {
        LastY = Y;
    }

    X = nX;
    Y = nY;
    for (int i = 0; i < 8 && !OnFire; i++)
{
        if (PlayersControlled & (1 << i)) {
            if (!Scene->Players[i]->OnScreen) {
                Scene->Players[i]->ObjectControlled = 0;
                PlayersControlled &= (1 << i) ^ 0xFF;
                Timer = 60;
            }

            if (Scene->Players[i]->Action == ActionType::Dead) {
                Scene->Players[i]->ObjectControlled = 0;
                PlayersControlled &= (1 << i) ^ 0xFF;
                Timer = 60;
                continue;
            }

            if (Scene->Players[i]->InputJump) {
                Scene->Players[i]->XSpeed = (X - LastX) * 0x80;
                Scene->Players[i]->YSpeed = (Y - LastY) * 0x80;
                if (Scene->Players[i]->InputLeft) Scene->Players[i]->XSpeed = -0x200;

                if (Scene->Players[i]->InputRight) Scene->Players[i]->XSpeed = 0x200;

                Scene->Players[i]->YSpeed -= 0x380;
                Scene->Players[i]->ObjectControlled = 0;
                Scene->Players[i]->Action = ActionType::Jumping;
                Scene->Players[i]->JumpVariable = 1;
                Scene->Players[i]->Angle = 0;
                PlayersControlled &= (1 << i) ^ 0xFF;
                Timer = 60;
            }
            else {
                Scene->Players[i]->EZX = X;
                Scene->Players[i]->EZY = Y - 3 + Scene->Players[i]->H / 2;
                Scene->Players[i]->XSpeed = 0;
                Scene->Players[i]->YSpeed = 0;
                Scene->Players[i]->Action = ActionType::Grab;
                Scene->Players[i]->ObjectControlled = 0xFF;
                Scene->Players[i]->GrabSwingValue = ((-framedAngle / 8 + 0x58000) / 0xB) >> 8;
                if (Scene->Players[i]->GrabSwingValue == 0x100) Scene->Players[i]->GrabSwingValue = 0XFF;

                if (Spinning) {
                    Scene->Players[i]->EZX = X + ((Math::sinHex((Rotation / 0x10000) & 0xFF) * (-3 + Scene->Players[i]->H / 2)) >> 16);
                    Scene->Players[i]->EZY = Y + ((Math::cosHex((Rotation / 0x10000) & 0xFF) * (-3 + Scene->Players[i]->H / 2)) >> 16);
                    Scene->Players[i]->Angle = (Rotation / 0x10000) & 0xFF;
                    Scene->Players[i]->DisplayAngle = Scene->Players[i]->Angle << 8;
                    Scene->Players[i]->GrabSwingValue = 0;
                }

            }
        }

    }
    if (Timer > 0) {
        Timer--;
    }

    Object::Update();
}

void RideVine::Render(int CamX, int CamY) {
    int nX;
    int nY;
    int framedAngle;
    nX = BaseX;
    nY = BaseY;
    if (OnFire) {
        nY = BaseY >> 8;
    }

    if (OnFire) {
        G->DrawSprite(Sprite, 2, (Scene->Frame >> 2) & 3, BaseX - CamX, nY - CamY, 0, IE_NOFLIP);
    }
    else {
        G->DrawSprite(Sprite, CurrentAnimation, 0x21, BaseX - CamX, nY - CamY, 0, IE_NOFLIP);
    }
    Rotation = Math::sinHex(Oscello >> 8) * Amp;
    if (Spinning) {
        Rotation = (Oscello << 9);
    }

    if (ClassicStyle) {
        if (Rotation < 0) {
            framedAngle = Rotation;
            if (Spinning) {
                framedAngle = 0;
            }

            Frame = ((Rotation >> 16) - 4) / 8;
            G->DrawSprite(Sprite, CurrentAnimation, Frame & 0x1F, nX - CamX, nY - CamY, 0, IE_NOFLIP);
            for (int i = 0; i < RopeLength - 1; i++)
{
                nX += Math::sinHex((Frame & 0x1F) * 8) >> 12;
                nY += Math::cosHex((Frame & 0x1F) * 8) >> 12;
                Rotation = Rotation + framedAngle;
                Frame = ((Rotation >> 16) - 4) / 8;
                G->DrawSprite(Sprite, CurrentAnimation, Frame & 0x1F, nX - CamX, nY - CamY, 0, IE_NOFLIP);
            }
        }
        else {
            framedAngle = Rotation;
            if (Spinning) {
                framedAngle = 0;
            }

            Frame = ((Rotation >> 16) + 4) / 8;
            G->DrawSprite(Sprite, CurrentAnimation, Frame & 0x1F, nX - CamX, nY - CamY, 0, IE_NOFLIP);
            for (int i = 0; i < RopeLength - 1; i++)
{
                nX += Math::sinHex((Frame & 0x1F) * 8) >> 12;
                nY += Math::cosHex((Frame & 0x1F) * 8) >> 12;
                Rotation = Rotation + framedAngle;
                Frame = ((Rotation >> 16) + 4) / 8;
                G->DrawSprite(Sprite, CurrentAnimation, Frame & 0x1F, nX - CamX, nY - CamY, 0, IE_NOFLIP);
            }
        }
    }
    else {
        framedAngle = Rotation;
        if (Spinning) {
            framedAngle = 0;
        }

        Frame = Rotation / 0x10000;
        G->DrawSprite(Sprite, CurrentAnimation, (Frame / 8) & 0x1F, nX - CamX, nY - CamY, Frame - ((Frame / 8) * 8), IE_NOFLIP);
        for (int i = 0; i < RopeLength - 1; i++)
{
            nX += Math::sinHex(Frame) / 0x1000;
            nY += Math::cosHex(Frame) / 0x1000;
            Rotation = Rotation + framedAngle;
            Frame = Rotation / 0x10000;
            G->DrawSprite(Sprite, CurrentAnimation, (Frame / 8) & 0x1F, nX - CamX, nY - CamY, Frame - ((Frame / 8) * 8), IE_NOFLIP);
        }
    }
    if (!Spinning) {
        G->DrawSprite(Sprite, CurrentAnimation, 0x20, X - CamX, Y - CamY, 0, IE_NOFLIP);
    }
    else {
        G->DrawSprite(Sprite, CurrentAnimation, 0x20, X - CamX, Y - CamY, Rotation / 0x10000, IE_NOFLIP);
    }
    if (DrawCollisions) {
        G->SetDrawAlpha(0x80);
        G->DrawRectangle(X - (W / 2) - CamX, Y - (H / 2) - CamY, W, H, DrawCollisionsColor);
        G->SetDrawAlpha(0xFF);
    }

    }

int RideVine::OnCollisionWithPlayer(int PlayerID, int HitFrom, int Data) {
    if (Timer == 0 && !(PlayersControlled & (1 << PlayerID))) {
        PlayersControlled |= 1 << PlayerID;
        Sound::Play(Sound::SFX_GRAB);
    }

    return 1;
}


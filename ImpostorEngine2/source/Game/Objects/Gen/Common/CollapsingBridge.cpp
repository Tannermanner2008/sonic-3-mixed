// Object ID: 0x0F
// Object Name: CollapsingBridge.cpp

#include "CollapsingBridge.h"

typedef IMath Math;

void CollapsingBridge::Create() {
    Object::Create();
    this->Active = true;
    this->Priority = false;
    this->DoDeform = true;
    this->W = 96;
    this->H = 64;
    f = -1;
    Allotted = 60 * 5;
    Separation = 2;
    Sections = 8;
    Vsect = 2;
    Reset = false;
    SolidTop = true;
    SolidCustomized = true;
    Scene->AddSelfToRegistry(this, "Solid");
    UseTrigger = (SubType & 0x80) == 0x80;
    BridgeType = SubType >> 4 & 0x7;
    if (UseTrigger) TriggerID = SubType & 0xF;
    else Delay = SubType & 0xF;
    Allotted = Delay * 16 + 8;
    switch (Scene->ZoneID) {
        case 1:
        W = 120;
        H = 0x40;
        break;
        case 2:
        W = 0x40;
        H = 0x10;
        VisualLayer = 1;
        break;
        case 3:
        CurrentAnimation = 0;
        Frame = BridgeType;
        switch (BridgeType) {
            case 1:
            W = 0x30;
            H = 0x20;
            break;
            case 0:
            case 2:
            W = 0x40;
            H = 0x20;
            break;
        }

        break;
        case 4:
        case 5:
        W = 80;
        H = 16;
        CurrentAnimation = 1;
        break;
        case 6:
        UseTrigger = false;
        Delay = SubType & 0xF;
        Allotted = Delay * 16 + 8;
        if (BridgeType == 4) {
            W = 0x20;
            H = 0x20;
            CurrentAnimation = 3;
        }
        else {
            W = 0x40;
            H = 0x10;
            CurrentAnimation = 2;
        }
        break;
        case 7:
        case 8:
        case 9:
        case 10:
        case 11:
        case 12:
        case 13:
        case 14:
        break;
    }

    VisW = W;
    VisH = H * 2 + 16;
    W <<= 1;
    H <<= 1;
    this->OnScreen = true;
}

void CollapsingBridge::Update() {
    this->OnScreen = true;
    if (UseTrigger) {
        if (this->f == -1 && (Scene->LevelTriggerFlag >> TriggerID & 1) == 1) {
            this->f = this->Allotted;
            this->Priority = true;
        }

    }

    if (!this->OnScreen && !this->Reset) {
        this->Reset = true;
        this->f = -1;
        this->SolidTop = true;
    }

    if (this->OnScreen) {
        this->Reset = false;
    }

    this->SolidTop = true;
    if (f > -1 && this->f <= 1) {
        this->SolidTop = false;
        this->Solid = false;
        if (f == 1) {
            Sound::Play(Sound::SFX_COLLAPSE);
            BreakHCZ();
            BreakMGZ();
            BreakICZ();
            Break();
        }

    }

    if (this->f > 0) this->f--;

    Object::Update();
}

void CollapsingBridge::BreakHCZ() {
    if (Scene->ZoneID != 2) return;

    if (BridgeType == 0) {
        for (int i = 0; i < 8; i++)
{
            if ((i & 1)) {
                Scene->AddFallingTile(i == 7 && FlipX ? 0x2F : 0x2D, this->X - this->W / 2 + (i << 4), this->Y, 0, -16, false, false, i * 4 + 2);
                Scene->AddFallingTile(i == 7 && FlipX ? 0x27 : 0x35, this->X - this->W / 2 + (i << 4), this->Y, 0, 0, false, false, i * 4);
            }
            else {
                Scene->AddFallingTile(i == 0 && !FlipX ? 0x2E : 0x2C, this->X - this->W / 2 + (i << 4), this->Y, 0, -16, false, false, i * 4 + 2);
                Scene->AddFallingTile(i == 0 && !FlipX ? 0x28 : 0x36, this->X - this->W / 2 + (i << 4), this->Y, 0, 0, false, false, i * 4);
            }
        }
    }
    else if (BridgeType == 1) {
        for (int i = 0; i < 8; i++)
{
            if (!(i & 1)) {
                Scene->AddFallingTile(0x2D, this->X - this->W / 2 + (i << 4), this->Y, 0, -16, false, false, i * 4 + 4 + 2);
                Scene->AddFallingTile(0x35, this->X - this->W / 2 + (i << 4), this->Y, 0, 0, false, false, i * 4 + 4);
            }
            else {
                Scene->AddFallingTile(0x2C, this->X - this->W / 2 + (i << 4), this->Y, 0, -16, false, false, i * 4 + 4 + 2);
                Scene->AddFallingTile(0x36, this->X - this->W / 2 + (i << 4), this->Y, 0, 0, false, false, i * 4 + 4);
            }
        }
        Scene->AddFallingTile(0x2C, this->X - (5 << 4), this->Y, 0, -16, false, false, 2);
        Scene->AddFallingTile(0x28, this->X - (5 << 4), this->Y, 0, 0, false, false, 0);
        Scene->AddFallingTile(0x2D, this->X + (4 << 4), this->Y, 0, -16, false, false, 9 * 4 + 2);
        Scene->AddFallingTile(0x35, this->X + (4 << 4), this->Y, 0, 0, false, false, 9 * 4);
    }
    else if (BridgeType == 2) {
        for (int i = 1; i < 7; i++)
{
            if ((i & 1)) {
                Scene->AddFallingTile(0x2D, this->X - this->W / 2 + (i << 4), this->Y, 0, -16, false, false, i * 4 + 2);
                Scene->AddFallingTile(0x35, this->X - this->W / 2 + (i << 4), this->Y, 0, 0, false, false, i * 4);
            }
            else {
                Scene->AddFallingTile(0x2C, this->X - this->W / 2 + (i << 4), this->Y, 0, -16, false, false, i * 4 + 2);
                Scene->AddFallingTile(0x36, this->X - this->W / 2 + (i << 4), this->Y, 0, 0, false, false, i * 4);
            }
        }
        if (!FlipX) {
            Scene->AddFallingTile(0x2E, this->X - (4 << 4), this->Y, 0, -16, false, false, 2);
            Scene->AddFallingTile(0x28, this->X - (4 << 4), this->Y, 0, 0, false, false, 0);
            Scene->AddFallingTile(0x2D, this->X + (3 << 4), this->Y, 0, -16, false, false, 7 * 4 + 2);
            Scene->AddFallingTile(0x35, this->X + (3 << 4), this->Y, 0, 0, false, false, 7 * 4);
        }
        else {
            Scene->AddFallingTile(0x2C, this->X - (4 << 4), this->Y, 0, -16, false, false, 2);
            Scene->AddFallingTile(0x36, this->X - (4 << 4), this->Y, 0, 0, false, false, 0);
            Scene->AddFallingTile(0x2F, this->X + (3 << 4), this->Y, 0, -16, false, false, 7 * 4 + 2);
            Scene->AddFallingTile(0x27, this->X + (3 << 4), this->Y, 0, 0, false, false, 7 * 4);
        }
    }
    else if (BridgeType == 3) {
        for (int i = 0; i < 8; i++)
{
            Scene->AddFallingTile(0x132, this->X - 64 + (i << 4), this->Y, 0, -16, !(i & 1), false, i * 4 + 6);
            if ((i & 3) == 0) {
                Scene->AddFallingTile(0x143, this->X - 64 + (i << 4), this->Y, 0, 0, false, false, i * 4 + 4);
                Scene->AddFallingTile(0x137, this->X - 64 + (i << 4), this->Y, 0, 16, false, false, i * 4 + 2);
                Scene->AddFallingTile(0x13A, this->X - 64 + (i << 4), this->Y, 0, 32, false, false, i * 4 + 0);
            }
            else if ((i & 3) == 1) {
                Scene->AddFallingTile(0x129, this->X - 64 + (i << 4), this->Y, 0, 0, true, false, i * 4 + 4);
                Scene->AddFallingTile(0x138, this->X - 64 + (i << 4), this->Y, 0, 16, false, false, i * 4 + 2);
                Scene->AddFallingTile(0x155, this->X - 64 + (i << 4), this->Y, 0, 32, false, false, i * 4 + 0);
            }
            else if ((i & 3) == 2) {
                Scene->AddFallingTile(0x12C, this->X - 64 + (i << 4), this->Y, 0, 0, false, false, i * 4 + 4);
                Scene->AddFallingTile(0x139, this->X - 64 + (i << 4), this->Y, 0, 16, false, false, i * 4 + 2);
            }
            else if ((i & 3) == 3) {
                Scene->AddFallingTile(0x12A, this->X - 64 + (i << 4), this->Y, 0, 0, false, false, i * 4 + 4);
                Scene->AddFallingTile(0x133, this->X - 64 + (i << 4), this->Y, 0, 16, false, false, i * 4 + 2);
            }

        }
    }

}

void CollapsingBridge::BreakMGZ() {
    if (Scene->ZoneID != 3) return;

    int x = X - W / 2 + 8;
    int y = Y - H / 2 - Sprite->Animations[CurrentAnimation].Frames[Frame].OffY;
    int w = W >> 4;
    int h = H >> 4;
    int left = Sprite->Animations[CurrentAnimation].Frames[Frame].X;
    int top = Sprite->Animations[CurrentAnimation].Frames[Frame].Y;
    for (int i = 0; i < w; i++)
{
        for (int j = 0; j < h; j++)
{
            int when = (h - 1 - j) * 2 + i * h * 2;
            if (BreakSide) {
                when = (h - 1 - j) * 2 + (w - 1 - i) * h * 2;
            }

            Scene->AddMovingSprite(Sprite, x + i * 0x10, y + j * 0x10, left + i * 0x10, top + j * 0x10, 0x10, 0x10, -8, -8, FlipX, false, 0, 0, 0x70, when);
        }
    }
}

void CollapsingBridge::BreakICZ() {
    if (Scene->ZoneID != 5) return;

    int sw = Sprite->Animations[CurrentAnimation].Frames[Frame].W;
    int sh = Sprite->Animations[CurrentAnimation].Frames[Frame].H;
    int x = X - sw / 2 + 8;
    int y = Y - sh / 2 - Sprite->Animations[CurrentAnimation].Frames[Frame].OffY + 10;
    int w = sw >> 4;
    int h = (sh + 0xF) >> 4;
    int left = Sprite->Animations[CurrentAnimation].Frames[Frame].X;
    int top = Sprite->Animations[CurrentAnimation].Frames[Frame].Y;
    int hLeft = sh;
    for (int j = 0; j < h; j++)
{
        for (int i = 0; i < w; i++)
{
            int when = (h - 1 - j) * 2 + i * h * 2;
            if (BreakSide) {
                when = (h - 1 - j) * 2 + (w - 1 - i) * h * 2;
            }

            int where = i;
            if (FlipX) where = (w - 1 - i);

            Scene->AddMovingSprite(Sprite, x + i * 0x10, y + j * 0x10, left + where * 0x10, top + j * 0x10, 0x10, hLeft >= 0x10 ? 0x10 : hLeft, -8, -8, FlipX, false, 0, 0, 0x70, when);
        }
        hLeft -= 0x10;
    }
}

void CollapsingBridge::Break() {
    if (Scene->ZoneID < 6) return;

    if (!Sprite) return;

    if (CurrentAnimation < 0) return;

    int x = X + Sprite->Animations[CurrentAnimation].Frames[Frame].OffX + 8;
    int y = Y + Sprite->Animations[CurrentAnimation].Frames[Frame].OffY + 8;
    int w = Sprite->Animations[CurrentAnimation].Frames[Frame].W >> 4;
    int h = Sprite->Animations[CurrentAnimation].Frames[Frame].H >> 4;
    int left = Sprite->Animations[CurrentAnimation].Frames[Frame].X;
    int top = Sprite->Animations[CurrentAnimation].Frames[Frame].Y;
    bool side = FlipX;
    if (side) {
        for (int i = 0; i < w; i++)
{
            for (int j = 0; j < h; j++)
{
                Scene->AddMovingSprite(Sprite, x + i * 0x10, y + j * 0x10, left + (w - 1 - i) * 0x10, top + j * 0x10, 0x10, 0x10, -8, -8, side, false, 0, 0, 0x70, (h - 1 - j) * 2 + i * h * 2);
            }
        }
    }
    else {
        for (int i = 0; i < w; i++)
{
            for (int j = 0; j < h; j++)
{
                Scene->AddMovingSprite(Sprite, x + i * 0x10, y + j * 0x10, left + i * 0x10, top + j * 0x10, 0x10, 0x10, -8, -8, side, false, 0, 0, 0x70, (h - 1 - j) * 2 + (w - 1 - i) * h * 2);
            }
        }
    }
}

void CollapsingBridge::Render(int CamX, int CamY) {
    if (!this->SolidTop) return;

    if (Scene->ZoneID == 2) {
        if (BridgeType == 0) {
            for (int i = 0; i < 8; i++)
{
                if ((i & 1)) {
                    G->DrawSprite(Scene->TileSprite, 0, i == 7 && FlipX ? 0x2F : 0x2D, 8 + this->X - CamX - this->W / 2 + (i << 4) + (0), 8 + this->Y - CamY + (-16), 0, IE_NOFLIP);
                    G->DrawSprite(Scene->TileSprite, 0, i == 7 && FlipX ? 0x27 : 0x35, 8 + this->X - CamX - this->W / 2 + (i << 4) + (0), 8 + this->Y - CamY + (0), 0, IE_NOFLIP);
                }
                else {
                    G->DrawSprite(Scene->TileSprite, 0, i == 0 && !FlipX ? 0x2E : 0x2C, 8 + this->X - CamX - this->W / 2 + (i << 4) + (0), 8 + this->Y - CamY + (-16), 0, IE_NOFLIP);
                    G->DrawSprite(Scene->TileSprite, 0, i == 0 && !FlipX ? 0x28 : 0x36, 8 + this->X - CamX - this->W / 2 + (i << 4) + (0), 8 + this->Y - CamY + (0), 0, IE_NOFLIP);
                }
            }
        }
        else if (BridgeType == 1) {
            for (int i = 0; i < 8; i++)
{
                if (!(i & 1)) {
                    G->DrawSprite(Scene->TileSprite, 0, 0x2D, 8 + this->X - CamX - this->W / 2 + (i << 4) + (0), 8 + this->Y - CamY + (-16), 0, IE_NOFLIP);
                    G->DrawSprite(Scene->TileSprite, 0, 0x35, 8 + this->X - CamX - this->W / 2 + (i << 4) + (0), 8 + this->Y - CamY + (0), 0, IE_NOFLIP);
                }
                else {
                    G->DrawSprite(Scene->TileSprite, 0, 0x2C, 8 + this->X - CamX - this->W / 2 + (i << 4) + (0), 8 + this->Y - CamY + (-16), 0, IE_NOFLIP);
                    G->DrawSprite(Scene->TileSprite, 0, 0x36, 8 + this->X - CamX - this->W / 2 + (i << 4) + (0), 8 + this->Y - CamY + (0), 0, IE_NOFLIP);
                }
            }
            G->DrawSprite(Scene->TileSprite, 0, 0x2C, 8 + this->X - CamX - (5 << 4) + (0), 8 + this->Y - CamY + (-16), 0, IE_NOFLIP);
            G->DrawSprite(Scene->TileSprite, 0, 0x28, 8 + this->X - CamX - (5 << 4) + (0), 8 + this->Y - CamY + (0), 0, IE_NOFLIP);
            G->DrawSprite(Scene->TileSprite, 0, 0x2D, 8 + this->X - CamX + (4 << 4) + (0), 8 + this->Y - CamY + (-16), 0, IE_NOFLIP);
            G->DrawSprite(Scene->TileSprite, 0, 0x35, 8 + this->X - CamX + (4 << 4) + (0), 8 + this->Y - CamY + (0), 0, IE_NOFLIP);
        }
        else if (BridgeType == 2) {
            for (int i = 1; i < 7; i++)
{
                if ((i & 1)) {
                    G->DrawSprite(Scene->TileSprite, 0, 0x2D, 8 + this->X - CamX - this->W / 2 + (i << 4) + (0), 8 + this->Y - CamY + (-16), 0, IE_NOFLIP);
                    G->DrawSprite(Scene->TileSprite, 0, 0x35, 8 + this->X - CamX - this->W / 2 + (i << 4) + (0), 8 + this->Y - CamY + (0), 0, IE_NOFLIP);
                }
                else {
                    G->DrawSprite(Scene->TileSprite, 0, 0x2C, 8 + this->X - CamX - this->W / 2 + (i << 4) + (0), 8 + this->Y - CamY + (-16), 0, IE_NOFLIP);
                    G->DrawSprite(Scene->TileSprite, 0, 0x36, 8 + this->X - CamX - this->W / 2 + (i << 4) + (0), 8 + this->Y - CamY + (0), 0, IE_NOFLIP);
                }
            }
            if (!FlipX) {
                G->DrawSprite(Scene->TileSprite, 0, 0x2E, 8 + this->X - CamX - (4 << 4) + (0), 8 + this->Y - CamY + (-16), 0, IE_NOFLIP);
                G->DrawSprite(Scene->TileSprite, 0, 0x28, 8 + this->X - CamX - (4 << 4) + (0), 8 + this->Y - CamY + (0), 0, IE_NOFLIP);
                G->DrawSprite(Scene->TileSprite, 0, 0x2D, 8 + this->X - CamX + (3 << 4) + (0), 8 + this->Y - CamY + (-16), 0, IE_NOFLIP);
                G->DrawSprite(Scene->TileSprite, 0, 0x35, 8 + this->X - CamX + (3 << 4) + (0), 8 + this->Y - CamY + (0), 0, IE_NOFLIP);
            }
            else {
                G->DrawSprite(Scene->TileSprite, 0, 0x2C, 8 + this->X - CamX - (4 << 4) + (0), 8 + this->Y - CamY + (-16), 0, IE_NOFLIP);
                G->DrawSprite(Scene->TileSprite, 0, 0x36, 8 + this->X - CamX - (4 << 4) + (0), 8 + this->Y - CamY + (0), 0, IE_NOFLIP);
                G->DrawSprite(Scene->TileSprite, 0, 0x2F, 8 + this->X - CamX + (3 << 4) + (0), 8 + this->Y - CamY + (-16), 0, IE_NOFLIP);
                G->DrawSprite(Scene->TileSprite, 0, 0x27, 8 + this->X - CamX + (3 << 4) + (0), 8 + this->Y - CamY + (0), 0, IE_NOFLIP);
            }
        }
        else if (BridgeType == 3) {
            for (int i = 0; i < 8; i++)
{
                G->DrawSprite(Scene->TileSprite, 0, 0x132, 8 + this->X - CamX - 64 + (i << 4) + (0), 8 + this->Y - CamY + (-16), 0, (i & 1) ? IE_NOFLIP : IE_FLIPX);
                if ((i & 3) == 0) {
                    G->DrawSprite(Scene->TileSprite, 0, 0x143, 8 + this->X - CamX - 64 + (i << 4) + (0), 8 + this->Y - CamY + (0), 0, IE_NOFLIP);
                    G->DrawSprite(Scene->TileSprite, 0, 0x137, 8 + this->X - CamX - 64 + (i << 4) + (0), 8 + this->Y - CamY + (16), 0, IE_NOFLIP);
                    G->DrawSprite(Scene->TileSprite, 0, 0x13A, 8 + this->X - CamX - 64 + (i << 4) + (0), 8 + this->Y - CamY + (32), 0, IE_NOFLIP);
                }
                else if ((i & 3) == 1) {
                    G->DrawSprite(Scene->TileSprite, 0, 0x129, 8 + this->X - CamX - 64 + (i << 4) + (0), 8 + this->Y - CamY + (0), 0, IE_FLIPX);
                    G->DrawSprite(Scene->TileSprite, 0, 0x138, 8 + this->X - CamX - 64 + (i << 4) + (0), 8 + this->Y - CamY + (16), 0, IE_NOFLIP);
                    G->DrawSprite(Scene->TileSprite, 0, 0x155, 8 + this->X - CamX - 64 + (i << 4) + (0), 8 + this->Y - CamY + (32), 0, IE_NOFLIP);
                }
                else if ((i & 3) == 2) {
                    G->DrawSprite(Scene->TileSprite, 0, 0x12C, 8 + this->X - CamX - 64 + (i << 4) + (0), 8 + this->Y - CamY + (0), 0, IE_NOFLIP);
                    G->DrawSprite(Scene->TileSprite, 0, 0x139, 8 + this->X - CamX - 64 + (i << 4) + (0), 8 + this->Y - CamY + (16), 0, IE_NOFLIP);
                }
                else if ((i & 3) == 3) {
                    G->DrawSprite(Scene->TileSprite, 0, 0x12A, 8 + this->X - CamX - 64 + (i << 4) + (0), 8 + this->Y - CamY + (0), 0, IE_NOFLIP);
                    G->DrawSprite(Scene->TileSprite, 0, 0x133, 8 + this->X - CamX - 64 + (i << 4) + (0), 8 + this->Y - CamY + (16), 0, IE_NOFLIP);
                }

            }
        }

    }
    else if (Scene->ZoneID == 3) {
        G->DrawSprite(Sprite, CurrentAnimation, Frame, X - CamX, Y - CamY, 0, IE_NOFLIP);
    }
    else if (CurrentAnimation != -1) {
        G->DrawSprite(Sprite, CurrentAnimation, Frame, X - CamX, Y - CamY, 0, FlipX);
    }
    else {
        G->DrawRectangle(X - W / 2 - CamX, Y - H / 2 - CamY, W, H, 0xFF0000);
    }
    }

int CollapsingBridge::CustomSolidityCheck(int probeX, int probeY, int PlayerID, int checkJumpThrough) {
    if (!checkJumpThrough) return 0;

    if (!this->SolidTop) return 0;

    int spriteoffset = -H / 2;
    if (CurrentAnimation != -1) {
        spriteoffset = Sprite->Animations[CurrentAnimation].Frames[Frame].OffY;
    }

    BreakSide = probeX > X;
    if (Scene->ZoneID != 3) {
        if (probeX >= X - W / 2 && probeY >= Y + spriteoffset && probeX < X + W / 2 && probeY < Y + spriteoffset + H) {
            if (!UseTrigger && this->f == -1 && Scene->Players[PlayerID]->Ground) {
                this->f = this->Allotted;
                this->Priority = true;
            }

            return 1;
        }

    }
    else if (Scene->ZoneID == 3) {
        if (probeX >= this->X - this->W / 2 && probeY >= this->Y - this->H / 2 + 0x11 && probeX < this->X + this->W / 2 && probeY < this->Y + this->H / 2) {
            if (BridgeType == 2) {
            }
            else {
                if (this->f == -1 && Scene->Players[PlayerID]->Ground) {
                    this->f = this->Allotted;
                    this->Priority = true;
                }

            }
            return 1;
        }

    }

    return 0;
}


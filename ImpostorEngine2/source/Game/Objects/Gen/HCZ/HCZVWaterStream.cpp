// Object ID: 0x37
// Object Name: HCZVWaterStream.cpp

#include "HCZVWaterStream.h"

typedef IMath Math;

void HCZVWaterStream::Create() {
    Object::Create();
    this->Active = true;
    this->Priority = false;
    this->Solid = true;
    Scene->AddSelfToRegistry(this, "Solid");
    this->W = 32;
    this->H = 64;
    this->X -= 48;
}

void HCZVWaterStream::Update() {
    if ((Scene->LevelTriggerFlag >> 0 & 1)) {
        this->Solid = false;
        if (this->Y > this->InitialY - 64) this->Y -= 8;

    }

    Object::Update();
}

void HCZVWaterStream::Render(int CamX, int CamY) {
    G->DrawSprite(Scene->TileSprite, 0, 0x8B, 8 + this->X - CamX + (-16), 8 + this->Y - 16 - CamY + (-16), 0, IE_NOFLIP);
    G->DrawSprite(Scene->TileSprite, 0, 0x8C, 8 + this->X - CamX + (0), 8 + this->Y - 16 - CamY + (-16), 0, IE_NOFLIP);
    G->DrawSprite(Scene->TileSprite, 0, 0x8D, 8 + this->X - CamX + (-16), 8 + this->Y - 16 - CamY + (0), 0, IE_NOFLIP);
    G->DrawSprite(Scene->TileSprite, 0, 0x8E, 8 + this->X - CamX + (0), 8 + this->Y - 16 - CamY + (0), 0, IE_NOFLIP);
    G->DrawSprite(Scene->TileSprite, 0, 0x8B, 8 + this->X - CamX + (-16), 8 + this->Y + 16 - CamY + (-16), 0, IE_NOFLIP);
    G->DrawSprite(Scene->TileSprite, 0, 0x8C, 8 + this->X - CamX + (0), 8 + this->Y + 16 - CamY + (-16), 0, IE_NOFLIP);
    G->DrawSprite(Scene->TileSprite, 0, 0x8D, 8 + this->X - CamX + (-16), 8 + this->Y + 16 - CamY + (0), 0, IE_NOFLIP);
    G->DrawSprite(Scene->TileSprite, 0, 0x8E, 8 + this->X - CamX + (0), 8 + this->Y + 16 - CamY + (0), 0, IE_NOFLIP);
    }


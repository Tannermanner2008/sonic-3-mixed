// Object ID: 0x01
// Object Name: Monitor.cpp

#include "Monitor.h"

typedef IMath Math;

void Monitor::Create() {
    Object::Create();
    Sprite = LevelScene::LoadSpriteFromBin("Global/ItemBox.bin", SaveGame::CurrentMode);
    W = 26;
    H = 32;
    Active = true;
    Priority = false;
    Frame = 0;
    YSpeed = 0;
    SubY = Y << 8;
    Solid = true;
    Scene->AddSelfToRegistry(this, "Solid");
    BreakableByRoll = CollideSide::TOP_SIDES;
    BreakableByJump = CollideSide::TOP_SIDES;
    BreakableByGlide = CollideSide::TOP_SIDES;
    Scene->AddSelfToRegistry(this, "Breakable");
    PlayerAggressor = 0;
    CanFall = false;
    GhostY = 0.0;
    CleanupInactiveObject = true;
    MonitorType = SubType;
    SubTypeFrame = 0;
    switch (MonitorType) {
        case ItemTypes::TYPE_RINGS:
        SubTypeFrame = 0;
        break;
        case ItemTypes::TYPE_SHIELD:
        SubTypeFrame = 1;
        break;
        case ItemTypes::TYPE_SHIELD_BUBBLE:
        SubTypeFrame = 2;
        break;
        case ItemTypes::TYPE_SHIELD_FIRE:
        SubTypeFrame = 3;
        break;
        case ItemTypes::TYPE_SHIELD_LIGHTNING:
        SubTypeFrame = 4;
        break;
        case ItemTypes::TYPE_INVINCIBILITY:
        SubTypeFrame = 5;
        break;
        case ItemTypes::TYPE_SPEED_SHOES:
        SubTypeFrame = 6;
        break;
        case ItemTypes::TYPE_1UP:
        SubTypeFrame = 7 + int(Scene->Player->Character);
        break;
        case ItemTypes::TYPE_SUPER:
        SubTypeFrame = 16;
        break;
        case ItemTypes::TYPE_HYPER:
        SubTypeFrame = 16;
        break;
        case ItemTypes::TYPE_HYPER_RING:
        SubTypeFrame = 11;
        break;
        case ItemTypes::TYPE_ROBOTNIK:
        SubTypeFrame = 12;
        break;
        case ItemTypes::TYPE_STATIC:
        SubTypeFrame = 14;
        break;
    }

    CurrentAnimation = 4;
}

void Monitor::UpdateSubType() {
    switch (MonitorType) {
        case ItemTypes::TYPE_RINGS:
        SubTypeFrame = 0;
        break;
        case ItemTypes::TYPE_SHIELD:
        SubTypeFrame = 1;
        break;
        case ItemTypes::TYPE_SHIELD_BUBBLE:
        SubTypeFrame = 2;
        break;
        case ItemTypes::TYPE_SHIELD_FIRE:
        SubTypeFrame = 3;
        break;
        case ItemTypes::TYPE_SHIELD_LIGHTNING:
        SubTypeFrame = 4;
        break;
        case ItemTypes::TYPE_INVINCIBILITY:
        SubTypeFrame = 5;
        break;
        case ItemTypes::TYPE_SPEED_SHOES:
        SubTypeFrame = 6;
        break;
        case ItemTypes::TYPE_1UP:
        SubTypeFrame = 7 + int(Scene->Player->Character);
        break;
        case ItemTypes::TYPE_SUPER:
        SubTypeFrame = 16;
        break;
        case ItemTypes::TYPE_HYPER:
        SubTypeFrame = 16;
        break;
        case ItemTypes::TYPE_HYPER_RING:
        SubTypeFrame = 11;
        break;
        case ItemTypes::TYPE_ROBOTNIK:
        SubTypeFrame = 12;
        break;
        case ItemTypes::TYPE_STATIC:
        SubTypeFrame = 14;
        break;
    }

}

uint8_t Monitor::GetSubTypeMax() {
    return ItemTypes::END_LIST_DONT_MOVE;
}

void Monitor::Update() {
    if (!CanFall && (YSpeed != 0)) {
        CanFall = true;
    }

    if (CanFall) {
        if (YSpeed < 0 && Scene->CollisionAt(X, (SubY >> 8) - 17)) {
            YSpeed = 0;
        }

        YSpeed += 0x38;
        SubY += YSpeed;
        Y = SubY >> 8;
        while (Scene->CollisionAt(X, Y + 16 + 1)) {
            Y--;
            YSpeed = 0;
            Priority = false;
            CanFall = false;
        }

        if (!CanFall) Y += 2;

    }

    if (YSpeed != 0) Priority = true;

    if (Timer >= 0 && Timer < 64 + 24) Timer++;
    else if (!CanFall) Priority = false;

    if (Timer == 32) {
        switch (MonitorType) {
            case ItemTypes::TYPE_STATIC:
            Scene->Players[PlayerAggressor]->Hurt(X, false);
            break;
            case ItemTypes::TYPE_1UP:
            Scene->Players[PlayerAggressor]->GiveLife(1);
            break;
            case ItemTypes::TYPE_ROBOTNIK:
            Scene->Players[PlayerAggressor]->Hurt(X, false);
            break;
            case ItemTypes::TYPE_RINGS:
            Scene->Players[PlayerAggressor]->GiveRing(10);
            Sound::Play(Sound::SFX_RING);
            break;
            case ItemTypes::TYPE_SPEED_SHOES:
            Scene->Players[PlayerAggressor]->SpeedSneakersActive = true;
            if (Scene->Players[PlayerAggressor]->SpeedSneakersTimer == 0) {
                App->Audio->PushMusic(Sound::SoundBank[0xFE], true, 120960);
            }

            Scene->Players[PlayerAggressor]->SpeedSneakersTimer += 1200;
            break;
            case ItemTypes::TYPE_SHIELD:
            Scene->Players[PlayerAggressor]->Shield = ShieldType::Basic;
            Sound::Play(Sound::SFX_SHIELD);
            break;
            case ItemTypes::TYPE_SHIELD_FIRE:
            Scene->Players[PlayerAggressor]->Shield = ShieldType::Fire;
            Scene->Players[PlayerAggressor]->ShieldUsable = true;
            Scene->Players[PlayerAggressor]->ShieldAction = false;
            Sound::Play(Sound::SFX_SHIELD_FIRE);
            break;
            case ItemTypes::TYPE_SHIELD_LIGHTNING:
            Scene->Players[PlayerAggressor]->Shield = ShieldType::Electric;
            Scene->Players[PlayerAggressor]->ShieldUsable = true;
            Scene->Players[PlayerAggressor]->ShieldAction = false;
            Sound::Play(Sound::SFX_SHIELD_ELECTRIC);
            break;
            case ItemTypes::TYPE_SHIELD_BUBBLE:
            Scene->Players[PlayerAggressor]->Shield = ShieldType::Bubble;
            Scene->Players[PlayerAggressor]->ShieldUsable = true;
            Scene->Players[PlayerAggressor]->ShieldAction = false;
            Sound::Play(Sound::SFX_SHIELD_BUBBLE);
            App->Audio->RemoveMusic(Sound::SoundBank[0xFD]);
            break;
            case ItemTypes::TYPE_INVINCIBILITY:
            if (Scene->Players[PlayerAggressor]->Invincibility == InvincibilityType::Full) {
                App->Achievements->SetAchievement(1, true);
            }

            if (!Scene->Players[PlayerAggressor]->SuperForm && !Scene->Players[PlayerAggressor]->HyperForm) {
                Scene->Players[PlayerAggressor]->Invincibility = InvincibilityType::Full;
                if (Scene->Players[PlayerAggressor]->InvincibilityTimer == 0) {
                    App->Audio->PushMusic(Sound::SoundBank[0xFF], true, 14702);
                }

                Scene->Players[PlayerAggressor]->InvincibilityTimer += 1200;
            }

            break;
            case ItemTypes::TYPE_SUPER:
            if (Scene->Players[PlayerAggressor]->HyperEnabled) {
                Scene->Players[PlayerAggressor]->HyperEnabled = false;
            }

            Scene->Players[PlayerAggressor]->GiveRing(100);
            Scene->Players[PlayerAggressor]->DoSuperTransform();
            break;
            case ItemTypes::TYPE_HYPER:
            Scene->Players[PlayerAggressor]->HyperEnabled = true;
            Scene->Players[PlayerAggressor]->GiveRing(100);
            Scene->Players[PlayerAggressor]->DoSuperTransform();
            break;
            case ItemTypes::TYPE_HYPER_RING:
            Scene->Players[PlayerAggressor]->HyperRings = true;
            Scene->Players[PlayerAggressor]->GiveRing(10);
            Sound::Play(Sound::SFX_RING);
            break;
        }

    }

    if (BreakableByRoll == CollideSide::NONE) {
        GhostY += (-35.0 - GhostY) / 10.0;
        Priority = true;
        if (Math::floor(GhostY) == -35.0) {
            GhostY = -35.0;
        }

    }

    AutoAnimate = true;
    Object::Update();
}

void Monitor::Render(int CamX, int CamY) {
    if (Scene->Thremixed) {
        if (CurrentAnimation == 4) {
            G->DrawSprite(Sprite, 0, 0, X - CamX, Y - CamY, 0, IE_NOFLIP);
            G->DrawModeOverlay = true;
            G->DrawSprite(Sprite, 3, Scene->Frame >> 1 & 1, X - CamX, Y - CamY - 2, 0, IE_NOFLIP);
            G->DrawModeOverlay = false;
        }
        else {
            G->DrawSprite(Sprite, CurrentAnimation, Frame, X - CamX, Y - CamY, 0, IE_NOFLIP);
        }
        if (CurrentAnimation == 1 && (Timer >= 64 && Timer % 3 != 0)) {
            return;
        }

        G->DrawSprite(Sprite, 2, SubTypeFrame, X - CamX, Y + (int)(-CamY - 5 + GhostY), 0, IE_NOFLIP);
    }
    else {
        if (CurrentAnimation == 4) {
            G->DrawSprite(Sprite, 0, 0, X - CamX, Y - CamY, 0, IE_NOFLIP);
        }
        else {
            G->DrawSprite(Sprite, CurrentAnimation, Frame, X - CamX, Y - CamY, 0, IE_NOFLIP);
        }
        if (CurrentAnimation == 4 && (Scene->Frame % 6 >= 4)) {
            return;
        }

        if (CurrentAnimation == 1 && (Timer >= 64 && Timer % 3 != 0)) {
            return;
        }

        G->DrawSprite(Sprite, 2, SubTypeFrame, X - CamX, Y + (int)(-CamY - 5 + GhostY), 0, IE_NOFLIP);
    }
    if (DrawCollisions) {
        G->SetDrawAlpha(0x80);
        G->DrawRectangle(X - (W / 2) - CamX, Y - (H / 2) - CamY, W, H, DrawCollisionsColor);
        G->SetDrawAlpha(0xFF);
    }

    }

int Monitor::OnBreakHorizontal(int PlayerID, int HitFrom) {
    BreakableByRoll = CollideSide::NONE;
    BreakableByJump = CollideSide::NONE;
    BreakableByGlide = CollideSide::NONE;
    Solid = false;
    Timer = 0;
    Priority = true;
    Sound::Play(Sound::SFX_DESTROY);
    ChangeAnimation(1);
    Scene->AddExplosion(3, false, X, Y - 12);
    return 1;
}

int Monitor::OnBreakVertical(int PlayerID, int HitFrom) {
    return OnBreakHorizontal(PlayerID, HitFrom);
}


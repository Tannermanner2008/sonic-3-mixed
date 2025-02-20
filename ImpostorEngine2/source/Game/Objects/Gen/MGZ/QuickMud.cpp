// Object ID: 0x4F
// Object Name: QuickMud.cpp

#include "QuickMud.h"

typedef IMath Math;

void QuickMud::Create() {
    Object::Create();
    Active = true;
    Priority = false;
    Solid = false;
    W = SubType << 4;
    H = 0x60;
}

int QuickMud::OnCollisionWithPlayer(int PlayerID, int HitFrom, int Data) {
    Scene->Players[PlayerID]->YSpeed = -0x10;
    if (Math::abs(Scene->Players[PlayerID]->GroundSpeed) < 0xB0) {
        if (Scene->Players[PlayerID]->GroundSpeed > 0) {
            Scene->Players[PlayerID]->GroundSpeed = 0xB0;
        }
        else {
            Scene->Players[PlayerID]->GroundSpeed = -0xB0;
        }
    }

    if (Scene->Players[PlayerID]->InputJump == true) {
        Scene->Players[PlayerID]->Jump();
    }

    if (Scene->Players[PlayerID]->Y == Y) {
        Scene->Players[PlayerID]->Die(false);
    }

    return true;
}


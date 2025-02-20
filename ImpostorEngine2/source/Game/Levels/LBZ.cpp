#if INTERFACE
#include <Game/LevelScene.h>

class Level_LBZ : public LevelScene {
public:
    ISprite* LBZObjectsSprite = NULL;
    ISprite* WaterLine = NULL;
};
#endif

#include <Game/Explosion.h>
#include <Game/LevelScene.h>

#include <Game/Objects/Gen/ObjectListing.h>

#include <Game/Levels/LBZ.h>

PUBLIC Level_LBZ::Level_LBZ(IApp* app, IGraphics* g, int act) : LevelScene(app, g) {
    ZoneID = 6;
    VisualAct = Act = act;
	sprintf(ZoneLetters, "LBZ");

	if (SaveGame::CurrentMode >= 1)
	{
		if (Act == 1) {
			Str_TileConfigBin = "Mixed/Stages/LBZ1/TileConfig.bin";
			Str_SceneBin = "Mixed/Stages/LBZ1/Scene.bin";
			Str_TileSprite = "Mixed/Stages/LBZ1/16x16Tiles.gif";
			Str_AnimatedSprites = "Mixed/Stages/LBZ1/Animated Tiles.gif";
			Str_StageBin = "Mixed/Stages/LBZ1/Stageconfig.bin";
		}
		else {
			Str_TileConfigBin = "Mixed/Stages/LBZ2/TileConfig.bin";
			Str_SceneBin = "Mixed/Stages/LBZ2/Scene.bin";
			Str_TileSprite = "Mixed/Stages/LBZ2/16x16Tiles.gif";
			Str_AnimatedSprites = "Mixed/Stages/LBZ2/Animated Tiles.gif";
			Str_StageBin = "Mixed/Stages/LBZ2/Stageconfig.bin";
			WaterLine = new ISprite("LBZ/AniTiles2.gif", App, SaveGame::CurrentMode);
		}
	}
	else
	{
		if (Act == 1) {
			Str_TileConfigBin = "Classic/Stages/LBZ1/TileConfig.bin";
			Str_SceneBin = "Classic/Stages/LBZ1/Scene.bin";
			Str_TileSprite = "Classic/Stages/LBZ1/16x16Tiles.gif";
			Str_AnimatedSprites = "Classic/Stages/LBZ1/Animated Tiles.gif";
			Str_StageBin = "Classic/Stages/LBZ1/Stageconfig.bin";
		}
		else {
			Str_TileConfigBin = "Classic/Stages/LBZ2/TileConfig.bin";
			Str_SceneBin = "Classic/Stages/LBZ2/Scene.bin";
			Str_TileSprite = "Classic/Stages/LBZ2/16x16Tiles.gif";
			Str_AnimatedSprites = "Classic/Stages/LBZ2/Animated Tiles.gif";
			Str_StageBin = "Classic/Stages/LBZ2/Stageconfig.bin";
			WaterLine = new ISprite("LBZ/AniTiles2.gif", App, SaveGame::CurrentMode);
		}
	}

    sprintf(LevelName, "LAUNCH BASE");
    sprintf(LevelNameDiscord, "Launch Base");

    if (Act == 1) {
        // PlayerStartX = 0x00C0;
        // PlayerStartY = 0x05BC;

        PlayerStartX = 0x0CC8;
        PlayerStartY = 0x076C;
    }
    else {
		VisualWaterLevel = WaterLevel = 0x660;
    }

	AddNewDebugObjectID(Obj_Orbinaut);
}

PUBLIC void Level_LBZ::Init() {
	LevelScene::Init();
}


PUBLIC void Level_LBZ::RestartStage(bool doActTransition, bool drawBackground) {
	App->Audio->ClearMusic();
	PlayMusic(Act, 0, SaveGame::CurrentMode);

    LevelScene::RestartStage(doActTransition, drawBackground);
}

PUBLIC void Level_LBZ::LoadData() {
	LevelScene::LoadData();
}

PUBLIC void Level_LBZ::AssignSpriteMapIDs() {
    LevelScene::AssignSpriteMapIDs();

	SpriteMapIDs.at(0x01) = ItemsSprite;
    SpriteMapIDs.at(0x04) = LBZObjectsSprite;
    SpriteMapIDs.at(0x05) = LBZObjectsSprite;
    SpriteMapIDs.at(0x06) = LBZObjectsSprite;
	SpriteMapIDs.at(0x07) = ObjectsSprite;
	SpriteMapIDs.at(0x08) = ObjectsSprite;
    SpriteMapIDs.at(0x09) = LBZObjectsSprite;
    SpriteMapIDs.at(0x0A) = LBZObjectsSprite;
    SpriteMapIDs.at(0x0C) = LBZObjectsSprite;
    SpriteMapIDs.at(0x0D) = LBZObjectsSprite;
    SpriteMapIDs.at(0x0F) = LBZObjectsSprite;
	SpriteMapIDs.at(0x2F) = LBZObjectsSprite;
	//SpriteMapIDs.at(0x33) = SpriteMap["HCZ"];
	SpriteMapIDs.at(0x34) = ObjectsSprite;
    SpriteMapIDs.at(0x35) = LBZObjectsSprite;

	SpriteMapIDs.at(0x51) = LBZObjectsSprite;
    SpriteMapIDs.at(0x8C) = LBZObjectsSprite;
}

PUBLIC void Level_LBZ::LoadZoneSpecificSprites() {
    if (!LBZObjectsSprite) {
		LBZObjectsSprite = new ISprite("LBZ/Objects.gif", App);
		LBZObjectsSprite->Print = true;

		LBZObjectsSprite->LoadAnimation("LBZ/Tunnel Exhaust.bin");
		LBZObjectsSprite->LoadAnimation("LBZ/Breakable Wall.bin");
		LBZObjectsSprite->LoadAnimation("LBZ/Collapsing Bridge.bin");
		LBZObjectsSprite->LoadAnimation("LBZ/Collapsing Ledge.bin");
		LBZObjectsSprite->LoadAnimation("LBZ/Cork Floor.bin");
		LBZObjectsSprite->LoadAnimation("LBZ/Cup Elevator.bin");
		LBZObjectsSprite->LoadAnimation("LBZ/Exploding Trigger.bin");
		LBZObjectsSprite->LoadAnimation("LBZ/Flame Thrower.bin");
		LBZObjectsSprite->LoadAnimation("LBZ/Exploding Trigger.bin");
		LBZObjectsSprite->LoadAnimation("LBZ/Gate Laser.bin");
		LBZObjectsSprite->LoadAnimation("LBZ/Knuckles Bomb.bin");
		LBZObjectsSprite->LoadAnimation("LBZ/Knuckles Pillar.bin");
		LBZObjectsSprite->LoadAnimation("LBZ/Lowering Grapple.bin");
		LBZObjectsSprite->LoadAnimation("LBZ/Floating Platform.bin");
		LBZObjectsSprite->LoadAnimation("LBZ/PipePlug.bin");
		LBZObjectsSprite->LoadAnimation("LBZ/Player Launcher.bin");
		LBZObjectsSprite->LoadAnimation("LBZ/Ride Grapple.bin");
		LBZObjectsSprite->LoadAnimation("LBZ/Smashing Spikes.bin");
		LBZObjectsSprite->LoadAnimation("LBZ/Spin Launcher.bin");
		LBZObjectsSprite->LoadAnimation("LBZ/Trigger Bridge.bin");
		LBZObjectsSprite->LoadAnimation("LBZ/Tube Elevator.bin");
		LBZObjectsSprite->LoadAnimation("LBZ/Miniboss.bin");
		LBZObjectsSprite->LoadAnimation("LBZ/End Boss.bin");
		LBZObjectsSprite->LoadAnimation("LBZ/Final Boss.bin");
		LBZObjectsSprite->LoadAnimation("LBZ/Non Animated Sprites.bin");
	}

	if (!KnuxSprite[0]) {
		if (SaveGame::CurrentMode >= 1)
		{
			KnuxSprite[0] = new ISprite("Mixed/Sprites/Players/Knux1.gif", App);
			KnuxSprite[1] = new ISprite("Mixed/Sprites/Players/Knux2.gif", App);
			KnuxSprite[2] = new ISprite("Mixed/Sprites/Players/Knux3.gif", App);
			KnuxSprite[3] = new ISprite("Mixed/Sprites/Players/KnuxCutsceneAIZ.gif", App);
			KnuxSprite[4] = new ISprite("Mixed/Sprites/Players/KnuxCutsceneHPZ.gif", App);

			KnuxSprite[0]->LoadAnimation("Mixed/Sprites/Players/Knux.bin");
		}
		else
		{
			KnuxSprite[0] = new ISprite("Classic/Sprites/Players/Knux1.gif", App);
			KnuxSprite[1] = new ISprite("Classic/Sprites/Players/Knux2.gif", App);
			KnuxSprite[2] = new ISprite("Classic/Sprites/Players/Knux3.gif", App);
			KnuxSprite[3] = new ISprite("Classic/Sprites/Players/KnuxCutsceneAIZ.gif", App);
			KnuxSprite[4] = new ISprite("Classic/Sprites/Players/KnuxCutsceneHPZ.gif", App);

			KnuxSprite[0]->LoadAnimation("Classic/Sprites/Players/Knux.bin");
		}
		KnuxSprite[1]->LinkAnimation(KnuxSprite[0]->Animations);
		KnuxSprite[2]->LinkAnimation(KnuxSprite[0]->Animations);
		KnuxSprite[3]->LinkAnimation(KnuxSprite[0]->Animations);
		KnuxSprite[4]->LinkAnimation(KnuxSprite[0]->Animations);
	}
}

PUBLIC void Level_LBZ::FinishResults() {
	if (VisualAct == 1) {
		LevelScene::FinishResults();
	}
	else {
		FadeAction = FadeActionType::NEXT_ZONE;
		FadeTimerMax = 90;
		FadeMax = 0x140;
		G->FadeToWhite = false;
	}
}
PUBLIC void Level_LBZ::GoToNextAct() {
	if (VisualAct == 1) {
		Level_LBZ* NextAct = new Level_LBZ(App, G, 2);

		TransferCommonLevelData(NextAct);
		NextAct->LBZObjectsSprite = LBZObjectsSprite;
		// Enable Title Card with no fade-in
		NextAct->LevelCardTimer = 0.0;
		NextAct->FadeTimer = 0;
		NextAct->FadeAction = 0;
		NextAct->LevelCardHide = false;
		// Transfer over current frame
		NextAct->Frame = Frame;
		// Set player spawn position relative to their previous position  
		NextAct->SpecialSpawnPositionX = Player->EZX - 0x3A00;
		NextAct->SpecialSpawnPositionY = Player->EZY;
		NextAct->RoutineNumber = 0x00;

		App->NextScene = NextAct;
	}
	else {
		//Level_CNZ* NextAct = new Level_CNZ(App, G, 1);
		//TransferCommonLevelData(NextAct);
		//App->NextScene = NextAct;
	}
}

PUBLIC void Level_LBZ::RenderAboveBackground() {
	if (Act == 2) {
		if (WaterLine) {
			int Y = 0x200 - (CameraY >> 2);
			int WY = VisualWaterLevel - CameraY;

			int xBase = CameraX >> 2;
			for (int X = xBase; X < xBase + App->WIDTH + 0x10; X += 0x10) {
				if (Y < WY) {
					if (WY - Y < 128)
						G->DrawSprite(WaterLine, 0, 0, 16, 112, (X & ~0xF) - xBase, Y, 0, IE_NOFLIP, 0, 0, 16, WY - Y);
					else
						G->DrawSprite(WaterLine, 0, 0, 16, 112, (X & ~0xF) - xBase, Y, 0, IE_NOFLIP, 0, 0, 16, 128);
				}
				else if (Y - WY > 0) {
					if (Y - WY < 128)
						G->DrawSprite(WaterLine, 0, 112, 16, 112, (X & ~0xF) - xBase, WY, 0, IE_NOFLIP, 0, 0, 16, Y - WY);
					else
						G->DrawSprite(WaterLine, 0, 112, 16, 112, (X & ~0xF) - xBase, Y - 128, 0, IE_NOFLIP, 0, 0, 16, 128);
				}
			}
		}
	}
}

PUBLIC void Level_LBZ::EarlyUpdate() {
    if (Act == 1) {

    }
    else if (Act == 2) {

    }
    LevelScene::EarlyUpdate();
}
PUBLIC void Level_LBZ::Subupdate() {
    LevelScene::Subupdate();
}

PUBLIC void Level_LBZ::HandleCamera() {
    if (Act == 1) {

    }
    else if (Act == 2) {

    }
    LevelScene::HandleCamera();
}

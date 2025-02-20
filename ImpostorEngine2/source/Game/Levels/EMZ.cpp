#if INTERFACE
#include <Game/LevelScene.h>

class Level_EMZ : public LevelScene {
public:
    int  CutsceneRoutineNumber = 0x00;
};
#endif

#include <Game/Explosion.h>
#include <Game/LevelScene.h>

#include <Game/Objects/Gen/ObjectListing.h>

#include <Game/Levels/EMZ.h>

PUBLIC Level_EMZ::Level_EMZ(IApp* app, IGraphics* g, int act) : LevelScene(app, g) {
    ZoneID = 7;
    Act = act;
	sprintf(ZoneLetters, "EMZ");
	PlayMusic(act, 0, SaveGame::CurrentMode);

	if (SaveGame::CurrentMode >= 1)
	{
		if (Act == 1) {
			Str_TileConfigBin = "Mixed/Stages/EMZ1/TileConfig.bin";
			Str_SceneBin = "Mixed/Stages/EMZ1/Scene.bin";
			Str_TileSprite = "Mixed/Stages/EMZ1/16x16Tiles.gif";
			Str_AnimatedSprites = "Mixed/Stages/EMZ1/Animated Tiles.gif";
			Str_StageBin = "Mixed/Stages/EMZ1/Stageconfig.bin";
		}
		else {
			Str_TileConfigBin = "Mixed/Stages/EMZ2/TileConfig.bin";
			Str_SceneBin = "Mixed/Stages/EMZ2/Scene.bin";
			Str_TileSprite = "Mixed/Stages/EMZ2/16x16Tiles.gif";
			Str_AnimatedSprites = "Mixed/Stages/EMZ2/Animated Tiles.gif";
			Str_StageBin = "Mixed/Stages/EMZ2/Stageconfig.bin";
		}
	}
	else
	{
		if (Act == 1) {
			Str_TileConfigBin = "Classic/Stages/EMZ1/TileConfig.bin";
			Str_SceneBin = "Classic/Stages/EMZ1/Scene.bin";
			Str_TileSprite = "Classic/Stages/EMZ1/16x16Tiles.gif";
			Str_AnimatedSprites = "Classic/Stages/EMZ1/Animated Tiles.gif";
			Str_StageBin = "Classic/Stages/EMZ1/Stageconfig.bin";
		}
		else {
			Str_TileConfigBin = "Classic/Stages/EMZ2/TileConfig.bin";
			Str_SceneBin = "Classic/Stages/EMZ2/Scene.bin";
			Str_TileSprite = "Classic/Stages/EMZ2/16x16Tiles.gif";
			Str_AnimatedSprites = "Classic/Stages/EMZ2/Animated Tiles.gif";
			Str_StageBin = "Classic/Stages/EMZ2/Stageconfig.bin";
		}
	}

    sprintf(LevelName, "ENDLESS MINE");
    sprintf(LevelNameDiscord, "Endless Mine");

    if (Act == 1) {
        // PlayerStartX = 0x00D8;
        // PlayerStartY = 0x0500;
    }
    else {

    }
}

PUBLIC void Level_EMZ::LoadZoneSpecificSprites() {
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

PUBLIC void Level_EMZ::RestartStage(bool doActTransition, bool drawBackground) {
    LevelScene::RestartStage(doActTransition, drawBackground);

    if (Act == 1) {

    }
}

PUBLIC void Level_EMZ::EarlyUpdate() {
    if (Act == 1) {

    }
    else if (Act == 2) {

    }

    LevelScene::EarlyUpdate();
}
PUBLIC void Level_EMZ::Subupdate() {
    LevelScene::Subupdate();
}

PUBLIC void Level_EMZ::HandleCamera() {
    if (Act == 1) {
        //int off = App->WIDTH / 2 - 0xA0;
        //int ToS3X = CameraX + off;
        if (false) { // SKAlone
            CameraMinX = 0x680;
            if (CameraX < 0x680) {
                CameraX = 0x680;
            }
        }
        else {
            if (Player->EZY < 0x580) {
                CameraMinX = 0xC0;
                if (CameraX < 0xC0) {
                    CameraX = 0xC0;
                }
            }
        }

        /*int MaxY = 0x0;
        MaxY += 0xE0;
        MaxY -= App->HEIGHT;
        if (CameraY > MaxY) {
            CameraY = MaxY;
        }*/
    }

    LevelScene::HandleCamera();
}

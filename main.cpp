#include "raylib-5.0_win64_msvc16/include/raylib.h"

const int screenWidth = 1600;
const int screenHeight = 800;
void defineGround(Vector2 scarfyVelocity,Vector2 scarfyPosition,float &groundYPos,float &jumpCap)
{
    if (scarfyVelocity.y == 0.0f && scarfyVelocity.x == 0.0f)
       groundYPos = scarfyPosition.y , jumpCap = groundYPos - 250.0f;


}
int main(void)
{
    //  Initialization  //

    InitWindow(screenWidth, screenHeight, "Raylib - newGame");
    Texture2D scarfyTex = LoadTexture("scarfy.png");
    Texture2D background = LoadTexture("fundal.png");

    unsigned numFrames = 6;
    float scarfyWidth = (float)scarfyTex.width;
    float scarfyHeight = (float)scarfyTex.height;
    float frameWidth = scarfyWidth/numFrames;

    Rectangle frameRec = { 0.0f,0.0f,frameWidth, scarfyHeight };
    Vector2 scarfyPosition = { 100.0f,300.0f};
    Vector2 scarfyVelocity = { 0.0f, 0.0f };

    const int scarfySpeed = 5;
    const int gravity = 6;
    float groundYPos =scarfyPosition.y;
    float jumpCap = groundYPos - 250.0f;


    bool scarfyMoving=false;
    bool scarfyFall = false;
    
    unsigned frameDelay = 5;
    unsigned frameIndex = 0;
    unsigned frameIndexJump = 4;
    unsigned frameIndexFall = 5;
    unsigned frameDelayCounter = 0;

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {   


        //  movementKeys  //
        {
            if (IsKeyDown(KEY_UP) && scarfyPosition.y > jumpCap && scarfyFall == false)
            {
                scarfyVelocity.y = 2 * -scarfySpeed;
                scarfyPosition.y += 2 * -scarfySpeed;
            }
            else
            {
                scarfyFall = true;
                if (scarfyPosition.y < groundYPos)
                {
                    scarfyPosition.y += gravity;
                    scarfyVelocity.y += gravity;
                }
                else
                    scarfyFall = false;
            }

            if (IsKeyDown(KEY_RIGHT))
            {
                scarfyVelocity.x = scarfySpeed;
                if (frameRec.width < 0.0f)
                    frameRec.width = -frameRec.width;
            }
            else if (IsKeyDown(KEY_LEFT))
            {
                scarfyVelocity.x = -scarfySpeed;
                if (frameRec.width > 0.0f)
                    frameRec.width = -frameRec.width;
            }
            else
                scarfyVelocity.x = 0;

            scarfyPosition.x = scarfyPosition.x + scarfyVelocity.x;
            if (scarfyVelocity.x != 0.0f)
                scarfyMoving = true;
            else
                scarfyMoving = false;
        }

        //  frames  //
        {
            ++frameDelayCounter;
            if (frameDelayCounter > frameDelay)
            {
                if (scarfyVelocity.x)
                {
                    ++frameIndex;
                    frameIndex = frameIndex % numFrames;
                    frameRec.x = frameWidth * frameIndex;
                }
                frameDelayCounter = 0;
            }
        }
        
        defineGround(scarfyVelocity,scarfyPosition,groundYPos,jumpCap);

        //  animation  //
        {
            BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawTexture(background, 0, 0, WHITE);

            if (scarfyFall == true)
                frameRec.x = frameWidth * frameIndexFall;
            else if (IsKeyDown(KEY_UP) && scarfyFall == false)
                frameRec.x = frameWidth * frameIndexJump;

            DrawTextureRec(scarfyTex, frameRec, scarfyPosition, RAYWHITE);
            EndDrawing();
        }
    }

    CloseWindow();        // Close window and OpenGL context

    return 0;
}

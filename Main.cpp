float TextToFloat(const char* text) {
    return 0.0f; 
}

#define RAYGUI_IMPLEMENTATION
#include <raylib.h>
#include "raygui.h"
#include "Particle.h"
#include "HashGrid.h"

Particle* particle = new Particle();
float dt = 0.03f;
float decay = 0.35f;
Image icon;

Camera2D camera = { 0 };
Vector2 initialCameraTarget = { 0.0f, 0.0f };
Vector2 initialCameraOffset = { 0.0f, 0.0f };
float initialCameraZoom = 1.0f;
float initialCameraRotation = 0.0f;

static void GUIControls(void)
{
    float posx = 5.0f;
    float posy = 7.0f;
    GuiGroupBox({ posx, posy, 335, 305 }, "CONTROLS");

    int style = GuiGetStyle(SCROLLBAR, BORDER_WIDTH);

    GuiSliderBar({ posx + 130, posy + 15, 145, 15 }, "", TextFormat("%i", (int)particle->GetParticleCount()), 
              (&particle->p_particleCount), 0, 11500);
    GuiSliderBar({ posx + 130, posy + 35, 145, 15 }, "", TextFormat("%i", (int)particle->GetRadius()), (&particle->p_radius), 5, 10);
    GuiSliderBar({ posx + 130, posy + 55, 145, 15 }, "", TextFormat("%i", (int)particle->p_hashGrid.m_cellSize), 
              (&particle->p_hashGrid.m_cellSize), 10, 50);
    GuiSliderBar({ posx + 130, posy + 75, 145, 15 }, "", TextFormat("%i", (int)particle->p_force.x), (&particle->p_force.x), 0, 725);
    GuiSliderBar({ posx + 130, posy + 95, 145, 15 }, "", TextFormat("%i", (int)particle->p_force.y), (&particle->p_force.y), 0, 145);
    GuiSliderBar({ posx + 130, posy + 115, 145, 15 }, "", TextFormat("%i", (int)particle->p_mass), (&particle->p_mass), 5, 35);
    GuiSliderBar({ posx + 130, posy + 135, 145, 15 }, "", TextFormat("%i", (int)decay), (&decay), 0, 1);
    GuiSliderBar({ posx + 130, posy + 155, 145, 15 }, "", TextFormat("%i", (int)dt), (&dt), 0, 1);
    GuiToggle({ posx + 90, posy + 195, 145, 15 }, "#97#TOGGLE HASH GRID   ", &particle->p_isGridActive);
    GuiToggle({ posx + 90, posy + 215, 145, 15 }, "#44#TOGGLE COLLISIONS  ", &particle->p_isShowingCollisions);
    GuiToggle({ posx + 90, posy + 235, 145, 15 }, "#44#TOGGLE CIRCLE LINES", &particle->p_toggleCircleLines);
    GuiDrawText("#191#EDIT THE PARTICLE SETTINGS BEFORE SPAWNING THEM.", { posx + 3, posy + 285, 300, 15 }, -555, RED);
    GuiDrawText("#147#SPAWN PARTICLES", { posx + 5 , posy + 15, 100, 15 }, 0, WHITE);
    GuiDrawText("#23#EDIT RADII", { posx + 5 , posy + 35, 100, 15 }, 0, WHITE);
    GuiDrawText("#23#EDIT CELL SIZE", { posx + 5 , posy + 55, 100, 15 }, 0, WHITE);
    GuiDrawText("#23#EDIT FORCE X", { posx + 5 , posy + 75, 100, 15 }, 0, WHITE);
    GuiDrawText("#23#EDIT FORCE Y", { posx + 5 , posy + 95, 100, 15 }, 0, WHITE);
    GuiDrawText("#23#EDIT MASS", { posx + 5 , posy + 115, 100, 15 }, 0, WHITE);
    GuiDrawText("#23#EDIT WORLD DECAY", { posx + 5 , posy + 135, 100, 15 }, 0, WHITE);
    GuiDrawText("#219#EDIT TIME STEP", { posx + 5 , posy + 155, 100, 15 }, 0, WHITE);

    if (GuiButton({ posx + 90, posy + 275, 145, 15 }, "#191#RESET VIEW")){
        camera.target = initialCameraTarget;
        camera.offset = initialCameraOffset;
        camera.zoom = initialCameraZoom;
        camera.rotation = initialCameraRotation;
    }
}

int main() {

    bool ResetScene = false; 
    SetTargetFPS(60);
    InitWindow(1920, 1200, "EXODIAN PARTICLE SIMULATOR");
    icon = LoadImage("..\\Physics_Engine\\Images\\WindowIcon_32x32_RGBA.png");
    SetWindowIcon(icon);

    camera.target = (Vector2){ 0.0f, 0.0f };  
    camera.offset = (Vector2){ 0.0f, 0.0f }; 
    camera.zoom = 1.0f;
    camera.rotation = 0.0f;

    initialCameraTarget = camera.target;
    initialCameraOffset = camera.offset;
    initialCameraZoom = camera.zoom;
    initialCameraRotation = camera.rotation;

    while (!WindowShouldClose()) {
        float wheel = GetMouseWheelMove();
        if (wheel != 0){
            camera.zoom += wheel * 0.05f;
            if (camera.zoom < 0.1f)
                camera.zoom = 0.1f;
            if (camera.zoom > 10.0f)
                camera.zoom = 10.0f;
        }

        if (IsMouseButtonDown(MOUSE_BUTTON_MIDDLE)){
            Vector2 delta = GetMouseDelta();
            delta.x *= -1.0f / camera.zoom;
            delta.y *= -1.0f / camera.zoom;
            camera.target.x += delta.x;
            camera.target.y += delta.y;
        }
        BeginDrawing();
        ClearBackground(BLACK);

        BeginMode2D(camera);
        
        const uint32_t sub_steps = 1;
        const float sub_dt = dt / static_cast<float>(sub_steps); 
        for (uint32_t i(sub_steps); i--;) {
            particle->UpdateLoop(sub_dt, decay);
        }

        EndMode2D();

        if (GuiButton({ 5 + 90, 5 + 255, 145, 15 }, "RESET SCENE")) {
            ResetScene = true;
        }
        if (ResetScene) {
            particle->Clear();
            ResetScene = false;
        }
        
        GUIControls();
        GuiButton({ 5 + 90, 5 + 255, 145, 15 }, "#191#RESET SCENE");
        DrawFPS(1830, 10);
        EndDrawing();
    }

    CloseWindow();
    delete particle;
    UnloadImage(icon);
    return 0;
}


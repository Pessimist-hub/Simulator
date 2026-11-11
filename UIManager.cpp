#include "UIManager.hpp"

#include <algorithm>
#include <string>
#include <raylib.h>

namespace {

constexpr Color Background{10, 28, 48, 225};
constexpr Color Panel{17, 47, 70, 245};
constexpr Color Blue{37, 150, 210, 255};
constexpr Color HoverBlue{63, 180, 226, 255};
constexpr Color Muted{140, 171, 188, 255};

void DrawButton(Rectangle bounds, const char* label, bool enabled = true) {
    const bool hovered = CheckCollisionPointRec(GetMousePosition(), bounds);
    const Color color = !enabled
        ? Color{77, 97, 111, 255}
        : (hovered ? HoverBlue : Blue);

    DrawRectangleRounded(bounds, 0.22f, 10, color);
    const int fontSize = 21;
    const int textWidth = MeasureText(label, fontSize);
    DrawText(label,
             static_cast<int>(bounds.x + (bounds.width - textWidth) * 0.5f),
             static_cast<int>(bounds.y + (bounds.height - fontSize) * 0.5f),
             fontSize, WHITE);
}

bool Button(Rectangle bounds, const char* label, bool enabled = true) {
    const bool hovered = CheckCollisionPointRec(GetMousePosition(), bounds);
    return enabled && hovered && IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
}

Rectangle CenterButton(float centerX, float y, float width = 300.0f) {
    return Rectangle{centerX - width * 0.5f, y, width, 54.0f};
}

Rectangle UpgradeButton(Rectangle panel, int row) {
    return Rectangle{panel.x + 30.0f, panel.y + 108.0f + row * 54.0f,
                     panel.width - 60.0f, 46.0f};
}

void DrawPanel(Rectangle panel) {
    DrawRectangleRounded(panel, 0.06f, 12, Background);
    DrawRectangleRoundedLines(panel, 0.06f, 12, Color{72, 158, 190, 255});
}

} // namespace

void UIManager::Update(Map& map, Player& player, UpgradeManager& upgrades,
                       float deltaTime) {
    if (screen == Screen::Playing || screen == Screen::PlayingUpgrades) {
        if (map.TrashLeft() == 0) {
            wonInTime = true;
            player.coins += OnTimeBonus;
            screen = Screen::Victory;
            return;
        }

        if (screen == Screen::Playing && IsKeyPressed(KEY_ESCAPE)) {
            screen = Screen::PauseMenu;
            return;
        }

        if (IsKeyPressed(KEY_U)) {
            screen = screen == Screen::Playing
                ? Screen::PlayingUpgrades
                : Screen::Playing;
            return;
        }

        if (deltaTime > 0.0f) {
            waveAnnouncementTimer = std::max(
                0.0f, waveAnnouncementTimer - deltaTime);
            challengeTimeRemaining = std::max(
                0.0f, challengeTimeRemaining - deltaTime);
            if (challengeTimeRemaining == 0.0f) {
                ++waveNumber;
                const int trashToSpawn = FirstWaveTrashCount +
                    (waveNumber - 1) * AdditionalTrashPerWave;
                lastWaveTrashCount = map.SpawnTrashWave(
                    trashToSpawn, player.position);
                challengeTimeRemaining = ChallengeDuration;
                waveAnnouncementTimer = 5.0f;
            }
        }
    }

    if (screen == Screen::MainMenu) {
        const float centerX = GetScreenWidth() * 0.5f;
        const float firstY = GetScreenHeight() * 0.5f + 10.0f;
        if (Button(CenterButton(centerX, firstY), "Start Joc")) {
            StartNewGame(map, player, upgrades);
        } else if (Button(CenterButton(centerX, firstY + 70.0f), "Upgrade-uri")) {
            screen = Screen::MainMenuUpgrades;
        } else if (Button(CenterButton(centerX, firstY + 140.0f), "Iesire")) {
            screen = Screen::Exit;
        }
    } else if (screen == Screen::MainMenuUpgrades) {
        const float centerX = GetScreenWidth() * 0.5f;
        const float firstY = GetScreenHeight() * 0.5f + 70.0f;
        if (IsKeyPressed(KEY_ESCAPE) ||
            Button(CenterButton(centerX, firstY), "Inapoi la meniu")) {
            screen = Screen::MainMenu;
        }
    } else if (screen == Screen::Playing) {
        if (Button(Rectangle{GetScreenWidth() - 208.0f, 22.0f, 184.0f, 44.0f},
                   "Upgrade-uri [U]")) {
            screen = Screen::PlayingUpgrades;
        }
    } else if (screen == Screen::PlayingUpgrades) {
        const Rectangle panel{GetScreenWidth() * 0.5f - 300.0f,
                              GetScreenHeight() * 0.5f - 250.0f, 600.0f, 500.0f};

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            const Vector2 mouse = GetMousePosition();
            if (CheckCollisionPointRec(mouse, UpgradeButton(panel, 0))) {
                upgrades.BuySpeed(player);
            } else if (CheckCollisionPointRec(mouse, UpgradeButton(panel, 1))) {
                upgrades.BuyRange(player);
            } else if (CheckCollisionPointRec(mouse, UpgradeButton(panel, 2))) {
                upgrades.BuyCoins(player);
            } else if (CheckCollisionPointRec(mouse, UpgradeButton(panel, 3))) {
                upgrades.BuyStamina(player);
            } else if (CheckCollisionPointRec(mouse, UpgradeButton(panel, 4))) {
                upgrades.BuyRegeneration(player);
            } else if (CheckCollisionPointRec(mouse, UpgradeButton(panel, 5))) {
                screen = Screen::Playing;
            }
        }

        if (IsKeyPressed(KEY_ESCAPE) || IsKeyPressed(KEY_U)) {
            screen = Screen::Playing;
        }
    } else if (screen == Screen::PauseMenu) {
        const float centerX = GetScreenWidth() * 0.5f;
        const float firstY = GetScreenHeight() * 0.5f - 10.0f;
        if (IsKeyPressed(KEY_ESCAPE) ||
            Button(CenterButton(centerX, firstY), "Continua jocul")) {
            screen = Screen::Playing;
        } else if (Button(CenterButton(centerX, firstY + 70.0f),
                          "Meniu principal")) {
            map.Init();
            player = Player(Point(map.width * 0.5f, 0.0f, map.depth * 0.5f),
                            0, 2.2f, 1.5f);
            upgrades.Reset();
            screen = Screen::MainMenu;
        } else if (Button(CenterButton(centerX, firstY + 140.0f), "Iesire")) {
            screen = Screen::Exit;
        }
    } else if (screen == Screen::Victory) {
        const float centerX = GetScreenWidth() * 0.5f;
        const float firstY = GetScreenHeight() * 0.5f + 74.0f;
        if (Button(CenterButton(centerX, firstY), "Joaca din nou")) {
            StartNewGame(map, player, upgrades);
        } else if (Button(CenterButton(centerX, firstY + 70.0f), "Meniu Principal")) {
            map.Init();
            player = Player(Point(map.width * 0.5f, 0.0f, map.depth * 0.5f),
                            0, 2.2f, 1.5f);
            upgrades.Reset();
            screen = Screen::MainMenu;
        }
    }
}

void UIManager::DrawOverlay(const Player& player,
                            const UpgradeManager& upgrades) const {
    const float centerX = GetScreenWidth() * 0.5f;
    const float centerY = GetScreenHeight() * 0.5f;

    if (screen == Screen::MainMenu) {
        const Rectangle panel{centerX - 235.0f, centerY - 250.0f, 470.0f, 470.0f};
        DrawPanel(panel);
        DrawText("ISLAND CLEANER", static_cast<int>(centerX - 183.0f),
                 static_cast<int>(panel.y + 48.0f), 35, WHITE);
        DrawText("Curata insula. Protejeaza natura.",
                 static_cast<int>(centerX - 159.0f),
                 static_cast<int>(panel.y + 99.0f), 18, Color{171, 217, 229, 255});
        const float firstY = centerY + 10.0f;
        DrawButton(CenterButton(centerX, firstY), "Start Joc");
        DrawButton(CenterButton(centerX, firstY + 70.0f), "Upgrade-uri");
        DrawButton(CenterButton(centerX, firstY + 140.0f), "Iesire");
    } else if (screen == Screen::MainMenuUpgrades) {
        const Rectangle panel{centerX - 255.0f, centerY - 230.0f, 510.0f, 460.0f};
        DrawPanel(panel);
        DrawText("MAGAZIN DE UPGRADE-URI",
                 static_cast<int>(centerX - 205.0f),
                 static_cast<int>(panel.y + 35.0f), 26, WHITE);
        DrawText("Viteza: +0.45 unitati/secunda",
                 static_cast<int>(panel.x + 42.0f),
                 static_cast<int>(panel.y + 100.0f), 18, SKYBLUE);
        DrawText("Raza de colectare: +0.35 unitati",
                 static_cast<int>(panel.x + 42.0f),
                 static_cast<int>(panel.y + 140.0f), 18, SKYBLUE);
        DrawText("Mai multe monede pentru fiecare deseu",
                 static_cast<int>(panel.x + 42.0f),
                 static_cast<int>(panel.y + 180.0f), 18, SKYBLUE);
        DrawText("Stamina maxima: +25 | Regenerare: +5/sec",
                 static_cast<int>(panel.x + 42.0f),
                 static_cast<int>(panel.y + 220.0f), 18, SKYBLUE);
        DrawText("Upgrade-urile se cumpara in joc, cu monede.",
                 static_cast<int>(panel.x + 42.0f),
                 static_cast<int>(panel.y + 285.0f), 16, Muted);
        DrawButton(CenterButton(centerX, centerY + 70.0f), "Inapoi la meniu");
    } else if (screen == Screen::Playing) {
        DrawRectangleRounded(Rectangle{GetScreenWidth() - 208.0f, 22.0f, 184.0f, 44.0f},
                             0.2f, 8, Color{17, 65, 91, 220});
        DrawText("Upgrade-uri [U]",
                 GetScreenWidth() - 190, 34, 18, WHITE);
    } else if (screen == Screen::PauseMenu) {
        DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(),
                      Color{4, 25, 38, 190});
        const Rectangle panel{centerX - 250.0f, centerY - 220.0f, 500.0f, 430.0f};
        DrawPanel(panel);
        DrawText("JOC IN PAUZA", static_cast<int>(centerX - 143.0f),
                 static_cast<int>(panel.y + 43.0f), 32, WHITE);
        DrawText("Apasa Esc ca sa continui jocul.",
                 static_cast<int>(centerX - 145.0f),
                 static_cast<int>(panel.y + 94.0f), 17, Muted);
        const float firstY = centerY - 10.0f;
        DrawButton(CenterButton(centerX, firstY), "Continua jocul");
        DrawButton(CenterButton(centerX, firstY + 70.0f), "Meniu principal");
        DrawButton(CenterButton(centerX, firstY + 140.0f), "Iesire");
    } else if (screen == Screen::PlayingUpgrades) {
        const Rectangle panel{centerX - 300.0f, centerY - 250.0f, 600.0f, 500.0f};
        DrawPanel(panel);
        DrawText("UPGRADE-URI", static_cast<int>(panel.x + 30.0f),
                 static_cast<int>(panel.y + 20.0f), 28, WHITE);
        DrawText(TextFormat("Monede disponibile: %i", player.coins),
                 static_cast<int>(panel.x + 30.0f),
                 static_cast<int>(panel.y + 60.0f), 18, GOLD);

        DrawButton(UpgradeButton(panel, 0),
                   TextFormat("Viteza +0.45 | nivel %i | %i monede",
                              upgrades.SpeedLevel(), upgrades.SpeedPrice()),
                   player.coins >= upgrades.SpeedPrice());
        DrawButton(UpgradeButton(panel, 1),
                   TextFormat("Raza +0.35 | nivel %i | %i monede",
                              upgrades.RangeLevel(), upgrades.RangePrice()),
                   player.coins >= upgrades.RangePrice());
        DrawButton(UpgradeButton(panel, 2),
                   TextFormat("Monede/deseu x%i | nivel %i | %i monede",
                              player.coinMultiplier + 1, upgrades.CoinLevel(),
                              upgrades.CoinPrice()),
                   player.coins >= upgrades.CoinPrice());
        DrawButton(UpgradeButton(panel, 3),
                   TextFormat("Stamina maxima +25 | nivel %i | %i monede",
                              upgrades.StaminaLevel(), upgrades.StaminaPrice()),
                   player.coins >= upgrades.StaminaPrice());
        DrawButton(UpgradeButton(panel, 4),
                   TextFormat("Regenerare stamina +5 | nivel %i | %i monede",
                              upgrades.RegenerationLevel(),
                              upgrades.RegenerationPrice()),
                   player.coins >= upgrades.RegenerationPrice());
        DrawButton(UpgradeButton(panel, 5), "Inchide  [U / Esc]");
        DrawText("Jocul continua in timp real cat timp magazinul este deschis.",
                 static_cast<int>(panel.x + 35.0f),
                 static_cast<int>(panel.y + 455.0f), 15, WHITE);
    } else if (screen == Screen::Victory) {
        DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(),
                      Color{4, 25, 38, 195});
        const Rectangle panel{centerX - 260.0f, centerY - 170.0f, 520.0f, 390.0f};
        DrawPanel(panel);
        DrawText("INSULA ESTE CURATA!",
                 static_cast<int>(centerX - 198.0f),
                 static_cast<int>(panel.y + 55.0f), 32, LIME);
        DrawText(wonInTime ? "Felicitari! Ai curatat insula la timp."
                           : "Ai curatat insula in prelungiri!",
                 static_cast<int>(centerX - 205.0f),
                 static_cast<int>(panel.y + 108.0f), 18, WHITE);
        DrawText(TextFormat("Monede castigate: %i", player.coins),
                 static_cast<int>(centerX - 101.0f),
                 static_cast<int>(panel.y + 151.0f), 18, GOLD);
        if (wonInTime) {
            DrawText(TextFormat("Bonus pentru curatenie rapida: +%i monede",
                                OnTimeBonus),
                     static_cast<int>(centerX - 170.0f),
                     static_cast<int>(panel.y + 181.0f), 16, LIME);
        }
        DrawButton(CenterButton(centerX, centerY + 74.0f), "Joaca din nou");
        DrawButton(CenterButton(centerX, centerY + 144.0f), "Meniu Principal");
    }
}

bool UIManager::ShouldExit() const {
    return screen == Screen::Exit;
}

bool UIManager::ShouldSimulate() const {
    return screen == Screen::Playing || screen == Screen::PlayingUpgrades;
}

bool UIManager::ShouldCollectTrash() const {
    return screen == Screen::Playing;
}

float UIManager::ChallengeTimeRemaining() const {
    return challengeTimeRemaining;
}

int UIManager::WaveNumber() const {
    return waveNumber;
}

int UIManager::LastWaveTrashCount() const {
    return lastWaveTrashCount;
}

bool UIManager::IsWaveAnnouncementVisible() const {
    return waveAnnouncementTimer > 0.0f;
}

void UIManager::StartNewGame(Map& map, Player& player, UpgradeManager& upgrades) {
    map.Init();
    player = Player(Point(map.width * 0.5f, 0.0f, map.depth * 0.5f), 0, 2.2f, 1.5f);
    upgrades.Reset();
    challengeTimeRemaining = ChallengeDuration;
    waveAnnouncementTimer = 0.0f;
    waveNumber = 0;
    lastWaveTrashCount = 0;
    wonInTime = false;
    screen = Screen::Playing;
}

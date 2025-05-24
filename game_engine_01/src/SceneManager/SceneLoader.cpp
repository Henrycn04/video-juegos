#include "SceneLoader.hpp"
#include <iostream>
#include "../Components/RigidBodyComponent.hpp"
#include "../Components/SpriteComponent.hpp"
#include "../Components/TransformComponent.hpp"
#include "../Components/CircleColliderComponent.hpp"
#include "../Components/HealthComponent.hpp"
#include "../Components/AnimationComponent.hpp"
#include "../Components/ScriptComponent.hpp"
#include "../Components/TextComponent.hpp"
#include "../Components/ClickableComponent.hpp"
#include "../Components/DrawableComponent.hpp"
#include "../Components/EnemyComponent.hpp"
#include "../Components/EffectReceiverComponent.hpp"
#include "../Components/DamageChargeComponent.hpp"
#include "../Components/SprintChargeComponent.hpp"
#include "../Components/SlowChargeComponent.hpp"
#include "../Game/Game.hpp"
SceneLoader::SceneLoader() {
    std::cout << "[SceneLoader] Se ejecuta constructor" << std::endl;
}
SceneLoader::~SceneLoader(){
    std::cout << "[SceneLoader] Se ejecuta destructor" << std::endl;

}
void SceneLoader::LoadScene(const std::string& scenePath, sol::state& lua, 
    std::unique_ptr<AssetManager>& assetManager, std::unique_ptr<ControllerManager>& controllerManager, 
    std::unique_ptr<Registry>& registry, SDL_Renderer* renderer) {
    sol::load_result script_result = lua.load_file(scenePath);
    if (!script_result.valid()) {
        sol::error err = script_result;
        std::string errMessage = err.what();
        std::cerr << "[SceneLoader] Error al cargar el archivo de escena: " << errMessage << std::endl;
        return;
    }
    lua.script_file(scenePath);
    sol::table scene = lua["scene"];

    sol::table background = scene["background"];
    LoadBackground(renderer, background, assetManager);


    sol::table sprites = scene["sprites"];
    LoadSprites(renderer, sprites, assetManager);

    sol::table fonts = scene["fonts"];
    LoadFonts(fonts, assetManager);
    

    sol::table keys = scene["keys"];
    LoadKey(keys, controllerManager);

    sol::table buttons = scene["buttons"];
    LoadButtons(buttons, controllerManager);

    sol::table entities = scene["entities"];
    LoadEntities(lua, entities, registry);
    
    std::cout << "[SceneLoader] Se cargó la escena correctamente." << std::endl;

}
void SceneLoader::LoadBackground(SDL_Renderer* renderer, const sol::table& backgrounds, std::unique_ptr<AssetManager>& assetManager){
    int index = 0;

    while (true) {
        sol::optional<sol::table> hasBackground = backgrounds[index];
        if (hasBackground == sol::nullopt) {
            break;
        }

        sol::table background = backgrounds[index];

        std::string assetId = background["assetId"];

        std::string filePath = background["file_path"];

        assetManager->AddTexture(renderer, assetId, filePath);

        index++;
    }
}


void SceneLoader::LoadSprites(SDL_Renderer* renderer, const sol::table& sprites, std::unique_ptr<AssetManager>& assetManager){
    int index = 0;
    while (true) {
        sol::optional<sol::table> hasSprite = sprites[index];
        if (hasSprite == sol::nullopt) {
            break;
        }
        sol::table sprite = sprites[index];

        std::string assetId = sprite["assetId"];
        std::string filePath = sprite["file_path"];

        assetManager->AddTexture(renderer, assetId, filePath);

        index++;
    }
    std::cout << "[SceneLoader] Se cargaron los sprites correctamente." << std::endl;
}
void SceneLoader::LoadFonts(const sol::table& fonts, std::unique_ptr<AssetManager>& assetManager){
    int index = 0;
    while (true) {
        sol::optional<sol::table> hasFont = fonts[index];
        if (hasFont == sol::nullopt) {
            break;
        }
        sol::table font = fonts[index];

        std::string fontId = font["fontId"];
        std::string filePath = font["filePath"];
        int fontSize = font["fontSize"];

        assetManager->AddFont(fontId, filePath, fontSize);

        index++;
    }
}
    // fonts loader
void SceneLoader::LoadKey(const sol::table& keys, std::unique_ptr<ControllerManager>& controllerManager){
    int index = 0;
    while (true) {
        sol::optional<sol::table> hasKey = keys[index];
        if (hasKey == sol::nullopt) {
            break;
        }
        sol::table key = keys[index];

        std::string action = key["name"];
        int keyCode = key["key"];

        controllerManager->AddActionKey(action, keyCode);

        index++;
    }

}
void SceneLoader::LoadButtons(const sol::table& buttons, std::unique_ptr<ControllerManager>& controllerManager){
    int index = 0;
    while (true) {
        sol::optional<sol::table> hasButton = buttons[index];
        if (hasButton == sol::nullopt) {
            break;
        }
        sol::table button = buttons[index];

        std::string action = button["name"];
        int buttonCode = button["button"];

        controllerManager->AddMouseButton(action, buttonCode);

        index++;
    }
}
void SceneLoader::LoadEntities(sol::state& lua, const sol::table& entities, std::unique_ptr<Registry>& registry){
    int index = 0;
    while (true) {
        sol::optional<sol::table> hasEntity = entities[index];
        if (hasEntity == sol::nullopt) {
            break;
        }

        sol::table entity = entities[index];


        Entity newEntity = registry->CreateEntity();
        sol::optional<sol::table> components = entity["components"];
        if (components != sol::nullopt) {
            sol::table components = entity["components"];
            
            sol::optional<sol::table> hasAnimation = components["animation"];
            if (hasAnimation != sol::nullopt) {
                newEntity.AddComponent<AnimationComponent>(
                    components["animation"]["num_frames"],
                    components["animation"]["frame_speed_rate"],
                    components["animation"]["loop"]

                );
            }
            sol::optional<sol::table> hasDrawable = components["drawable"];
            if (hasDrawable != sol::nullopt) {
                newEntity.AddComponent<DrawableComponent>();
            }

            
            sol::optional<sol::table> hasCircleCollider = components["circle_collider"];
            if (hasCircleCollider != sol::nullopt) {
                newEntity.AddComponent<CircleColliderComponent>(
                    components["circle_collider"]["radius"],
                    components["circle_collider"]["width"],
                    components["circle_collider"]["height"]
                );
            }
            sol::optional<sol::table> hasHealth = components["health"];
            if (hasHealth != sol::nullopt) {
                newEntity.AddComponent<HealthComponent>(
                    components["health"]["health"],
                    components["health"]["maxHealth"],
                    components["health"]["isPlayer"],
                    components["health"]["damage"],
                    components["health"]["attack_timeout"]
                );
            }
            sol::optional<sol::table> hasEnemy = components["enemy"];
            if (hasEnemy != sol::nullopt) {
                newEntity.AddComponent<EnemyComponent>(
                    components["enemy"]["amountToSpawn"],
                    newEntity.GetId(),
                    components["enemy"]["totalAmount"]

                );
                Game::GetInstance().enemiesLeft += newEntity.GetComponent<EnemyComponent>().totalAmount;
            }


            sol::optional<sol::table> hasClickable = components["clickable"];
            if (hasClickable != sol::nullopt) {
                newEntity.AddComponent<ClickableComponent>(
                );
            }
            sol::optional<sol::table> hasRigidBody = components["rigidbody"];
            if (hasRigidBody != sol::nullopt) {
                newEntity.AddComponent<RigidBodyComponent>(
                    glm::vec2(components["rigidbody"]["velocity"]["x"], 
                        components["rigidbody"]["velocity"]["y"])
                );
            }
            sol::optional<sol::table> hasScript = components["script"];
            if (hasScript != sol::nullopt) {
                lua["update"] = sol::nil;
                lua["onClick"] = sol::nil;

                std::string path = components["script"]["path"];
                lua.script_file(path);

                sol::optional<sol::function> hasOnClick = lua["on_click"];
                sol::function onClick = sol::nil;
                if (hasOnClick != sol::nullopt) {
                    onClick = lua["on_click"];
                }
                

                sol::optional<sol::function> hasUpdate = lua["update"];
                sol::function update = sol::nil;
                if (hasUpdate != sol::nullopt) {
                    update = lua["update"];
                }
                newEntity.AddComponent<ScriptComponent>(update, onClick);
            }
            sol::optional<sol::table> hasSprite = components["sprite"];
            if (hasSprite != sol::nullopt) {
                newEntity.AddComponent<SpriteComponent>(
                    components["sprite"]["assetId"],
                    components["sprite"]["width"],
                    components["sprite"]["height"],
                    components["sprite"]["src_rect"]["x"],
                    components["sprite"]["src_rect"]["y"],
                    components["sprite"]["active"]
                );
            }

            sol::optional<sol::table> hasText = components["text"];
            if (hasText != sol::nullopt) {
                newEntity.AddComponent<TextComponent>(
                    components["text"]["text"],
                    components["text"]["fontId"],
                    components["text"]["r"],
                    components["text"]["g"],
                    components["text"]["b"],
                    components["text"]["a"]
                );
            }


            sol::optional<sol::table> hasTransform = components["transform"];
            if (hasTransform != sol::nullopt) {
                newEntity.AddComponent<TransformComponent>(
                    glm::vec2(components["transform"]["position"]["x"], 
                        components["transform"]["position"]["y"]),
                    glm::vec2(components["transform"]["scale"]["x"], 
                        components["transform"]["scale"]["y"]),
                    components["transform"]["rotation"]
                );
            }

            sol::optional<sol::table> hasEffectReceiver = components["effect_receiver"];
            if (hasEffectReceiver != sol::nullopt) {
                newEntity.AddComponent<EffectReceiverComponent>(
                );
            }

            sol::optional<sol::table> hasDamageCharge = components["damageCharge"];
            if (hasDamageCharge != sol::nullopt) {
                newEntity.AddComponent<DamageChargeComponent>(
                    components["damageCharge"]["totalCharge"],
                    components["damageCharge"]["initialCharge"]
                );
            }
            sol::optional<sol::table> hasSprintCharge = components["sprintCharge"];
            if (hasSprintCharge != sol::nullopt) {
                newEntity.AddComponent<SprintChargeComponent>(
                    components["sprintCharge"]["totalCharge"],
                    components["sprintCharge"]["initialCharge"]

                );
            }
            sol::optional<sol::table> hasSlowCharge = components["slowCharge"];
            if (hasSlowCharge != sol::nullopt) {
                newEntity.AddComponent<SlowChargeComponent>(
                    components["slowCharge"]["totalCharge"],
                    components["slowCharge"]["initialCharge"]
                );
            }

        
            
        }
        index++;

    }
}
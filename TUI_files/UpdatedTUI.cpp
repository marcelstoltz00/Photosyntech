#include "ftxui/component/captured_mouse.hpp"
#include "ftxui/component/component.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/dom/elements.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <vector>
#include <list>
#include <memory>
#include <algorithm>
#include "../../../facade/NurseryFacade.h"
#include "../../../composite/PlantGroup.h"
#include "../../../composite/PlantComponent.h"

using namespace ftxui;

std::map<int, PlantComponent*> treeIndexToComponent;
std::vector<std::string> treeEntries;
int selectedTreeIndex = -1;
int previousSelectedTreeIndex = -1;
int plantInfoScrollY = 0;
int selectedInfoScrollY = 0;
PlantComponent* selectedInventoryComponent = nullptr;

std::string inventoryStatusText = "Inventory: Initialising...";
std::string selectedInfoText = "Component details will appear here.";
bool showCreateGroupDialogue = false;
bool showMoveDialogue = false;
int groupCounter = 1;

PlantComponent* componentToMove = nullptr;
PlantComponent* targetGroup = nullptr;

Component mainContainer;
Component groupDialogueContainer;
Component moveDialogueContainer;
Component main_ui;

void buildTreeEntries(
    PlantComponent* component,
    std::vector<std::string>& entries,
    std::map<int, PlantComponent*>& indexMap,
    int depth = 0)
{
    if (!component) return;

    int currentIndex = entries.size();
    std::string indent(depth * 2, ' ');
    std::string prefix = depth > 0 ? "├─ " : "📦 ";

    std::string icon = "";
    if (component->getType() == ComponentType::PLANT_GROUP) {
        icon = "📁 ";
    } else {
        icon = "🌱 ";
    }

    entries.push_back(indent + prefix + icon + component->getName());
    indexMap[currentIndex] = component;

    if (component->getType() == ComponentType::PLANT_GROUP) {
        PlantGroup* group = dynamic_cast<PlantGroup*>(component);
        if (group) {
            std::list<PlantComponent*> children = *group->getPlants();
            for (PlantComponent* child : children) {
                buildTreeEntries(child, entries, indexMap, depth + 1);
            }
        }
    }
}

void refreshInventoryView(NurseryFacade& nursery) {
    treeEntries.clear();
    treeIndexToComponent.clear();

    selectedInfoText = "Select an item in the inventory.";
    inventoryStatusText = "Inventory refreshed.";

    PlantComponent* root = nursery.getInventoryRoot();
    if (root) {
        buildTreeEntries(root, treeEntries, treeIndexToComponent);
    }

    if (selectedTreeIndex >= 0 && selectedTreeIndex < treeEntries.size()) {
        auto it = treeIndexToComponent.find(selectedTreeIndex);
        if (it != treeIndexToComponent.end()) {
            selectedInventoryComponent = it->second;
        }
    }
}

int main() {
    std::ofstream cerrLog("plant_manager_debug.txt");
    std::streambuf* oldCerrBuf = std::cerr.rdbuf();
    std::cerr.rdbuf(cerrLog.rdbuf());

    auto screen = ScreenInteractive::Fullscreen();
    NurseryFacade nursery;

    auto plantTypes = nursery.getAvailablePlantTypes();
    int plantSelectorIndex = 0;
    std::string plantInfoText = "No plant selected";
    std::string statusText = "Status: Ready";
    PlantComponent* currentPlant = nullptr;

    auto plantSelector = Dropdown(&plantTypes, &plantSelectorIndex);

    auto createButton = Button("Create Plant", [&] {
        if (plantSelectorIndex >= 0 && plantSelectorIndex < plantTypes.size()) {
            std::string selectedType = plantTypes[plantSelectorIndex];
            currentPlant = nursery.createPlant(selectedType);
            if (currentPlant) {
                plantInfoText = currentPlant->getDecorator()->getInfo();
                statusText = "Status: Created new " + selectedType + " and added to Inventory.";
                refreshInventoryView(nursery);
            }
        }
    });

    auto waterButton = Button("Water Plant", [&] {
        if (currentPlant) {
            nursery.waterPlant(currentPlant);
            plantInfoText = currentPlant->getDecorator()->getInfo();
            statusText = "Status: Watered plant";
        }
    });

    auto sunButton = Button("Add Sunlight", [&] {
        if (currentPlant) {
            nursery.addSunlight(currentPlant);
            plantInfoText = currentPlant->getDecorator()->getInfo();
            statusText = "Status: Added sunlight";
        }
    });

    auto infoButton = Button("Get Info", [&] {
        if (currentPlant) {
            plantInfoText = currentPlant->getDecorator()->getInfo();
            statusText = "Status: Updated info";
        }
    });

    auto refreshButton = Button("Refresh", [&] {
        refreshInventoryView(nursery);
    });

    auto startTickButton = Button("Start Ticker", [&] {
        if (nursery.startNurseryTick()) {
            inventoryStatusText = "Inventory: Ticker Started.";
        } else {
            inventoryStatusText = "Inventory: Ticker already running.";
        }
    });

    auto stopTickButton = Button("Stop Ticker", [&] {
        if (nursery.stopNurseryTick()) {
            inventoryStatusText = "Inventory: Ticker Stopped.";
        } else {
            inventoryStatusText = "Inventory: Ticker was not running.";
        }
        refreshInventoryView(nursery);
    });

    auto createGroupButton = Button("Create Group", [&] {
        showCreateGroupDialogue = true;

        mainContainer->SetActiveChild(groupDialogueContainer.get());
    });


    auto confirmGroupButton = Button("Create", [&] {
            PlantGroup* newGroup = nursery.createPlantGroup();

            if (selectedInventoryComponent &&
                selectedInventoryComponent->getType() == ComponentType::PLANT_GROUP) {
                nursery.addComponentToGroup(selectedInventoryComponent, newGroup);
            } else {
                nursery.addComponentToGroup(nursery.getInventoryRoot(), newGroup);
            }

            inventoryStatusText = "Created Group " + std::to_string(groupCounter);
            groupCounter++;
            showCreateGroupDialogue = false;
            refreshInventoryView(nursery);
            mainContainer->SetActiveChild(main_ui.get());
    });

    auto cancelGroupButton = Button("Cancel", [&] {
        showCreateGroupDialogue = false;
        mainContainer->SetActiveChild(main_ui.get());
    });

    groupDialogueContainer = Container::Vertical({
        Container::Horizontal({
            confirmGroupButton,
            cancelGroupButton
        })
    });

    std::vector<std::string> groupList;
    std::vector<PlantComponent*> groupComponents;
    int selectedGroupIndex = 0;

    std::function<void()> buildGroupList = [&]() {
        groupList.clear();
        groupComponents.clear();
        selectedGroupIndex = 0;

        PlantComponent* root = nursery.getInventoryRoot();
        groupList.push_back("Root Inventory");
        groupComponents.push_back(root);

        std::function<void(PlantComponent*, int)> findGroups = [&](PlantComponent* comp, int depth) {
            if (comp && comp->getType() == ComponentType::PLANT_GROUP) {
                PlantGroup* group = dynamic_cast<PlantGroup*>(comp);
                if (group && comp != nursery.getInventoryRoot() && comp != componentToMove) {
                    std::string indent(depth * 2, ' ');
                    groupList.push_back(indent + "└─ " + comp->getName());
                    groupComponents.push_back(comp);

                    std::list<PlantComponent*> children = *group->getPlants();
                    for (PlantComponent* child : children) {
                        findGroups(child, depth + 1);
                    }
                }
            }
        };

        if (root && root->getType() == ComponentType::PLANT_GROUP) {
            PlantGroup* rootGroup = dynamic_cast<PlantGroup*>(root);
            std::list<PlantComponent*> children = *rootGroup->getPlants();
            for (PlantComponent* child : children) {
                findGroups(child, 1);
            }
        }
    };

    auto addToGroupButton = Button("Move to Group", [&] {
        if (selectedInventoryComponent &&
            selectedInventoryComponent->getType() != ComponentType::PLANT_GROUP) {
            componentToMove = selectedInventoryComponent;
            showMoveDialogue = true;

            buildGroupList();

            mainContainer->SetActiveChild(moveDialogueContainer.get());
        } else {
            inventoryStatusText = "Select a plant (not a group) to move.";
        }
    });

    auto groupSelectMenu = Menu(&groupList, &selectedGroupIndex);

    auto confirmMoveButton = Button("Move", [&] {
        if (selectedGroupIndex >= 0 && selectedGroupIndex < groupComponents.size()) {
            targetGroup = groupComponents[selectedGroupIndex];

            nursery.removeComponentFromInventory(componentToMove);

            nursery.addComponentToGroup(targetGroup, componentToMove);

            inventoryStatusText = "Moved component to " + targetGroup->getName();
            showMoveDialogue = false;
            refreshInventoryView(nursery);
            mainContainer->SetActiveChild(main_ui.get());
        }
    });

    auto cancelMoveButton = Button("Cancel", [&] {
        showMoveDialogue = false;
        mainContainer->SetActiveChild(main_ui.get());
    });

    moveDialogueContainer = Container::Vertical({
        groupSelectMenu,
        Container::Horizontal({
            confirmMoveButton,
            cancelMoveButton
        })
    });

auto on_menu_change = [&] {
    if (selectedTreeIndex >= 0 && selectedTreeIndex < treeEntries.size()) {
        auto it = treeIndexToComponent.find(selectedTreeIndex);
        if (it != treeIndexToComponent.end()) {
            selectedInventoryComponent = it->second;

            if (selectedInventoryComponent->getType() == ComponentType::PLANT_GROUP) {
                selectedInfoText = selectedInventoryComponent->getInfo();
            } else {
                selectedInfoText = selectedInventoryComponent->getDecorator()->getInfo();
            }

            inventoryStatusText = "Status: Selected item in Inventory.";
        }
    }
};

MenuOption menuOption;
menuOption.on_change = on_menu_change;

auto treeMenu = Menu(&treeEntries, &selectedTreeIndex, menuOption);

    int tabSelected = 0;
    std::vector<std::string> tabTitles = {
        "Plant Manager (Builder)",
        "Inventory (Composite/Singleton)"
    };

    auto tabToggle = Toggle(&tabTitles, &tabSelected);

    // FIXED: Scrollable plant info - using simpler approach
    auto plantInfoRenderer = Renderer([&] {
        return paragraph(plantInfoText) | color(Color::GrayLight);
    });

    auto tab1Content = Container::Vertical({
        plantSelector,
        createButton,
        Container::Horizontal({
            waterButton,
            sunButton,
            infoButton,
        }),
        plantInfoRenderer,
    });

    // FIXED: Scrollable selected info with mouse wheel support
    auto selectedInfoRenderer_Base = Renderer([&] {
        return paragraph(selectedInfoText) | color(Color::GrayLight) |
                vscroll_indicator | yframe |
                focusPositionRelative(0, selectedInfoScrollY);
    }) | size(HEIGHT, EQUAL, 10);

    auto selectedInfoRenderer = CatchEvent(selectedInfoRenderer_Base, [&](Event event) {
        // Mouse wheel scrolling (works without focus)
        if (event.is_mouse() && event.mouse().button == Mouse::WheelUp) {
            selectedInfoScrollY = std::max(0, selectedInfoScrollY - 1);
            return true;
        }
        if (event.is_mouse() && event.mouse().button == Mouse::WheelDown) {
            selectedInfoScrollY++;
            return true;
        }
        
        // Arrow key scrolling when focused
        if (event == Event::ArrowUp) {
            selectedInfoScrollY = std::max(0, selectedInfoScrollY - 1);
            return true;
        }
        if (event == Event::ArrowDown) {
            selectedInfoScrollY++;
            return true;
        }
        
        // Click to focus
        if (event.is_mouse() && event.mouse().button == Mouse::Left && event.mouse().motion == Mouse::Pressed) {
            selectedInfoRenderer_Base->TakeFocus();
            return true;
        }
        
        return false;
    });

    auto tab2Content = Container::Vertical({
        Container::Horizontal({
            refreshButton,
            createGroupButton,
            addToGroupButton,
        }),
        Container::Horizontal({
            startTickButton,
            stopTickButton,
        }),
        treeMenu | size(HEIGHT, EQUAL, 15),
        selectedInfoRenderer,
    });

    auto tabContainer = Container::Tab({
        tab1Content,
        tab2Content,
    }, &tabSelected);

    main_ui = Container::Vertical({
        tabToggle,
        tabContainer,
    });

    mainContainer = Container::Stacked({
        main_ui,
        groupDialogueContainer,
        moveDialogueContainer,
    });

auto mainRenderer = Renderer(mainContainer, [&] {
        Element Dialogue = text("");

        if (showCreateGroupDialogue) {
            Dialogue = dbox({
                text(""),
                vbox({
                    window(text("Create New Group") | bold | color(Color::Yellow), vbox({
                text("Group Name:"),
                text("Create a new, empty group?"),

                separator(),
                hbox({
                    confirmGroupButton->Render() | color(Color::Green),
                    text(" "),
                    cancelGroupButton->Render() | color(Color::Red)
                })
            }))
                }) | center | size(WIDTH, LESS_THAN, 50)
            });
        } else if (showMoveDialogue) {
            Dialogue = dbox({
                text(""),
                hbox({
                    filler(),

                    vbox({
                window(text("Move Component") | bold | color(Color::Yellow), vbox({
                            text("Select target group:") | color(Color::GrayLight),
                            groupSelectMenu->Render() | frame | size(HEIGHT, LESS_THAN, 10),
                            separator(),
                            hbox({
                                confirmMoveButton->Render() | color(Color::Green),
                                text(" "),
                                cancelMoveButton->Render() | color(Color::Red)
                            })
                }))
                        }) | size(WIDTH, LESS_THAN, 60)
                })
            });
        }

Element tab1View = vbox({
            window(text("Plant Creation") | bold | color(Color::Cyan), vbox({
                hbox(text("Select Plant Type: ") | color(Color::GrayLight), text(plantTypes[plantSelectorIndex]) | bold | color(Color::White)),
                plantSelector->Render(),
                createButton->Render() | color(Color::Green),
            })),
            window(text("Plant Actions") | bold | color(Color::Cyan),
                hbox({
                    waterButton->Render() | color(Color::Blue),
                    text(" "),
                    sunButton->Render() | color(Color::Yellow),
                    text(" "),
                    infoButton->Render() | color(Color::GrayLight),
                })
            ),
            window(text("Current Plant Information") | bold | color(Color::Cyan),
                plantInfoRenderer->Render()
            ),
        });

        Element tab2View = vbox({
            hbox({
                refreshButton->Render() | color(Color::Blue),
                text(" "),
                createGroupButton->Render() | color(Color::Green),
                text(" "),
                addToGroupButton->Render() | color(Color::Yellow),
            }),
            hbox({
                startTickButton->Render() | color(Color::LightGreen),
                text(" "),
                stopTickButton->Render() | color(Color::RedLight),
            }),
            separator(),
            text(inventoryStatusText) | color(Color::Yellow),
            separator(),
            window(text("Inventory Hierarchy") | bold | color(Color::Cyan),
                treeMenu->Render() | frame
            ),
            window(text("Selected Component Info") | bold | color(Color::Cyan),
                selectedInfoRenderer->Render()
            ),
        });

        Element main = vbox({
            hbox({
                text("🌿 Photosyntech Plant Manager 🌿") | bold | center | color(Color::Green),
            }) | border,
            tabToggle->Render(),
            separator(),
            (tabSelected == 0 ? tab1View : tab2View) | flex,
            separator(),
            text(statusText) | border | color(Color::Cyan),
        });

        if (showCreateGroupDialogue || showMoveDialogue) {
            return dbox({
                main,
                Dialogue
            });
        }

        return main;
    });

    refreshInventoryView(nursery);

    screen.Loop(mainRenderer);

    try {
        nursery.stopNurseryTick();
    } catch (const std::exception& e) {
        std::cerr << "Error during cleanup: " << e.what() << std::endl;
    }

    std::cerr.rdbuf(oldCerrBuf);

    return 0;
}
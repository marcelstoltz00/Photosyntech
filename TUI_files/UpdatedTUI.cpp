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
PlantComponent* selectedInventoryComponent = nullptr;

std::string inventoryStatusText = "Inventory: Initialising...";
std::string selectedInfoText = "Component details will appear here.";
std::string groupNameInput = "";
bool showCreateGroupDialog = false;
bool showMoveDialog = false;
int groupCounter = 1; 

PlantComponent* componentToMove = nullptr;
PlantComponent* targetGroup = nullptr;

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
        showCreateGroupDialog = true;
        groupNameInput = "Group " + std::to_string(groupCounter);
    });

    auto addToGroupButton = Button("Move to Group", [&] {
        if (selectedInventoryComponent && 
            selectedInventoryComponent->getType() != ComponentType::PLANT_GROUP) {
            componentToMove = selectedInventoryComponent;
            showMoveDialog = true;
        } else {
            inventoryStatusText = "Select a plant (not a group) to move.";
        }
    });

    auto selectAsCurrentButton = Button("Use as Current", [&] {
        if (selectedInventoryComponent && 
            selectedInventoryComponent->getType() != ComponentType::PLANT_GROUP) {
            currentPlant = selectedInventoryComponent;
            plantInfoText = currentPlant->getDecorator()->getInfo();
            statusText = "Status: Selected plant from inventory";
        }
    });

    auto groupNameInputComponent = Input(&groupNameInput, "Group name");
    auto confirmGroupButton = Button("Create", [&] {
        if (!groupNameInput.empty()) {
            PlantGroup* newGroup = nursery.createPlantGroup();
            
            if (selectedInventoryComponent && 
                selectedInventoryComponent->getType() == ComponentType::PLANT_GROUP) {
                nursery.addComponentToGroup(selectedInventoryComponent, newGroup);
            } else {
                nursery.addComponentToGroup(nursery.getInventoryRoot(), newGroup);
            }
            
            inventoryStatusText = "Created " + groupNameInput;
            groupCounter++; 
            showCreateGroupDialog = false;
            refreshInventoryView(nursery);
        }
    });
    
    auto cancelGroupButton = Button("Cancel", [&] {
        showCreateGroupDialog = false;
    });

    auto groupDialogContainer = Container::Vertical({
        groupNameInputComponent,
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

    auto groupSelectMenu = Menu(&groupList, &selectedGroupIndex);
    
    auto confirmMoveButton = Button("Move", [&] {
        if (selectedGroupIndex >= 0 && selectedGroupIndex < groupComponents.size()) {
            targetGroup = groupComponents[selectedGroupIndex];
            
            nursery.addComponentToGroup(targetGroup, componentToMove);
            inventoryStatusText = "Moved component to " + targetGroup->getName();
            showMoveDialog = false;
            refreshInventoryView(nursery);
        }
    });
    
    auto cancelMoveButton = Button("Cancel", [&] {
        showMoveDialog = false;
    });

    auto moveDialogContainer = Container::Vertical({
        groupSelectMenu,
        Container::Horizontal({
            confirmMoveButton,
            cancelMoveButton
        })
    });

    auto treeMenu = Menu(&treeEntries, &selectedTreeIndex);
    treeMenu |= CatchEvent([&](Event event) {
        if (event == Event::Return && selectedTreeIndex >= 0) {
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
        return false;
    });

    int tabSelected = 0;
    std::vector<std::string> tabTitles = {
        "Plant Manager (Builder)",
        "Inventory (Composite/Singleton)"
    };

    auto tabToggle = Toggle(&tabTitles, &tabSelected);

    auto tab1Content = Container::Vertical({
        plantSelector,
        createButton,
        Container::Horizontal({
            waterButton,
            sunButton,
            infoButton,
        }),
    });

    auto tab2Content = Container::Vertical({
        Container::Horizontal({
            refreshButton,
            createGroupButton,
            addToGroupButton,
        }),
        Container::Horizontal({
            selectAsCurrentButton,
            startTickButton,
            stopTickButton,
        }),
        treeMenu,
    });

    auto tabContainer = Container::Tab({
        tab1Content,
        tab2Content,
    }, &tabSelected);

    auto mainContainer = Container::Vertical({
        tabToggle,
        tabContainer,
    });

    auto mainRenderer = Renderer(mainContainer, [&] {
        Element dialog = text("");
        
        if (showCreateGroupDialog) {
            dialog = dbox({
                text("") | bgcolor(Color::Black) | dim, 
                vbox({
                    window(text("Create New Group"), vbox({
                        text("Group Name (auto-generated):"),
                        text(groupNameInput) | bold | color(Color::Cyan),
                        separator(),
                        text("This will create: " + groupNameInput),
                        separator(),
                        hbox({
                            confirmGroupButton->Render(),
                            text(" "),
                            cancelGroupButton->Render()
                        })
                    }))
                }) | center | size(WIDTH, LESS_THAN, 50)
            });
        } else if (showMoveDialog) {
            buildGroupList(); 
            dialog = dbox({
                text("") | bgcolor(Color::Black) | dim,
                vbox({
                    window(text("Move Component"), vbox({
                        text("Select target group:"),
                        groupSelectMenu->Render() | frame | size(HEIGHT, LESS_THAN, 10),
                        separator(),
                        hbox({
                            confirmMoveButton->Render(),
                            text(" "),
                            cancelMoveButton->Render()
                        })
                    }))
                }) | center | size(WIDTH, LESS_THAN, 60)
            });
        }

        Element tab1View = vbox({
            window(text("Plant Creation"), vbox({
                hbox(text("Select Plant Type: "), text(plantTypes[plantSelectorIndex]) | bold),
                plantSelector->Render(),
                createButton->Render(),
            })),
            window(text("Plant Actions"), 
                hbox({
                    waterButton->Render(),
                    text(" "),
                    sunButton->Render(),
                    text(" "),
                    infoButton->Render(),
                })
            ),
            window(text("Current Plant Information"), 
                vbox({
                    paragraph(plantInfoText) | size(HEIGHT, LESS_THAN, 15)
                }) | frame
            ),
        });

        Element tab2View = vbox({
            hbox({
                refreshButton->Render(),
                text(" "),
                createGroupButton->Render(),
                text(" "),
                addToGroupButton->Render(),
            }),
            hbox({
                selectAsCurrentButton->Render(),
                text(" "),
                startTickButton->Render(),
                text(" "),
                stopTickButton->Render(),
            }),
            separator(),
            text(inventoryStatusText) | color(Color::Yellow),
            separator(),
            window(text("Inventory Hierarchy"), 
                treeMenu->Render() | frame | size(HEIGHT, LESS_THAN, 15)
            ),
            window(text("Selected Component Info"), 
                vbox({
                    paragraph(selectedInfoText) | size(HEIGHT, LESS_THAN, 10)
                }) | frame
            ),
        });

        Element main = vbox({
            hbox({
                text("🌿 Photosyntech Plant Manager 🌿") | bold | center,
            }) | border,
            tabToggle->Render(),
            separator(),
            (tabSelected == 0 ? tab1View : tab2View) | flex,
            separator(),
            text(statusText) | border,
        });

        if (showCreateGroupDialog || showMoveDialog) {
            return dbox({
                main,
                dialog
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
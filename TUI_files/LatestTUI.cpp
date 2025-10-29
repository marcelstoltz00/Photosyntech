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

using namespace ftxui;

std::map<int, PlantComponent*> treeIndexToComponent;
std::vector<std::string> treeEntries;
int selectedTreeIndex = -1;
int previousSelectedTreeIndex = -1;
int plantInfoScrollY = 0;
int selectedInfoScrollY = 0;
PlantComponent* selectedInventoryComponent = nullptr;

PlantComponent* plantToView = nullptr;
std::string plantDetailText = "No plant selected to view.";
int previousTab = 0;
int tabSelected = 0;

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

void refreshCustomerView(NurseryFacade& nursery, vector<string>& plantNames) {
    plantNames = nursery.getMenuString();
}

void refreshCustomerBasket(NurseryFacade& nursery, vector<string>& plantNames, Customer* customer) {
    if (customer)
        plantNames = nursery.getCustomerBasketString(customer);
}

int main() {
    Inventory::getInstance();

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
                plantInfoText = nursery.getPlantInfo(currentPlant);
                statusText = "Status: Created new " + selectedType + " and added to Inventory.";
                refreshInventoryView(nursery);
            }
        }
    });

    auto waterButton = Button("Water Plant", [&] {
        if (currentPlant) {
            nursery.waterPlant(currentPlant);
            plantInfoText = nursery.getPlantInfo(currentPlant);
            statusText = "Status: Watered plant";
        }
    });

    auto sunButton = Button("Add Sunlight", [&] {
        if (currentPlant) {
            nursery.addSunlight(currentPlant);
            plantInfoText = nursery.getPlantInfo(currentPlant);
            statusText = "Status: Added sunlight";
        }
    });

    auto infoButton = Button("Get Info", [&] {
        if (currentPlant) {
            plantToView = currentPlant;
            previousTab = tabSelected;
            tabSelected = 2;
            statusText = "Status: Viewing " + currentPlant->getName();

            screen.Post([]{});
        } else {
            statusText = "Status: You must create a plant first.";
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
        std::string newGroupName = "Group " + std::to_string(groupCounter);
        PlantGroup* newGroup = nursery.createPlantGroup(newGroupName);

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

    string userName = "";
    Customer* currentCustomer = nullptr;
    PlantComponent* currentCustomerPlant = nursery.findPlant(0);
    int customerTreeIndex = 0;
    int customerBasketIndex = 0;
    int water = 0;
    int sun = 0;
    vector<string> plantNames = nursery.getMenuString();
    vector<string> basketNames = {};
    nursery.addCustomer("Customer");
    nursery.addStaff("Staff");

    string customerTerminalStr = "Your conversations go here";
    auto nameInput = Input(&userName, "Enter your name here");
    auto customerMenu = Menu(&plantNames, &customerTreeIndex);
    auto customerBasket = Menu(&basketNames, &customerBasketIndex);

    auto addCustomerButton = Button("Login", [&] {
        currentCustomer = nursery.addCustomer(userName);
        screen.Post([&] {
            if (currentCustomer)
                refreshCustomerBasket(nursery, basketNames, currentCustomer);
        });
    });

    auto askAdvice = Button("Get Suggestion", [&] {
        customerTerminalStr = nursery.askForSuggestion(currentCustomer);
    });

    auto basketAddBtn = Button("Add to Basket", [&] {
        bool result = nursery.addToCustomerBasket(currentCustomer, nursery.findPlant(customerTreeIndex));
        result ? statusText = "Plant added successfully" : statusText = "Something went wrong with plant adding";
        currentCustomerPlant = nursery.findPlant(customerTreeIndex);
        customerTreeIndex = 0;
        refreshCustomerBasket(nursery, basketNames, currentCustomer);
        refreshInventoryView(nursery);
    });

    auto purchaseBtn = Button("Purchase Plants", [&] {
        customerTerminalStr = nursery.customerPurchase(currentCustomer);
        refreshCustomerBasket(nursery, basketNames, currentCustomer);
    });

    auto removeFromBasket = Button("Remove Plant", [&] {
        nursery.removeFromCustomer(currentCustomer, customerBasketIndex);
        refreshCustomerBasket(nursery, basketNames, currentCustomer);
    });


auto viewInventoryPlantButton = Button("View Plant", [&] {
    if (selectedInventoryComponent && 
        selectedInventoryComponent->getType() != ComponentType::PLANT_GROUP) {
        
        plantToView = selectedInventoryComponent;
        previousTab = tabSelected;
        tabSelected = 2;

        screen.Post([]{});
    
    } else {
        inventoryStatusText = "Select a plant (not a group) to view.";
    }
});


    int tabSelected = 0;
    std::vector<std::string> tabTitles = {
        "Manager and Inventory",
        "Customer",
        "Plant Details"
    };

    auto tabToggle = Toggle(&tabTitles, &tabSelected);

    auto plantInfoRenderer = Renderer([&] {
        return paragraph(plantInfoText) | color(Color::GrayLight);
    });



    auto selectedInfoRenderer_Base = Renderer([&] {
        return paragraph(selectedInfoText) | color(Color::GrayLight) |
                vscroll_indicator | yframe |
                focusPositionRelative(0, selectedInfoScrollY);
    }) | size(HEIGHT, EQUAL, 10);

    auto selectedInfoRenderer = CatchEvent(selectedInfoRenderer_Base, [&](Event event) {
        if (event.is_mouse() && event.mouse().button == Mouse::WheelUp) {
            selectedInfoScrollY = std::max(0, selectedInfoScrollY - 1);
            return true;
        }
        if (event.is_mouse() && event.mouse().button == Mouse::WheelDown) {
            selectedInfoScrollY++;
            return true;
        }
        if (event == Event::ArrowUp) {
            selectedInfoScrollY = std::max(0, selectedInfoScrollY - 1);
            return true;
        }
        if (event == Event::ArrowDown) {
            selectedInfoScrollY++;
            return true;
        }
        if (event.is_mouse() && event.mouse().button == Mouse::Left && event.mouse().motion == Mouse::Pressed) {
            selectedInfoRenderer_Base->TakeFocus();
            return true;
        }
        return false;
    });

    auto managerInventoryTab = Container::Vertical({
        plantSelector,
        createButton,
        Container::Horizontal({
            waterButton,
            sunButton,
            infoButton,
        }),

        Container::Horizontal({
            refreshButton,
            createGroupButton,
            addToGroupButton,
            viewInventoryPlantButton 
        }),
        Container::Horizontal({
            startTickButton,
            stopTickButton,
        }),
        treeMenu | size(HEIGHT, EQUAL, 15),
        selectedInfoRenderer,
    });


ftxui::SliderOption<int> water_slider_option;
water_slider_option.value = &water;
water_slider_option.min = 0;
water_slider_option.max = 200;
water_slider_option.increment = 1;
water_slider_option.color_active = ftxui::Color::Blue;
water_slider_option.color_inactive = ftxui::Color::GrayDark;


    auto waterSlider = Slider(water_slider_option);
    auto waterStyled = Renderer(waterSlider, [&] {
        return waterSlider->Render()  | size(HEIGHT, EQUAL, 1) | size(WIDTH, EQUAL, 90);
    });
ftxui::SliderOption<int> sun_slider_option;
sun_slider_option.value = &sun;
sun_slider_option.min = 0;
sun_slider_option.max = 200;
sun_slider_option.increment = 1;
sun_slider_option.color_active = ftxui::Color::Yellow;
sun_slider_option.color_inactive = ftxui::Color::GrayDark;

    auto sunSlider = Slider(sun_slider_option);
    auto sunStyled = Renderer(sunSlider, [&] {
        return sunSlider->Render()  | size(HEIGHT, EQUAL, 1) | size(WIDTH, EQUAL, 90);
    });

    auto backButton = Button("<< Back", [&] {
    tabSelected = previousTab;
    plantToView = nullptr;
    });

    auto detailsWaterButton = Button("Water Plant", [&] {
        if (plantToView && plantToView->getType() != ComponentType::PLANT_GROUP) {
            nursery.waterPlant(plantToView);
            statusText = "Status: Watered " + plantToView->getName();
        } else {
            statusText = "Status: No plant selected to water.";
        }
    });

    auto detailsSunButton = Button("Add Sunlight", [&] {
        if (plantToView && plantToView->getType() != ComponentType::PLANT_GROUP) {
            nursery.addSunlight(plantToView);
            statusText = "Status: Added sunlight to " + plantToView->getName();
        } else {
            statusText = "Status: No plant selected for sun.";
        }
    });

    auto tab4Content = Container::Vertical({
        backButton,
        detailsWaterButton,
        detailsSunButton
    });

    auto customerTab = Container::Vertical({
        Container::Horizontal({nameInput, addCustomerButton}),
        Container::Vertical({
            askAdvice,
            basketAddBtn,
            purchaseBtn,
            removeFromBasket,
        }),
        Container::Horizontal({
            customerMenu,
            customerBasket,
        }),
    });

    auto tabContainer = Container::Tab({
        managerInventoryTab,
        customerTab,
        tab4Content
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
        refreshCustomerView(nursery, plantNames);
        currentCustomerPlant = nursery.findPlant(customerTreeIndex);

        if (currentCustomerPlant) {
            water = currentCustomerPlant->getWaterValue();
            sun = currentCustomerPlant->getSunlightValue();
        }

        Element Dialogue = text("");

        if (showCreateGroupDialogue) {
            Dialogue = dbox({
                text(""),
                hbox({ 
                    filler(),
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
                    }) | size(WIDTH, LESS_THAN, 50) 
                })
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

    Element managerInventoryView = vbox({
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
        separator(),

        hbox({
            refreshButton->Render() | color(Color::Blue),
            text(" "),
            createGroupButton->Render() | color(Color::Green),
            text(" "),
            addToGroupButton->Render() | color(Color::Yellow),
            text(" "),
            viewInventoryPlantButton->Render() | color(Color::Cyan)
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

        Element customerView = vbox({
            hcenter(hbox({
                window(text("Enter username") | bold | color(Color::Cyan), nameInput->Render() | frame | size(HEIGHT, EQUAL, 1) | size(WIDTH, EQUAL, 100)),
                filler(),
                addCustomerButton->Render() | color(Color::Green) | size(HEIGHT, EQUAL, 3) | size(WIDTH, EQUAL, 10)
            })) | size(HEIGHT, EQUAL, 3),

            currentCustomer
            ? hcenter(vbox({
                hbox({
                    window(text("Available Plants") | bold | color(Color::Cyan), customerMenu->Render())
                    | size(WIDTH, GREATER_THAN, 100)
                    | size(HEIGHT, GREATER_THAN, 12),
                    window(text(currentCustomer->getName() + "'s basket") | bold | color(Color::Cyan), customerBasket->Render())
                    | size(WIDTH, GREATER_THAN, 100)
                    | size(HEIGHT, GREATER_THAN, 12)
                }),

                hbox({
                    
                    window (text("Water Level"),{waterStyled->Render()}),
                    filler(),
                     window (text("Sun level"),{sunStyled->Render()}),
                }),
                filler(),

                window(
                    text("Conversations") | bold | color(Color::Cyan),
                    paragraph(customerTerminalStr) | frame | vscroll_indicator | size(HEIGHT, EQUAL, 15) | color(Color::GrayLight)
                ),

                hbox({
                askAdvice->Render() | color(Color::Magenta) | size(HEIGHT, EQUAL, 3) | size(WIDTH, EQUAL, 20),
                filler(),

                vbox({
                    basketAddBtn->Render() | color(Color::Green),
            
                }) | size(WIDTH, EQUAL, 25),

                filler(),
                purchaseBtn->Render() | color(Color::Yellow) | size(HEIGHT, EQUAL, 3) | size(WIDTH, EQUAL, 25),
                filler(),

                vbox({
                    removeFromBasket->Render() | color(Color::Red),

                }) | size(WIDTH, EQUAL, 25)

        }) | border | size(WIDTH, EQUAL, 200),
                filler()
            }))
            : vbox({
                window(text("Enter details") | bold | color(Color::Yellow), 
                    paragraph("Please enter your name first and press login") | color(Color::GrayLight))
            })
        });
            Element tab4View = vbox({
            window(text("Plant Details") | bold | color(Color::Cyan),
                vbox({
                    [=] {
                        float water_val = 0;
                        float sun_val = 0;
                        float max_stat = 200; 
                        std::string info_text = "No plant selected. Go back and select one.";

                        if (plantToView && plantToView->getType() != ComponentType::PLANT_GROUP) {
                            water_val = (float)plantToView->getWaterValue();
                            sun_val = (float)plantToView->getSunlightValue();
                        }

                        if (plantToView) {
                             if (plantToView->getType() == ComponentType::PLANT_GROUP) {
                                info_text = plantToView->getInfo();
                            } else {
                                info_text = plantToView->getDecorator()->getInfo();
                            }
                        }

                        Element waterBar = hbox({
                            text("Water:  ") | size(WIDTH, EQUAL, 8),
                            gauge(water_val / max_stat) | color(Color::Blue) | flex
                        });
                        Element sunBar = hbox({
                            text("Sun:    ") | size(WIDTH, EQUAL, 8),
                            gauge(sun_val / max_stat) | color(Color::Yellow) | flex
                        });

                        Element infoBox = paragraph(info_text) |
                                          color(Color::GrayLight) | 
                                          yframe | 
                                          vscroll_indicator | 
                                          size(HEIGHT, EQUAL, 30);

                        if (plantToView && plantToView->getType() != ComponentType::PLANT_GROUP) {
                             return vbox({
                                waterBar,
                                sunBar,
                                separator(),
                                infoBox
                            });
                        } else {
                            return vbox({infoBox});
                        }
                    }()
                })
            ),
            separator(),
            hbox({
                filler(),
                detailsWaterButton->Render() | color(Color::Blue),
                text(" "),
                detailsSunButton->Render() | color(Color::Yellow),
                filler()
            }) | vcenter | size(HEIGHT, EQUAL, 3),
            separator(),
            backButton->Render() | color(Color::RedLight) | center
        });

        Element main = vbox({
        hbox({
            text("🌿 Photosyntech Plant Manager 🌿") | bold | center | color(Color::Green),
        }) | border,
        tabToggle->Render(),
        separator(),

        (tabSelected == 0 ? managerInventoryView :
        tabSelected == 1 ? customerView :
        tab4View) | flex,

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

    delete Inventory::getInstance();
    return 0;
}
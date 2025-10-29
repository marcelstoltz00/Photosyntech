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
#include "../../../facade/NurseryFacade.h"
#include "../../../composite/PlantGroup.h"
#include "../../../composite/PlantComponent.h"

using namespace ftxui;

std::map<int, PlantComponent *> treeIndexToComponent;
int selectedTreeIndex = -1;
PlantComponent *selectedInventoryComponent = nullptr;
std::string inventoryStatusText = "Inventory: Initialising...";
std::string selectedInfoText = "Component details will appear here.";

std::vector<std::string> treeEntries;

void buildTreeEntries(
    PlantComponent *component,
    std::vector<std::string> &entries,
    std::map<int, PlantComponent *> &indexMap,
    int depth = 0)
{
    if (!component)
        return;

    int currentIndex = entries.size();
    std::string indent(depth * 2, ' ');
    std::string prefix = depth > 0 ? "├─ " : "";
    entries.push_back(indent + prefix + component->getName());
    indexMap[currentIndex] = component;

    if (component->getType() == ComponentType::PLANT_GROUP)
    {
        PlantGroup *group = static_cast<PlantGroup *>(component);
        if (group)
        {
            std::list<PlantComponent *> children = *group->getPlants();
            for (PlantComponent *child : children)
            {
                buildTreeEntries(child, entries, indexMap, depth + 1);
            }
        }
    }
}

void refreshInventoryView(NurseryFacade &nursery)
{
    treeEntries.clear();
    treeIndexToComponent.clear();
    selectedTreeIndex = -1;
    selectedInventoryComponent = nullptr;

    selectedInfoText = "Select an item in the inventory.";
    inventoryStatusText = "Inventory refreshed.";

    PlantComponent *root = nursery.getInventoryRoot();
    if (root)
    {
        buildTreeEntries(root, treeEntries, treeIndexToComponent);
    }
}

int main()
{
    Inventory::getInstance();

    std::ofstream cerrLog("plant_manager_debug.txt");
    std::streambuf *oldCerrBuf = std::cerr.rdbuf();
    std::cerr.rdbuf(cerrLog.rdbuf());

    auto screen = ScreenInteractive::Fullscreen();

    NurseryFacade nursery;

    auto plantTypes = nursery.getAvailablePlantTypes();
    int plantSelectorIndex = 0;
    std::string plantInfoText = "No plant selected";
    std::string statusText = "Status: Ready";
    PlantComponent *currentPlant = nullptr;

    auto plantSelector = Dropdown(&plantTypes, &plantSelectorIndex);

    auto createButton = Button("Create Plant", [&]
                               {
        if (plantSelectorIndex >= 0 && plantSelectorIndex < plantTypes.size()){
            std::string selectedType = plantTypes[plantSelectorIndex];
            currentPlant = nursery.createPlant(selectedType);
            if (currentPlant){
                plantInfoText = nursery.getPlantInfo(currentPlant);
                statusText = "Status: Created new " + selectedType + " and added to Inventory.";
                refreshInventoryView(nursery);
            }
        } });

    auto waterButton = Button("Water Plant", [&]
                              {
        if (currentPlant){
            nursery.waterPlant(currentPlant);
            plantInfoText = nursery.getPlantInfo(currentPlant);
            statusText = "Status: Watered plant";
        } });

    auto sunButton = Button("Add Sunlight", [&]
                            {
        if (currentPlant){
            nursery.addSunlight(currentPlant);
            plantInfoText = nursery.getPlantInfo(currentPlant);
            statusText = "Status: Added sunlight";
        } });

    auto infoButton = Button("Get Info", [&]
                             {
        if (currentPlant){
            plantInfoText = nursery.getPlantInfo(currentPlant);
            statusText = "Status: Updated info";
        } });

    auto refreshButton = Button("Refresh Inventory", [&]
                                { refreshInventoryView(nursery); });

    auto startTickButton = Button("Start Ticker", [&]
                                  {
        if (nursery.startNurseryTick()){
            inventoryStatusText = "Inventory: Ticker Started.";
        }else{
            inventoryStatusText = "Inventory: Ticker already running.";
        } });

    auto stopTickButton = Button("Stop Ticker", [&]
                                 {
        if (nursery.stopNurseryTick()){
            inventoryStatusText = "Inventory: Ticker Stopped.";
        }else{
            inventoryStatusText = "Inventory: Ticker was not running.";
        }
        refreshInventoryView(nursery); });

    auto treeMenu = Menu(&treeEntries, &selectedTreeIndex);
    treeMenu |= CatchEvent([&](Event event)
                           {
        if (event == Event::Return && selectedTreeIndex >= 0){
            auto it = treeIndexToComponent.find(selectedTreeIndex);
            if (it != treeIndexToComponent.end()){
                selectedInventoryComponent = it->second;
                selectedInfoText = nursery.getPlantInfo(selectedInventoryComponent);
                inventoryStatusText = "Status: Selected item in Inventory.";
            }
        }
        return false; });

    int tabSelected = 0;
    std::vector<std::string> tabTitles = {
        "Plant Manager (Builder)",
        "Inventory (Composite/Singleton)",
        "Customer"};

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
            startTickButton,
            stopTickButton,
        }),
        treeMenu,
    });
    string userName = "";
    Customer *currentCustomer = nullptr;

    nursery.addCustomer("Customer");
    nursery.addStaff("Staff");

    string customerTerminalStr = "";
    auto nameInput = Input(&userName, "Enter your name here");
    auto addCustomerButton = Button("Login", [&]
                                    { currentCustomer = nursery.addCustomer(userName); });

    auto askAdvice = Button("get suggestion", [&]
                            { customerTerminalStr = nursery.askForSuggestion(currentCustomer); });

    auto customerTab = Container::Vertical(
        {Container::Horizontal({nameInput, addCustomerButton}),
         Container::Vertical({
             askAdvice,
         })});

    auto tabContainer = Container::Tab({tab1Content,
                                        tab2Content,
                                        customerTab},
                                       &tabSelected);

    auto mainContainer = Container::Vertical({
        tabToggle,
        tabContainer,
    });

    auto mainRenderer = Renderer(mainContainer, [&]
                                 {
        Element tab1View = vbox({
            window(text("Plant Creation"), vbox({
                hbox(text("Select Plant Type: "), text(plantTypes[plantSelectorIndex])),
                plantSelector->Render(),
                createButton->Render(),
            })),
            window(text("Plant Actions"), 
                hbox({
                    waterButton->Render(),
                    sunButton->Render(),
                    infoButton->Render(),
                })
            ),
            window(text("Current Plant Information"), 
                paragraphAlignLeft(plantInfoText)
            ),
        });

        Element tab2View = vbox({
            hbox({
                refreshButton->Render(),
                startTickButton->Render(),
                stopTickButton->Render(),

            }),
            text(inventoryStatusText),
            window(text("Inventory Hierarchy"), 
                treeMenu->Render() | frame | size(HEIGHT, LESS_THAN, 15)
            ),
            window(text("Selected Component Info"), 
                paragraphAlignLeft(selectedInfoText)
            ),
        });
 
        Element customerView = vbox({
            hbox({
               nameInput->Render() | frame |size(HEIGHT,EQUAL,3)| size(WIDTH, EQUAL, 200),
               addCustomerButton->Render() |size(HEIGHT,EQUAL,3) |size(WIDTH,EQUAL,10)
            }),
             currentCustomer // ? vbox(with access) : vbox (no access)
        ? vbox({
             // This is the section where user is logged in any access user not logged in
              askAdvice->Render(),
              window(text("Conversations"), paragraph(customerTerminalStr)),
                treeMenu->Render() | frame | size(HEIGHT, LESS_THAN, 15)
          })
       
        : vbox({
             // This is the section without any access user not logged in
              window(text("Enter details"), paragraph("Please enter your name first and press login"))
          })
             
        });


        return vbox({
            hbox({
                text("Photosyntech Plant Manager") | bold | center,
            }) | border,
            tabToggle->Render(),
            separator(),
            (tabSelected == 0 ? tab1View : tabSelected == 1 ? tab2View :customerView) | flex,
            separator(),
            text(statusText) | border,
        }); });

    refreshInventoryView(nursery);

    screen.Loop(mainRenderer);

    try
    {
        nursery.stopNurseryTick();
    }
    catch (const std::exception &e)
    {
    }

    std::cerr.rdbuf(oldCerrBuf);

    delete Inventory::getInstance();
    return 0;
}

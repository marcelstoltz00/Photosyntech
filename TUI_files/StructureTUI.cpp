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

#include "../TUI/TUIKit/include/tuikit.h"
#include "../TUI/TUIKit/external/ftxui-image-view/include/image_view.hpp"

using namespace ftxui;
std::map<int, PlantComponent *> treeIndexToComponent;
std::vector<std::string> treeEntries;
int selectedTreeIndex = -1;
int previousSelectedTreeIndex = -1;
PlantComponent *selectedInventoryComponent = nullptr;

PlantComponent *plantToView = nullptr;
std::string plantDetailText = "No plant selected to view.";
int previousTab = 0;
int tabSelected = 0;

std::string inventoryStatusText = "Inventory: Initialising...";
std::string selectedInfoText = "Component details will appear here.";
bool showCreateGroupDialogue = false;
bool showMoveDialogue = false;
int groupCounter = 1;

PlantComponent *componentToMove = nullptr;
PlantComponent *targetGroup = nullptr;

Component mainContainer;
Component groupDialogueContainer;
Component moveDialogueContainer;
Component main_ui;

unordered_map<string, Element> cache;

Element  &getImage(const std::string &id)
{
    auto it = cache.find(id);
    if (it != cache.end())
        return it->second;

    return cache[id] = image_view(id);
}

void preloadImages(const std::vector<std::string> &ids)
{
    for (const auto &id : ids)
    {
        cache[id] = image_view(id); // expensive, but done once
    }
}

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
    std::string prefix = depth > 0 ? "├─ " : "📦 ";

    std::string icon = "";
    if (component->getType() == ComponentType::PLANT_GROUP)
    {
        icon = "📁 ";
    }
    else
    {
        icon = "🌱 ";
    }

    entries.push_back(indent + prefix + icon + component->getName());
    indexMap[currentIndex] = component;

    if (component->getType() == ComponentType::PLANT_GROUP)
    {
        PlantGroup *group = dynamic_cast<PlantGroup *>(component);
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

    selectedInfoText = "Select an item in the inventory.";
    inventoryStatusText = "Inventory refreshed.";

    PlantComponent *root = nursery.getInventoryRoot();
    if (root)
    {
        buildTreeEntries(root, treeEntries, treeIndexToComponent);
    }

    if (selectedTreeIndex >= 0 && selectedTreeIndex < treeEntries.size())
    {
        auto it = treeIndexToComponent.find(selectedTreeIndex);
        if (it != treeIndexToComponent.end())
        {
            selectedInventoryComponent = it->second;
        }
    }
}

void refreshCustomerView(NurseryFacade &nursery, vector<string> &plantNames)
{
    plantNames = nursery.getMenuString();
}
void refreshStaffView(NurseryFacade &nursery, vector<string> &staffNames)
{
    staffNames = nursery.getAllStaffMembers();
}
void refreshPlantGroupView(NurseryFacade &nursery, vector<string> &PGnames)
{
    PGnames = nursery.getAllPlantGroups();
}

void refreshCustomerBasket(NurseryFacade &nursery, vector<string> &plantNames, Customer *customer)
{
    if (customer)
        plantNames = nursery.getCustomerBasketString(customer);
}
int main()
{
    std::vector<std::string> imagePaths = {
        "../docs/images/Cactus0.png", "../docs/images/Cactus1.png", "../docs/images/Cactus2.png", "../docs/images/Cactus3.png",
        "../docs/images/CherryBlossom0.png", "../docs/images/CherryBlossom1.png", "../docs/images/CherryBlossom2.png", "../docs/images/CherryBlossom3.png",
        "../docs/images/Jade0.png", "../docs/images/Jade1.png", "../docs/images/Jade2.png", "../docs/images/Jade3.png",
        "../docs/images/Lavender0.png", "../docs/images/Lavender1.png", "../docs/images/Lavender2.png", "../docs/images/Lavender3.png",
        "../docs/images/MapleTree0.png", "../docs/images/MapleTree1.png", "../docs/images/MapleTree2.png", "../docs/images/MapleTree3.png",
        "../docs/images/photosyntech_logo.JPG",
        "../docs/images/PineTree0.png", "../docs/images/PineTree1.png", "../docs/images/PineTree2.png", "../docs/images/PineTree3.png",
        "../docs/images/Rose0.png", "../docs/images/Rose1.png", "../docs/images/Rose2.png", "../docs/images/Rose3.png",
        "../docs/images/Sunflower0.png", "../docs/images/Sunflower1.png", "../docs/images/Sunflower2.png", "../docs/images/Sunflower3.png"};
    preloadImages(imagePaths);

    Inventory::getInstance();
    bool refreshIterator = false;
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
        if (plantSelectorIndex >= 0 && plantSelectorIndex < plantTypes.size()) {
            std::string selectedType = plantTypes[plantSelectorIndex];
            currentPlant = nursery.createPlant(selectedType);
            if (currentPlant) {
                plantInfoText = nursery.getPlantInfo(currentPlant);
                statusText = "Status: Created new " + selectedType + " and added to Inventory.";
                refreshInventoryView(nursery);
            }
        } });

    auto waterButton = Button("Water Plant", [&]
                              {
        if (currentPlant) {
            nursery.waterPlant(currentPlant);
            plantInfoText = nursery.getPlantInfo(currentPlant);
            statusText = "Status: Watered plant";
        } });

    auto sunButton = Button("Add Sunlight", [&]
                            {
        if (currentPlant) {
            nursery.addSunlight(currentPlant);
            plantInfoText = nursery.getPlantInfo(currentPlant);
            statusText = "Status: Added sunlight";
        } });

    auto refreshButton = Button("Refresh", [&]
                                { refreshInventoryView(nursery); });

    auto startTickButton = Button("Start Ticker", [&]
                                  {
        if (nursery.startNurseryTick()) {
            inventoryStatusText = "Inventory: Ticker Started.";
        } else {
            inventoryStatusText = "Inventory: Ticker already running.";
        } });

    auto stopTickButton = Button("Stop Ticker", [&]
                                 {
        if (nursery.stopNurseryTick()) {
            inventoryStatusText = "Inventory: Ticker Stopped.";
        } else {
            inventoryStatusText = "Inventory: Ticker was not running.";
        }
        refreshInventoryView(nursery); });

    auto createGroupButton = Button("Create Group", [&]
                                    { showCreateGroupDialogue = true; });

    auto confirmGroupButton = Button("Create", [&]
                                     {
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
        refreshInventoryView(nursery); }) |
                              color(Color::Green);

    auto cancelGroupButton = Button("Cancel", [&]
                                    { showCreateGroupDialogue = false; }) |
                             color(Color::Red);

    std::vector<std::string> groupList;
    std::vector<PlantComponent *> groupComponents;
    int selectedGroupIndex = 0;

    std::function<void()> buildGroupList = [&]()
    {
        groupList.clear();
        groupComponents.clear();
        selectedGroupIndex = 0;

        PlantComponent *root = nursery.getInventoryRoot();
        groupList.push_back("Root Inventory");
        groupComponents.push_back(root);

        std::function<void(PlantComponent *, int)> findGroups = [&](PlantComponent *comp, int depth)
        {
            if (comp && comp->getType() == ComponentType::PLANT_GROUP)
            {
                PlantGroup *group = dynamic_cast<PlantGroup *>(comp);
                if (group && comp != nursery.getInventoryRoot() && comp != componentToMove)
                {
                    std::string indent(depth * 2, ' ');
                    groupList.push_back(indent + "└─ " + comp->getName());
                    groupComponents.push_back(comp);

                    std::list<PlantComponent *> children = *group->getPlants();
                    for (PlantComponent *child : children)
                    {
                        findGroups(child, depth + 1);
                    }
                }
            }
        };

        if (root && root->getType() == ComponentType::PLANT_GROUP)
        {
            PlantGroup *rootGroup = dynamic_cast<PlantGroup *>(root);
            std::list<PlantComponent *> children = *rootGroup->getPlants();
            for (PlantComponent *child : children)
            {
                findGroups(child, 1);
            }
        }
    };

    auto addToGroupButton = Button("Move to Group", [&]
                                   {
    if (selectedInventoryComponent){
        componentToMove = selectedInventoryComponent;
        showMoveDialogue = true;
        buildGroupList();
    }else{
        inventoryStatusText = "Select an item to move.";
    } });

    auto groupSelectMenu = Menu(&groupList, &selectedGroupIndex);

    auto confirmMoveButton = Button("Move", [&]
                                    {
        if (selectedGroupIndex >= 0 && selectedGroupIndex < groupComponents.size()) {
            targetGroup = groupComponents[selectedGroupIndex];
            nursery.removeComponentFromInventory(componentToMove);
            nursery.addComponentToGroup(targetGroup, componentToMove);
            inventoryStatusText = "Moved component to " + targetGroup->getName();
            showMoveDialogue = false;
            refreshInventoryView(nursery);
        } }) |
                             color(Color::Green);

    auto cancelMoveButton = Button("Cancel", [&]
                                   { showMoveDialogue = false; }) |
                            color(Color::Red);

    auto on_menu_change = [&]
    {
        if (selectedTreeIndex >= 0 && selectedTreeIndex < treeEntries.size())
        {
            auto it = treeIndexToComponent.find(selectedTreeIndex);
            if (it != treeIndexToComponent.end())
            {
                selectedInventoryComponent = it->second;

                if (selectedInventoryComponent->getType() == ComponentType::PLANT_GROUP)
                {
                    selectedInfoText = selectedInventoryComponent->getInfo();
                }
                else
                {
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
    Customer *currentCustomer = nullptr;
    PlantComponent *currentCustomerPlant = nursery.findPlant(0);
    int customerTreeIndex = 0;
    int customerBasketIndex = 0;
    int water = 0;
    int sun = 0;
    int health = 0;
    vector<string> plantNames = nursery.getMenuString();
    vector<string> basketNames = {};
    nursery.addCustomer("Customer");
    nursery.addStaff("Mark");

    string customerTerminalStr = "Your conversations go here";
    auto nameInput = Input(&userName, "Enter your name here");
    auto customerMenu = Menu(&plantNames, &customerTreeIndex);
    auto customerBasket = Menu(&basketNames, &customerBasketIndex);

    auto addCustomerButton = Button("Login", [&]
                                    {
        currentCustomer = nursery.addCustomer(userName);
        screen.Post([&] {
            if (currentCustomer)
                refreshCustomerBasket(nursery, basketNames, currentCustomer);
        }); });

    auto askAdvice = Button("Get Suggestion", [&]
                            { customerTerminalStr = nursery.askForSuggestion(currentCustomer); });

    auto basketAddBtn = Button("Add to Basket", [&]
                               {
        refreshIterator = true;
        bool result = nursery.addToCustomerBasket(currentCustomer, nursery.findPlant(customerTreeIndex));
        result ? statusText = "Plant added successfully" : statusText = "Something went wrong with plant adding";
        currentCustomerPlant = nursery.findPlant(customerTreeIndex);
        customerTreeIndex = 0;
        refreshCustomerBasket(nursery, basketNames, currentCustomer);
        refreshInventoryView(nursery); });

    auto purchaseBtn = Button("Purchase Plants", [&]
                              {
        customerTerminalStr = nursery.customerPurchase(currentCustomer);
        refreshCustomerBasket(nursery, basketNames, currentCustomer); });

    auto removeFromBasket = Button("Remove Plant", [&]
                                   {
        nursery.removeFromCustomer(currentCustomer, customerBasketIndex);
        refreshCustomerBasket(nursery, basketNames, currentCustomer); });

    int tabSelected = 0;
    auto viewInventoryPlantButton = Button("View Plant", [&]
                                           {
    if (selectedInventoryComponent && 
        selectedInventoryComponent->getType() != ComponentType::PLANT_GROUP) {
        
        plantToView = selectedInventoryComponent;
        previousTab = tabSelected;
        tabSelected = 1;
    } else {
        inventoryStatusText = "Select a plant (not a group) to view.";
    } });

    std::vector<std::string> tabTitles = {
        "Manager and Inventory",

        "Plant Details",
        "Staff management",
        "Customer",
        "Carousel"};

    auto tabToggle = Toggle(&tabTitles, &tabSelected);

    auto plantInfoRenderer = Renderer([&]
                                      { return paragraph(plantInfoText) | color(Color::GrayLight); });

    auto managerInventoryTab = Container::Vertical({
        plantSelector,
        createButton,
        Container::Horizontal({
            waterButton,
            sunButton,
        }),

        Container::Horizontal({refreshButton,
                               createGroupButton,
                               addToGroupButton,
                               viewInventoryPlantButton}),
        Container::Horizontal({
            startTickButton,
            stopTickButton,
        }),
        treeMenu | size(HEIGHT, EQUAL, 15),
    });

    ftxui::SliderOption<int> water_slider_option;
    water_slider_option.value = &water;
    water_slider_option.min = 0;
    water_slider_option.max = 200;
    water_slider_option.increment = 1;
    water_slider_option.color_active = ftxui::Color::Blue;
    water_slider_option.color_inactive = ftxui::Color::GrayDark;

    auto waterSlider = Slider(water_slider_option);
    auto waterStyled = Renderer(waterSlider, [&]
                                { return waterSlider->Render() | size(HEIGHT, EQUAL, 1) | size(WIDTH, EQUAL, 65); });

    ftxui::SliderOption<int> sun_slider_option;
    sun_slider_option.value = &sun;
    sun_slider_option.min = 0;
    sun_slider_option.max = 200;
    sun_slider_option.increment = 1;
    sun_slider_option.color_active = ftxui::Color::Yellow;
    sun_slider_option.color_inactive = ftxui::Color::GrayDark;

    auto sunSlider = Slider(sun_slider_option);
    auto sunStyled = Renderer(sunSlider, [&]
                              { return sunSlider->Render() | size(HEIGHT, EQUAL, 1) | size(WIDTH, EQUAL, 65); });
    ftxui::SliderOption<int> health_Slider_option;
    health_Slider_option.value = &health;
    health_Slider_option.min = 0;
    health_Slider_option.max = 200;
    health_Slider_option.increment = 1;
    health_Slider_option.color_active = ftxui::Color::LightGreen;
    health_Slider_option.color_inactive = ftxui::Color::GrayDark;

    auto healthSlider = Slider(health_Slider_option);
    auto healthStyled = Renderer(healthSlider, [&]
                                 { return healthSlider->Render() | size(HEIGHT, EQUAL, 1) | size(WIDTH, EQUAL, 65); });

    auto backButton = Button("<< Back", [&]
                             {
    tabSelected = previousTab;
    plantToView = nullptr; });

    auto detailsWaterButton = Button("Water Plant", [&]
                                     {
        if (plantToView && plantToView->getType() != ComponentType::PLANT_GROUP) {
            nursery.waterPlant(plantToView);
            statusText = "Status: Watered " + plantToView->getName();
        } else {
            statusText = "Status: No plant selected to water.";
        } });

    auto detailsSunButton = Button("Add Sunlight", [&]
                                   {
        if (plantToView && plantToView->getType() != ComponentType::PLANT_GROUP) {
            nursery.addSunlight(plantToView);
            statusText = "Status: Added sunlight to " + plantToView->getName();
        } else {
            statusText = "Status: No plant selected for sun.";
        } });

    auto tab4Content = Container::Vertical({backButton,
                                            detailsWaterButton,
                                            detailsSunButton});

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
    // ########################### staff additions
    string staffName = "";
    auto staffNameInput = Input(&staffName);
    auto staffNames = nursery.getAllStaffMembers();
    auto plantGroupNames = nursery.getAllPlantGroups();
    vector<string> plantGroupContents;
    vector<string> observerNames;

   
    int staffIndex = 0;
    int plantGroupIndex = 0;
    int internalPlantGroupIndex = 0;
    int currentObserverIndex = 0;
    PlantGroup *currentPlantGroupStaff = nullptr;
    auto plantGroupMenu = Menu(&plantGroupNames, &plantGroupIndex);

    auto plantGroupObservers = Menu(&observerNames, &currentObserverIndex);

    auto staffMenu = Menu(&staffNames, &staffIndex);
    auto plantGroupContentsMenu = Menu(&plantGroupContents, &internalPlantGroupIndex);
    Staff *currentStaffMember = nullptr;
    auto addStaff = Button("Add Staff", [&]
                           {
                               currentStaffMember= nursery.addStaff(staffName);
                               statusText = currentStaffMember ? "Staff Member added " : "Staff member could not be added";
                               refreshStaffView(nursery,staffNames);
                               refreshPlantGroupView(nursery,plantGroupNames); });
    auto AddStaffObserver = Button("set observer", [&]
                                   { nursery.setAsObserver(currentStaffMember, currentPlantGroupStaff);
                             statusText =    currentPlantGroupStaff?    currentStaffMember->getName() + " successfully added as an observer":" could nort process request"; });
    auto removeStaffObserver = Button("detach observer", [&]
                                      { nursery.RemoveObserver(currentStaffMember, currentPlantGroupStaff);
                             statusText =    currentPlantGroupStaff?    currentStaffMember->getName() + " successfully removed as an observer":" could not process request"; });

    auto staffManagement = Container::Vertical({

        Container::Horizontal({removeStaffObserver, AddStaffObserver, staffNameInput, addStaff}),
        Container::Horizontal({staffMenu, plantGroupMenu, plantGroupContentsMenu, plantGroupObservers})

    });
    // ########################### staff additions

    // ########################### Iterator additions

    LivingPlant *carouselPlant = nullptr;
    string filterTextCarousel = "";
    string plantInfoCarousel = "";
    string imgString = "";

    bool seasonfilter = false;
    bool endOfList = true;
    bool plantChanged = true;

    auto CreatePlantIterator = Button("CreateIterator", [&]
                                      { carouselPlant = nursery.createItr(filterTextCarousel,seasonfilter); 
                                     endOfList = carouselPlant == nullptr;
                                    plantChanged = true; });

    auto forwardButton = Button("->", [&]
                                { carouselPlant = nursery.next(); 
                                    endOfList = carouselPlant == nullptr;
                                    plantChanged = true; });

    auto backButtonCarousel = Button("<-", [&]
                                     { carouselPlant = nursery.back(); 
                                endOfList = carouselPlant == nullptr;
                                plantChanged = true; });

    auto carousel = Container ::Horizontal({backButtonCarousel, CreatePlantIterator, forwardButton});

    // ########################### Iterator additions

    auto tabContainer = Container::Tab({managerInventoryTab,
                                        tab4Content,
                                        staffManagement,
                                        customerTab,
                                        carousel},
                                       &tabSelected);

    main_ui = Container::Vertical({
        tabToggle,
        tabContainer,
    });
    int counter = 0;
    Element imageElement ;
    string prevImgStr ="";
    auto mainRenderer = Renderer(main_ui, [&]
                                 {
                                    counter++;

            

                        if (refreshIterator)
                        {
                            carouselPlant = nursery.createItr(filterTextCarousel,seasonfilter);
                            plantInfoCarousel = carouselPlant ? carouselPlant->getInfo(): "";
                            imgString = carouselPlant ? carouselPlant->getImageStr(): "";
                            refreshIterator= false;
                        }

         if (plantChanged  && !endOfList && carouselPlant)
        {
        plantInfoCarousel = carouselPlant ? carouselPlant->getInfo(): "";
        prevImgStr = imgString;
        imgString = carouselPlant ? carouselPlant->getImageStr(): "";
        if (prevImgStr != imgString)
        {
            imageElement  = getImage(imgString);
        }
        plantChanged = false;
        }
          
                        
                    if (counter == 15)
                    {
        plantInfoCarousel = carouselPlant ? carouselPlant->getInfo(): "";

        prevImgStr = imgString;
        imgString = carouselPlant ? carouselPlant->getImageStr(): "";
        if (prevImgStr != imgString)
        {
            imageElement  = getImage(imgString);
        }


refreshCustomerView(nursery, plantNames);
     refreshPlantGroupView(nursery,plantGroupNames);
        currentCustomerPlant = nursery.findPlant(customerTreeIndex);
        currentStaffMember = nursery.findStaff(staffIndex);
        currentPlantGroupStaff = nursery.findPlantGroup(plantGroupIndex);
                   
        plantGroupContents = nursery.getPlantGroupContents(currentPlantGroupStaff);
        observerNames = nursery.getObservers(currentPlantGroupStaff);
        
        if (currentCustomerPlant) {
            water = currentCustomerPlant->getWaterValue();
            sun = currentCustomerPlant->getSunlightValue();
            health = currentCustomerPlant->getHealth();
        }
    counter =0;}




    Element managerInventoryView = vbox({
        window(text("Plant Creation") | bold | color(Color::Cyan), 
        vbox({
    
           hbox({ filler(),
           window(text("Plant Interactions"),
            hbox( { 
                 filler(),
            createButton->Render() | color(Color::Green),
            filler(),
            waterButton->Render() | color(Color::Blue),
            filler(),
            sunButton->Render() | color(Color::Yellow),
                     filler(),
            addToGroupButton->Render() | color(Color::Yellow),
            filler(),
            viewInventoryPlantButton->Render() | color(Color::Cyan),
            })) 

        | size(HEIGHT,LESS_THAN,3),
                             filler(),      
                         vbox({text("Select Plant Type: ")|hcenter | color(Color::GrayLight), 
                            text(plantTypes[plantSelectorIndex]) |hcenter| bold | color(Color::White),
                            plantSelector->Render()|hcenter,}),
                       filler(),
            filler(),

            window( text("Inventory interactions"),   hbox({
            refreshButton->Render() | color(Color::Blue),
            filler(),
            createGroupButton->Render() | color(Color::Green),

            filler(),
         startTickButton->Render() | color(Color::LightGreen),
           filler(),
            stopTickButton->Render() | color(Color::RedLight),
        }))| size(HEIGHT,EQUAL,3),

    filler(),})

        })| size(HEIGHT,GREATER_THAN,5)| size(HEIGHT,LESS_THAN,15)),


        text(inventoryStatusText) | color(Color::Yellow),
        separator(),
        window(text("Inventory Hierarchy") | bold | color(Color::Cyan),
            treeMenu->Render() | frame | size(HEIGHT,LESS_THAN,16)| size(HEIGHT,GREATER_THAN,12)
        ),
    });
    Element StaffView = vbox(
        {
           hcenter (hbox({ filler(),removeStaffObserver->Render()|center| size(WIDTH,EQUAL,20),filler(),
               window(text("Enter staff"), staffNameInput->Render()| size(WIDTH,EQUAL,40)|size(HEIGHT,EQUAL,2)) ,addStaff->Render() |center |size(WIDTH,LESS_THAN,13),filler(),
               AddStaffObserver->Render()|center| size(WIDTH,EQUAL,20),
         filler()   })  |size(HEIGHT,EQUAL,3)| size(WIDTH,EQUAL,300)|border),
            hbox({

             filler(),
            window(text("Staff members"),staffMenu->Render())|size(WIDTH,EQUAL,32)|size(HEIGHT,GREATER_THAN,30), 
            window(text("Plant groups"),plantGroupMenu->Render())|size(WIDTH,EQUAL,80)|size(HEIGHT,GREATER_THAN,30),

            vbox({
            window(text("Plant group contents"),plantGroupContentsMenu->Render())|size(WIDTH,GREATER_THAN,32)|size(HEIGHT,GREATER_THAN,15),
            window(text("Observers for current group"),plantGroupObservers->Render())|size(WIDTH,EQUAL,32)|size(HEIGHT,GREATER_THAN,15)               
            }),
            filler()
        
        })| border 

        }
    ) ;

    Element carouselView =vbox({

                    CreatePlantIterator->Render()|hcenter,
        
        hbox({
            backButtonCarousel->Render()|vcenter,
            carouselPlant?  !imgString.empty() ? imageElement|size(WIDTH,EQUAL,50)|border|size(HEIGHT,EQUAL,30) : filler() :filler(),

            forwardButton->Render()|vcenter

        })|hcenter,

    });

             Element customerView =  vbox({
            hbox({ 
                filler(),
                currentCustomer?  
                hbox({
                filler(),
                askAdvice->Render()|center | color(Color::Magenta) | size(HEIGHT, EQUAL, 3) | size(WIDTH, EQUAL, 20),
                filler(),               
                basketAddBtn->Render()|center | color(Color::Green) | size(WIDTH, EQUAL, 25),
                filler()
                }): filler(),
                filler(),
                window(text("Enter username") | bold | color(Color::Cyan), nameInput->Render() | frame | size(HEIGHT, EQUAL, 1) | size(WIDTH, EQUAL, 40)),
                
                addCustomerButton->Render() |center| color(Color::Green) | size(HEIGHT, EQUAL, 2) | size(WIDTH, EQUAL, 10),
                filler(),

                currentCustomer? 
                hbox({
                filler(),
                purchaseBtn->Render()|center | color(Color::Yellow) | size(HEIGHT, EQUAL, 3) | size(WIDTH, EQUAL, 25),
                filler(),          
                removeFromBasket->Render() |center| color(Color::Red) | size(WIDTH, EQUAL, 25),

                }): filler() ,
            filler(),
            }) |size(HEIGHT, EQUAL, 3) |size(WIDTH, GREATER_THAN, 200) ,

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
                     window (text("Health Level"),{healthStyled->Render()}),
                     window (text("Sun level"),{sunStyled->Render()}),
                }),
                filler(),

                window(
                    text("Conversations") | bold | color(Color::Cyan),
                    paragraph(customerTerminalStr) | frame | vscroll_indicator | size(HEIGHT, EQUAL, 15) | color(Color::GrayLight) 
                )|size(WIDTH, EQUAL, 200),


                filler()
            }))
            : vbox({
                window(text("Enter details") | bold | color(Color::Yellow), 
                    paragraph("Please enter your name first and press login") | color(Color::GrayLight))
            })
        }) | size(WIDTH,EQUAL ,500) |border|hcenter;
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
        tabSelected == 1 ? tab4View : tabSelected == 2 ?
        StaffView : tabSelected ==3 ? customerView : carouselView) | flex,

        separator(),
        text(statusText) | border | color(Color::Cyan),
    });


        return main; });

    refreshInventoryView(nursery);

    auto groupDialogueComponent = Container::Horizontal({confirmGroupButton,
                                                         cancelGroupButton});

    auto createGroupModal = Renderer(groupDialogueComponent, [&]
                                     { return window(text("Create New Group") | bold | color(Color::Yellow),
                                                     vbox({text("Create a new, empty group?"),
                                                           separator(),
                                                           groupDialogueComponent->Render() | center})) |
                                              center; });

    auto moveDialogueComponent = Container::Vertical({groupSelectMenu,
                                                      Container::Horizontal({confirmMoveButton,
                                                                             cancelMoveButton})});

    auto moveDialogModal = Renderer(moveDialogueComponent, [&]
                                    { return window(text("Move Component") | bold | color(Color::Yellow),
                                                    vbox({text("Select target group:") | color(Color::GrayLight),
                                                          moveDialogueComponent->ChildAt(0)->Render() | frame | size(HEIGHT, LESS_THAN, 10),
                                                          separator(),
                                                          moveDialogueComponent->ChildAt(1)->Render() | center})) |
                                             center; });

    auto modal_component = Modal(mainRenderer, createGroupModal, &showCreateGroupDialogue);
    auto final_component = Modal(modal_component, moveDialogModal, &showMoveDialogue);

    screen.Loop(final_component);

    try
    {
        nursery.stopNurseryTick();
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error during cleanup: " << e.what() << std::endl;
    }

    std::cerr.rdbuf(oldCerrBuf);

    delete Inventory::getInstance();
    return 0;
}
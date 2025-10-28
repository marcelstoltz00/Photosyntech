#ifndef NurseryFacade_h
#define NurseryFacade_h

#include "../builder/Director.h"
#include "../singleton/Singleton.h"
#include "../mediator/Mediator.h"
#include "../command/Command.h"
#include "../iterator/Aggregate.h"
#include "../composite/PlantComponent.h"
#include <string>
#include <vector>
#include "../builder/Director.h"
#include "../builder/SunflowerBuilder.h"
#include "../builder/RoseBuilder.h"
#include "../builder/JadePlantBuilder.h"
#include "../builder/MapleBuilder.h"
#include "../builder/CactusBuilder.h"
#include "../builder/CherryBlossomBuilder.h"
#include "../builder/LavenderBuilder.h"
#include "../builder/PineBuilder.h"
#include "../composite/PlantGroup.h"
#include "../decorator/plantDecorator/PlantAttributesHeader.h"
#include "../decorator/plantDecorator/LargeStem.h"
#include "../decorator/plantDecorator/LargeLeaf.h"
#include "../decorator/plantDecorator/LargeFlowers.h"
#include "../decorator/plantDecorator/SmallStem.h"
#include "../decorator/plantDecorator/SmallLeaf.h"
#include "../decorator/plantDecorator/SmallFlowers.h"
#include "../decorator/plantDecorator/Thorns.h"
#include "../decorator/plantDecorator/Spring.h"
#include "../decorator/plantDecorator/Summer.h"
#include "../decorator/plantDecorator/Autumn.h"
#include "../decorator/plantDecorator/Winter.h"
#include "../prototype/LivingPlant.h"
#include "../prototype/Herb.h"
#include "../prototype/Shrub.h"
#include "../prototype/Succulent.h"
#include "../prototype/Tree.h"


/**
 * @brief Unified facade interface for the nursery management system.
 *
 * Provides simplified, high-level methods for common operations by
 * coordinating multiple subsystems (plant creation via Builder/Director,
 * inventory management via Singleton, sales via Mediator, operations via Command,
 * and filtering via Iterator). Hides system complexity from GUI and external clients.
 *
 * **System Role:**
 * This class serves as the single integration point for the entire Photosyntech system.
 * It is the only interface that GUI, CLI, and external systems need to know about.
 * All system operations are coordinated through this facade:
 * - Plant creation and inventory management
 * - Sales transactions and customer interactions
 * - Plant care operations and monitoring
 * - Collection filtering and browsing
 *
 * **Pattern Role:** Facade (simplifies complex subsystem interactions, hides implementation)
 *
 * **Related Patterns:**
 * - Builder/Director: Delegates plant creation requests
 * - Singleton: Accesses centralized inventory and resources
 * - Mediator: Routes customer/staff interactions through floor mediators
 * - Command: Encapsulates operations with undo/redo capability
 * - Iterator: Provides filtered plant collection access
 * - Composite: Works with plant hierarchies for bulk operations
 * - Observer: Coordinates staff monitoring setup
 * - Decorator: Manages plant customization
 * - Prototype: Handles plant cloning for inventory
 * - Flyweight: Ensures strategy resource reuse
 * - State: Manages plant lifecycle transitions
 * - Strategy: Executes plant care algorithms
 *
 * **System Interactions:**
 * - External interfaces (GUI/CLI) call methods on facade only
 * - Facade delegates to appropriate subsystem implementations
 * - Commands queued through facade for operation history
 * - All resource access goes through singleton instance
 * - Staff-customer interactions coordinated via mediators
 * - Plant filtering delegated to iterator factories
 *
 * @see Singleton (resource hub accessed by facade)
 * @see Builder (plant creation via director)
 * @see Mediator (sales and suggestion floor coordination)
 * @see Command (operation encapsulation)
 * @see Iterator (plant filtering and browsing)
 */


class NurseryFacade {
private:
    Director* director;
    Builder* sunflowerBuilder;
    Builder* roseBuilder;
    Builder* jadePlantBuilder;
    Builder* mapleBuilder;
	Builder* cactusBuilder;
	Builder* cherryBlossomBuilder;
	Builder* lavenderBuilder;
	Builder* pineBuilder;
    std::vector<PlantComponent*> plants;

public:
    NurseryFacade();
    ~NurseryFacade();

    PlantComponent* createPlant(const std::string& type);
    void waterPlant(PlantComponent* plant);
    void addSunlight(PlantComponent* plant);
    std::string getPlantInfo(PlantComponent* plant);

    std::vector<std::string> getAvailablePlantTypes();

	PlantComponent* getInventoryRoot();

    std::list<PlantComponent*> getGroupContents(PlantComponent* group);

    PlantGroup* createPlantGroup(const std::string& name);

    void addComponentToGroup(PlantComponent* parent, PlantComponent* child);

    bool startNurseryTick();

    bool stopNurseryTick();
};

#endif
